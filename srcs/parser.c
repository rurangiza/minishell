/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:31:49 by akorompa          #+#    #+#             */
/*   Updated: 2023/04/18 10:27:46 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	return (*(envp + i) + 5);
}

char	**get_built_in(char **tokens, int i)
{
	char	**cmd;
	int		j;
	int		len;

	j = 0;
	len = get_cmd_len(tokens, i);
	cmd = malloc(sizeof(char *) * (len + 1));
	if (!cmd)
		return (NULL);
	while (j < len)
	{
		cmd[j] = ft_strdup(tokens[i]);
		i++;
		j++;
	}
	cmd[j] = 0;
	return (cmd);
}

char	**get_cmd(char **tokens, int i)
{
	char	**cmd;
	int		j;
	int		len;

	j = 0;
	len = get_cmd_len(tokens, i);
	cmd = malloc(sizeof(char *) * (len + 1));
	if (!cmd)
		return (NULL);
	while (j < len)
	{
		cmd[j] = ft_strdup(tokens[i]);
		i++;
		j++;
	}
	cmd[j] = 0;
	return (cmd);
}

///////////////////////////////////////////////////////////////////////////////

t_token	get_cmds(char **tokens, t_prompt *prompt, int *j)
{
	t_token	cmd;

	init_cmd(&cmd);
	init_cmd_data(tokens, prompt, j, &cmd);
	*j = init_redirections(tokens, &cmd, j);
	return (cmd);
}

///////////////////////////////////////////////////////////////////////////////

void	parser(t_prompt *prompt, t_lexer *lexer)
{
	char	*path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!lexer || !lexer->tokens || !lexer->tokens[0])
		return ;
	prompt->pipe_nb = get_pipe_nb(lexer);
	if (prompt->pipe_nb == -1)
		return ;
	prompt->cmds = malloc(sizeof(t_token) * (prompt->pipe_nb + 1));
	if (!prompt->cmds)
		return ;
	path = find_path(prompt->envp);
	prompt->path = ft_split(path, ':');
	while (i < prompt->pipe_nb + 1)
	{
		
		prompt->cmds[i] = get_cmds(lexer->tokens, prompt, &j);
		j++;
		i++;
	}
	ft_free_matrix(prompt->path);
	prompt->pipe_nb += 1;
}
