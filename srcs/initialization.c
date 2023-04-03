/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:07:15 by Arsene            #+#    #+#             */
/*   Updated: 2023/04/03 17:11:21 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**ft_initab(char **envp)
{
	int		len;
	char	**tmp;

	len = ft_tablen(envp);
	if (getenv("OLDPWD"))
		len--;
	tmp = malloc((len + 1) * sizeof(char *));
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	**init_environment(char **envp)
{
	int		len;
	char	**copy;
	int		index;

	copy = ft_initab(envp);
	if (!copy)
		return (NULL);
	index = 0;
	len = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "OLDPWD=", 7) != 0)
		{
			if (ft_strncmp(envp[index], "SHLVL=", 6) == 0)
				copy[len] = update_shell_level(envp[index] + 6);
			else
				copy[len] = ft_strdup(envp[index]);
			len++;
		}
		index++;
	}
	copy[len] = NULL;
	return (copy);
}

char	*update_shell_level(char *variable)
{
	int		int_level;
	char	*str_level;
	char	*prefix;
	char	*new_variable;

	int_level = ft_atoi(variable);
	if (int_level < 0)
		int_level = 1;
	else
		int_level++;
	str_level = ft_itoa(int_level);
	prefix = ft_strdup("SHLVL=");
	new_variable = ft_strjoin(prefix, str_level);
	free(prefix);
	free(str_level);
	return (new_variable);
}

void	init_shell(t_prompt *prompt, int argc, char **argv, char **envp)
{
	struct termios	term;

	(void)argv;
	g_exitcode = 0;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	if (argc != 1)
	{
		printf("Usage: ./minishell\n");
		exit(EXIT_FAILURE);
	}
	prompt->envp = init_environment(envp);
}

void	init_prompt(t_prompt *prompt)
{
	prompt->cmds = NULL;
	prompt->path = NULL;
	prompt->saved_pid = NULL;
	prompt->prevpipe = -1;
}

void	init_exec(t_prompt *prompt)
{
	prompt->stdio[0] = dup(STDIN_FILENO);
	prompt->stdio[1] = dup(STDOUT_FILENO);
	if (prompt->pipe_nb > 0)
	{
		prompt->saved_pid = malloc(prompt->pipe_nb * sizeof(pid_t));
		if (!prompt->saved_pid)
			return ;
	}
	prompt->prevpipe = -1;
}
