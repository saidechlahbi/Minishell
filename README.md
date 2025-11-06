# Minishell

A small, POSIX-like shell written for the 1337 Coding School project. This repository contains a compact, carefully implemented command-line interpreter that supports parsing, expansions, redirections, pipes, basic builtins, job execution with fork/execve, and robust memory management suitable for evaluation with tools such as Valgrind.

This README explains the goals, architecture, implementation concepts (including memory management), usage, testing tips, and known limitations — written in clear, professional, and human language to help reviewers, collaborators, or future-you understand the design decisions and how to work with the code.

---

## Table of Contents

- Project goals
- Features
- High-level architecture
- Important implementation concepts
  - Parsing and tokenization
  - Command execution
  - Builtins
  - Redirections, heredocs, and pipes
  - Signals
  - Environment management
- Memory management (design & checklist)
- Building and running
- Debugging and testing
- Coding style & project constraints
- Known limitations & future improvements
- Contributing
- License & contact

---

## Project goals

- Implement a functional miniature shell compatible with the mandatory requirements of the 42 Minishell project.
- Provide a readable, maintainable codebase with clear separation of concerns (lexer, parser, executor, builtin handlers, utils).
- Ensure correct behavior across typical shell operations: parsing commands, expansions, builtins, pipelines, and redirections.
- Avoid memory leaks and undefined behavior; keep the code testable with Valgrind and sanitizers.

---

## Features

- Read and parse command lines with:
  - word splitting and quoting (single/double quotes)
  - environment variable expansion (e.g., $HOME)
- Builtins typically required by the 42 project:
  - echo, cd, pwd, export, unset, env, exit
- External command execution using fork + execve
- Support for:
  - Input/output redirections (`>`, `>>`, `<`)
  - Here-documents (`<<`) (temporary file or pipe-based)
  - Pipelines (`|`)
- Basic signal handling for interactive mode (e.g., ctrl-C to interrupt a running command without killing the shell)
- Readline-like prompt loop (or minimal alternative depending on project constraints)

Note: The exact list of implemented builtins and behaviors follows the 42 project rubric; confirm against your grading checklist and tests.

---

## High-level architecture

- main/loop:
  - Initialize environment and signal handlers.
  - Repeatedly read lines from stdin and pass them to the lexer-parser-executor pipeline.

- lexer:
  - Tokenizes the input into words, operators, and quoted segments.
  - Produces a token list used by the parser.

- parser:
  - Converts tokens into a command structure (simple AST or command list).
  - Validates syntax and builds redirections, argument arrays, and pipeline sequences.

- executor:
  - Decides whether a command is a builtin or an external program.
  - For builtins: executes in the current process when required (e.g., `cd`, `export`).
  - For pipelines/external commands: forks children and performs execve.
  - Sets up file descriptor redirections and pipe wiring.

- utils:
  - String helpers, environment list management, error handling, cleanup helpers.

---

## Important implementation concepts

### Parsing and tokenization
- Proper handling of single quotes (literal) vs double quotes (allow expansions).
- Tokenization separates operators (`|`, `<`, `>`, `>>`, `<<`) from words.
- Expand variables only outside single quotes and evaluate ambiguous/empty expansions appropriately.

### Command execution
- Builtins that modify shell state (cd, export, unset) must run in the parent process.
- External commands and non-stateful builtins in pipelines run in child processes.
- Use execve with the current environment array (char **envp) constructed from the internal environment representation.

### Builtins
- Implement the required builtin semantics carefully (exit status, argument handling, error messages compatible with tests).
- Manage exported variables vs shell-only variables.

### Redirections, heredocs, and pipes
- Open files with correct flags and permissions for `>`, `>>` and `<`.
- For `<<` heredoc, read until the delimiter, then provide content to the command either via a temporary file or a pipe. Ensure temp files are cleaned up.
- Ensure proper dup2 and close sequence to avoid leaking fds between processes.

### Signals
- In interactive mode the shell itself should not exit on SIGINT; it should interrupt the current input or command.
- Children inherit default signals unless overridden for special behavior.
- Use careful signal handling: restore default behavior in children where appropriate.

