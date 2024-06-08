/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jackson <jackson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 23:26:22 by jackson           #+#    #+#             */
/*   Updated: 2024/06/07 23:40:01 by jackson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

int		is_command(int type)
{
	return (type == COMMAND);
}

int		is_builtins(int type)
{
	return (type >= ECHO && type <= EXIT);
}
