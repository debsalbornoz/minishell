/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:17 by jraupp            #+#    #+#             */
/*   Updated: 2024/05/06 12:31:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	process_delimiter(t_list *lst_tokens, int signal, char *input, int i)
{
	int	delimiter;

	delimiter = 0;
	if (!signal && is_delimiter(input[i]))
	{
		delimiter = 1;
		if (is_redirect(input[i]))
		{
			lst_tokens = process_redirect(lst_tokens, input, i);
			if (is_append(input[i], input[i + 1])
				|| is_heredoc(input[i], input[i + 1]))
				return (2);
		}
		else if (is_pipe(input[i]))
		{
			lst_tokens = add_node(lst_tokens);
			lst_tokens->node->data = ft_calloc(1, sizeof(union u_data));
			lst_tokens->node->data->token = ft_calloc(1, sizeof(t_token));
			lst_tokens->node->data->token->value = ft_strdup("|");
			lst_tokens->node->data->token->type = PIPE;
		}
	}
	return (delimiter);
}


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
