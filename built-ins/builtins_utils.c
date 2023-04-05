/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:00:49 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/05 13:49:58 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

///////////////////////////////////////////////////////////////////////////////

char	*getenv_custm(char *variable, t_prompt *prompt)
{
	int	index;
	int	var_length;

	var_length = ft_strlen(variable);
	index = 0;
	while (prompt->envp[index])
	{
		if (ft_strncmp(prompt->envp[index], variable, var_length) == 0)
			return (ft_substr(prompt->envp[index],
					var_length,
					ft_strlen(prompt->envp[index])));
		index++;
	}
	index = 0;
	return (NULL);
}

///////////////////////////////////////////////////////////////////////////////

char	*get_variable_in_environment(char *variable, t_prompt *prompt)
{
	int	index;
	int	var_length;

	var_length = ft_strlen(variable);
	index = 0;
	while (prompt->envp[index])
	{
		if (ft_strncmp(prompt->envp[index], variable, var_length) == 0)
			return (ft_substr(prompt->envp[index],
					var_length,
					ft_strlen(prompt->envp[index])));
		index++;
	}
	write(1, "bash: cd: ", 10);
	index = 0;
	while (variable[index] && variable[index] != '=')
		write(1, &variable[index++], 1);
	write(1, " not set\n", 9);
	return (NULL);
}

///////////////////////////////////////////////////////////////////////////////

char	*save_cwd(void)
{
	char	*cwd;
	char	*oldpwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	free(cwd);
	return (oldpwd);
}
