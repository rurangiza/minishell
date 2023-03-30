/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:33:13 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/30 11:34:15 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int envp_len(t_prompt *prompt)
{
	int i;

	i = 0;
	while (prompt->envp[i])
	{
		i++;
	}
	return (i);
}

void	sort_array(t_prompt *prompt)
{
	int i;
	int j;
	int len;
	char *tmp;

	i = 0;
	len = envp_len(prompt);
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(prompt->envp[i], prompt->envp[j], ft_strlen(prompt->envp[i])) > 0)
			{
				tmp = prompt->envp[i];
				prompt->envp[i] = prompt->envp[j];
				prompt->envp[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_export(t_prompt *prompt)
{
	int i;

	i = 0;
	sort_array(prompt);
	while (prompt->envp[i])
	{
		printf("declare -x %s\n", prompt->envp[i]);
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

void	export_2(char **cpy, int size, int len, t_prompt *prompt)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		cpy[i] = ft_strdup(prompt->envp[i]);
		i++;
	}
	j = 0;
	while (++j < len + 1 )
	{
		cpy[i] = ft_strdup(prompt->cmds->cmd[j]);
		i++;
	}
	cpy[i] = 0;
}

int	export(t_token *tokens, t_prompt *prompt)
{
	char **cpy;
	int size;
	int len;
	// int i;
	// int j;
	
	if (!tokens->cmd[1])
	{
		print_export(prompt);
		return (0);
	}
	if (check_export(tokens->cmd))
		return (printf("export : 'var_name=value'\n"));
	size = envp_len(prompt);
	len = tokens_to_export(tokens->cmd);
	cpy = malloc(sizeof(char *) * ((size + len) + 1));
	if (!cpy)
		return (0);
	export_2(cpy, size, len, prompt);
	prompt->envp = cpy;
	return (0);
}
