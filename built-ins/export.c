/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:33:13 by akorompa          #+#    #+#             */
/*   Updated: 2023/04/19 15:54:24 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	tokens_to_export(char **cmd, t_prompt *prompt)
{
	int	i;
	int	count;

	if (!cmd[1])
		return (0);
	i = 1;
	count = 0;
	while (cmd[i])
	{
		if (!is_env_var(cmd[i], prompt))
			count++;
		i++;
	}
	return (count);
}

int	check_export(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (check_equal(cmd[i]))
		{
			printf("export : 'var_name=value'\n");
			return (1);
		}
		if (check_forbidden(cmd[i]))
		{
			printf("minishell: export: %s: not a valid identifier\n", cmd[i]);
			return (2);
		}
		i++;
	}
	return (0);
}

int	check_env_var(t_prompt *prompt, t_token *tokens)
{
	int	i;

	i = 1;
	while (tokens->cmd[i] && is_env_var(tokens->cmd[i], prompt))
	{
		prompt->envp = ft_delete_var(tokens, prompt, i);
		i++;
	}
	return (0);
}

void	export_2(char **cpy, t_token *tokens, int len, t_prompt *prompt)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (prompt->envp[i])
	{
		cpy[i] = ft_strdup(prompt->envp[i]);
		i++;
	}
	while (j < len + 1)
	{
		cpy[i++] = ft_strdup(tokens->cmd[j]);
		j++;
	}
	cpy[i] = 0;
}

int	export(t_token *tokens, t_prompt *prompt)
{
	char	**cpy;
	int		size;
	int		len;

	if (!tokens->cmd[1])
	{
		print_export(prompt);
		return (0);
	}
	if (check_export(tokens->cmd))
		return (1);
	check_env_var(prompt, tokens);
	size = ft_tablen(prompt->envp);
	len = tokens_to_export(tokens->cmd, prompt);
	cpy = malloc(sizeof(char *) * ((size + len) + 1));
	if (!cpy)
		return (0);
	export_2(cpy, tokens, len, prompt);
	ft_free_matrix(prompt->envp);
	prompt->envp = ft_dup_matrix(cpy);
	return (0);
}
