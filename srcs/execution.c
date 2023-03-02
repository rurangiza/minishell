/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:01:10 by Arsene            #+#    #+#             */
/*   Updated: 2023/03/02 11:38:27 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	execute_v2(t_token *token, int nbr_of_pipes)
// {
// 	int	index = 0, **pipends, prevpipe = 69, cmd_type;

// 	// Allocate memory for each pipes
// 	pipends = malloc(sizeof(int *) * nbr_of_pipes - 1);
// 	for (int i = 0; i < nbr_of_pipes - 1; i++)
// 		pipends[i] = malloc(sizeof(int) * 2);

// 	// Execute all commands
// 	while (index < nbr_of_pipes)
// 	{
// 		cmd_type = get_cmd_type(nbr_of_pipes, index);
// 		if (pipe(pipends[index]) == -1)
// 			exit_msg();
//         pid_t pid = fork();
//         if (pid == -1)
//             exit_msg();
//         else if (pid == 0)
// 		{
// 			if (token->infile != -1)
// 				redirect_in(token);
// 			if (token->outfile != -1)
// 				redirect_out(token);
// 			execve(token->cmd_path, token->cmd, token->envp);
// 			exit_msg();
// 		}
//         parent_process(pid, cmd_type, pipends[index], &prevpipe);
// 		index++;
// 	}
// }

void	execute(t_token *token, int nbr_of_pipes)
{
	int	index = 0, pipends[2], prevpipe = 69, cmd_type;

	int cat_counter = 0;
	while (index < nbr_of_pipes)
	{
        cmd_type = get_cmd_type(nbr_of_pipes, index);
        if (cmd_type == _middle)
		{
			if (pipe(pipends) == -1)
				exit_msg();
		}
        pid_t pid = fork();
        if (pid == -1)
            exit_msg();
        else if (pid == 0)
		{
			if (cmd_type == _single) 
				single_child(&token[index]);
			else if (cmd_type == _last)
				last_child(&token[index], prevpipe);
			else
				middle_child(&token[index], index, prevpipe, pipends);
		}
        parent_process(pid, cmd_type, pipends, &prevpipe);
		index++;
	}
	
	index = 0;
	if (index == 0 && ft_strncmp(token[index].cmd[0], "cat", 3) == 0 && token[index].cmd[1] == NULL)
	{
		while (ft_strncmp(token[index].cmd[0], "cat", 3) == 0 && token[index].cmd[1] == NULL)
		{
			cat_counter++;
			index++;
		}
	}
	
	char *tmp;
	for (int i = 0; i < cat_counter; i++)
	{
		tmp = get_next_line(STDIN_FILENO);
		free(tmp);
	}
}

int get_cmd_type(int size, int index)
{
    if (size == 1)
        return (_single);
    else if (index == size - 1 && index != 0)
        return (_last);
    return (_middle);
}

void	single_child(t_token *token)
{
	int	error_code;

	if (token->infile != -1)
		redirect_in(token);
	if (token->outfile != -1)
		redirect_out(token);
	error_code = execve(token->cmd_path, token->cmd, token->envp);
	if (error_code == -1)
		exit_msg();
}

void	last_child(t_token *token, int prevpipe)
{
	int error_code;

	if (token->infile != -1)
		redirect_in(token);
	else
		dup2(prevpipe, STDIN_FILENO);
	close(prevpipe);
	if (token->outfile != -1)
		redirect_out(token);
	error_code = execve(token->cmd_path, token->cmd, token->envp);
	if (error_code == -1)
		exit_msg();
}

void	middle_child(t_token *token, int index, int prevpipe, int *pipends)
{
	int error_code;

	close(pipends[READ]);
	if (token->infile != -1)
		redirect_in(token);
	else if (index > 0)
		dup2(prevpipe, STDIN_FILENO);
	if (index != 0)
		close(prevpipe);

	if (ft_strncmp(token->cmd[0], "cat", 3) == 0 && token->cmd[1] == NULL)
		exit(0);

	if (token->outfile != -1)
		redirect_out(token);
	else
	{
		if (dup2(pipends[WRITE], STDOUT_FILENO) == -1)
			printf("Error with DUP2()\n");
	}	

	close(pipends[WRITE]);
	
	error_code = execve(token->cmd_path, token->cmd, token->envp);
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
