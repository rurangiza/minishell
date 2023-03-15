/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:31:49 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/15 13:59:52 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
	{
		envp++;
	}
	return (*envp + 5);
}
/*
 * Utile dans l'execution pour
 * - verifier que PATH est present
*/
int is_valid_cmd_bis(char *str, char *path) 
{
	char *tmp;
	char *cmd;
	char **splited;

	if (path == NULL)
		return (0);
	splited = ft_split(path, ':');
	while (splited && *splited)
	{
		tmp = ft_strjoin(*splited, "/");
		cmd = ft_strjoin(tmp, str);
		free(tmp);
		if (access(cmd, 0) == 0)
		{
			free(cmd);
			return (1);
		}
		free(cmd);
		splited++;
	}
	free(splited);
	return (0);
}

int is_valid_cmd(char *str, char **path)
{
	char *tmp;
	char *cmd;

	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		cmd = ft_strjoin(tmp, str);
		free(tmp);
		if (access(cmd, 0) == 0)
		{
			free(cmd);
			return (1);
		}
		free(cmd);
		path++;
	}
	return (0);
}

int	is_built_in(char *str)
{
	if(ft_strncmp(str, "echo", 4) == 0
		|| ft_strncmp(str, "cd", 2) == 0
		|| ft_strncmp(str, "pwd", 3) == 0
		|| ft_strncmp(str, "export", 6) == 0
		|| ft_strncmp(str, "unset", 5) == 0
		|| ft_strncmp(str, "env", 3) == 0
		|| ft_strncmp(str, "exit", 4) == 0)
	{
		return (1);
	}
	return (0);
}

static int get_pipe_nb(t_lexer *lexer)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (!ft_strncmp(lexer->tokens[i], "|", 1))
		return (-1);
	while (lexer->tokens[i])
	{
		if (!ft_strncmp(lexer->tokens[i], "|", 1))
		{
			if (!ft_strncmp(lexer->tokens[i + 1],"|", 1) && lexer->tokens[i + 1])
				return (-1);
			count++;
		}
		i++;
	}
	return (count);
}

int get_outfile_apmod(char *str)
{
	int outfile;
	
	if (!str)
		return (-2);
	outfile = open(str, O_APPEND | O_RDWR | O_CREAT, 0644);
	if (outfile < 0)
		return (-1);
	return (outfile);
}

int get_outfile(char *str)
{
	int outfile;

	outfile = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile < 0)
		return (-1);
	return (outfile);
}

int get_infile(char *str)
{
	int infile;
	
	infile = open(str, O_RDONLY);
	if (infile < 0)
		return (-1);
	return (infile);
}

char *get_cmd_path(char *str, char **path)
{
	char *tmp;
	char *cmd;

	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		cmd = ft_strjoin(tmp, str);
		free(tmp);
		if (access(cmd, 0) == 0)
			return (cmd);
		free(cmd);
		path++;
	}
	return (NULL);
}

int	get_cmd_len(char **tokens, int i)
{
	int len;
	//int j;
	
	//j = 1;
	len = 0;
	while(tokens[i] && ft_strncmp(tokens[i], "|", 1) && ft_strncmp(tokens[i], ">", 1) && ft_strncmp(tokens[i], "<", 1))
	{
		len++;
		i++;
	}
	return(len);
}

char **get_built_in(char **tokens, int i)
{
	char **cmd;
	int j;
	int len;

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

char **get_cmd(char **tokens, int i)
{
	char **cmd;
	int j;
	int len;

	j = 0;
	len = get_cmd_len(tokens, i);
	cmd = malloc(sizeof(char *) * (len + 1));
	if (!cmd)
		return (NULL);
	while (j < len)
	{
		cmd[j] = ft_strdup(tokens[i]);
		//printf("%s\n", cmd[j]);
		i++;
		j++;
	}
	cmd[j] = 0;
	return (cmd);
}

void	init_cmd(t_token *cmd)
{
	cmd->infile = -1;
	cmd->outfile = -1;
	cmd->delimiter = NULL;
	cmd->heredoc_mode = -1;
	cmd->cmd_path = NULL;
	cmd->cmd = NULL;
}

void	check_heredoc_mod(char *str, t_token *cmd)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			cmd->heredoc_mode = FALSE;
			break ;
		}
		else
			cmd->heredoc_mode = TRUE;
		i++;
	}
}

