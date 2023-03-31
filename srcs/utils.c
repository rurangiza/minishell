/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 08:52:49 by Arsene            #+#    #+#             */
/*   Updated: 2023/03/31 15:20:50 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

// void	handle_spacial()
// {
	
// 	expanded = ft_itoa(g_exitcode);
// 	end = start + 1;
// 	tmp = ft_strjoin_trio(ft_substr(buffer, 0, start - 1), expanded, ft_strdup(buffer + end));
// 	free(expanded);
// 	free(buffer);
// 	return(tmp);
// }

char *expand_variable(char *buffer, char **envp)
{
	int		start;
	int		end;
	char	*tmp;
	char	*variable;
	char	*expanded;
	
	// Find start
	start = ft_strchr_mod(buffer, '$') + 1;
	if (!buffer[start] || (buffer[start] == '\"') || buffer[start] == '?')
	{
		expanded = ft_itoa(g_exitcode);
		end = start + 1;
		
		char *sub = ft_substr(buffer, 0, start - 1);
		char	*sub2 = ft_strdup(buffer + end);
		tmp = ft_strjoin_trio(sub, expanded, sub2);
		//free(sub);
		free(sub2);
		free(expanded);
		free(buffer);
		return(tmp);
	}
	// Find end
	end = start;
	while (buffer[end] && !ft_isspace(buffer[end]) && buffer[end] != '\'' && buffer[end] != '\"' && buffer[end] != '$')
		end++;
	printf("s=%c e=%c\n", buffer[start], buffer[end]);
	// Isolate the variable
	variable = ft_substr(buffer, start, end - start);
	// Check if variable exists in envp
	expanded = get_envp_variable(variable, envp);
	if (expanded)
		tmp = ft_strjoin_trio(ft_substr(buffer, 0, start - 1), expanded, buffer + end);
	else
	{
		//printf("---- in here\n");
		tmp = ft_strjoin_mod(ft_substr(buffer, 0, start - 1), buffer + end);
		//tmp = NULL;
	}
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
