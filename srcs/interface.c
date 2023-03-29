/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:11:11 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/29 11:17:41 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_readline(void)
{
	char	*user_input;
	char	*level;
	
	level = getenv_custm("SHLVL");
	if (level)
		printf(CGRAY CBOLD"[lvl:%s] "CRESET, level + 1);
	user_input = readline(CGREEN CBOLD"minishell $> "CRESET);
	return (user_input);
}