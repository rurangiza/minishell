/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:49:50 by Arsene            #+#    #+#             */
/*   Updated: 2023/02/06 10:37:32 by arurangi         ###   ########.fr       */
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

int	heredoc(char *limiter)
{
	char	*stash = NULL;
	char	*buffer = NULL;
	//int		tempfile = open("tmp_xyz95d4e", O_RDWR | O_CREAT | O_TRUNC, 0777);

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
			break ;
	
		stash = ft_strjoin_mod(stash, buffer);
	}
	free(buffer);
	write(ends[1], stash, ft_strlen(stash));
	free(stash);
	close(ends[1]);
	return (ends[0]);
}
