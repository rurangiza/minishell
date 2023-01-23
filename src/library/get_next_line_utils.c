/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:14:37 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/23 12:14:50 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ************************************************************************** */
/*                              ft_strlen()                                   */
/* ************************************************************************** */
/*  Calculates the length of a string                                         */
/* ******************************************************************** ***** */

int	ft_strlen(const	char *str)
{
	int	len;

	len = 0;
	if (str)
	{
		while (str[len])
			len++;
	}
	return (len);
}

/* ************************************************************************** */
/*                              ft_strjoin_mod()                              */
/* ************************************************************************** */
/*  Concatenates two strings                                                  */
/*                                                                            */
/*  Why mod?                                                                  */
/*  - allocates memory to first argument if non-existing (stash)              */
/*  - allocates memory to tmp variable (tmp)                                  */
/* 	- frees the first argument (stash)                                        */
/* ************************************************************************** */

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

/* ************************************************************************** */
/*                               ft_strdup()                                  */
/* ************************************************************************** */
/*  Duplicates a string (str)                                                 */
/* ************************************************************************** */

char	*ft_strdup(const char *str)
{
	char	*deep_copy;
	int		s_len;
	int		s_index;

	s_len = ft_strlen(str);
	deep_copy = (char *) malloc(sizeof(char) * (s_len + 1));
	if (!deep_copy)
		return (NULL);
	s_index = 0;
	while (str[s_index])
	{
		deep_copy[s_index] = str[s_index];
		s_index++;
	}
	deep_copy[s_index] = '\0';
	return (deep_copy);
}

/* ************************************************************************** */
/*                             ft_strchr_mod()                                */
/* ************************************************************************** */
/*  Locates first occurence of character {ch} in string {s}                   */
/*                                                                            */
/*  Why mod                                                                   */
/* 	- If found, the index of the character is returned.     vs a string       */
/*  - Else, -1 is returned. Since index 0 is a valid value. vs NULL           */
/*  - '\0' is not a valid character to look for                               */
/* ************************************************************************** */

int	ft_strchr_mod(const char *s, char ch)
{
	int		index;

	if (s && ch)
	{
		index = 0;
		while (s[index])
		{
			if (s[index] == ch)
				return (index);
			index++;
		}
	}
	return (-1);
}

/* ************************************************************************** */
/*                               free_stash()                                 */
/* ************************************************************************** */
/*  This function frees (stash) and returns NULL.                             */
/*  N.B: Mostly used to save lines                                            */
/* ************************************************************************** */

char	*free_stash(char *stash)
{
	free(stash);
	return (NULL);
}