/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:33:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/06 11:56:46 by arurangi         ###   ########.fr       */
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
	
	printf("current: %s\n", current_dir);

	//Changing the current working directory
	int end = ft_strrchr_mod(current_dir, '/');
	path = ft_substr(current_dir, 0, end + 1);
	if (ft_strncmp(token->cmd[1], "..", 2) != 0)
		path = ft_strjoin(path, token->cmd[1]);

	printf("new: %s\n", path);

    if (chdir(path) == -1)
		perror("chdir");
}
