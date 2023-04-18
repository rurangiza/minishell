/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:51:01 by akorompa          #+#    #+#             */
/*   Updated: 2023/04/17 15:17:56 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	check_forbidden(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (str[i] != '=')
		return (1);
	return (0);
}

int	len_to_equal(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '=')
		i++;
	return (i);
}

int	is_env_var(char *str, t_prompt *prompt)
{
	int	i;

	i = 0;
	while (prompt->envp[i])
	{
		if (ft_strncmp(str, prompt->envp[i], len_to_equal(str) + 1) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	**ft_delete_var(t_token *tokens, t_prompt *prompt, int index)
{
	char	**cpy;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = arr_len(prompt->envp);
	cpy = malloc(sizeof(char *) * (len));
	while (j < len && prompt->envp[i])
	{
		if (ft_strncmp(tokens->cmd[index], prompt->envp[i],
				len_to_equal(tokens->cmd[index]) + 1) != 0)
		{
			cpy[j] = ft_strdup(prompt->envp[i]);
			j++;
		}
		i++;
	}
	cpy[j] = 0;
	ft_free_matrix(prompt->envp);
	prompt->envp = cpy;
	return (cpy);
}
