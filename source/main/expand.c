/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:59:57 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/20 21:10:30 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char  *expand(t_list *lst_env, char *input)
{
	char	signal;
	char	*temp;
	char	*varible;

	signal = 0;
	temp = input;
	while (*temp)
	{
		signal = process_quotes(signal, *temp);
		if (*temp == '$' && !is_single_quote(signal) && *(temp + 1))
		temp++;
	}
	temp = 0;
	return (input);
}
