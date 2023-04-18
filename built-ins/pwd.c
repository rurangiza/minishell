/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:19:36 by akorompa          #+#    #+#             */
/*   Updated: 2023/04/17 15:18:10 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(t_token *token)
{
	char	*str;

	(void)token;
	str = getcwd(NULL, 0);
	printf("%s\n", str);
	free(str);
}
