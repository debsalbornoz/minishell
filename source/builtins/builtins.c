/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:33:53 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/27 20:03:36 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/minishell.h"

static int	handle_redir(t_list *exec, t_list *envp, int ftype, union u_func f);
static int	select_func(t_list *exec, t_list *envp, int ftype, union u_func f);

int	builtins(t_list *exec, t_list *envp, int fd_in, int fd_out)
{
	char	**cmd_table;

	if (handle_redirect(exec->head, envp, fd_in, fd_out) == -1)
		return (0);
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
	handle_redir(exec, envp, 1, (union u_func)mini_exit);
	if (!ft_strcmp(ft_get_env("?"), "exit"))
		return (update_env_list(envp, "?", "1"), 0);
	return (1);
}

static int	handle_redir(t_list *exec, t_list *envp, int ftype, union u_func f)
{
	char	*value;

	value = NULL;
	if (!ft_strcmp(ft_get_env("?"), "1"))
		return (select_func(exec, envp, ftype, f), 0);
	value = ft_itoa(select_func(exec, envp, ftype, f));
	if (ft_strcmp(ft_get_env("?"), "exit"))
		update_env_list(envp, "?", value);
	free(value);
	return (0);
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
