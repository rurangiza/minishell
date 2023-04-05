/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:44:23 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/05 13:40:29 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	is_ending_character(char *buffer, int end)
{
	if (ft_isspace(buffer[end])
		|| buffer[end] == '\''
		|| buffer[end] == '\"'
		|| buffer[end] == '$')
		return (TRUE);
	return (FALSE);
}

/* Custom for parsing */
int	is_built_in(char *str)
{
	if (ft_strncmp(str, "echo", 4) == 0
		|| ft_strncmp(str, "cd", 2) == 0
		|| ft_strncmp(str, "pwd", 3) == 0
		|| ft_strncmp(str, "export", 6) == 0
		|| ft_strncmp(str, "unset", 5) == 0
		|| ft_strncmp(str, "env", 3) == 0
		|| ft_strncmp(str, "exit", 4) == 0)
	{
		return (1);
	}
	return (0);
}
