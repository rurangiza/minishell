/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:41:54 by akorompa          #+#    #+#             */
/*   Updated: 2022/10/20 16:50:02 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tab;
	int		end;
	int		start;

	start = 0;
	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	while (isset((char *)set, s1[start]) == 1)
		start++;
	if (start == (int)ft_strlen(s1))
	{
		tab = ft_strdup("");
		if (!tab)
			return (NULL);
		return (tab);
	}
	end = ft_strlen(s1) - 1;
	while (isset((char *)set, s1[end]) == 1)
		end--;
	tab = ft_substr(s1, start, (end - start + 1));
	if (!tab)
		return (NULL);
	return (tab);
}
