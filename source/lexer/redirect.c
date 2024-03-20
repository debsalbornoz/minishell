/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:17 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/20 13:20:22 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*process_redirect(t_list *lst_tokens, char *input, int i)
{
	if (is_redirect_input(input[i]))
		lst_tokens = process_redirect_input(lst_tokens, input, i);
	else if (is_redirect_output(input[i]))
		lst_tokens = process_redirect_output(lst_tokens, input, i);
	return (lst_tokens);
}

t_list	*process_redirect_input(t_list *lst_tokens, char *input, int i)
{
	if (is_redirect_input(input[i + 1]))
	{
		lst_tokens = add_node(lst_tokens);
		lst_tokens->node->data = ft_calloc(1, sizeof(union u_data));
		lst_tokens->node->data->token = ft_calloc(1, sizeof(t_token));
		lst_tokens->node->data->token->value = ft_strdup("<<");
		lst_tokens->node->data->token->type = HEREDOC;
	}
	else
	{
		lst_tokens = add_node(lst_tokens);
		lst_tokens->node->data = ft_calloc(1, sizeof(union u_data));
		lst_tokens->node->data->token = ft_calloc(1, sizeof(t_token));
		lst_tokens->node->data->token->value = ft_strdup("<");
		lst_tokens->node->data->token->type = INPUT;
	}
	return (lst_tokens);
}

t_list	*process_redirect_output(t_list *lst_tokens, char *input, int i)
{
	if (is_redirect_output(input[i + 1]))
	{
		lst_tokens = add_node(lst_tokens);
		lst_tokens->node->data = ft_calloc(1, sizeof(union u_data));
		lst_tokens->node->data->token = ft_calloc(1, sizeof(t_token));
		lst_tokens->node->data->token->value = ft_strdup(">>");
		lst_tokens->node->data->token->type = APPEND;
	}
	else
	{
		lst_tokens = add_node(lst_tokens);
		lst_tokens->node->data = ft_calloc(1, sizeof(union u_data));
		lst_tokens->node->data->token = ft_calloc(1, sizeof(t_token));
		lst_tokens->node->data->token->value = ft_strdup(">");
		lst_tokens->node->data->token->type = OUTPUT;
	}
	return (lst_tokens);
}
