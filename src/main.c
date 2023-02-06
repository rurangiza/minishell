/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:21:06 by Arsene            #+#    #+#             */
/*   Updated: 2023/02/06 14:28:24 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int arg_count, char **arg_list, char **envp)
{
	if (arg_count != 1)
		return (EXIT_FAILURE);
	(void)arg_list;
	
	system("clear");
	//printshell();
	while (TRUE)
	{
		/* Prompt: get user input */
		char *user_input = readline(CBLUE CBOLD"minishell $ "CRESET);
		add_history(user_input);

		/* Parsing: divide into pipes & tokens (commands) */
		char **pipeline = ft_split(user_input, '|');
		int nbr_of_pipes = 0;
		while (pipeline[nbr_of_pipes])
			nbr_of_pipes++;

		//int fdout = open("oufile", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		//int fdin = open("oufile", O_RDONLY , 0644);
		// if (!fdout)
		// 	return (1);
		t_token *tokens = malloc(sizeof(t_token) * nbr_of_pipes);
		for (int i = 0; i < nbr_of_pipes; i++)
		{
			tokens[i].cmd = ft_split(pipeline[i], ' ');
			tokens[i].infile = -1;
			tokens[i].outfile = -1;
			tokens[i].delimiter = "stop";
			tokens[i].envp = envp;
			tokens[i].variable_expdr = TRUE;
		}
		//tokens[0].outfile = fdout;
		tokens[0].infile = HERE_DOC;
		/* Run the commands */
		execute(tokens, nbr_of_pipes);

		/* Terminate program */
		ft_free_matrix(pipeline);
		free(user_input);
		
	}
	return (0);
}


