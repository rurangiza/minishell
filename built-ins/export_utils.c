/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:32:30 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/05 11:42:29 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**ft_dup_matrix(char **arr)
{
	char	**cpy;
	int		len;
	int		i;

	len = arr_len(arr);
	i = 0;
	cpy = malloc(sizeof(char *) * (len + 1));
	if (!cpy)
		return (NULL);
	while (i < len)
	{
		cpy[i] = ft_strdup(arr[i]);
		i++;
	}
	cpy[i] = 0;
	ft_free_matrix(arr);
	return (cpy);
}

static void	sort_array(t_prompt *prompt)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	len = ft_tablen(prompt->envp);
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(prompt->envp[i], prompt->envp[j],
					ft_strlen(prompt->envp[i])) > 0)
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
	int	i;

	i = 0;
	sort_array(prompt);
	while (prompt->envp[i])
	{
		printf("declare -x %s\n", prompt->envp[i]);
		i++;
	}
}
