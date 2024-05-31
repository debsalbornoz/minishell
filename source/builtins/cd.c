/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jackson <jackson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:43:15 by jraupp            #+#    #+#             */
/*   Updated: 2024/05/28 10:18:02 by jackson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

/*
	- [ ] Falta implementar '~' e '/'
	- [ ] Está com falha de segmentação quando tento expandir alguma variável
*/

int	mini_cd(t_list *token)
{
	char	cwd[2048];

	if (token->node->next)
		token->node = token->node->next;
	else
		return (chdir("~"), 0);
	if (token->node->next && token->node->next->data->token->type != PIPE)
	{
		fprintf(stderr, "número excessivo de argumentos\n");
		return (1);
	}
	if (chdir(token->node->data->token->value))
	{
		perror("chdir");
		return (1);
	}
	if (!getcwd(cwd, sizeof(cwd)))
		return (perror("getcwd"), 1);
	return (0);
}
