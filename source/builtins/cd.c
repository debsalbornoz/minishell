/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jackson <jackson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:34:21 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/08 15:41:33 by jackson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	mini_cd(t_list *token)
{
	char	cwd[2048];

	if (token->node->next)
		token->node = token->node->next;
	if (token->node->next && token->node->next->data->token->type != PIPE)
		return (printf("cd: excessive number of arguments\n"), 1);
	if (!ft_strcmp(token->node->data->token->value, "~")
		|| !ft_strcmp(token->node->data->token->value, "-"))
	{
		if (chdir(getenv("HOME")))
			return (perror("chdir"), 1);
	}
	else if (chdir(token->node->data->token->value))
		return (perror("chdir"), 1);
	if (!getcwd(cwd, sizeof(cwd)))
		return (perror("getcwd"), 1);
	return (0);
}
