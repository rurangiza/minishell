/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 09:38:06 by akorompa          #+#    #+#             */
/*   Updated: 2023/04/05 10:54:59 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_token(char *str, int i, int *count)
{
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
	{
		if (str[i + 1] && !(str[i + 1] == '|' || str[i + 1] == '>'
				|| str[i + 1] == '<'))
			(*count)++;
		i++;
	}
	return (i);
}

int	found_sep(char *str, int i, int *count, char sep)
{
	(*count)++;
	if (str[i + 1] == sep)
		i++;
	if (str[i + 1] && str[i + 1] != sep)
		(*count)++;
	i++;
	return (i);
}

int	len_utils(char *str, int *len, int i, char sep)
{
	i++;
	(*len)++;
	while (str[i] && str[i] != sep)
	{
		i++;
		(*len)++;
	}
	return (i);
}

int	get_nb_token(char *str)
{
	int	i;
	int	count;

	count = 1;
	i = 0;
	if (str[i] && str[1] == '\0')
		return (1);
	i = check_token(str, i, &count);
	while (str[i])
	{
		if (str[i] == '\'')
			i = skip_quote(str, i, '\'');
		if (str[i] == '\"')
			i = skip_quote(str, i, '\"');
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			i = found_sep(str, i, &count, str[i]);
		if (!str[i])
			break ;
		i++;
	}
	return (count);
}
