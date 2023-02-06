/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:49:50 by Arsene            #+#    #+#             */
/*   Updated: 2023/02/06 13:33:51 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int get_cmd_type(int size, int index)
{
    if (size == 1)
        return (_single);
    else if (index == size - 1 && index != 0)
        return (_last);
    return (_middle);
}


/*
 * REQUIREMENTS
 * - parsing:init: variable expander (TRUE, FALSE)
 * - parsing:init: pass down ENVP
 * - parsing:init : pass down LIMITER
*/
int	heredoc(char *limiter, char **envp, int var_expand)
{
	char	*stash = NULL;
	char	*buffer = NULL;

	int ends[2];
	pipe(ends);

	while (TRUE)
	{
		write(1, "> ", 2);
		buffer = get_next_line(STDIN_FILENO);
        if (!buffer)
            exit_msg(); // if I simply return NULL, execve will run
		if (ft_strncmp(buffer, limiter, ft_strlen(limiter)) == 0
            && ft_strlen(buffer) - 1 == ft_strlen(limiter))
			{
				free(buffer);
				break ;
			}
		// Interprete environment variables
		if (ft_strchr_mod(buffer, '$') != -1 && var_expand == TRUE)
		{
			// Find start
			int start = ft_strchr_mod(buffer, '$') + 1;
			// Find end
			int end = start;
			while (buffer[end] && !ft_isspace(buffer[end]))
				end++;
			// Isolate the variable
			char *variable = ft_substr(buffer, start, end - start);
			// Check if variable exists in envp

			//getenv(variable);
			
			int index = 0;
			while (envp[index])
			{
				if (ft_strnstr(envp[index], variable, ft_strlen(variable)) && envp[index][ft_strlen(variable)] == '=') // hello [HOME] nothing
				{
					// if so, join its content to start of buffer
					char *s1 = ft_substr(buffer, 0, start - 1);					
					char *s2 = envp[index] + ft_strlen(variable) + 1;
					char *s3 = buffer + end;
					char *tmp = ft_strjoin_trio(s1, s2, s3);
					free(variable);
					stash = ft_strjoin_mod(stash, tmp);
					index = -1;
					break ;
				}
				index++;
			}
			if (index != -1)
			{
				// else, join start of buffer with rest ignoring the variable part
				char *s1 = ft_substr(buffer, 0, start - 1);
				char *s2 = buffer + end;
				char *tmp = ft_strjoin_mod(s1, s2); // to free
				stash = ft_strjoin_mod(stash, tmp);
			}
		}
		else
			stash = ft_strjoin_mod(stash, buffer);
	}
	write(ends[1], stash, ft_strlen(stash));
	free(stash);
	close(ends[1]);
	return (ends[0]);
}

char	*ft_strjoin_trio(char *s1, char *s2, char *s3)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	// if (!s1)
	// {
	// 	s1 = ft_strdup("");
	// 	if (!s1)
	// 		return (NULL);
	// }
	// if (!s2)
	// {
	// 	s2 = ft_strdup("");
	// 	if (!s2)
	// 		return (NULL);
	// }
	// if (!s3)
	// {
	// 	s3 = ft_strdup("");
	// 	if (!s3)
	// 		return (NULL);
	// }
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
	// free(s1);
	// free(s2);
	// free(s3);
	return (tmp);
}

// int main(void)
// {
// 	char *s1 = "hello";
// 	char *s2 = " mister ";
// 	char *s3 = " dongy";

// 	char *result = ft_strjoin_trio(s1, s2, s3);
// 	printf("%s\n", result);
// 	return (0);
// }