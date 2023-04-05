/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:49:57 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/05 17:02:11 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(t_token *token)
{
	size_t	index;
	int		newline_mode;
	char	*str;

	index = 1;
	newline_mode = 1;
	index = update_newlinemode(token, index, &newline_mode);
	while (token->cmd[index])
	{
		if (ft_strlen(token->cmd[index]) == 1 && token->cmd[index][0] == '~')
			write(1, getenv("HOME"), ft_strlen(getenv("HOME")));
		else if (ft_strncmp("$?", token->cmd[index], 2) == 0)
		{
			str = ft_itoa(g_exitcode);
			write(1, str, ft_strlen(str));
			free(str);
		}
		else
			write(1, token->cmd[index], ft_strlen(token->cmd[index]));
		if (index > 0 && index < ft_strlen(token->cmd[index]))
			write(1, " ", 1);
		index++;
	}
	if (newline_mode == 1)
		write(STDOUT_FILENO, "\n", 1);
}

int	update_newlinemode(t_token *token, int index, int *newline_mode)
{
	while (token->cmd[index] && is_echo_option(token->cmd[index]))
	{
		*newline_mode = 0;
		index++;
	}
	return (index);
}

int	is_echo_option(char *str)
{
	int	index;

	index = 0;
	if (str[index] != '-')
		return (0);
	index += 1;
	while (str[index])
	{
		if (str[index] != 'n')
			return (0);
		index++;
	}
	return (1);
}