int is_sep(char *sep, char c)
{
	int i;
	
	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int get_size_delimiter(char *str)
{
	int i;
	int count;
	
	i = 0;
	count = 0;
	while (str[i])
	{
		if (is_sep("\'\"", str[i]))
			i++;
		else
		{
			count++;
			i++;
		}
	}
	return(count);
}

char *delete_quotes_2(char *str, char c)
{
	int i;
	int j;
	int len;
	char *token;
	
	len = get_size(str, c);
	token = malloc(sizeof (char) * (len + 1));
	if (!token)
		return (NULL);
	i = 0;
	j = 0;
	while(str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			token[j] = str[i];
			i++;
			j++;
		}
	}
	token[j] = 0;
	return (token);
}

char	*get_delimiter(char *str)
{
	int i;
	char *delimiter;
	
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			delimiter = delete_quotes_2(str, '\'');
			return(delimiter);
		}
		else if (str[i] == '\"')
		{
			delimiter = delete_quotes_2(str, '\"');
			return(delimiter);
		}
		i++;
	}
	return(str);
}

t_token get_cmds(char **tokens, t_prompt *prompt, int *j)
{
	int i;
	t_token cmd;
	
	i = *j;
	init_cmd(&cmd);
	while(tokens[i] && ft_strncmp(tokens[i], "|", 1))
	{
		if(tokens[i][0] == '<' || tokens[i][0] == '>')
		{
			while(tokens[i][0] == '<' || tokens[i][0] == '>')
				i++;
			i++;
		}
		if (tokens[i])
		{
			if (is_built_in(tokens[i]))
			{
				cmd.cmd_path = NULL;
				cmd.cmd = get_built_in(tokens, i);
				break ;
			}
			else //if (is_valid_cmd(tokens[i], prompt->path))
			{
				cmd.cmd_path = get_cmd_path(tokens[i], prompt->path);
				cmd.cmd = get_cmd(tokens, i);
				printf("%s\n", cmd.cmd[0]);
				printf("%s\n", cmd.cmd[1]);
				break ;
			}
		}
		i++;
	}
	i = *j;
	while (tokens[i] && ft_strncmp(tokens[i], "|", 1))
	{
		if (tokens[i] && tokens[i][0] == '<')
		{
			if (tokens[i + 1] && tokens[i + 1][0] == '<' && tokens[i + 2])
			{
				cmd.infile = -3;
				check_heredoc_mod(tokens[i + 2], &cmd);
				cmd.delimiter = get_delimiter(tokens[i + 2]);
				i++;
			}
			else
				cmd.infile = get_infile(tokens[i + 1]);
		}
		if (tokens[i] && tokens[i][0] == '>')
		{
			if (tokens[i + 1] && tokens[i + 1][0] == '>')
			{
				if (tokens[i + 2])
					cmd.outfile = get_outfile_apmod(tokens[i + 2]);
				i++;
			}
			else
				cmd.outfile = get_outfile(tokens[i + 1]);
		}
		i++;
	}
	*j = i;
	return (cmd);
}

void  parser(t_prompt *prompt, t_lexer *lexer, char **envp)
{
	(void)envp;
	char *path;
	int i;
	int j;

	i = 0;
	j = 0;
	prompt->pipe_nb = get_pipe_nb(lexer);
	if (prompt->pipe_nb == -1)
	{
		return ;
	}
	prompt->cmds = malloc(sizeof(t_token) * (prompt->pipe_nb + 1));
	if (!prompt->cmds)
		return ;
	path = find_path(envp);
	prompt->path = ft_split(path, ':');
	while (i < prompt->pipe_nb + 1)
	{
		prompt->cmds[i] = get_cmds(lexer->tokens, prompt, &j);
		j++;
		i++;
	}
	//printf("--- End of Parser!! ---\n");
	prompt->pipe_nb += 1; // CHECK THIS
	// printf("number of commands: %i\n", prompt->pipe_nb);
	//printf("%s\n", prompt->cmds[0].cmd[0]);
}