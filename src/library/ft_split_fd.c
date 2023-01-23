/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 09:43:09 by arurangi          #+#    #+#             */
/*   Updated: 2022/11/25 11:52:26 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
 * Breaks up a text file {fd}
 * into an {array} of substrings
 * based on a seperator character {ch}
 * 
 * Returns array of strings
 */

// split, strjoin, malloc, read, free

#include "libft.h"

char	*read_and_save(int fd);

char	**ft_split_fd(int fd, char seperator)
{
	char	*extracted_text;

	if (fd < 0 || fd > FOPEN_MAX || !seperator)
	{
		printf("Error: couldn't open file or no seperator");
		return (NULL);
	}
	extracted_text = read_and_save(fd);
	if (!extracted_text)
	{
		free(extracted_text);
		return (NULL);
	}
	return (ft_split(extracted_text, seperator));
}

// Reads a file and returns its content
char	*read_and_save(int fd)
{
	char		buffer[5 + 1];
	char		*tmp;
	int			bytes_read;

	tmp = malloc(sizeof(char) * 1);
	if (!tmp)
		return (NULL);
	tmp[0] = 0;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, 5);
		if (bytes_read == -1)
			return (NULL);
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(tmp, buffer);
	}
	return (tmp);
}
