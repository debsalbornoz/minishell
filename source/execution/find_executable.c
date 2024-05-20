/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/20 17:50:23 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fill_path_in_exec(t_list *tokens, t_list *exec, t_list *envp)
{
	char		*path;

	tokens->node = tokens->head;
	exec->node = exec->head;
	envp->node = envp->head;
	path = NULL;
	if (!exec || !tokens || !envp)
		return ;
	while (exec->node)
	{
		path = validate_path(exec->node->data->execution->command_table,
				exec->node, envp);
		exec->node->data->execution->path = ft_strdup(path);
		free(path);
		exec->node = exec->node->next;
	}
	exec->node = exec->head;
}

char	*validate_path(char **command_table, t_node *exec, t_list *envp)
{
	char	**path_array;
	char	*absolute_path;

	(void)exec;
	path_array = split_path(envp);
	absolute_path = NULL;
	envp->node = envp->head;
	if (is_absolute_path(command_table))
	{
		absolute_path = ft_strdup(command_table[0]);
		free_matrix(path_array);
		return (absolute_path);
	}
	else
		absolute_path = create_absolute_path(path_array,
				command_table, envp, exec);
	return (absolute_path);
}

int	is_absolute_path(char **command_table)
{
	if (!ft_strncmp(command_table[0], "/", 1)
		|| !ft_strncmp(command_table[0], "./", 2))
		return (1);
	return (0);
}

int	is_executable(t_node *exec, char *path)
{
	if (*(exec->data->execution->command_table[0]) == '\0')
		return (0);
	if (access(path, X_OK) == 0 && access(path, F_OK) == 0)
	{
		if (exec)
		{
			exec->data->execution->path = path;
			return (1);
		}
	}
	return (0);
}
