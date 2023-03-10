/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:49:57 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/14 13:28:16 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_echo_option(char *str)
{
	int index = 0;

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

void	echo(t_token *token)
{
	size_t index = 1;
	int newline_mode = 1;

	while (token->cmd[index] && is_echo_option(token->cmd[index]))
	{
		newline_mode = 0;
		index++;
	}
	while (token->cmd[index])
	{
		if (ft_strncmp("$?", token->cmd[index], 2) == 0)
			printf("%i bra", g_tools.exit_code);
		else
			write(STDOUT_FILENO, token->cmd[index], ft_strlen(token->cmd[index]));
		if (index > 0 && index < ft_strlen(token->cmd[index]) - 1)
			write(STDOUT_FILENO, " ", 1);
		index++;
	}
	if (newline_mode == 1)
		write(STDOUT_FILENO, "\n", 1);
}
