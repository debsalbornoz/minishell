/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/20 18:28:31 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_builtins(t_node *exec, t_list *envp)
{
	char	**cmd_table;

	cmd_table = exec->data->exec->command_table;
	if (!cmd_table)
		return (-1);
	if (!ft_strcmp(*cmd_table, "cd"))
		return (handle_builtins(cmd_table, envp, 0, (union u_func)mini_cd));
	else if (!ft_strcmp(*cmd_table, "pwd"))
		return (handle_builtins(cmd_table, envp, 0, (union u_func)mini_pwd));
	else if (!ft_strcmp(*cmd_table, "echo"))
		return (handle_builtins(cmd_table, envp, 0, (union u_func)mini_echo));
	else if (!ft_strcmp(*cmd_table, "unset"))
		return (handle_builtins(cmd_table, envp, 1, (union u_func)mini_unset));
	else if (!ft_strcmp(*cmd_table, "env"))
		return (handle_builtins(cmd_table, envp, 2, (union u_func)mini_env));
	else if (!ft_strcmp(*cmd_table, "export"))
		return (handle_builtins(cmd_table, envp, 1,
				(union u_func)mini_export));
	else if (!ft_strcmp(*cmd_table, "exit"))
		return (handle_builtins(cmd_table, envp, 1,
				(union u_func)mini_exit), 2);
	return (0);
}

int	handle_builtins(char **cmd_table,
				t_list *envp, int type, union u_func f)
{
	char	*value;

	value = 0;
	if (!type)
		return (value = ft_itoa(f.f_cmd_table(cmd_table)),
			update_env_list(envp, "?", value), free(value), 1);
	if (type == 1)
		return (value = ft_itoa(f.f_cmd_table_n_env_list(cmd_table, envp)),
			update_env_list(envp, "?", value), free(value), 1);
	return (value = ft_itoa(f.f_env_list(envp)),
		update_env_list(envp, "?", value), free(value), 1);
}
