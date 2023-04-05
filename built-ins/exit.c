/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:05:25 by akorompa          #+#    #+#             */
/*   Updated: 2023/04/05 11:29:34 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	only_digit(const char *arg)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(arg);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			break ;
		i++;
		if (i == j)
			return (0);
	}
	return (1);
}

long	ft_atoi_exit(const char *str)
{
	long		i;
	int			sign;
	long		result;

	sign = 1;
	i = 0;
	result = 0;
	if (only_digit(str))
		return (255);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (sign * result);
}

int	check_exit_status(char *arg)
{
	int	status;

	status = ft_atoi_exit(arg);
	if (status >= 0 && status <= 255)
		return (status);
	else
		status = (status % 255) - 1;
	return (status);
}

int	my_exit(t_token *tokens)
{
	int	j;

	printf("exit\n");
	if (!tokens->cmd[1])
		return (0);
	if (tokens->cmd[2])
	{
		printf("minishell: exit: too many arguments\n");
		g_exitcode = 1;
		return (-1);
	}
	if (tokens->cmd[1])
	{
		j = check_exit_status(tokens->cmd[1]);
		if (only_digit(tokens->cmd[1]))
		{
			printf("minishell: exit: %s: numeric argument needed\n",
				tokens->cmd[1]);
			return (255);
		}
		else
			return (j);
	}
	return (0);
}
