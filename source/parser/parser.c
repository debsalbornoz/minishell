/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 20:07:44 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/01 20:07:48 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*parsing(t_list *lst_tokens, t_list	*lst_env)
{
	(void)lst_env;
	lst_tokens = syntax_error(lst_tokens, lst_env);
	while(lst_tokens->node)
	{
		lst_tokens->node = new_str(lst_tokens->node);
		printf("%s\n", lst_tokens->node->data->token->value);
		lst_tokens->node = lst_tokens->node->next;
	}
	return (lst_tokens);
}

