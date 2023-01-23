/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:49:14 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/09 17:06:50 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
 * Breaks up a string {str}
 * into an {array} of substrings
 * based on a seperator character {ch}
 * 
 * Returns array of strings
 */

#include "libft.h"

static int	count_words(char *str, char c);
static char	**malloc_array(char *str, char ch);
static char	*copy_word(char *str, char c);
static char	**free_array(char **tab);

char	**ft_split(char const *str, char ch)
{
	char	**array;
	int		a_index;
	int		s_index;

	array = malloc_array((char *)str, ch);
	if (!array)
		return (NULL);
	s_index = 0;
	a_index = 0;
	while (str[s_index])
	{
		while (str[s_index] == ch && str[s_index])
			s_index++;
		if (str[s_index] != ch && str[s_index])
		{
			array[a_index] = copy_word((char *)str + s_index, ch);
			if (!array[a_index])
				return (free_array(array));
			a_index++;
		}
		while (str[s_index] != ch && str[s_index])
			s_index++;
	}
	array[a_index] = NULL;
	return (array);
}

static char	**malloc_array(char *str, char ch)
{
	char	**ptr;

	if (!str)
		return (NULL);
	ptr = malloc((count_words((char *)str, ch) + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	return (ptr);
}

static int	count_words(char *str, char ch)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ch && str[i] != '\0')
			i++;
		if (str[i] != ch && str[i] != '\0')
			counter++;
		while (str[i] != ch && str[i] != '\0')
			i++;
	}
	return (counter);
}

static char	*copy_word(char *str, char ch)
{
	int		index;
	int		length;
	char	*word;

	length = 0;
	while (str[length] != ch && str[length] != '\0')
		length++;
	word = malloc(sizeof(char) * (length + 1));
	if (!word)
		return (NULL);
	index = 0;
	while (index < length)
	{
		word[index] = str[index];
		index++;
	}
	word[index] = '\0';
	return (word);
}

static char	**free_array(char **array)
{
	int	index;

	index = 0;
	while (array[index])
		free(array[index++]);
	free(array);
	return (0);
}
