/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:07:15 by Arsene            #+#    #+#             */
/*   Updated: 2023/03/30 15:49:18 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**init_environment(char **envp)
{
	int		index;
	char	**tmp;
	int		outdex;

	index = 0;
	while (envp[index])
		index++;
	if (!getenv("OLDPWD"))
		index--;
	tmp = malloc((index + 2) * sizeof(char *));
	if (!tmp)
		return (NULL);
	index = 0;
	outdex = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "OLDPWD=", 7) != 0)
		{
			if (ft_strncmp(envp[index], "SHLVL=", 6) == 0)
				tmp[outdex] = update_shell_level(envp[index] + 6);
			else
				tmp[outdex] = ft_strdup(envp[index]);
			outdex++;
		}
		index++;
	}
	tmp[outdex] = NULL;
	return (tmp);
}

char	*update_shell_level(char *variable)
{
	int		level;
	char	*new;
	char	*tmp;
	char	*tmp2;

	level = ft_atoi(variable);
	tmp = ft_strdup("SHLVL=");
	if (level < 1)
		level = 1;
	else
		level++;
	tmp2 = ft_itoa(level);
	new = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	return (new);
}

void	init_shell(t_prompt *prompt, int arg_count, char **arg_list, char **envp)
{
	(void)arg_list;
	(void)prompt;

	g_exitcode = 0;
	// Remove ^C when pressing Ctrl^C
	struct termios term; //! Declare structure in head
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
	// Valid arguments
	if (arg_count != 1)
	{
		printf("Usage: ./minishell\n");
		exit(EXIT_FAILURE);
	}
	// Clone environment variables
	prompt->envp = init_environment(envp);
}

void	init_prompt(t_prompt *prompt)
{
	prompt->cmds = NULL;
	prompt->path = NULL;
	prompt->saved_pid = NULL;
	prompt->prevpipe = -1;
}