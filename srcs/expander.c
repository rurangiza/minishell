/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:55:10 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/15 11:30:09 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

char    *free_stash(char *stash)
{
    free(stash);
    return (NULL);
}

char    *ft_strjoin_mod(char *stash, char *buffer)
{
    int        i;
    int        j;
    char    *tmp;

    if (!stash)
    {
        stash = ft_strdup("");
        if (!stash)
            return (NULL);
    }
    if (!buffer)
        return (NULL);
    tmp = malloc(sizeof(char) * ((ft_strlen(stash) + ft_strlen(buffer)) + 1));
    if (!tmp)
        return (NULL);
    i = -1;
    j = 0;
    while (stash[++i])
        tmp[i] = stash[i];
    while (buffer[j])
        tmp[i++] = buffer[j++];
    tmp[ft_strlen(stash) + ft_strlen(buffer)] = '\0';
    free(stash);
    return (tmp);
}

int    ft_strchr_mod(const char *s, char ch)
{
    int        index;

    index = 0;
    if (s && ch)
    {
        while (s[index])
        {
			if (s[index] == '\'')
			{
				index++;
				while(s[index] != '\'')
					index++;
			}
            if (s[index] == ch)
                return (index);
            index++;
        }
    }
    return (-1);
}

void	expander(t_lexer *lexer, char **envp)
{
	int i;
	(void)envp;
	
	i = 0;
	while(lexer->tmp[i])
	{
		while (ft_strchr_mod(lexer->tmp[i], '$') != -1)
		{
			lexer->tmp[i] = expand_variable(lexer->tmp[i]);
		}
		i++;
	}
}