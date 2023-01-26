/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:31:07 by akorompa          #+#    #+#             */
/*   Updated: 2023/01/26 17:07:24 by akorompa         ###   ########.fr       */
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
	
	count = 0;
	while(ft_strncmp(lexer->tokens[i], "|", 1))
	{
		count++;
		i++;
	}
	return (count);
}

int get_infile(lexer)
{
	if 
	else 
	tok
}

void	get_cmd_line_2(t_lexer *lexer, t_token *token, t_parser *pars, int i)
{
	int j;
	int n;
	int k;
	int option;
	(void)pars;

	j = 0;
	k = 0;
	n = get_index(lexer, i);
	option = option_count(lexer, n);
	token[i].cmd = malloc(sizeof(char *) * (1000000));
	if (!token[i].cmd)
		return ;
	while(ft_strncmp(lexer->tokens[n], "|", 1))
	{
		token[i].cmd[k] = ft_strdup(lexer->tokens[n]);
		k++;
		n++;
	}
}

void get_cmd_line(t_lexer *lexer, t_token *token, t_parser *pars)
{
	int i;
	
	token = malloc(sizeof(t_token) * (pars->op_count + 1));
	if (!token)
		return ;
	i = 0;
	while (i < pars->op_count + 1)
	{
		get_cmd_line_2(lexer, token, pars, i);	
		i++;
	}
}

void	parser(t_lexer *lexer, t_token *token, char **envp)
{
	t_parser pars;
	char *path;
	
	pars.op_count = count_operations(lexer);
	path = find_path(envp);
	pars.cmd_path = ft_split(path, ':');
	get_cmd_line(lexer, token, &pars);
}
