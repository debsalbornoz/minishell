/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jackson <jackson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 07:54:54 by jackson           #+#    #+#             */
/*   Updated: 2024/05/28 03:58:50 by jackson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

/*
	- [x] implementar pwd;
	- [x] implementar 'echo'
	- [x] implementar 'cd'
	- [ ] Em cd falta retornar o erro se falha ao mudar de diretório
	- [ ] implementar 'exit'
	- [ ] implementar 'unset'
	- [ ] implementar 'export'
	- [ ] implementar 'env'
*/

void	builtins(t_list *token, t_list *exec, t_list *envp)
{
	(void)exec;
	(void)envp;
	if (token->node->data->token->type == CD)
		mini_cd(token);
	else if (token->node->data->token->type == PWD)
		mini_pwd();
	else if (token->node->data->token->type == ENV)
		mini_env();
	else if (token->node->data->token->type == EXIT)
		mini_exit();
	else if (token->node->data->token->type == ECHO)
		mini_echo(token);
	else if (token->node->data->token->type == UNSET)
		mini_unset();
	else if (token->node->data->token->type == EXPORT)
		mini_export();
}
