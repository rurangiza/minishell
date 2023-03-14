/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:58:13 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/14 10:46:03 by arurangi         ###   ########.fr       */
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
# include <errno.h>
# include <dirent.h>

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
# define NO_REDIR -1

extern char **g_environment;

char 	**g_environment;

typedef struct s_tools {
	int		exit_code;
	char	**environment;
} t_tools;

t_tools g_tools;

typedef struct s_lexer
{
	char **tokens;
	char **tmp;
}	t_lexer;

typedef struct s_token
{
	char	**cmd;
	char	*cmd_path;
	int		outfile;
	int		infile;
	char	**envp;
	char	*delimiter;
	int		heredoc_mode;
}	t_token;

typedef struct s_prompt
{
	t_token	*cmds;
	char	**path;
	char	**envp;
	int		pipe_nb;
	t_list	*directory_history;
}	t_prompt;

typedef enum e_state {
    _single	= 0,
    _last	= 1,
    _middle	= 2
} t_state;

/* ~~~~~~~~~~~~~~~~~~~~~~~ LEXER ~~~~~~~~~~~~~~~~~~~~~~~ */
t_lexer	lexerinho(char *prompt, char **envp);
char	**token(t_lexer *lexer);
char *delete_quotes_1(char *str, char c);
int	get_size(char *str, char c);

/* ~~~~~~~~~~~~~~~~~~~~~~ EXPANDER ~~~~~~~~~~~~~~~~~~~~~ */
void	expander(t_lexer *lexer, char **envp);
char	*ft_strjoin_trio(char *s1, char *s2, char *s3);
char	*get_envp_variable(char *variable);

void	parser(t_prompt *prompt, t_lexer *lexer, char **envp);
int		is_valid_cmd(char *str, char **path);
int		is_valid_cmd_bis(char *str, char *path);
char	*find_path(char **envp);

/* ~~~~~~~~~~~ EXECUTION & I/O REDIRECTIONS ~~~~~~~~~~~~ */

void	execute(t_token *token, t_prompt *prompt);

void    parent_process(int child_pid, t_state cmd_type, int *pipends, int *prevpipe);

void	single_child(t_token *token);
void	last_child(t_token *token, int prevpipe);
void	middle_child(t_token *token, int index, int prevpipe, int *pipends);

void	redirect_in(t_token *token);
void	redirect_out(t_token *token);

int		get_cmd_type(int size, int index);

int		heredoc(char *limiter, int var_expdr);
char	*expand_variable(char *buffer);

void	execute_builtins(t_token *token);

/* ~~~~~~~~~~~ BUILT-INS ~~~~~~~~~~~~~ */
void	echo(t_token *token);
void	pwd(t_token *token);
void	env(t_token *tokens);
int		export(t_token *tokens);
void	unset(t_token *token);
void	cd(char *directory);
//void	unset_shift(t_token *token);

/* ~~~~~~~~~~~~ INITIALIZATION ~~~~~~~~~~~~~~~ */
void	init_environment(char **envp);

/* ~~~~~~~~~~~ MEMORY MANAGEMENT ~~~~~~~~~~~~~ */
void	ft_free_matrix(char **matrix);
void	dup_matrix(char **environment);

/* ~~~~~~~~~~~~~ ERROR HANDLING ~~~~~~~~~~~~~~~ */
void	exit_msg(void);
void	exit_wrongcmd_msg(char *cmd, int error_code);

/* ~~~~~~~~~~ UTILS ~~~~~~~~~~~~~~ */
char	*ft_strjoin_trio(char *s1, char *s2, char *s3);
char	*expand_variable(char *buffer);
//char	*get_userdir(void);
char	*get_variable_in_environment(char *variable);

/* ~~~~~~~~~~ UTILS ~~~~~~~~~~~~~~ */
int		is_builtin(char *cmd);
int		is_variable_to_be_deleted(char *target, char *source);
int		is_in_environment(char *variable);
int		is_special_symbol(char *directory);
int		is_valid_identifier(char *str);

void	hanging_cats(t_token *token);

void	update_directory_history(t_prompt *prompt, char *path);
//char	*get_previous_directory();
void	update_pwd(char *oldpwd, char *pwd);
void	add_missing_oldpwd(char *newold);

#endif