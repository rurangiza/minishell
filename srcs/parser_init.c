/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:37:08 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/05 13:57:01 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_cmd(t_token *cmd)
{
	cmd->infile = -1;
	cmd->outfile = -1;
	cmd->delimiter = NULL;
	cmd->heredoc_mode = -1;
	cmd->cmd_path = NULL;
	cmd->cmd = NULL;
}

///////////////////////////////////////////////////////////////////////////////

void	set_cmd_data(char **tokens, t_prompt *prompt, t_token *cmd, int i)
{
	if (is_built_in(tokens[i]))
	{
		cmd->cmd_path = NULL;
		cmd->cmd = get_built_in(tokens, i);
	}
	else
	{
		cmd->cmd_path = get_cmd_path(tokens[i], prompt->path);
		cmd->cmd = get_cmd(tokens, i);
	}
}

void	init_cmd_data(char **tokens, t_prompt *prompt, int *j, t_token *cmd)
{
	int	i;

	i = *j;
	while (tokens[i] && ft_strncmp(tokens[i], "|", 1))
	{
		if (tokens[i] && (tokens[i][0] == '<' || tokens[i][0] == '>'))
		{
			i++;
			if (tokens[i] && (tokens[i][0] == tokens[i - 1][0]))
				i += 2;
			else if (tokens[i])
				i++;
		}
		if (tokens[i] && tokens[i][0] != '<' && tokens[i][0] != '>')
		{
			set_cmd_data(tokens, prompt, cmd, i);
			break ;
		}
		else if (!tokens[i])
			break ;
	}
}

///////////////////////////////////////////////////////////////////////////////

void	set_redirections(char **tokens, t_token *cmd, int *i)
{
	if (tokens[*i + 1] && tokens[*i + 1][0] == '>')
	{
		if (tokens[*i + 2])
			cmd->outfile = get_outfile_apmod(tokens[*i + 2]);
		*i += 1;
	}
	else
		cmd->outfile = get_outfile(tokens[*i + 1]);
}

int	init_redirections(char **tokens, t_token *cmd, int *j)
{
	int	i;

	i = *j;
	while (tokens[i] && ft_strncmp(tokens[i], "|", 1))
	{
		if (tokens[i] && tokens[i][0] == '<')
		{
			if (tokens[i + 1] && tokens[i + 1][0] == '<' && tokens[i + 2])
			{
				cmd->infile = -3;
				check_heredoc_mod(tokens[i + 2], cmd);
				cmd->delimiter = get_delimiter(tokens[i + 2]);
				i++;
			}
			else
				cmd->infile = get_infile(tokens[i + 1]);
		}
		if (tokens[i] && tokens[i][0] == '>')
			set_redirections(tokens, cmd, &i);
		i++;
	}
	return (i);
}
