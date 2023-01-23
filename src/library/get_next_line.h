/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:21:56 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/23 12:23:36 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

# define BUFFER_SIZE 1

int		ft_strlen(const	char *str);
char	*ft_strjoin_mod(char *old_stash, char *buff);
char	*ft_strdup(const char *str);
int		ft_strchr_mod(const char *s, char ch);

char	*get_next_line(int fd);
char	*save_raw_line(int fd, char *stash);
char	*trim_right(char *raw_line);
char	*trim_left(char *stash);
char	*free_stash(char *stash);

#endif