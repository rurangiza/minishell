/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:11:11 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/21 11:01:34 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_readline(void)
{
	char	*user_input;

	user_input = NULL;
	if (g_exitcode == 0)
		user_input = readline(
				"\x1b[32m•\033[0m \x1b[1m\x1b[37mminishell $ "CRESET);
	else
		user_input = readline(
				"\x1b[31m•\033[0m \x1b[1m\x1b[37mminishell $ "CRESET);
	return (user_input);
}
