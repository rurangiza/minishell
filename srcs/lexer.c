/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:16:24 by akorompa          #+#    #+#             */
/*   Updated: 2023/04/18 15:29:55 by akorompa         ###   ########.fr       */
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

int	is_special_token(char *str, char c)
{
	int	i;
	
	i = 0;
	if (ft_strlen(str) != 3)
		return (0);
	if (str[0] != c && str[2] != c && ft_isset("<|>", str[1]))
		return (0);
	return (1);
}

char	*special_token(char *str)
{
	char	*token;
	
	token = malloc(sizeof(char) * 3);
	if (!token)
		return (NULL);
	token[0] = str[1];
	token[1] = ' ';
	token[2] = 0;
	return (token);
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
	while (str[i])
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
