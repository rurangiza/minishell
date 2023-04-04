/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:16:24 by akorompa          #+#    #+#             */

/*   Updated: 2023/03/27 14:47:09 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int count_words(char *prompt)
// {
// 	int i;
// 	int count;

// 	i = 0;
// 	count = 0;
// 	if (!prompt)
// 		return (0);
// 	while(prompt[i])
// 	{
// 		while(prompt[i] != '\0' && prompt[i] == ' ')
// 			i++;
// 		if (prompt[i] != '\0')
// 		{
// 			while(prompt[i] && prompt[i] != ' ' && prompt[i] != '\"' && prompt[i] != '\'')
// 				i++;
// 			if (prompt[i] == '\"')
// 			{
// 				i++;
// 				while(prompt[i])
// 				{
// 					if (prompt[i] == '\"')
// 						break ;
// 					i++;
// 				}
// 				if (prompt[i] == '\0')
// 					return (-1);
// 			}
// 			else if (prompt[i] == '\'')
// 			{
// 				i++;
// 				while (prompt[i])
// 				{
// 					if (prompt[i] == '\'')
// 						break ;
// 					i++;
// 				}
// 				if (prompt[i] == '\0')
// 					return (-1);
// 			}
// 			count++;
// 		}
// 		while(prompt[i] != '\0' && prompt[i] != ' ')
// 			i++;
// 	}
// 	return(count);
// }

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
			if (tokens[i] && tokens[i + 1] && tokens[i][0] == '<')
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
		if (!tokens[i])
			break ;
		i++;
	}
}

t_lexer	lexerinho(char *prompt, char **envp)
{
	(void)envp;
	t_lexer	lexer;

	if (!prompt || check_quotes(prompt) == -1)
	{
		printf("syntax error in quotes\n");
		lexer.tmp = NULL;
		lexer.tokens = NULL;
		return (lexer);
	}
	lexer.tmp = ft_cmd_lexer(prompt);
	if (!lexer.tmp)
	{
		printf("syntax error\n");
		lexer.tmp = NULL;
		lexer.tokens = NULL;
		return (lexer);
	}
	expander(&lexer, envp);
	lexer.tokens = token(&lexer);
	ft_free_matrix(lexer.tmp);
	delete_quotes(lexer.tokens);
	return (lexer);
}
