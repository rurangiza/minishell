/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:01:10 by Arsene            #+#    #+#             */
/*   Updated: 2023/02/05 16:19:34 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_token *tree, int nbr_of_pipes)
{
	int	index = 0, pipends[2], prevpipe = 69;
	
	while (index < nbr_of_pipes)
	{
        t_state cmd_type = get_cmd_type(nbr_of_pipes, index);
        if (cmd_type == _middle)
		{
			if (pipe(pipends) == -1)
				exit_msg();
		}
        pid_t pid = fork();
        if (pid == -1)
            exit_msg();
        else if (pid == 0)
            child_process(tree, cmd_type, index, pipends, prevpipe);
        parent_process(pid, cmd_type, pipends, &prevpipe);
		index++;
	}
}

void    child_process(t_token *tree, t_state cmd_type, int index, int *pipends, int prevpipe)
{
    if (cmd_type == _single) // no need to use pipe
        single_child(&tree[index]);
    else if (cmd_type == _last) // no need to create a pipe, need to redirect output
        last_child(&tree[index], prevpipe);
    else // create pipe, redirect I/O
        average_child(&tree[index], index, prevpipe, pipends);
}

void	single_child(t_token *token)
{
	int	error_code;
	char *stash = NULL;
	
	if (token->infile != -1)
	{
		dup2(token->infile, STDIN_FILENO);
		close(token->infile);
	}
	if (ft_strncmp(token->cmd[0], "<<", 2) == 0)
		stash = heredoc(token->cmd[1]);
	if (token->outfile != -1)
	{
		//fdout = dup(STDOUT_FILENO);
		dup2(token->outfile, STDOUT_FILENO);
		close(token->outfile);
	}
	if (stash != NULL)
	{
		write(STDOUT_FILENO, stash, ft_strlen(stash));
		exit(0);
	}
	error_code = execvp(token->cmd[0], token->cmd);
	if (error_code == -1)
		exit_msg();
}

void	last_child(t_token *token, int prevpipe)
{
	int error_code;

	// Handling infiles
	if (token->infile != -1)
	{
		dup2(token->infile, STDIN_FILENO);
		close(token->infile);
	}
	else
		dup2(prevpipe, STDIN_FILENO);
	close(prevpipe);
	// Handling outfiles
	if (token->outfile != -1)
	{
		dup2(token->outfile, STDOUT_FILENO);
		close(token->outfile);
	}
	error_code = execvp(token->cmd[0], token->cmd);
	if (error_code == -1)
		exit_msg();
}

void	average_child(t_token *token, int index, int prevpipe, int *pipends)
{
	int error_code;
	
	close(pipends[READ]);
	// Handle infiles
	if (token->infile != -1)
	{
		dup2(token->infile, STDIN_FILENO);
		close(token->infile);
	}
	else if (index > 0)
		dup2(prevpipe, STDIN_FILENO);
	close(prevpipe);
	// Handle outfiles
	if (token->outfile != -1)
	{
		dup2(token->outfile, STDOUT_FILENO);
		close(token->outfile);
	}
	else
		dup2(pipends[WRITE], STDOUT_FILENO);
	close(pipends[WRITE]);
	error_code = execvp(token->cmd[0], token->cmd);
	if (error_code == -1)
		exit_msg();
}

void    parent_process(int child_pid, t_state cmd_type, int *pipends, int *prevpipe)
{
    int status;

    if (cmd_type == _middle)
    {
        close(pipends[WRITE]);
        *prevpipe = pipends[READ];
    }
    else if (cmd_type == _last)
        close(*prevpipe);
    waitpid(child_pid, &status, 0);
	if (WIFEXITED(status))
	{
		//exit(WEXITSTATUS(status));
		if (WEXITSTATUS(status) != 0 && cmd_type == _last)
			return ;
			
	}
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGTERM)
			return ;
		else if (WTERMSIG(status) == SIGKILL)
			return ;
	}
}
