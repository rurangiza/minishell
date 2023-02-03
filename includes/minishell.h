/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:28:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/02/03 14:06:55 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../src/library/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <sys/stat.h> // fstat ?

# define READ 0
# define WRITE 1
# define TRUE	1
# define FALSE	0

typedef struct s_token
{
	char	**cmd;
	char	*cmd_path;
	int		infile;
	int		outfile;
}	t_token;

typedef enum e_state {
    _single	= 0,
    _last	= 1,
    _middle	= 2
} t_state;

/* ~~~~~~~~~~~ EXECUTION & I/O REDIRECTIONS ~~~~~~~~~~~~ */

void	execute(t_token *tree, int size);

void    child_process(t_token *tree, t_state cmd_type, int index, int *pipends, int prevpipe);
void    parent_process(int child_pid, t_state cmd_type, int *pipends, int *prevpipe);

void	single_child(t_token *token);
void	last_child(t_token *token, int prevpipe);
void	average_child(t_token *token, int index, int prevpipe, int *pipends);

int		get_cmd_type(int size, int index);


/* ~~~~~~~~~~~ BUILT-INS ~~~~~~~~~~~~~ */
void	echo(int option, char *argument);
char	*check_escape_seq(char *argument, int index);

/* ~~~~~~~~~~~ MEMORY MANAGEMENT ~~~~~~~~~~~~~ */
void	ft_free_matrix(char **matrix);

/* ~~~~~~~~~~~~~ ERROR HANDLING ~~~~~~~~~~~~~~~ */
void	exit_msg(void);

#endif