/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jackson <jackson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 20:23:46 by jackson           #+#    #+#             */
/*   Updated: 2024/05/28 10:17:27 by jackson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_command(int type)
{
	return (type >= COMMAND && type <= EXIT);
}

int	is_builtins(int type)
{
	return (type >= ECHO && type <= EXIT);
}
