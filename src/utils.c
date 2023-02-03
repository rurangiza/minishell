/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:49:50 by Arsene            #+#    #+#             */
/*   Updated: 2023/02/03 20:03:55 by Arsene           ###   ########.fr       */
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

char	*heredoc(char *limiter)
{
	char *stash;
	char *buffer = NULL;
	
	while (TRUE)
	{
		write(1, "heredoc> ", 9);
		buffer = get_next_line(STDIN_FILENO);
        if (!buffer)
            exit_msg(); // if I simply return NULL, execve will run
		if (ft_strncmp(buffer, limiter, ft_strlen(limiter)) == 0)
			break ;
		stash = ft_strjoin_mod(stash, buffer);
	}
	//write(STDOUT_FILENO, stash, ft_strlen(stash));
	free(buffer);
	return (stash);
}