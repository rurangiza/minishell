/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:13:25 by arurangi          #+#    #+#             */
/*   Updated: 2023/02/28 18:13:33 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
 * ft_strjoin_mod()
 * 
 *  Concatenates two strings
 *
 *  Why mod? 
 *  - allocates memory to first argument if non-existing (stash)
 *  - allocates memory to tmp variable (tmp)
 * 	- frees the first argument (stash) 
*/

#include "libft.h"

char	*free_stash(char *stash);

char	*ft_strjoin_mod(char *stash, char *buffer)
{
	int		i;
	int		j;
	char	*tmp;

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

/*
 *  ft_strchr_mod()
 * 
 *  Locates first occurence of character {ch} in string {s}
 *  
 *  Why mod 
 * 	- If found, the index of the character is returned.     vs a string
 *  - Else, -1 is returned. Since index 0 is a valid value. vs NULL
 *  - '\0' is not a valid character to look for
*/

int	ft_strchr_mod(const char *s, char ch)
{
	int		index;

	index = 0;
	if (s && ch)
	{
		while (s[index])
		{
			if (s[index] == ch)
				return (index);
			index++;
		}
	}
	return (-1);
}

/*
 *  free_stash() 
 *
 *  This function frees (stash) and returns NULL.
 *  N.B: Mostly used to save lines 
*/

char	*free_stash(char *stash)
{
	free(stash);
	return (NULL);
}