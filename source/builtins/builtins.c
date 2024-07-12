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

static int	handle_redir(t_list *exec, t_list *envp, int ftype, union u_func f);
static int	select_func(t_list *exec, t_list *envp, int ftype, union u_func f);

int	builtins(t_list *exec, t_list *envp)
{
	char	**cmd_table;

	cmd_table = exec->node->data->exec->command_table;
	if (!ft_strcmp(*cmd_table, "cd"))
		return (handle_redir(exec, envp, 0, (union u_func)mini_cd), 0);
	else if (!ft_strcmp(*cmd_table, "pwd"))
		return (handle_redir(exec, envp, 0, (union u_func)mini_pwd), 0);
	else if (!ft_strcmp(*cmd_table, "echo"))
		return (handle_redir(exec, envp, 0, (union u_func)mini_echo), 0);
	else if (!ft_strcmp(*cmd_table, "unset"))
		return (handle_redir(exec, envp, 1, (union u_func)mini_unset), 0);
	else if (!ft_strcmp(*cmd_table, "env"))
		return (handle_redir(exec, envp, 2, (union u_func)mini_env), 0);
	else if (!ft_strcmp(*cmd_table, "export"))
		return (handle_redir(exec, envp, 1, (union u_func)mini_export), 0);
	return (handle_redir(exec, envp, 1, (union u_func)mini_exit), 1);
}

static int	handle_redir(t_list *exec, t_list *envp, int ftype, union u_func f)
{
	int		fd_in;
	int		fd_out;
	char	*value;

	value = NULL;
	fd_in = dup(STDIN_FILENO);
	if (fd_in == -1)
		return (perror("dup stdin"), -1);
	fd_out = dup(STDOUT_FILENO);
	if (fd_out == -1)
		return (perror("dup stdout"), close(fd_in), -1);
	handle_redirect(exec->head, envp, fd_in, fd_out);
	value = ft_itoa(select_func(exec, envp, ftype, f));
	update_env_list(envp, "?", value);
	free(value);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		perror("dup2 stdin");
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		perror("dup2 stdout");
	return (close(fd_in), close(fd_out), 0);
}

static int	select_func(t_list *exec, t_list *envp, int ftype, union u_func f)
{
	char	**cmd_table;

	cmd_table = exec->node->data->exec->command_table;
	if (!ftype)
		return (f.f_cmd_table(cmd_table));
	if (ftype == 1)
		return (f.f_cmd_table_n_env_list(cmd_table, envp));
	return (f.f_env_list(envp));
}
