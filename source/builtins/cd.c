/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:34:21 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/07 13:50:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

/*
	- [ ] Falta implementar '~' e '/'
	- [ ] Está com falha de segmentação quando tento expandir alguma variável
*/

/*int	mini_cd(t_list *token)
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
*/
