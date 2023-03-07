/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:33:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/06 17:06:25 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(t_token *token)
{
	char	current_dir[100];
	char	*path;

	ft_bzero(current_dir, 100);
    //Getting the current working directory
	getcwd(current_dir, 1000);
	
	printf("\033[33mcurrent:\033[0m %s\n", current_dir);

	//Changing the current working directory
	path = ft_substr(current_dir, 0, ft_strlen(current_dir));
	//if (ft_strncmp(token->cmd[1], "..", 2) != 0)
	if (token->cmd[1])
		path = ft_strjoin_trio(path, "/", token->cmd[1]);
	else
	{
		// cd only sends to /Users/arurangi
		free(path);
		//path = ft_strjoin("/Users/", ft_substr(path));
		int pos_name = 6;
		while (path[pos_name] != '/')
			pos_name++;
			
		char *user_name = ft_substr(path, 6, pos_name);
		printf("--User_name = %s\n", user_name);
		path = ft_strjoin("/Users/", user_name);
	}

	printf("\033[33mnew:\033[0m %s\n", path);

	//return ;
    if (chdir(path) == -1)
		perror(CRED"chdir"CRESET);
}
