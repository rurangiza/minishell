/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:41:31 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/23 16:34:25 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*init_cmd(char **envp, char *args, t_cmd *cmd)
{
	char	**paths_list;
	int		index;

	cmd->args = ft_split(args, ' ');
	index = 0;
	while (envp[index] != NULL)
	{
		if (ft_strnstr(envp[index], "PATH", 4))
		{
			paths_list = ft_split_sep(envp[index] + 4, ':', '/');
			if (paths_list == NULL)
				return (NULL);
			cmd->path = validated_path(paths_list, args);
		}
		index++;
	}
	return (NULL);
}

char	*validated_path(char **paths_list, char *args)
{
	char	*cmd_path;
	char	*cmd;
	int		index;

	cmd = cut_first_word(args);
	index = 0;
	while (paths_list[index] != NULL)
	{
		cmd_path = ft_strjoin(paths_list[index], cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			ft_free_matrix(paths_list);
			free(cmd);
			return (cmd_path);
		}
		free(cmd_path);
		index++;
	}
	ft_free_matrix(paths_list);
	free(cmd);
	return (NULL);
}

char	*cut_first_word(char *str)
{
	int		length;
	int		index;
	char	*cut;

	length = 0;
	while (str[length] != ' ' && str[length])
		length++;
	cut = malloc(sizeof(char) * length + 1);
	index = 0;
	while (index < length)
	{
		cut[index] = str[index];
		index++;
	}
	cut[length] = '\0';
	return (cut);
}

int	count_words(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' && str[i] != '\0')
			i++;
		if (str[i] != ' ' && str[i] != '\0')
			counter++;
		while (str[i] != ' ' && str[i] != '\0')
			i++;
	}
	return (counter);
}
