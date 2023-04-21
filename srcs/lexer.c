/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:16:24 by akorompa          #+#    #+#             */
/*   Updated: 2023/04/21 14:38:04 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_size(char *str, char c)
{
	int	i;
	int	count;

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

char	*delete_quotes_1(char *str, char c)
{
	int		i;
	int		j;
	int		len;
	char	*token;

	if (is_special_token(str, c))
	{
		token = special_token(str);
		return (token);
	}
	len = get_size(str, c);
	token = malloc(sizeof (char) * (len + 1));
	if (!token)
		return (NULL);
	i = 0;
	j = 0;
	delete_quotes_utils(str, token, c);
	free(str);
	return (token);
}

void	delete_quotes(char **tokens)
{
	int	i;
	int	j;

	i = -1;
	while (tokens[++i])
	{
		if (tokens[i] && tokens[i][0] == '<')
			i = skip_red(tokens, i);
		j = -1;
		while (tokens[i] && tokens[i][++j])
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
		}
		if (!tokens[i])
			break ;
	}
}

t_lexer	lexerinho(char *prompt, char **envp)
{
	t_lexer	lexer;

	(void)envp;
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
