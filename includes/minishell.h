/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:28:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/02/07 16:59:25 by arurangi         ###   ########.fr       */
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
# define HERE_DOC 999

typedef struct s_token
{
	char	**cmd;
	char	*cmd_path;
	int		infile;
	int		outfile;
	char	*delimiter;
	char	**envp;
	int		variable_expdr;
	int		state;
}	t_token;

typedef enum e_state {
    _single	= 0,
    _last	= 1,
    _middle	= 2
} t_state;

#define CRED     "\x1b[31m"
#define CGREEN   "\x1b[32m"
#define CYELLOW  "\x1b[33m"
#define CBLUE    "\x1b[34m"
#define CMAGENTA "\x1b[35m"
#define CCYAN    "\x1b[36m"
#define CWHITE    "\x1b[36m"
#define CBOLD   "\x1b[1m"
#define CRESET   "\x1b[0m"

/* ~~~~~~~~~~~ EXECUTION & I/O REDIRECTIONS ~~~~~~~~~~~~ */

void	execute(t_token *tree, int size);

void    parent_process(int child_pid, t_state cmd_type, int *pipends, int *prevpipe);

void	single_child(t_token *token);
void	last_child(t_token *token, int prevpipe);
void	middle_child(t_token *token, int index, int prevpipe, int *pipends);

void	redirect_in(t_token *token);
void	redirect_out(t_token *token);

int		get_pipeline_position(int size, int index);

int		heredoc(char *limiter, int var_expdr);
char	*expand_variable(char *buffer);

/* ~~~~~~~~~~~ BUILT-INS ~~~~~~~~~~~~~ */
void	echo(int option, char *argument);
char	*check_escape_seq(char *argument, int index);

/* ~~~~~~~~~~~ MEMORY MANAGEMENT ~~~~~~~~~~~~~ */
void	ft_free_matrix(char **matrix);

/* ~~~~~~~~~~~~~ ERROR HANDLING ~~~~~~~~~~~~~~~ */
void	exit_msg(void);

void    printshell(void);

/* ~~~~~~~~~~ UTILS ~~~~~~~~~~~~~~ */
char	*ft_strjoin_trio(char *s1, char *s2, char *s3);

#endif