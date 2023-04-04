/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 08:52:49 by Arsene            #+#    #+#             */
/*   Updated: 2023/04/04 12:04:09 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

char	*ft_strjoin_trio(char *s1, char *s2, char *s3)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	if (!s1)
	{
		s1 = ft_strdup("");
		if (!s1)
			return (NULL);
	}
	if (!s2)
	{
		s2 = ft_strdup("");
		if (!s2)
			return (NULL);
	}
	tmp = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + ft_strlen(s3) + 1));
	if (!tmp)
		return (NULL);
	i = -1;
	j = 0;
	k = 0;
	while (s1[++i])
		tmp[i] = s1[i];
	while (s2[j])
		tmp[i++] = s2[j++];
	while (s3[k])
		tmp[i++] = s3[k++];
	tmp[ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3)] = '\0';
	free(s1);
	return (tmp);
}

char *expand_variable(char *buffer, char **envp)
{
	int		start;
	int		end;
	char	*tmp;
	char	*variable;
	char	*expanded;

	start = ft_strchr_mod(buffer, '$') + 1;
	if (!buffer[start] || (buffer[start] == '\"') || buffer[start] == '?')
	{
		expanded = ft_itoa(g_exitcode);
		end = start + 1;
		char *sub = ft_substr(buffer, 0, start - 1);
		char	*sub2 = ft_strdup(buffer + end);
		tmp = ft_strjoin_trio(sub, expanded, sub2);
		free(sub2);
		free(expanded);
		free(buffer);
		return (tmp);
	}
	end = start;
	while (buffer[end] && !ft_isspace(buffer[end]) && buffer[end] != '\'' && buffer[end] != '\"' && buffer[end] != '$')
		end++;
	variable = ft_substr(buffer, start, end - start);
	expanded = get_envp_variable(variable, envp);
	if (expanded)
		tmp = ft_strjoin_trio(ft_substr(buffer, 0, start - 1), expanded, buffer + end);
	else
		tmp = ft_strjoin_mod(ft_substr(buffer, 0, start - 1), buffer + end);
	free(expanded);
	free(variable);
	free(buffer);
	return (tmp);
}

char	*ft_strjoin_freeboth(char *s1, char *s2)
{
	char	*tab;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = ft_strdup("");
		if (!s1)
			return (NULL);
	}
	if (!s2)
	{
		s2 = ft_strdup("");
		if (!s2)
			return (NULL);
	}
	tab = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!tab)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		tab[i] = s1[i];
	while (s2[j] != '\0')
		tab[i++] = s2[j++];
	tab[i] = '\0';
	free(s1);
	free(s2);
	return (tab);
}

int	get_cmd_type(int size, int index)
{
	if (size == 1)
		return (_single);
	else if (index == size - 1 && index != 0)
		return (_last);
	return (_middle);
}
