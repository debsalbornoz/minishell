/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:40:56 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/29 18:47:01 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*syntax_error(t_list *lst_tokens, t_list	*lst_env)
{
	lst_tokens = pipe_error(lst_tokens, lst_env);
	lst_tokens = redirect_error(lst_tokens, lst_env);
	return (lst_tokens);
}

t_list	*pipe_error(t_list	*lst_tokens, t_list	*lst_env)
{
	int	flag;

	flag = 0;
	if (lst_tokens)
	{
		if (lst_tokens->head->data->token->type == PIPE)
			flag = 1;
		while (lst_tokens->node)
		{
			if (lst_tokens->node->next == NULL
				&& lst_tokens->node->data->token->type == PIPE)
				flag = 1;
			lst_tokens->node = lst_tokens->node->next;
		}
		if (flag == 1)
		{
			printf("Syntax error\n");
			update_env_list(lst_env, "?", "2: command not found");
		}
	}
	return (lst_tokens);
}

t_list	*redirect_error(t_list	*lst_tokens, t_list	*lst_env)
{
	if (output_error(lst_tokens) || input_error(lst_tokens))
	{
		update_env_list (lst_env, "?", "2: command not found");
		printf("Syntax error\n");
	}
	return (lst_tokens);
}

int	output_error(t_list	*lst_tokens)
{
	int	flag;

	flag = 0;
	if (lst_tokens)
		lst_tokens->node = lst_tokens->head;
	while (lst_tokens->node)
	{
		if (lst_tokens->node->data->token->type == OUTPUT)
		{
			if (lst_tokens->node->next)
			{
				if (is_redirect_2(lst_tokens->node->next->data->token->type))
					flag = 1;
			}
		}
			lst_tokens->node = lst_tokens->node->next;
	}
	lst_tokens->node = lst_tokens->head;
	return (flag);
}

int	input_error(t_list	*lst_tokens)
{
	int	flag;

	flag = 0;
	if (lst_tokens)
		lst_tokens->node = lst_tokens->head;
	while (lst_tokens->node)
	{
		if (lst_tokens->node->data->token->type == INPUT)
		{
			if (lst_tokens->node->next)
			{
				if (is_redirect_2(lst_tokens->node->next->data->token->type))
					flag = 1;
			}
		}
			lst_tokens->node = lst_tokens->node->next;
	}
	lst_tokens->node = lst_tokens->head;
	return (flag);
}
