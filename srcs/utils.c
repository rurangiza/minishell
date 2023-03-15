/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 08:52:49 by Arsene            #+#    #+#             */
/*   Updated: 2023/03/15 11:49:17 by akorompa         ###   ########.fr       */
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

char *expand_variable(char *buffer)
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
		expanded = ft_itoa(g_tools.exit_code);
		end = start + 1;
		tmp = ft_strjoin_trio(ft_substr(buffer, 0, start - 1), expanded, ft_strdup(buffer + end));
		free(buffer);
		return(tmp);
	}
	// Find end
	end = start;
	while (buffer[end] && !ft_isspace(buffer[end]) && buffer[end] != '\"' && buffer[end] != '$')
		end++;
	// Isolate the variable
	variable = ft_substr(buffer, start, end - start);
	//printf("%s\n", variable);
	// Check if variable exists in envp
	expanded = get_envp_variable(variable);
	if (expanded)
		tmp = ft_strjoin_trio(ft_substr(buffer, 0, start - 1), expanded, buffer + end);
	else
		tmp = ft_strjoin_mod(ft_substr(buffer, 0, start - 1), buffer + end);
	free(variable);
	free(buffer);
	return (tmp);
}
