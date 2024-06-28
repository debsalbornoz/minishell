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

static void	test_redirects(t_list *exec, t_list *envp,
				int (*function)(char **));

/*
	- [x] Obs.: implementar verificação de erros atualizando a variavel
		de ambiente '?'.
	- [x] implementar 'cd'.
		- [ ] Obs.: verificar a atualização da variável de ambiente
			'OLDPWD' e 'PWD'.
	- [x] implementar pwd;
	- [x] implementar 'echo'
	- [x] implementar 'exit'
		- [ ] Obs.: Em 'exit' falta implementar parâmetro numérico.
	- [ ] implementar 'unset'
	- [x] implementar 'export'
		- [ ] Obs.: Em 'export' falta implementar alterações de variáveis.
	- [x] implementar 'env'
		- [ ] Obs.: Em 'env' falta implementar alterações de variáveis.
*/

int	builtins(t_list *exec, t_list *envp)
{
	char	**command_table;

	command_table = exec->node->data->exec->command_table;
	if (!ft_strcmp(*command_table, "cd"))
		return (test_redirects(exec, envp, mini_cd), 0);
	else if (!ft_strcmp(*command_table, "pwd"))
		return (test_redirects(exec, envp, mini_pwd), 0);
	else if (!ft_strcmp(*command_table, "echo"))
		return (test_redirects(exec, envp, mini_echo), 0);
	else if (!ft_strcmp(*command_table, "unset"))
		return (mini_unset(), 0);
	else if (!ft_strcmp(*command_table, "env"))
		return (mini_env(envp), 0);
	else if (!ft_strcmp(*command_table, "export"))
		return (mini_export(command_table, envp), 0);
	return (mini_exit());
}

static void	test_redirects(t_list *exec, t_list *envp,
				int (*function)(char **))
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(STDIN_FILENO);
	if (fd_in == -1)
	{
		perror("dup stdin");
		return ;
	}
	fd_out = dup(STDOUT_FILENO);
	if (fd_out == -1)
	{
		perror("dup stdout");
		close(fd_in);
		return ;
	}
	handle_redirect(exec->head, envp);
	function(exec->node->data->exec->command_table);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		perror("dup2 stdin");
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		perror("dup2 stdout");
	close(fd_in);
	close(fd_out);
}
