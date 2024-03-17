/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:17 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/17 15:08:38 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*process_redirect(t_list *tokens, char *input, int i)
{
	if (is_redirect_input(input[i]))
		tokens = process_redirect_input(tokens, input, i);
	else if (is_redirect_output(input[i]))
		tokens = process_redirect_output(tokens, input, i);
	return (tokens);
}

t_list	*process_redirect_input(t_list *tokens, char *input, int i)
{
	if (is_redirect_input(input[i + 1]))
	{
		tokens = add_node(tokens);
		tokens->node->data = ft_calloc(1, sizeof(int));
		tokens->node->value = ft_strdup("<<");
		tokens->node->data->type = HEREDOC;
	}
	else
	{
		tokens = add_node(tokens);
		tokens->node->data = ft_calloc(1, sizeof(int));
		tokens->node->value = ft_strdup("<");
		tokens->node->data->type = INPUT;
	}
	return (tokens);
}

t_list	*process_redirect_output(t_list *tokens, char *input, int i)
{
	if (is_redirect_output(input[i + 1]))
	{
		tokens = add_node(tokens);
		tokens->node->data = ft_calloc(1, sizeof(int));
		tokens->node->value = ft_strdup(">>");
		tokens->node->data->type = APPEND;
	}
	else
	{
		tokens = add_node(tokens);
		tokens->node->data = ft_calloc(1, sizeof(int));
		tokens->node->value = ft_strdup(">");
		tokens->node->data->type = OUTPUT;
	}
	return (tokens);
}
