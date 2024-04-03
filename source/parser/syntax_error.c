/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:57:17 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/01 19:57:19 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int syntax_error(t_list *lst_tokens, t_list	*lst_env, char *input)
{
	if (redirect_error(lst_tokens) || pipe_error(lst_tokens))
	{
		printf("Syntax error\n");
		update_env_list(lst_env, "?", "2: command not found");
		free_list(lst_tokens, free_lst_tokens);
		free(input);
		return (1);
	}
	lst_tokens->node = lst_tokens->head;
	return (0);
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
