/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:58:13 by akorompa          #+#    #+#             */
/*   Updated: 2023/04/17 15:53:54 by akorompa         ###   ########.fr       */
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
# include <signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
// tcgetattr(), 
# include <termios.h>

# define CGRAY     "\x1b[30m"
# define CRED     "\x1b[31m"
# define CGREEN   "\x1b[32m"
# define CYELLOW  "\x1b[33m"
# define CBLUE    "\x1b[34m"
# define CMAGENTA "\x1b[35m"
# define CCYAN    "\x1b[36m"
# define CWHITE    "\x1b[37m"
# define CBOLD   "\x1b[1m"
# define CRESET   "\x1b[0m"

# define BG_BLACK   "\x1b[40m"
# define BG_RED   "\x1b[41m"
# define BG_GREEN   "\x1b[42m"
# define BG_YELLOW   "\x1b[43m"
# define BG_BLUE   "\x1b[44m"
# define BG_MAGENTA   "\x1b[45m"
# define BG_CYAN   "\x1b[46m"
# define BG_WHITE   "\x1b[47m"

# define READ 0
# define WRITE 1
# define TRUE	1
# define FALSE	0
# define HERE_DOC -3
# define NO_REDIR -1
# define STAT_POS 1
# define STAT_NEG -1

extern int	g_exitcode;
int			g_exitcode;

typedef struct s_lexer
{
	char	**tokens;
	char	**tmp;
}	t_lexer;

typedef struct s_utils
{
	int	i;
	int	k;
	int	count;
	int	len;
	int	j;
}	t_utils;

typedef struct s_token
{
	char			**cmd;
	char			*cmd_path;
	int				outfile;
	int				infile;
	char			*delimiter;
	int				heredoc_mode;
	struct stat		stats;
}	t_token;

typedef struct s_prompt
{
	t_token	*cmds;
	char	**path;
	char	**envp;
	int		pipe_nb;
	int		prevpipe;
	int		pipends[2];
	pid_t	*saved_pid;
	int		stdio[2];
}	t_prompt;

typedef enum e_state {
	_single		= 0,
	_last		= 1,
	_middle		= 2,
	_FREEBUCKET = 11,
}	t_state;

/* ~~~~~~~~~~~~~~~~~~~~~~~ LEXER ~~~~~~~~~~~~~~~~~~~~~~~ */
t_lexer	lexerinho(char *prompt, char **envp);
char	**token(t_lexer *lexer);
char	*get_tokens(char *str, int *j, int *k);
int		get_nb_token(char *str);
int		len_utils(char *str, int *len, int i, char sep);
int		len_tokens(char *str);
void	found_set(char *str, int i, int *j, int *k);
int		ft_isset(char *set, char c);
char	*delete_quotes_1(char *str, char c);
int		get_size(char *str, char c);
int		count_words(char *prompt);
int		check_quotes(char *prompt);
int		skip_quote(char *prompt, int i, char quote);
int		skip_quote_count(char *prompt, int i, char quote);
int		skip_not_spaces(char *prompt, int i);
int		skip_spaces(char *prompt, int i);
int		skip_red(char **token, int i);
char	**ft_cmd_lexer(char *prompt);

/* ~~~~~~~~~~~~~~~~~~~~~~ EXPANDER ~~~~~~~~~~~~~~~~~~~~~ */
void	expander(t_lexer *lexer, char **envp);
char	*ft_strjoin_trio(char *s1, char *s2, char *s3);
char	*get_envp_variable(char *variable, char **envp);

/* ~~~~~~~~~~~~~~~~~~~~~~ PARSER ~~~~~~~~~~~~~~~~~~~~~ */
void	parser(t_prompt *prompt, t_lexer *lexer);
char	*find_path(char **envp);

/* ~~~~~~~~~~~ EXECUTION & I/O REDIRECTIONS ~~~~~~~~~~~~ */

void	execute(t_token *token, t_prompt *prompt);
void	exec_cmds(t_token *token, t_prompt *prompt, int index, int cmd_type);

void	parent_process(t_token *token, t_prompt *prompt, int cmd_type);
void	child_process(t_token *token, t_prompt *prompt,
			int cmd_type, int index);
void	single_child(t_token *token, t_prompt *prompt);
void	last_child(t_token *token, t_prompt *prompt);
void	middle_child(t_token *token, t_prompt *prompt, int index);

void	check_cmds_status(t_token *token, t_prompt *prompt);

/* ~~~~~~~~~~~ REDIRECTIONS ~~~~~~~~~~~~~ */
void	redirect_in(t_token *token, t_prompt *prompt);
void	redirect_out(t_token *token);
void	simple_redirect(t_token *token, t_prompt *prompt, int index);

int		get_cmd_type(int size, int index);

int		heredoc(char *limiter, int var_expdr, t_prompt *prompt);

void	exec_builtins(t_token *token, t_prompt *prompt, int index);

/* ~~~~~~~~~~~ BUILT-INS ~~~~~~~~~~~~~ */
void	echo(t_token *token);
int		update_newlinemode(t_token *token, int index, int *newline_mode);

void	pwd(t_token *token);

void	env(t_token *tokens, t_prompt *prompt);

