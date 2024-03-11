/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:17 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/11 16:14:17 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*process_redirect(t_list *list, char *input, int i)
{
	if (is_redirect_input(input[i]))
		list = process_redirect_input(list, input, i);
	else if (is_redirect_output(input[i]))
		list = process_redirect_output(list, input, i);
	return (list);
}

t_list	*process_redirect_input(t_list *list, char *input, int i)
{
	if (is_redirect_input(input[i + 1]))
	{
		list = add_node(list, "<<");
		list->node->redirect = HEREDOC;
	}
	else
	{
		list = add_node(list, "<");
		list->node->redirect = INPUT;
	}
	return (list);
}

t_list	*process_redirect_output(t_list *list, char *input, int i)
{
	if (is_redirect_output(input[i + 1]))
	{
		list = add_node(list, ">>");
		list->node->redirect = APPEND;
	}
	else
	{
		list = add_node(list, ">");
		list->node->redirect = OUTPUT;
	}
	return (list);
}
