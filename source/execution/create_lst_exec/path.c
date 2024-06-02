/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:29:20 by codespace         #+#    #+#             */
/*   Updated: 2024/06/02 16:17:35 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*create_absolute_path(char **path_array,
	char **command_table, t_node *exec)
{
	int		i;
	char	*absolute_path;

	i = 0;
	absolute_path = NULL;
	while (path_array[i])
	{
		absolute_path = concatenate_path(path_array[i], command_table[0]);
		if (i++, is_executable(exec, absolute_path))
		{
			free_matrix(path_array);
			return (absolute_path);
		}
		free(absolute_path);
	}
	free_matrix(path_array);
	return (NULL);
}

char	*concatenate_path(char *path, char *command)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

	i = 0;
	j = 0;
	if (!path || !command)
		return (NULL);
	len = ft_strlen(path) + ft_strlen(command) + 2;
	temp = ft_calloc(len, sizeof(char));
	while (path[i] != '\0')
	{
		temp[i] = path[i];
		i++;
	}
	temp[i] = '/';
	i++;
	while (command[j] != '\0')
	{
		temp[i] = command[j];
		i++;
		j++;
	}
	return (temp);
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
				command_table, exec);
	return (absolute_path);
}

int	is_absolute_path(char **command_table)
{
	if (!ft_strncmp(command_table[0], "/", 1)
		|| !ft_strncmp(command_table[0], "./", 2))
		return (1);
	return (0);
}
