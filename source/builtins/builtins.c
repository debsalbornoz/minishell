/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 07:54:54 by jackson           #+#    #+#             */
/*   Updated: 2024/05/30 18:36:59 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

/*
	- [x] implementar pwd;
	- [x] implementar 'echo'
	- [x] implementar 'cd'.
		- [ ] Em 'cd' falta retornar o erro se falha ao mudar de diretório.
	- [x] implementar 'exit'
		- [ ] Obs.: Em 'exit' falta implementar parâmetro numérico.
	- [ ] implementar 'unset'
	- [x] implementar 'export'
		- [ ] Obs.: Em 'export' falta implementar alterações de variáveis.
	- [x] implementar 'env'
		- [ ] Obs.: Em 'env' falta implementar alterações de variáveis.
*/

int	builtins(t_list *token, t_list *exec, t_list *envp)
{
	(void)exec;
	if (token->node->data->token->type == CD)
		return (mini_cd(token), 0);
	else if (token->node->data->token->type == PWD)
		return (mini_pwd(), 0);
	else if (token->node->data->token->type == ENV)
		return (mini_env(envp), 0);
	else if (token->node->data->token->type == ECHO)
		return (mini_echo(token), 0);
	else if (token->node->data->token->type == UNSET)
		return (mini_unset(), 0);
	else if (token->node->data->token->type == EXPORT)
		return (mini_export(envp), 0);
	return (mini_exit());
}
