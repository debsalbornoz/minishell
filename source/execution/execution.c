/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/09 19:24:01 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	execute_builtins(t_node *exec, t_list *envp);
static int	handle_builtins(char **cmd_table,
				t_list *envp, int type, union u_func f);

int	execute(t_list *lst_tokens, t_list *lst_exec,
	t_list *lst_env, char *input)
{
	int	status;

	status = 0;
	lst_exec = create_lst_exec(lst_tokens, lst_exec, lst_env);
	if (!lst_exec)
		return (0);
	if (is_simple_command(lst_tokens))
	{
		if (is_builtins(lst_tokens->node->data->token->type))
			status = builtins(lst_exec, lst_env);
		else
		{
			execute_simple_command(lst_exec, lst_tokens, lst_env, input);
			close_fds();
		}
	}
	else
		execute_multiple_commands(lst_exec, lst_tokens, lst_env, input);
	if (lst_exec->node)
		lst_exec->node = lst_exec->head;
	return (release_memory(lst_tokens, lst_exec, input), status);
}

int	handle_execution(t_node *exec, t_list *envp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execute_builtins(exec, envp))
		return (-1);
	if (!execute_builtins(exec, envp))
	{
		if (validate_command(exec))
		{

			if (execve(exec->data->exec->path,
					exec->data->exec->command_table,
					exec->data->exec->envp) == -1)
				return (-1);
		}
		if (exec->data->exec->command_table
			&& exec->data->exec->path == NULL
			&& ft_strncmp("126", ft_get_env("?"), 3) != 0)
		{
			update_env_list(envp, "?", "127");
			ft_putstr_fd("command not found\n", 2);
			return (-1);
		}
	}
	return (0);
}

void	restore_file_descriptors(int fd_in, int fd_out)
{
	dup2(fd_in, 0);
	dup2(fd_out, 1);
}

static int	execute_builtins(t_node *exec, t_list *envp)
{
	char	**cmd_table;

	cmd_table = exec->data->exec->command_table;
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

static int	handle_builtins(char **cmd_table,
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
