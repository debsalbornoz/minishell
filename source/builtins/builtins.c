/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:33:53 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/23 16:01:52 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/minishell.h"

static	void test_redirects(t_list *exec, t_list *envp,t_list *token, void (function)(t_list *));

/*
	- [x] implementar pwd;
	- [x] implementar 'echo'
	- [x] implementar 'cd'.
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
	// handle_redirect(exec->head, envp);
	if (token->node->data->token->type == CD)
		return (mini_cd(token), 0);
	else if (token->node->data->token->type == PWD)
		return (mini_pwd(), 0);
	else if (token->node->data->token->type == ENV)
		return (mini_env(envp), 0);
	else if (token->node->data->token->type == ECHO)
		return (test_redirects(exec, envp,token, mini_echo), 0);
	else if (token->node->data->token->type == UNSET)
		return (mini_unset(), 0);
	else if (token->node->data->token->type == EXPORT)
		return (mini_export(exec->node->data->exec->command_table, envp), 0);
	return (mini_exit());
}

static void test_redirects(t_list *exec, t_list *envp, t_list *token, void (*function)(t_list *))
{
	int fd_in = dup(STDIN_FILENO);
	if (fd_in == -1)
	{
		perror("dup stdin");
		return;
	}
	int fd_out = dup(STDOUT_FILENO);
	if (fd_out == -1)
	{
		perror("dup stdout");
		close(fd_in);
		return;
	}
	handle_redirect(exec->head, envp);
	function(token);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		perror("dup2 stdin");
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		perror("dup2 stdout");
	close(fd_in);
	close(fd_out);
}

