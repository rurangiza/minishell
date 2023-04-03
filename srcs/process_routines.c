/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_routines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:17:06 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/03 16:57:09 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_process(t_token *token, t_prompt *prompt, int cmd_type, int index)
{
	if (cmd_type == _single)
		single_child(&token[index], prompt);
	else if (cmd_type == _last)
		last_child(&token[index], prompt->prevpipe, prompt);
	else
		middle_child(&token[index], index, prompt->prevpipe, prompt->pipends, prompt);
}

///////////////////////////////////////////////////////////////////////////////

void	single_child(t_token *token, t_prompt *prompt)
{
	if (token->infile != -1)
		redirect_in(token, prompt);
	if (token->outfile != -1)
		redirect_out(token);
	handle_execution_errors(token, prompt);
	execve(token->cmd_path, token->cmd, prompt->envp);
	exit_msg();
}

///////////////////////////////////////////////////////////////////////////////

void	last_child(t_token *token, int prevpipe, t_prompt *prompt)
{
	if (token->infile != -1)
		redirect_in(token, prompt);
	else
		dup2(prevpipe, STDIN_FILENO);
	close(prevpipe);
	if (token->outfile != -1)
		redirect_out(token);
	handle_execution_errors(token, prompt);
	execve(token->cmd_path, token->cmd, prompt->envp);
	exit_msg();
}

///////////////////////////////////////////////////////////////////////////////

void	middle_child(t_token *token, int index, int prevpipe, int *pipends, t_prompt *prompt)
{
	(void)prevpipe; // Delete and remove from arguments
	close(pipends[READ]);
	if (token->infile != -1)
		redirect_in(token, prompt);
	else if (index > 0)
	{
		dup2(prompt->prevpipe, STDIN_FILENO);
		close(prompt->prevpipe);
	}
	if (token->outfile != -1)
		redirect_out(token);
	else
		dup2(pipends[WRITE], STDOUT_FILENO);
	close(pipends[WRITE]);
	handle_execution_errors(token, prompt);
	execve(token->cmd_path, token->cmd, prompt->envp);
	exit_msg();
}

///////////////////////////////////////////////////////////////////////////////

void	parent_process(t_token *token, t_prompt *prompt, int cmd_type)
{
	if (cmd_type == _middle)
	{
		close(prompt->pipends[WRITE]);
		prompt->prevpipe = prompt->pipends[READ];
		if (is_empty_pipe(prompt->pipends[READ])
			&& ft_strncmp("cat", token->cmd[0], 3) == 0
			&& !token->cmd[1] && token->infile < 0)
			close(prompt->pipends[READ]);
	}
}

void	check_cmds_status(t_token *token, t_prompt *prompt)
{
	int	i;
	int	status;

	i = 0;
	while (i < prompt->pipe_nb)
	{
		waitpid(prompt->saved_pid[i], &status, 0);
		if (WIFEXITED(status))
		{
			g_exitcode = WEXITSTATUS(status);
			if (WEXITSTATUS(status) != 0 && prompt->pipe_nb == 1
				&& token[i].cmd && ft_strncmp("exit", token[i].cmd[0], 4) == 0)
				exit(g_exitcode);
		}
		i++;
	}
}
