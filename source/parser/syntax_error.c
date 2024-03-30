/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:40:56 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/30 13:50:55 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*syntax_error(t_list *lst_tokens, t_list	*lst_env)
{
	if (redirect_error(lst_tokens) || pipe_error(lst_tokens))
	{
		printf("Syntax error\n");
		update_env_list(lst_env, "?", "2: command not found");
	}
	return (lst_tokens);
}

int	redirect_error(t_list	*lst_tokens)
{
	if (output_error(lst_tokens) || input_error(lst_tokens)
		|| append_error(lst_tokens))
		return (1);
	return (0);
}

int	pipe_error(t_list	*lst_tokens)
{
	if (check_first_pipe(lst_tokens) || check_last_pipe(lst_tokens))
		return (1);
	return (0);
}
