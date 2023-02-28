/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:58:13 by akorompa          #+#    #+#             */
/*   Updated: 2023/02/28 12:56:21 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
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

typedef struct s_lexer
{
	char **tokens;
	char **tmp;
}	t_lexer;

typedef struct s_token
{
	char *delimiter;
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


//LEXER
t_lexer	lexerinho(char *prompt, char **envp);
char **token(t_lexer *lexer);

//EXPANDER
void	expander(t_lexer *lexer, char **envp);
char	*ft_strjoin_trio(char *s1, char *s2, char *s3);

void parser(t_prompt *prompt, t_lexer *lexer, char **envp);
char	*find_path(char **envp);

#endif