/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:19:36 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/31 11:49:11 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(t_token *token)
{
	char *str;
	int i;

	i = 1;
	if (token->cmd[i])
	{
		printf("pwd: too many arguments\n");
		g_exitcode = 0;
		return ;
	}
	str = getcwd(NULL, 0);
	printf("%s\n", str);
	free(str);
}
