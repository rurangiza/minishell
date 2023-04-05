/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:26:19 by akorompa          #+#    #+#             */
/*   Updated: 2023/04/05 11:26:15 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	found_set(char *str, int i, int *j, int *k)
{
	if (str[i + 1])
		(*j)++;
	else if (str[i + 1] == '\0')
	{
		(*k)++;
		*j = 0;
	}
}

// void	token_utils(char *str, int i, int *j, int *k)
// {
// 	(*j)++;
// 	i++;
// 	while (str[i] && str[i] != '\'')
	
// }


// char	*get_tokens(char *str, int *j, int *k)
// {
// 	char	*line;
// 	int		i;
// 	int		len;

// 	len = len_tokens(str);
// 	line = malloc(sizeof(char) * (len + 1));
// 	if (!line)
// 		return (NULL);
// 	i = 0;
// }
