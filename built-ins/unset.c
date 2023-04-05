/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:33:00 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/05 11:43:40 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset(t_token *token, t_prompt *prompt)
{
	int		index;

	index = 1;
	while (token->cmd[index] && is_in_environment(token->cmd[index], prompt))
	{
		if (!is_valid_identifier(token->cmd[index]))
		{
			printf("bash: unset: `%s': not a valid identifier\n",
				token->cmd[index]);
			return ;
		}
		prompt->envp = ft_remove_variable(token, prompt, index);
		index++;
	}
}

/* Check whether a variable {token} is in the global environment */
int	is_in_environment(char *variable, t_prompt *prompt)
{
	int	index;
	int	variable_length;

	variable_length = ft_strlen(variable);
	index = 0;
	while (prompt->envp[index])
	{
		if (ft_strncmp(prompt->envp[index], variable, variable_length) == 0
			&& prompt->envp[index][variable_length] == '=')
			return (1);
		index++;
	}
	return (0);
}

int	is_valid_identifier(char *str)
{
	int	index;

	index = 0;
	if (str)
	{
		while (str[index])
		{
			if (index == 0 && !ft_isalpha(str[index]))
				return (0);
			if (!ft_isalnum(str[index]) && str[index] != '_')
				return (0);
			index++;
		}
	}
	return (1);
}

char	**ft_remove_variable(t_token *token, t_prompt *prompt, int index)
{
	int		src_index;
	int		copy_index;
	int		size;
	char	**copy;

	size = ft_tablen(prompt->envp);
	copy = malloc(sizeof(char *) * (size + 1));
	src_index = 0;
	copy_index = 0;
	while (src_index < size && prompt->envp[src_index])
	{
		if (!is_variable_to_be_deleted(prompt->envp[src_index],
				token->cmd[index]))
		{
			copy[copy_index] = ft_strdup(prompt->envp[src_index]);
			copy_index++;
		}
		src_index++;
	}
	copy[copy_index] = NULL;
	ft_free_matrix(prompt->envp);
	prompt->envp = copy;
	return (copy);
}

/* Check if current item in environemnt is the target */
int	is_variable_to_be_deleted(char *target, char *source)
{
	int	src_len;

	src_len = ft_strlen(source);
	if (ft_strncmp(target, source, src_len) == 0 && target[src_len] == '=')
		return (TRUE);
	return (FALSE);
}
