/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:40:56 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/27 21:47:13 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	syntax_error(t_list *lst_tokens, t_list	*lst_env)
{
	pipe_error(lst_tokens, lst_env);
	output_error(lst_tokens, lst_env);
}

void	pipe_error(t_list	*lst_tokens, t_list	*lst_env)
{
	if (lst_tokens->head->data->token->type == PIPE)
	{
		printf("bash: syntax error near unexpected token `|'");
		update_env_list(lst_env, "?", "2: command not found");
		printf("\n");
	}	
}

void	output_error(t_list	*lst_tokens, t_list	*lst_env)
{
	if (lst_tokens)
		lst_tokens->node = lst_tokens->head;
	while (lst_tokens->node)
	{
		if (lst_tokens->node->data->token->type == OUTPUT)
		{
			if (lst_tokens->node->next)
			{
				if (lst_tokens->node->next->data->token->type == OUTPUT)
					printf("bash: syntax error near unexpected token `>'");
				if (lst_tokens->node->next->data->token->type == INPUT)
					printf("bash: syntax error near unexpected token `<'");
				if (lst_tokens->node->next->data->token->type == APPEND)
					printf("bash: syntax error near unexpected token `>>'");
				if (lst_tokens->node->next->data->token->type == HEREDOC)
					printf("bash: syntax error near unexpected token `<<'");
				if (is_redirect_2(lst_tokens->node->next->data->token->type))
					update_env_list (lst_env,"?", "2: command not found");
			}
		}
			lst_tokens->node = lst_tokens->node->next;
	}
}
