/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:03:51 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/30 20:45:41 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int check_the_readability(char *input)
{
    int single_quote;
    int double_quote;

    single_quote = 0;
    double_quote = 0;
    if (*input == '\'')
        single_quote++;
    if (*input == '"')
        double_quote++;
    input++;
    while (*input)
    {
        while (*input && *input != '\'' && *input != '"')
            input++;
        if (!(*input))
            break;
        if (*input == '\'' && single_quote == 1)
            single_quote--;
        else if (*input == '"' && double_quote == 1)
            double_quote--;
        else if (*input == '\'' && double_quote == 0)
            single_quote++;
        else if (*input == '"' && single_quote == 0)
            double_quote++;
        input++;
    }
    if (single_quote == 0 && double_quote == 0)
        return 0;
    return 1;
}

t_opirators *check_opirateur(char *input)
{
    t_opirators *opirators;
    
    opirators = ft_calloc(1, sizeof(t_opirators));
    if (!opirators)
        exit(1);
    while (*input)
    {
        if (*input == '|') 
            opirators->pipe++;
        else if (*input == '<' && *(input + 1) == '<')
        {
            opirators->here_doc++;
            input++;
        }
        else if (*input == '>' && *(input + 1) == '>')
        {
            opirators->append_output++;
            input++;
        }
        else if (*input == '<')
            opirators->redirect_input++;
        else if (*input == '>')
            opirators->redirect_output++;
        input++;
    }
    return (opirators);
}

// t_list *spliting(char *input)
// {
//     t_list *head;

//     str = "|<>";
//     if (ft_strchr(inline, '|' || ft_strchr(input, '<') || ft_strchr(input, '<')))
        
//     while (*input)
//     {
//     }
// }



int main(void)
{
    t_opirators *opirator;
    while (1)
    {
        char *input = readline("minishell$ ");
        if (!input)
            exit(1);
        if (!ft_strncmp(input, "exit",4))
            exit(0);
        add_history(input);
        printf("%s %d\n",input, check_the_readability(input));
        opirator = check_opirateur(input);
        printf("%d %d %d %d %d\n",
        opirator->redirect_input, opirator->redirect_output,
    opirator->pipe, opirator->append_output, opirator->here_doc);
        memset(opirator, 0, sizeof(t_opirators));
        
        
        if (!ft_strncmp(input, "history -c",10))
            rl_clear_history();
    }
    // printf("%s\n",getenv("PATH"));
}