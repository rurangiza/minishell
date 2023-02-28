/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:31:07 by akorompa          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/28 13:36:07 by arurangi         ###   ########.fr       */
=======
/*   Updated: 2023/02/28 15:06:20 by akorompa         ###   ########.fr       */
>>>>>>> 2931aaba83088582cb8562d8c189a0bbd9ab9c2f
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
	outfile = open(str, O_APPEND);
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
	int j;
	
	j = 1;
	len = 0;
	while(tokens[i] && ft_strncmp(tokens[i], "|", 1))
	{
		len++;
		i++;
	}
	return(len);
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
		i++;
		j++;
	}
	cmd[j] = 0;
	return (cmd);
}

void	init_cmd(t_token *cmd)
{
	cmd->infile = -2;
	cmd->outfile = -2;
	cmd->delimiter = NULL;
	cmd->here_doc = -1;
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
			cmd->here_doc = 0;
			break ;
		}
		else
			cmd->here_doc = 1;
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

char	*get_delimiter(char *str)
{
	int i;
	int j;
	int len;
	char *delimiter;

	len = get_size_delimiter(str);
	delimiter = malloc(sizeof(char) * (len + 1));
	if (!delimiter)
		return (NULL);
	i = 0;
	j = 0;
	while(str[i])
	{
		if (is_sep("\'\"", str[i]))
			i++;
		else
		{
			delimiter[j] = str[i];
			i++;
			j++;
		}
	}
	delimiter[j] = 0;
	free(str);
	return(delimiter);
}

t_token get_cmds(char **tokens, t_prompt *prompt, int *j)
{
	int i;
	t_token cmd;
	
	i = *j;
	printf("i = %d\n", i);
	init_cmd(&cmd);
	while(tokens[i] && ft_strncmp(tokens[i], "|", 1))
	{
		if (tokens[i] && is_valid_cmd(tokens[i], prompt->path))
		{
			cmd.cmd_path = get_cmd_path(tokens[i], prompt->path);
			cmd.cmd = get_cmd(tokens, i);
			break ;
		}
		if (tokens[i][0] == '<' || tokens[i][0] == '>')
			i++;
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
		printf("UNEXPECTED TOKEN : '|'\n");
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
<<<<<<< HEAD
	// for(int k = 0; k < prompt->pipe_nb + 1; k++)
	// {
	// 	printf(CBLUE"$$$$$$$$$$$$$$\n"CRESET);
	// 	if (prompt->cmds[k].cmd[0] == NULL)
	// 		printf("cmds = null\n");
	// 	for(int l = 0; prompt->cmds[k].cmd[l]; l++)
	// 	{
	// 		printf("cmds = %s\n", prompt->cmds[k].cmd[l]);
	// 	}
	// 	printf("--------\n");
	// 	printf("cmd_path = %s\n", prompt->cmds[k].cmd_path);
	// 	// printf("%s\n", prompt->cmds[k].delimiter);
	// 	printf("--------\n");
	// 	printf("infile :%d outfile :%d\n", prompt->cmds[k].infile, prompt->cmds[k].outfile);
	// }
=======
	for(int k = 0; k < prompt->pipe_nb + 1; k++)
	{
		printf(CBLUE"$$$$$$$$$$$$$$\n"CRESET);
		// if (prompt->cmds[k].cmd[0] == NULL)
		// 	printf("cmds = null\n");
		// for(int l = 0; prompt->cmds[k].cmd[l]; l++)
		// {
		// 	printf("cmds = %s\n", prompt->cmds[k].cmd[l]);
		// }
		printf("heredoc = %d\n", prompt->cmds[k].here_doc);
		printf("--------\n");
		printf("cmd_path = %s\n", prompt->cmds[k].cmd_path);
		printf("delimiter = %s\n", prompt->cmds[k].delimiter);
		printf("--------\n");
		printf("infile :%d outfile :%d\n", prompt->cmds[k].infile, prompt->cmds[k].outfile);
	}
>>>>>>> 2931aaba83088582cb8562d8c189a0bbd9ab9c2f
}
