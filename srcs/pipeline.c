/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:33:37 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/03 16:34:49 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	createpipe(t_prompt *prompt, int cmd_type)
{
	if (cmd_type == _middle)
	{
		if (pipe(prompt->pipends) == -1)
			exit_msg();
	}
}
