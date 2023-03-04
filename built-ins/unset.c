/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:33:00 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/04 08:42:17 by Arsene           ###   ########.fr       */
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
*/

void	unset(t_token *token)
{
	// Checks whether variable exists
	if (!token->cmd[1] || getenv(token->cmd[1]) == NULL)
		exit(EXIT_FAILURE);

	// Find position
	int position = 0;
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
	free(g_environment[position++]);
	while (g_environment[position])
	{
		g_environment[position - 1] = ft_strdup(g_environment[position]);
		free(g_environment[position]);
		position++;
	}
	g_environment[position] = NULL;
	
	// printf(CBLUE"---- UNSET() -----\n"CRESET);
	// for (int i = 0; i < position - 1; i++)
	// 	printf("[%i] %s\n", i, g_environment[i]);
	return ;
	
	printf("------------ Hello\n");


	// // Save content of environment in buffer except the line I'll delete
	// int size = 0;
	// while (environment[size]) // Count number of lines minus one (the one I'll remove)
	// 	size++;
	// size -= 1;
	// char **buffer = malloc(sizeof(char *) * (size + 1)); // Allocate matrix (- 1)

	// int src_index = 0;
	// int buffer_index = 0;
	// while (src_index < size && environment[src_index]) // Allocate memory for new table
	// {
	// 	// Sauter la variable que je veux supprimer
	// 	if (ft_strncmp(environment[src_index], token->cmd[1], ft_strlen(token->cmd[1])) == 0
	// 		&& environment[src_index][ft_strlen(token->cmd[1])] == '=')
	// 	{
	// 		src_index++;
	// 	}
	// 	// Allouer le reste
	// 	buffer[buffer_index] = ft_strdup(environment[src_index]);

	// 	buffer_index++;
	// 	src_index++;
	// }
	// buffer[buffer_index] = NULL;

	// // Free old environment
	// int index = 0;
	// while (environment[index])
	// 	free(environment[index++]);
	// free(environment);

	// // Save new environment
	// environment = buffer;
	
	// for (int i = 0; environment[i]; i++)
	// 	printf("%s\n", environment[i]);
	//exit(EXIT_SUCCESS);
}
