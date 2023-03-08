/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:33:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/08 16:28:51 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(char *directory, t_prompt *prompt)
{
	char	*path = NULL;
	//char	*oldwd = getcwd(NULL, 0);
		
	if (!directory)
		path = get_userdir();
	else if (ft_strlen(directory) == 1 && is_special_symbol(directory))
	{
		if (directory[0] == '-')
		{
			path = get_previous_directory(prompt);
			printf("%s\n", prompt->directory_history->content);
			//printf("%s\n", path);
		}
		else if (directory[0] == '~')
			path = get_userdir();
		else if (directory[0] == '/')
			path = ft_strdup("/");
	}
	else
	{
		path = ft_strdup(getcwd(NULL, 0));
		if (ft_strlen(path) == 1 && ft_strncmp(path, "/", 1) == 0)
			path = ft_strjoin(path, directory);
		else
			path = ft_strjoin_trio(path, "/", directory);
	}
    if (chdir(path) == -1)
		perror(CRED"chdir"CRESET);
	else
		update_directory_history(prompt, path);
	//else if (!(ft_strlen(directory) == 1 && is_special_symbol(directory) && directory[0] == '-'))
	
	// t_list	*tmp = prompt->directory_history;
	// printf(CBLUE"~~~~~~~~~ DIRECTORY HISTORY ~~~~~~~~~\n"CRESET);
	// while (tmp && tmp->content)
	// {
	// 	printf(CBLUE"• %s\n"CRESET, tmp->content);
	// 	if (!tmp->next)
	// 		break ;
	// 	tmp = tmp->next;
	// }
	
}

char	*get_userdir(void)
{
	char	*username;
	char	*path;

	username = ft_strdup(getenv("USER"));
	if (username == NULL)
		return (NULL);
	path = ft_strdup("/Users/");
	return (ft_strjoin(path, username));
}

char	*get_previous_directory(t_prompt *prompt)
{
	// int index = 0;

	// (void)prompt;
	// while (g_environment[index])
	// {
	// 	if (ft_strncmp(g_environment[index], "OLDPWD=", 7) == 0)
	// 	{
	// 		printf("%s\n", g_environment[index]);
	// 		return (ft_substr(g_environment[index], 7, ft_strlen(g_environment[index])));
	// 	}
	// 	index++;
	// }
	// return (NULL);
		
	char	*tmp;
	
	if (ft_lstsize(prompt->directory_history) > 1)
	{
		tmp = prompt->directory_history->content;
		free(prompt->directory_history->content);
		prompt->directory_history->content = ft_strdup(getcwd(NULL, 0));
		return (tmp);
	}
	else
		return (prompt->directory_history->content);
}

void	update_directory_history(t_prompt *prompt, char *path)
{
	// int index = 0;

	// (void)prompt;
	// while (g_environment[index])
	// {
	// 	if (ft_strncmp(g_environment[index], "OLDPWD=", 7) == 0)
	// 	{
	// 		//free(g_environment[index]);
	// 		g_environment[index] = ft_strdup(oldwd);
	// 	}
	// 	if (ft_strncmp(g_environment[index], "PWD=", 4) == 0)
	// 	{
	// 		//free(g_environment[index]);
	// 		g_environment[index] = ft_strdup(cwd);
	// 	}
	// 	index++;
	// }
	
	t_list *current;
	t_list *second_last;
	
	ft_lstadd_front(&prompt->directory_history, ft_lstnew(path));
	if (ft_lstsize(prompt->directory_history) > 1)
	{
		current = prompt->directory_history;
		second_last = NULL;
		while (current && current->content && current->next != NULL)
		{
			second_last = current;
			current = current->next;
		}
		free(second_last->next->content);
		second_last->next = NULL;
	}
}