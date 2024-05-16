/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/16 19:37:23 by codespace        ###   ########.fr       */
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
		exec->node->data->execution->path = path;
		exec->node = exec->node->next;
	}
}

char	*validate_path(char **command_table, t_node *exec, t_list *envp)
{
	char	**path_array;
	char	*absolute_path;
	int		i;

	i = 0;
	path_array = split_path(envp);
	absolute_path = NULL;
	envp->node = envp->head;
	if (is_absolute_path(command_table))
		exec->data->execution->path = ft_strdup(command_table[0]);
	else
	{
		while (path_array[i])
		{
			absolute_path = concatenate_path(path_array[i], command_table[0]);
			if (is_executable(exec, absolute_path))
			{
				free_matrix(path_array);
				return (absolute_path);
			}
			free(absolute_path);
			i++;
		}
		free_and_update_lst(path_array, envp);
	}
	return (NULL);
}

void	free_and_update_lst(char **path_array, t_list	*envp)
{
	free_matrix(path_array);
	update_env_list(envp, "?", " 127: command not found");
	printf("%s\n", "Command not found");
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

char	*create_path(char *path, t_node *tokens)
{
	char	*absolute_path;

	absolute_path = NULL;
	if (!tokens)
		return (NULL);
	while (tokens)
	{
		if (!is_file_redirect_or_pipe(tokens->data->token->type))
		{
			if (tokens->data->token->type == PATH)
				absolute_path = ft_strdup(tokens->data->token->value);
			if (tokens->data->token->type == COMMAND)
				absolute_path
					= concatenate_path(path, tokens->data->token->value);
		}
		if (tokens->data->token->type == PIPE && tokens->next)
		{
			tokens = tokens->next;
			break ;
		}
		tokens = tokens->next;
	}
	return (absolute_path);
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
