/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:11:33 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/23 13:11:28 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int arg_count, char **arg_list)
{
	(void)arg_count;
	(void)arg_list;

	if (arg_count != 1)
	{
		write(1, "Usage: ./minishell\n", 19);
		return (EXIT_FAILURE);
	}
	char *str = readline(CYELLOW"minishell $ "CRESET);
	printf("%s\n", str);
	return (0);
}