### Environment management
- Keep an internal representation (linked list or dictionary) for environment variables so builtins can modify it easily.
- When execve is called, convert the internal representation to a contiguous `char **envp` and ensure it is freed once no longer needed.

---

## Memory management (design & checklist)

Memory correctness is critical: this project is evaluated with memory checkers. The shell uses manual memory management (malloc/free). The following describes the approach and a checklist to avoid leaks or invalid memory access.

Design principles:
- Clear ownership: for every allocation, document which module/function is responsible for freeing it.
- Centralized cleanup routines: implement functions to free token lists, command structures (AST), argument arrays, and environment lists.
- Close file descriptors as soon as their use finishes; don't rely solely on process exit to release resources.
- For temporary objects (e.g., strings created during expansion), free them after they're incorporated into their owner structure.

Memory checklist to follow before returning to prompt or exiting:
- Free token list produced by lexer on both success and error paths.
- Free parsed command trees / arrays after executor completes.
- Free duplicated strings (strdup, join results) or transfer ownership to a data structure that will free them.
- Free environment list and associated strings on shell exit.
- Close and unlink any temporary heredoc files.
- On forked children: ensure no unnecessary global memory is relied on after execve; in error paths, exit after cleaning what is necessary.

Debugging with tools:
- Valgrind: valgrind --leak-check=full --show-leak-kinds=all ./minishell
- AddressSanitizer: compile with -fsanitize=address -g for local debugging.
- Track double-frees and use-after-free by careful code review and sanitizer use.

Common pitfalls:
- Forgetting to free argv arrays (NULL-terminated arrays of char *).
- Not freeing intermediate expansion strings.
- Leaving file descriptors open across forks leading to unexpected behavior.

---

## Building and running

Typical build steps (adjust to your Makefile):

1. Build:
   - make

2. Run:
   - ./minishell

3. Test with:
   - echo hello | ./minishell
   - ./minishell tests/test_script.sh
   - Use Valgrind to detect leaks:
     - valgrind --leak-check=full --show-leak-kinds=all ./minishell

Replace commands above with the specific targets and paths from this repository (e.g., `make all`, `make clean`).

---

## Debugging and testing

- Start with simple commands: `ls`, `echo`, `pwd`.
- Try redirections: `echo hi > out.txt`, `cat < out.txt`.
- Test pipes: `echo foo | wc -c`.
- Test complex lines with quotes and expansions: `echo "Hello $USER"`, `echo 'no $expand'`.
- Test builtins that affect shell state: `cd ..`, `export TEST=1`, and then `env | grep TEST`.
- Run automated or manual tests and verify exit statuses.
- Use Valgrind and AddressSanitizer during development; iterate until reports are clean.

---

## Coding style & project constraints

- Follow the 42 project norms and code style (function length / line length, allowed functions).
- Keep modules small, with single responsibility.
- Add comments where complex behavior or memory ownership is not obvious.
- Maintain consistent error messages that help automated tests verify behavior.

---

## Known limitations & future improvements

- Edge cases around complex quoting and expansion may need refinement.
- Performance is not a primary concern here — correctness and memory safety are.
- Future improvements:
  - More complete readline features (history, line editing).
  - Job control (background jobs, job suspension).
  - More robust parsing into a richer AST for advanced features.

---

## Contributing

This repository is primarily an academic project for the 42 curriculum. If you'd like to propose improvements:
- Open an issue describing the feature or bug with reproduction steps.
- Send a pull request with a focused change and tests where appropriate.
- Keep changes small and well-documented.

---

## License & contact

This project follows typical 1337 student project licensing or personal license. Please contact the repo owner for specific licensing questions.

Author: @saidechlahbi

---

Thank you for reading — this README aims to clearly explain what the project is, how it's organized, and what to watch for when working on or reviewing the shell. If you'd like, I can tailor the README to include exact build commands, implemented function lists, or examples drawn directly from the repository source files.
