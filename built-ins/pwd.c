/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:19:36 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/02 15:04:27 by akorompa         ###   ########.fr       */
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
		exit (1);
	}
	str = getcwd(NULL, 0);
	printf("%s\n", str);
	free(str);
	exit (0);
}