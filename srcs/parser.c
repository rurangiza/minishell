/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:31:07 by akorompa          #+#    #+#             */
/*   Updated: 2023/01/30 10:36:41 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_index(t_lexer *lexer, int j)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (j == 0)
		return (0);
	while (lexer->tokens[i])
	{
		if (!ft_strncmp(lexer->tokens[i], "|", 1))
		{
			count++;
			if (count == j)
			{
				i++;
				return (i);
			}
		}
		i++;
	}
	return (count);
}

int	count_operations(t_lexer *lexer)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (lexer->tokens[i])
	{
		if (!ft_strncmp(lexer->tokens[i], "|", 1))
			count++;
		i++;
	}
	return (count);
}

int option_count(t_lexer *lexer, int i)
{
	int count;
	int j;
	
	j = 1;
	count = 1;
	while(ft_strncmp(lexer->tokens[i], "|", 1))
	{
		if (!ft_strncmp(lexer->tokens[i], "-", 1) && (lexer->tokens[i][j] > 96 && lexer->tokens[i][j] < 123))
			count++;
		i++;
	}
	return (count);
}

void	get_cmd_line_3(t_lexer *lexer, t_token *token, t_parser *pars, int i)
{
	int option;
	int n;
	int k;
	
	n = get_index(lexer, i);
	option = option_count(lexer, n);
	k = 0;
	if (get_cmd(lexer->tokens[n], pars->cmd_path))
	{
		token[i].cmd[k] = ft_strdup(lexer->tokens[n]);
		token[i].cmd_path = get_cmd(lexer->tokens[n], pars->cmd_path);
		printf("%s\n", token[i].cmd[k]);
		printf("%s\n", token[i].cmd_path);
		k++;
		n++;
	} 
	else
	{
		token[i].cmd[k] = ft_strdup(lexer->tokens[n]);
		printf("%s\n", token[i].cmd[k]);
		k++;
		n++;
	}
	while(ft_strncmp(lexer->tokens[n], "|", 1))
	{
		if (!ft_strncmp(lexer->tokens[n], "-", 1) && (lexer->tokens[n][1] > 96 && lexer->tokens[i][1] < 123))
		{
			token[i].cmd[k] = ft_strdup(lexer->tokens[n]);
			printf("%s\n", token[i].cmd[k]);
		}
		k++;
		n++;
	}
	token[i].cmd[k] = 0;
}

void	get_file(t_lexer *lexer, t_token *token, t_parser *pars, int i)
{
	int option;
	int n;
	
	n = get_index(lexer, i);
	option = option_count(lexer, n);
	if (get_cmd(lexer->tokens[n], pars->cmd_path))
		n++;
	while (ft_strncmp(lexer->tokens[n], "|", 1))
	{
		if (ft_strncmp(lexer->tokens[n], "-", 1))
		{
			token[i].infile = open(lexer->tokens[n], O_RDONLY);
			printf("%d\n", token[i].infile);
			if(token[i].infile < 0)
				printf("error infile : %s\n", lexer->tokens[n]);
			break ;
		}
		n++;
	}
}

void	get_cmd_line_2(t_lexer *lexer, t_token *token, t_parser *pars, int i)
{
	int j;
	int n;
	int k;
	int option;
	(void)pars;
	(void)token;

	j = 0;
	k = 0;
	n = get_index(lexer, i);
	option = option_count(lexer, n);
	token[i].cmd = malloc(sizeof(char *) * (option + 1));
	if (!token[i].cmd)
		return ;
	printf("------------- : %d\n", i);
	get_cmd_line_3(lexer, token, pars, i);
	get_file(lexer, token, pars, i);
}

t_token  *get_cmd_line(t_lexer *lexer, t_parser *pars)
{
	int i;
	t_token *token;
	
	token = malloc(sizeof(t_token) * (pars->op_count + 1));
	if (!token)
		return (NULL);
	i = 0;
	while (i < pars->op_count + 1)
	{
		get_cmd_line_2(lexer, token, pars, i);	
		i++;
	}
	return (token);
}

t_token  *parser(t_lexer *lexer, char **envp)
{
	t_parser pars;
	t_token *token;
	char *path;
	int i;
	
	i = 0;
	pars.op_count = count_operations(lexer);
	path = find_path(envp);
	pars.cmd_path = ft_split(path, ':');
	token = get_cmd_line(lexer, &pars);
	return (token);
}
