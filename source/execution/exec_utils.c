/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:59:18 by codespace         #+#    #+#             */
/*   Updated: 2024/05/16 16:34:39 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_file(int type)
{
	if (type == OUTPUT_FILE || type == INPUT_FILE
		|| type == APPEND_FILE || type == HEREDOC_KEY)
		return (1);
	return (0);
}

int	is_file_redirect_or_pipe(int type)
{
	if (find_file(type) || find_redirect(type) || type == PIPE)
		return (1);
	else
		return (0);
}
