/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:58:13 by akorompa          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/28 14:56:28 by akorompa         ###   ########.fr       */
=======
/*   Updated: 2023/02/28 17:53:29 by arurangi         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"

#define CRED     "\x1b[31m"
#define CGREEN   "\x1b[32m"
#define CYELLOW  "\x1b[33m"
#define CBLUE    "\x1b[34m"
#define CMAGENTA "\x1b[35m"
#define CCYAN    "\x1b[36m"
#define CWHITE    "\x1b[36m"
#define CBOLD   "\x1b[1m"
#define CRESET   "\x1b[0m"

# define READ 0
# define WRITE 1
# define TRUE	1
# define FALSE	0
# define HERE_DOC -3

typedef struct s_lexer
{
	char **tokens;
	char **tmp;
}	t_lexer;

typedef struct s_token
{
	char *delimiter;
	int	here_doc;
	char **cmd;
	char *cmd_path;
	int outfile;
	int infile;
}	t_token;

typedef struct s_prompt
{
	t_token	*cmds;
	char **path;
	char **envp;
	int pipe_nb;
}	t_prompt;

typedef enum e_state {
    _single	= 0,
    _last	= 1,
    _middle	= 2
} t_state;

/* ~~~~~~~~~~~ LEXER ~~~~~~~~~~~~ */
t_lexer	lexerinho(char *prompt, char **envp);
char	**token(t_lexer *lexer);

/* ~~~~~~~~~~~ EXPANDER ~~~~~~~~~~~~ */
void	expander(t_lexer *lexer, char **envp);
char	*ft_strjoin_trio(char *s1, char *s2, char *s3);

void	parser(t_prompt *prompt, t_lexer *lexer, char **envp);
char	*find_path(char **envp);
void	delete_quotes(char **tokens);
char *delete_quotes_1(char *str, char c);
int	get_size(char *str, char c);


/* ~~~~~~~~~~~ EXECUTION & I/O REDIRECTIONS ~~~~~~~~~~~~ */

void	execute(t_token *tree, int size);

void    parent_process(int child_pid, t_state cmd_type, int *pipends, int *prevpipe);

void	single_child(t_token *token);
void	last_child(t_token *token, int prevpipe);
void	middle_child(t_token *token, int index, int prevpipe, int *pipends);

void	redirect_in(t_token *token);
void	redirect_out(t_token *token);

int		get_cmd_type(int size, int index);

int		heredoc(char *limiter, int var_expdr);
char	*expand_variable(char *buffer);

/* ~~~~~~~~~~~ BUILT-INS ~~~~~~~~~~~~~ */
void	echo(int option, char *argument);
char	*check_escape_seq(char *argument, int index);

/* ~~~~~~~~~~~ MEMORY MANAGEMENT ~~~~~~~~~~~~~ */
void	ft_free_matrix(char **matrix);

/* ~~~~~~~~~~~~~ ERROR HANDLING ~~~~~~~~~~~~~~~ */
void	exit_msg(void);

/* ~~~~~~~~~~ UTILS ~~~~~~~~~~~~~~ */
char	*ft_strjoin_trio(char *s1, char *s2, char *s3);

#endif