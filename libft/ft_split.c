/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:04:06 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/06 09:27:35 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ischar(char a, char c)
{
	if (a == c)
		return (1);
	return (0);
}

static int	wordcount(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && ischar(str[i], c) == 1)
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && ischar(str[i], c) == 0)
			i++;
	}
	return (count);
}

static char	*ft_word(char *str, char c)
{
	int		i;
	int		j;
	char	*tab;

	i = 0;
	j = 0;
	while (str[j] != '\0' && ischar(str[j], c) == 0)
		j++;
	tab = malloc(sizeof(char) * (j + 1));
	if (!tab)
		return (NULL);
	while (i < j)
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

static char	**ft_free(char **arr, char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = wordcount((char *)s, c);
	while (i < j)
	{
		if (arr[i] == NULL)
		{
			i = 0;
			while (i < j)
			{
				free(arr[i]);
				i++;
			}
			free(arr);
			return (NULL);
		}
		i++;
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	arr = malloc((wordcount((char *)s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && ischar(s[i], c) == 1)
			i++;
		if (s[i] != '\0')
		{
			arr[j] = ft_word((char *)s + i, c);
			j++;
		}
		while (s[i] != '\0' && ischar(s[i], c) == 0)
			i++;
	}
	arr[j] = 0;
	return (ft_free(arr, s, c));
}
