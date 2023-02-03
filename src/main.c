/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:21:06 by Arsene            #+#    #+#             */
/*   Updated: 2023/02/03 14:11:46 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int arg_count, char **arg_list)
{
	if (arg_count != 1)
		return (EXIT_FAILURE);
	(void)arg_list;
	
	system("clear");
	while (TRUE)
	{
		/* Prompt: get user input */
		char *user_input = readline("\033[1mminishell $\033[0m ");
		add_history(user_input);
		
		/* Parsing: divide into pipes & tokens (commands) */
		char **pipeline = ft_split(user_input, '|');
		int pipeline_size = 0;
		while (pipeline[pipeline_size])
			pipeline_size++;
		t_token *tokens = malloc(sizeof(t_token) * pipeline_size);
		for (int i = 0; i < pipeline_size; i++)
		{
			tokens[i].cmd = ft_split(pipeline[i], ' ');
			tokens[i].infile = -1;
			tokens[i].outfile = -1;
		}

		/* Run the commands */
		execute(tokens, pipeline_size);
		
		/* Terminate program */
		ft_free_matrix(pipeline);
		free(user_input);
	}
	return (0);
}


