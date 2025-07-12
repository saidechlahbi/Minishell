/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:10 by schahir           #+#    #+#             */
/*   Updated: 2025/07/12 13:32:11 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int    ft_pwd(void)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    ft_putstr_fd(1, pwd);
    ft_putstr_fd(1, "\n");
    free(pwd);
}