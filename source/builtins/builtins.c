/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:33:53 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/29 16:32:36 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/minishell.h"

static void	hadle_redir(t_list *exec, t_list *envp, int ftype, union u_func f);
static int	select_func(t_list *exec, t_list *envp, int ftype, union u_func f);

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
	char	**cmd_table;

	cmd_table = exec->node->data->exec->command_table;
	if (!ft_strcmp(*cmd_table, "cd"))
		return (hadle_redir(exec, envp, 0, (union u_func)mini_cd), 0);
	else if (!ft_strcmp(*cmd_table, "pwd"))
		return (hadle_redir(exec, envp, 0, (union u_func)mini_pwd), 0);
	else if (!ft_strcmp(*cmd_table, "echo"))
		return (hadle_redir(exec, envp, 0, (union u_func)mini_echo), 0);
	else if (!ft_strcmp(*cmd_table, "unset"))
		return (hadle_redir(exec, envp, 1, (union u_func)mini_unset), 0);
	else if (!ft_strcmp(*cmd_table, "env"))
		return (mini_env(envp), 0);
	else if (!ft_strcmp(*cmd_table, "export"))
		return (hadle_redir(exec, envp, 1, (union u_func)mini_export), 0);
	return (mini_exit());
}

static void	hadle_redir(t_list *exec, t_list *envp, int ftype, union u_func f)
{
	int		fd_in;
	int		fd_out;
	char	*value;

	value = NULL;
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
	handle_redirect(exec->head, envp, fd_in, fd_out);
	value = ft_itoa(select_func(exec, envp, ftype, f));
	update_env_list(envp, "?", value);
	free(value);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		perror("dup2 stdin");
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		perror("dup2 stdout");
	close(fd_in);
	close(fd_out);
}

static int	select_func(t_list *exec, t_list *envp, int ftype, union u_func f)
{
	char	**cmd_table;

	cmd_table = exec->node->data->exec->command_table;
	if (!ftype)
		return (f.f_cmd_table(cmd_table));
	return (f.f_cmd_table_n_env_list(cmd_table, envp));
}
