/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/07 20:28:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_executable_in_path(t_list *exec, t_list *tokens, t_list *envp)
{
	int		i;
	char	*path;
	char	**path_array;
	int		validate;

	i = 0;
	envp->node = envp->head;
	if (!exec || !tokens || !envp)
		return (NULL);
	path_array = split_path(envp);
	while (path_array[i] != NULL)
	{
		path = create_path(path_array[i], tokens);
		validate = is_executable(exec, path);
		if (validate)
		{
			free_matrix(path_array);
			return (path);
		}
		free(path);
		i++;
	}
	free_matrix(path_array);
	update_env_list(envp, "?", " 127: command not found");
	printf("%s\n", "Command not found");
	return (NULL);
}

int	is_executable(t_list *exec, char *path)
{
	if (*(exec->node->data->execution->command_table[0]) == '\0')
		return (0);
	if (access(path, X_OK) == 0 && access(path, F_OK) == 0)
	{
		if (exec)
		{
			exec->node->data->execution->path = path;
			printf("%s\n", exec->node->data->execution->path);
			return (1);
		}
	}
	return (0);
}

char	*create_path(char *path, t_list *tokens)
{
	char	*temp;
	t_node	*aux;

	temp = NULL;
	if (!tokens)
		return (NULL);
	aux = tokens->head;
	while (aux)
	{
		if (aux->data->token->type == PATH)
			temp = ft_strdup(aux->data->token->value);
		if (aux->data->token->type == COMMAND)
		{
			temp = concatenate_path(path, aux->data->token->value);
			return (temp);
		}
		aux = aux->next;
	}
	return (temp);
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
