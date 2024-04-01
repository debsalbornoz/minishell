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
	lst_tokens = syntax_error(lst_tokens, lst_env);
	return (lst_tokens);
}
