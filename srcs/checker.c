/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:50:23 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/07 10:18:40 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* check whether a string {cmd} matches with the list of built-ins */
int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0
		|| ft_strncmp(cmd, "cd", 2) == 0
		|| ft_strncmp(cmd, "pwd", 3) == 0
		|| ft_strncmp(cmd, "export", 6) == 0
		|| ft_strncmp(cmd, "unset", 5) == 0
		|| ft_strncmp(cmd, "env", 3) == 0
		|| ft_strncmp(cmd, "exit", 4) == 0)
		return (TRUE);
	return (FALSE);
}

/* Check if current item in environemnt is the target */
int	is_variable_to_be_deleted(char *target, char *source)
{
	int	src_len = ft_strlen(source);
	
	if (ft_strncmp(target, source, src_len) == 0 && target[src_len] == '=')
		return (TRUE);
	return (FALSE);
}

/* Check whether a variable {token} is in the global environment */
int is_in_environment(char *variable)
{
    int index;
    int variable_length;

    variable_length = ft_strlen(variable);
    index = 0;
    while (g_environment[index])
    {
        if (ft_strncmp(g_environment[index], variable, variable_length) == 0
            && g_environment[index][variable_length] == '=')
            return (1);
        index++;
    }
    return (0);
}