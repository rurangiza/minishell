/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:50:23 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/30 11:13:12 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* check whether a string {cmd} matches with the list of built-ins */
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (FALSE);
	if ((ft_strncmp(cmd, "echo", 4) == 0 && !cmd[4])
		|| (ft_strncmp(cmd, "cd", 2) == 0 && !cmd[2])
		|| (ft_strncmp(cmd, "pwd", 3) == 0 && !cmd[3])
		|| (ft_strncmp(cmd, "export", 6) == 0 && !cmd[6])
		|| (ft_strncmp(cmd, "unset", 5) == 0 && !cmd[5])
		|| (ft_strncmp(cmd, "env", 3) == 0 && !cmd[3])
		|| (ft_strncmp(cmd, "exit", 4) == 0 && !cmd[4]))
		return (TRUE);
	return (FALSE);
}

/* Check if current item in environemnt is the target */
int	is_variable_to_be_deleted(char *target, char *source)
{
	int	src_len = ft_strlen(source);
	
	if (ft_strncmp(target, source, src_len) == 0 && target[src_len] == '=')
		return (TRUE);
	return (FALSE);
}

/* Check whether a variable {token} is in the global environment */
int is_in_environment(char *variable, t_prompt *prompt)
{
    int index;
    int variable_length;

    variable_length = ft_strlen(variable);
    index = 0;
    while (prompt->envp[index])
    {
        if (ft_strncmp(prompt->envp[index], variable, variable_length) == 0
            && prompt->envp[index][variable_length] == '=')
            return (1);
        index++;
    }
    return (0);
}

int	is_special_symbol(char *directory)
{
	if (ft_strlen(directory) != 1)
		return (0);
	if (directory[0] == '-' 
		|| directory[0] == '~'
		|| directory[0] == '/')
	{
		return (1);
	}
	return (0);
}

int	is_valid_identifier(char *str)
{
	int index;

	index = 0;
	if (str)
	{
		while (str[index])
		{
			if (index == 0 && !ft_isalpha(str[index]))
				return (0);
			if (!ft_isalnum(str[index]) && str[index] != '_')
				return (0);
			index++;
		}
	}
	return (1);
}

int	is_directory(char *path, struct stat stat_buffer)
{
	int	file_status;
	
	file_status = stat(path + 2, &stat_buffer);
	if (file_status == 0)
	{
        if (S_ISDIR(stat_buffer.st_mode))
            return (TRUE);
        return (FALSE);
	}
	return (FALSE);
}


int is_executable(char *path, struct stat stat_buffer) {
	if (ft_strncmp("./", path, 2) == 0)
	{
		if (stat(path + 2, &stat_buffer) == -1) {
			return (FALSE);
		}
		return (stat_buffer.st_mode & S_IXUSR) != 0;
	}
	return (FALSE);
}

int	is_unexpected_token(char *token)
{
	if (!token && !token[0])
		return (-1);
	// `&`, `(`, `)`, `}`,  
	if (token[0] == ')' || token[0] == '&' || token[0] == '}')
		return (TRUE);
	return (FALSE);
}

int	is_empty_pipe(int read_end)
{
	int	nbytes;

	if (ioctl(read_end, FIONREAD, &nbytes) < 0)
		return (-1);
	else if (nbytes == 0)
		return (1);
	return (0);
}


void	check_user_input(char *input)
{
	if (!input)
		exit (0);
}