int		export(t_token *tokens, t_prompt *prompt);
char	**ft_dup_matrix(char **arr);
void	print_export(t_prompt *prompt);
int		check_export_utils(char *str, int *n);
char	**ft_delete_var(t_token *tokens, t_prompt *prompt, int index);
int		is_env_var(char *str, t_prompt *prompt);
int		len_to_equal(char *str);
int		check_equal(char *str);
int		check_forbidden(char *str);
int		arr_len(char **arr);

void	unset(t_token *token, t_prompt *prompt);
char	**ft_remove_variable(t_token *token, t_prompt *prompt, int index);
int		is_in_environment(char *variable, t_prompt *prompt);
int		is_valid_identifier(char *str);
int		is_variable_to_be_deleted(char *target, char *source);

int		my_exit(t_token *tokens);

void	cd(char *directory, t_prompt *prompt);
char	*ft_find_destination(char *directory, t_prompt *prompt);
char	*save_cwd(void);

int		is_echo_option(char *str);

/* ~~~~~~~~~~~~ INITIALIZATION ~~~~~~~~~~~~~~~ */
char	**init_environment(char **envp);
void	init_shell(t_prompt *prompt, int argc, char **argv, char **envp);
void	init_prompt(t_prompt *prompt);
void	init_signals(void);
void	init_signals_inprocess(void);
int		init_exec(t_token *token, t_prompt *prompt);
void	init_heredoc(char *limiter, int *ends, char **stash, char **buffer);

/* ~~~~~~~~~~~ MEMORY MANAGEMENT ~~~~~~~~~~~~~ */
void	ft_free_matrix(char **matrix);
void	terminate_exec(t_prompt *prompt);
void	ft_freetrio(char *s1, char *s2, char *s3);
void	ft_freeduo(char *s1, char *s2);

/* ~~~~~~~~~~~~~ ERROR HANDLING ~~~~~~~~~~~~~~~ */
void	exit_msg(void);
void	exitmsg(char *msg, char *cmd, int code);
void	handle_execution_errors(t_token *token, t_prompt *prompt);

/* ~~~~~~~~~~ UTILS ~~~~~~~~~~~~~~ */
char	*ft_strjoin_trio(char *s1, char *s2, char *s3);
char	*expand_variable(char *buffer, char **envp);
//char	*get_userdir(void);
char	*get_variable_in_environment(char *variable, t_prompt *prompt); // cd()
char	*getenv_custm(char *variable, t_prompt *prompt); // Same without message

/* ~~~~~~~~~~ UTILS ~~~~~~~~~~~~~~ */
int		is_builtin(char *cmd);
int		is_path_alias(char *directory);
void	check_user_input(char *input);
int		is_empty_pipe(int read_end);
char	*ft_strjoin_freeboth(char *s1, char *s2);
int		not_real(char *str, char c);

/* ~~~~~~~~~~ CHECKER ~~~~~~~~~~~~~~ */
int		ft_isspace(char c);
int		is_ending_character(char *buffer, int end);

//void	hanging_cats(t_token *token);

void	update_directory_history(t_prompt *prompt, char *path);
void	update_pwd(char *oldpwd, char *pwd, t_prompt *prompt);
void	add_missing_oldpwd(char *newold, t_prompt *prompt);

char	*update_shell_level(char *variable);

/* ~~~~~~~~~~~~~ SIGNALS ~~~~~~~~~~~~~~~ */
void	handle_signals(int signo);
void	handle_inprocess_signals(int signo);
void	handle_inheredoc_signals(int signo);

/* ~~~~~~~~~~~~~ INTERFACE ~~~~~~~~~~~~~~~ */
char	*ft_readline(void);

/* ~~~~~~~~~~ DISPLAY ~~~~~~~~~~~~~~ */
void	display_tree(int level, const char *function, t_token *token);
void	display_start(void);
void	display_end(void);
void	display_prompt(t_prompt *prompt);
void	display_env(t_prompt *prompt, char *str);

/* ~~~~~~~~~~ CALCULATOR ~~~~~~~~~~~~~~ */
int		ft_tablen(char **tab);

/* ~~~~~~~~~~ CALCULATOR ~~~~~~~~~~~~~~ */
void	createpipe(t_prompt *prompt, int cmd_type);

/* ~~~~~~~~~~ CALCULATOR ~~~~~~~~~~~~~~ */
int		is_sep(char *sep, char c);
void	check_heredoc_mod(char *str, t_token *cmd);
int		get_size_delimiter(char *str);

/* ~~~~~~~~~~ PARSER ~~~~~~~~~~~~~~ */
int		get_cmd_len(char **tokens, int i);

void	init_cmd(t_token *cmd);
int		init_redirections(char **tokens, t_token *cmd, int *j);
void	set_redirections(char **tokens, t_token *cmd, int *i);
void	init_cmd_data(char **tokens, t_prompt *prompt, int *j, t_token *cmd);
void	set_cmd_data(char **tokens, t_prompt *prompt, t_token *cmd, int i);

int		is_built_in(char *str);

char	**get_built_in(char **tokens, int i);

char	*get_cmd_path(char *str, char **path);
char	**get_cmd(char **tokens, int i);
char	*get_delimiter(char *str);

int		get_pipe_nb(t_lexer *lexer);
int		get_outfile_apmod(char *str);
int		get_outfile(char *str);
int		get_infile(char *str);
#endif