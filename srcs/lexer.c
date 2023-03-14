/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:16:24 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/10 11:28:08 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



static int count_words(char *prompt)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (!prompt)
		return (0);
	while(prompt[i])
	{
		while(prompt[i] != '\0' && prompt[i] == ' ')
			i++;
		if (prompt[i] != '\0')
		{
			while(prompt[i] && prompt[i] != ' ' && prompt[i] != '\"' && prompt[i] != '\'')
				i++;
			if (prompt[i] == '\"')
			{
				i++;
				while(prompt[i])
				{
					if (prompt[i] == '\"')
						break ;
					i++;
				}
				if (prompt[i] == '\0')
					return (-1);
			}
			else if (prompt[i] == '\'')
			{
				i++;
				while (prompt[i])
				{
					if (prompt[i] == '\'')
						break ;
					i++;
				}
				if (prompt[i] == '\0')
					return (-1);
			}
			count++;
		}
		while(prompt[i] != '\0' && prompt[i] != ' ')
			i++;
	}
	return(count);
}

static int check_quotes(char *prompt)
{
	int i;
	int count;
	int count2;

	i = 0;
	count = 0;
	count2 = 0;
	if (prompt)
	{
		while (prompt[i])
		{
			if (prompt[i] == '\'')
				count++;
			else if(prompt[i] == '\"')
				count2++;
			i++;
		}
	}
	if (((count2 % 2) != 0) || ((count % 2) != 0))
		return (-1);
	else
		return (0);
	return (0);
}

static int ft_word_len(char *prompt)
{
	int i;

	i = 0;
	while (prompt[i] && prompt[i] != ' ')
	{
		if (prompt[i] == '\"')
		{
			i++;
			while (prompt[i] != '\"' && prompt[i])
				i++;
		}
		else if (prompt[i] == '\'')
		{
			i++;
			while (prompt[i] != '\'' && prompt[i])
				i++;
		}
		i++;
	}
	return (i);
}

char *ft_get_words(char *prompt)
{
	int i;
	int j;
	char *str;
	
	i = 0;
	j = ft_word_len(prompt);
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	while (i < j)
	{
		str[i] = prompt[i];
		i++;
	}
	str[i] = 0;
	return(str);
}

char **ft_cmd_lexer(char *prompt)
{
	char **arr;
	int i;
	int j;

	i = 0;
	j = 0;
	if (!prompt)
		return (NULL);
	if(count_words(prompt) == -1)
	{
		printf("syntax error\n");
		return(NULL);
	}
	arr = malloc(sizeof(char *) * (count_words(prompt) + 1));
	if (!arr)
		return (NULL);
	while(prompt[i])
	{
		while (prompt[i] && prompt[i] == ' ')
			i++;
		if (prompt[i] != '\0')
		{
			arr[j] = ft_get_words(prompt + i);
			while(prompt[i] && prompt[i] != ' ' && prompt[i] != '\"' && prompt[i] != '\'')
				i++;
			if (prompt[i] == '\"')
			{
				i++;
				while (prompt[i] != '\"' && prompt[i])
					i++;
			}
			else if (prompt[i] == '\'')
			{
				i++;
				while(prompt[i] != '\'' && prompt[i])
					i++;
			}
			j++;
		}
		while (prompt[i] && prompt[i] != ' ')
			i++;
	}
	arr[j] = 0;
	return (arr);
}

int	get_size(char *str, char c)
{
	int i;
	int count;
	
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{	
			count++;
			i++;
		}
	}
	return (count);
}

char *delete_quotes_1(char *str, char c)
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
	free(str);
	return (token);
}

void	delete_quotes(char **tokens)
{
	int i;
	int j;

	i = 0;
	while(tokens[i])
	{
		if (tokens[i] && tokens[i][0] == '<')
		{
			i++;
			if (tokens[i] && tokens[i][0] == '<' && tokens[i + 1])
				i += 2;
		}
		j = 0;
		while (tokens[i] && tokens[i][j])
		{
			if (tokens[i][j] == '\'')
			{
				tokens[i] = delete_quotes_1(tokens[i], '\'');
				break ;	
			}
			else if (tokens[i][j] == '\"')
			{
				tokens[i] = delete_quotes_1(tokens[i], '\"');
				break ;
			}
			j++;
		}
		i++;
	}
}


t_lexer	lexerinho(char *prompt, char **envp)
{
	(void)envp;
	t_lexer lexer;
	
	if (check_quotes(prompt) == -1)
	{
		printf("syntax error\n");
		lexer.tmp = NULL;
		lexer.tokens = NULL;
		return (lexer);
	}
	lexer.tmp = ft_cmd_lexer(prompt);
	if (!lexer.tmp)
	{
		lexer.tmp = NULL;
		lexer.tokens = NULL;
		return (lexer);
	}
	expander(&lexer, envp);
	lexer.tokens = token(&lexer);
	delete_quotes(lexer.tokens);
	return (lexer);
}
