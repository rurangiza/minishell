/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:33:13 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/07 13:03:26 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int envp_len(void)
{
	int i;

	i = 0;
	while (g_environment[i])
	{
		i++;
	}
	return (i);
}

void	sort_array(void)
{
	int i;
	int j;
	int len;
	char *tmp;

	i = 0;
	len = envp_len();
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(g_environment[i], g_environment[j], ft_strlen(g_environment[i])) > 0)
			{
				tmp = g_environment[i];
				g_environment[i] = g_environment[j];
				g_environment[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_export(void)
{
	int i;

	i = 0;
	sort_array();
	while (g_environment[i])
	{
		printf("declare -x %s\n", g_environment[i]);
		i++;
	}
}

int tokens_to_export(char **cmd)
{
	int i;
	int count;

	if (!cmd[1])
		return (0);
	i = 1;
	count = 0;
	while (cmd[i])
	{
		count++;
		i++;
	}
	return (count);
}

int	check_export(char **cmd)
{
	int i;
	int j;
	int n;

	i = 1;
	n = 0;
	if (!cmd[1])
		return (0);
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '=')
				n = 1;
			j++;
		}
		if (n != 1)
			return (1);
		i++;
	}
	return (0);
}

void	export_2(char **cpy, int size, int len, t_token *tokens)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		cpy[i] = ft_strdup(g_environment[i]);
		i++;
	}
	j = 0;
	while (++j < len + 1 )
	{
		cpy[i] = ft_strdup(tokens->cmd[j]);
		i++;
	}
	cpy[i] = 0;
}

int	export(t_token *tokens)
{
	char **cpy;
	int size;
	int len;
	// int i;
	// int j;
	
	if (!tokens->cmd[1])
	{
		print_export();
		return (0);
	}
	if (check_export(tokens->cmd))
		return (printf("export : 'var_name=value'\n"));
	size = envp_len();
	len = tokens_to_export(tokens->cmd);
	cpy = malloc(sizeof(char *) * ((size + len) + 1));
	if (!cpy)
		return (0);
	export_2(cpy, size, len, tokens);
	g_environment = cpy;
	return (0);
}
