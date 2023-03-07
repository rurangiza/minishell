/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:33:00 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/07 12:50:17 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * The unset command in a shell program is used to remove a variable
 * or function from the shell's environment.
 * 
 * 
 * getenv: get an environment variable 
 * tgetenv
 * 
 * env: If no utility is specified, env prints out the names and values 
 * of the variables in the environment, with one name/value pair per line.
 * 
*/


void	unset(t_token *token)
{
	// Checks whether variable exists
	if (!token->cmd[1] || getenv(token->cmd[1]) == NULL)
		return ;
	// Save content of environment in buffer except the line I'll delete
	char **copy;

	int size = 0;
	while (g_environment[size])
		size++;
	copy = malloc(sizeof(char *) * (size + 1));

	int src_index = 0;
	int copy_index = 0;
	while (src_index < size && g_environment[src_index])
	{
		if (!is_variable_to_be_deleted(g_environment[src_index], token->cmd[1]))
		{
			copy[copy_index] = ft_strdup(g_environment[src_index]);
			copy_index++;
		}
		src_index++;
	}
	copy[copy_index] = NULL;
	ft_free_matrix(g_environment);

	g_environment = copy;
}


/*
void	unset_shift(t_token *token)
{
	int position;
	
	// Checks whether variable exists
	if (!token->cmd[1] || getenv(token->cmd[1]) == NULL)
		exit(EXIT_FAILURE);

	// Find position
	position = 0;
	while (g_environment[position])
	{
		if (ft_strncmp(g_environment[position], token->cmd[1], ft_strlen(token->cmd[1])) == 0
			&& g_environment[position][ft_strlen(token->cmd[1])] == '=')
		{
			break ;
		}
		position++;
	}
	// Shift elements of the matrix to LEFT
	g_environment[position] = NULL;
	position += 1;
	while (g_environment[position] && position > 0)
	{
		//printf(CYELLOW"[%i] copying... | %s\n"CRESET, position, g_environment[position]);
		
		g_environment[position - 1] = ft_strdup(g_environment[position]);
		//g_environment[position - 1] = g_environment[position];
		g_environment[position] = NULL;
		//free(g_environment[position]);
		position++;
	}
	g_environment[position] = NULL;
	//exit(0);
}
*/