/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_delimiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:46:06 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/07 12:42:16 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_delimiter(char chr)
{
	return (is_space(chr) || is_redirect(chr)
		|| is_pipe(chr) || is_dollar(chr));
}

int	is_space(char chr)
{
	return (chr == ' ' || chr == '\t');
}

int	is_pipe(char chr)
{
	return (chr == '|');
}

int	is_dollar(char chr)
{
	return (chr == '$');
}
