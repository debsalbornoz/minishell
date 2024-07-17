/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:29:20 by codespace         #+#    #+#             */
/*   Updated: 2024/07/07 16:15:13 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	find_path(t_list *tokens, t_list *exec, t_list *envp)
{
	char	*path;

	envp->node = envp->head;
	path = NULL;
	if (!exec || !tokens || !envp)
		return ;
	while (exec->node)
	{
		if (exec->node->data->exec->command_table)
		{
			path = validate_path(exec->node->data->exec->command_table,
					exec->node, envp);
			exec->node->data->exec->path = ft_strdup(path);
			free(path);
		}
		exec->node = exec->node->next;
	}
	exec->node = exec->head;
	tokens->node = tokens->head;
}

char	*validate_path(char **command_table, t_node *exec, t_list *envp)
{
	char		**path_array;
	char		*absolute_path;

	path_array = split_path(envp);
	absolute_path = NULL;
	envp->node = envp->head;
	if (is_absolute_path(command_table))
	{
		if (check_command_validity(command_table[0], envp, command_table) == -1)
			return (NULL);
		absolute_path = ft_strdup(command_table[0]);
		free_matrix(path_array);
		return (absolute_path);
	}
	else
		absolute_path = create_absolute_path(path_array,
				command_table, exec);
	return (absolute_path);
}

int	check_command_validity(char *command, t_list *envp, char **command_table)
{
	struct stat	st;
	(void) command_table;

	if (access(command, F_OK) == -1)
		return (-1);
	if (access(command, X_OK) == -1)
	{
		update_env_list(envp, "?", "126");
		ft_putstr_fd("Permission denied", 2);
		return (-1);
	}
	else if (stat(command, &st) == 0)
	{
		if ((st.st_mode & S_IFMT) == S_IFDIR)
		{
			update_env_list(envp, "?", "126");
			ft_putstr_fd("Is a directory\n", 2);
			return (-1);
		}
}
	return (0);
}

int	is_executable(t_node *exec, char *path)
{
	if (*(exec->data->exec->command_table[0]) == '\0')
		return (0);
	if (access(path, X_OK) == 0 && access(path, F_OK) == 0)
	{
		if (exec)
		{
			exec->data->exec->path = path;
			return (1);
		}
	}
	return (0);
}

int	is_absolute_path(char **command_table)
{
	if (!ft_strncmp(command_table[0], "/", 1)
		|| !ft_strncmp(command_table[0], "./", 2))
		return (1);
	return (0);
}
