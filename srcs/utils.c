/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 08:52:49 by Arsene            #+#    #+#             */
/*   Updated: 2023/04/05 13:50:55 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

///////////////////////////////////////////////////////////////////////////////

char	*expand_exitstatus(char *buffer, int start, int end)
{
	char	*expanded;
	char	*prefix;
	char	*suffix;
	char	*newstring;

	expanded = ft_itoa(g_exitcode);
	end = start + 1;
	prefix = ft_substr(buffer, 0, start - 1);
	suffix = ft_strdup(buffer + end);
	newstring = ft_strjoin_trio(prefix, expanded, suffix);
	ft_freetrio(suffix, expanded, buffer);
	return (newstring);
}

char	*expand_variable(char *buffer, char **envp)
{
	int		start;
	int		end;
	char	*tmp;
	char	*variable;
	char	*expanded;

	start = ft_strchr_mod(buffer, '$') + 1;
	end = 0;
	if (!buffer[start] || (buffer[start] == '\"') || buffer[start] == '?')
	{
		tmp = expand_exitstatus(buffer, start, end);
		return (tmp);
	}
	end = start;
	while (buffer[end] && !is_ending_character(buffer, end))
		end++;
	variable = ft_substr(buffer, start, end - start);
	expanded = get_envp_variable(variable, envp);
	if (expanded)
		tmp = ft_strjoin_trio(
				ft_substr(buffer, 0, start - 1), expanded, buffer + end);
	else
		tmp = ft_strjoin_mod(ft_substr(buffer, 0, start - 1), buffer + end);
	ft_freetrio(expanded, variable, buffer);
	return (tmp);
}

///////////////////////////////////////////////////////////////////////////////

int	check_string_input(char **s1, char **s2)
{
	if (!*s1)
	{
		*s1 = ft_strdup("");
		if (!*s1)
			return (STAT_NEG);
	}
	if (!*s2)
	{
		*s2 = ft_strdup("");
		if (!*s2)
			return (STAT_NEG);
	}
	return (STAT_POS);
}

char	*ft_strjoin_trio(char *s1, char *s2, char *s3)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	if (check_string_input(&s1, &s2) == STAT_NEG)
		return (NULL);
	tmp = malloc(sizeof(char)
			* ((ft_strlen(s1) + ft_strlen(s2)) + ft_strlen(s3) + 1));
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

char	*ft_strjoin_freeboth(char *s1, char *s2)
{
	char	*tab;
	int		i;
	int		j;

	if (check_string_input(&s1, &s2) == STAT_NEG)
		return (NULL);
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
	ft_freeduo(s1, s2);
	return (tab);
}
