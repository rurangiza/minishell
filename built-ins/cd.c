/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:33:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/08 12:01:32 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_previous_directory(t_prompt *prompt)
{
	// Find last
	//ft_lstlast(prompt->directory_history)->content;
	char	*last;

	if (!prompt->directory_history)
		return ;
	while (prompt->directory_history != NULL)
	{
		if (!prompt->directory_history->next)
		{
			last = prompt->directory_history->content;
			prompt->directory_history->content = NULL;
			free(prompt->directory_history);
		}
		prompt->directory_history = prompt->directory_history->next;
	}
	// Save it
}







void	update_directory_history(t_prompt *prompt, char *path)
{
	t_list	*last;
	t_list	*new = ft_lstnew(path);

	if (prompt->directory_history)
	{
		if (prompt->directory_history)
		{
			last = ft_lstlast(prompt->directory_history);
			last->next = new;
		}
		else
			prompt->directory_history = new;
	}
}





void	cd(char *directory, t_prompt *prompt)
{
	char	*path = NULL;
	
	if (!directory)
		path = get_userdir();
	else if (ft_strlen(directory) == 1 && is_special_symbol(directory))
	{
		if (directory[0] == '-')
		{
			t_list *tmp;
			// if (ft_listsize() > 1)
			free(prompt->directory_history->content);
			tmp = prompt->directory_history->next;
			free(prompt->directory_history);
			prompt->directory_history = tmp;
			path = prompt->directory_history->content;
			printf("%s\n", prompt->directory_history->content);
		}
		else if (directory[0] == '~')
			path = get_userdir();
		else if (directory[0] == '/')
		{
			path = ft_strdup("/");
		}
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
	else if (!(ft_strlen(directory) == 1 && is_special_symbol(directory) && directory[0] == '-'))
		ft_lstadd_front(&prompt->directory_history, ft_lstnew(path));
	
	t_list	*tmp = prompt->directory_history;
	while (tmp && tmp->content)
	{
		printf(CBLUE"• %s\n"CRESET, tmp->content);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
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
