/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:13:49 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/23 12:14:05 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ************************************************************************** */
/*                           get_next_line(int fd)                            */
/* ************************************************************************** */
/*  Reads a file, a specific number of bytes at a time, until it reaches the  */
/*  end of the file or '\n' (new line). Then returns what was read.           */
/*                                                                            */
/*  N.B: Might jump over a '\n'.                                              */
/* ************************************************************************** */
/* BONUS: Keeps track of multiple files                                       */
/* ************************************************************************ * */

char	*get_next_line(int fd)
{
	static char	*stash[FOPEN_MAX];
	char		*line;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	stash[fd] = save_raw_line(fd, stash[fd]);
	if (!stash[fd])
		return (free_stash(stash[fd]));
	line = trim_right(stash[fd]);
	stash[fd] = trim_left(stash[fd]);
	if (!line)
	{
		free(line);
		return (free_stash(stash[fd]));
	}
	return (line);
}

/* ************************************************************************** */
/*                              save_raw_line()                               */
/* ************************************************************************** */
/*  Reads a file a specific number of bytes at a time until it reaches the    */
/*  end of the file or '\n' (new line). Then returns what was read.           */
/*  Nota Bene: Might jump over a '\n'.                                        */
/* ********************************************************************* **** */

char	*save_raw_line(int fd, char *stash)
{
	int		i;
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;

	i = 0;
	while (i < BUFFER_SIZE)
		buffer[i++] = 0;
	bytes_read = 1;
	while (bytes_read > 0 && ft_strchr_mod(buffer, '\n') == -1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = ft_strjoin_mod(stash, buffer);
	}
	return (stash);
}

/* ************************************************************************** */
/*                               trim_right()                                 */
/* ************************************************************************** */
/*  In case save_raw_line() returned more characters then needed, due to      */
/*  "BUFFER_SIZE jumps", this function removes the excess characters          */
/* ************************************************************************** */

char	*trim_right(char *raw_line)
{
	char	*clean_line;
	int		i;

	i = 0;
	if (!raw_line[i])
		return (NULL);
	while (raw_line[i] && raw_line[i] != '\n')
		i++;
	clean_line = malloc(sizeof(char) * (i + 2));
	if (!clean_line)
		return (NULL);
	i = 0;
	while (raw_line[i] && raw_line[i] != '\n')
	{
		clean_line[i] = raw_line[i];
		i++;
	}
	if (raw_line[i] == '\n')
	{
		clean_line[i] = raw_line[i];
		i++;
	}
	clean_line[i] = '\0';
	return (clean_line);
}

/* ************************************************************************** */
/*                               trim_left()                                  */
/* ************************************************************************** */
/*  This function updated the static variable "stash" with either:            */
/*    => the excess characters returned after the '\n'                        */
/*    => NULL, if there was no excess characters or an error occured          */
/* ************************************************************************** */

char	*trim_left(char *stash)
{
	char	*trimmed_stash;
	int		i;
	int		j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (i == ft_strlen(stash))
		return (free_stash(stash));
	else
	{
		trimmed_stash = malloc(sizeof(char) * (ft_strlen(stash) - i) + 1);
		if (!trimmed_stash)
			return (free_stash(stash));
		i += 1;
		j = 0;
		while (stash[i])
			trimmed_stash[j++] = stash[i++];
		trimmed_stash[j] = '\0';
	}
	free(stash);
	return (trimmed_stash);
}