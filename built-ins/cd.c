/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:33:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/06 10:42:37 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(t_token *token)
{
	DIR				*dir;
    struct dirent	*dp;

	(void)dp;
    if ((dir = opendir (token->cmd[1])) == NULL) {
        perror ("Cannot open .");
        //exit (1);
    }
}