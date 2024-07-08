/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jackson <jackson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 23:26:22 by jackson           #+#    #+#             */
/*   Updated: 2024/06/08 13:29:24 by jackson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

int	is_command(int type)
{
	return (type == COMMAND);
}

int	is_builtins(int type)
{
	return (type >= ECHO && type <= EXIT);
}

int	is_valid_first_char(char chr)
{
	return ((chr >= 'A' && chr <= 'Z')
		|| (chr >= 'a' && chr <= 'z') || (chr == '_'));
}

int	is_valid_char(char chr)
{
	return (is_valid_first_char(chr)
		|| (chr >= '0' && chr <= '9'));
}
