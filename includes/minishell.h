/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:58:13 by akorompa          #+#    #+#             */
/*   Updated: 2023/01/30 10:05:32 by akorompa         ###   ########.fr       */
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

typedef struct s_cmd
{
	char *cmd;
	char *path;
	char **cmd_path;
	char **cmd_args;
}	 t_cmd;

typedef struct s_lexer
{
	char **tokens;
}	t_lexer;

typedef struct s_parser
{
	int op_count;
	char **cmd_path;
	
}	t_parser;

typedef struct s_token
{
	char **cmd;
	char *cmd_path;
	int outfile;
	int infile;
}	t_token;

t_token *parser(t_lexer *lexer, char **envp);
char	*find_path(char **envp);
char *get_cmd(char *str, char **cmd_path);

#endif