/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_absolute_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:29:20 by codespace         #+#    #+#             */
/*   Updated: 2024/05/20 17:49:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*create_absolute_path(char **path_array,
	char **command_table, t_list *envp, t_node	*exec)
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
	free_and_update_lst(path_array, envp);
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
