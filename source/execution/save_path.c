/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/06 11:53:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*save_path(t_list *lst_exec, t_list *lst_token, t_list *lst_env)
{
	int		i;
	char	*path;
	char	**path_array;
	int		validate;

	i = 0;
	lst_env->node = lst_env->head;
	if (!lst_exec || !lst_token || !lst_env)
		return (NULL);
	path_array = split_path(lst_env);
	while (path_array[i] != NULL)
	{
		path = create_path(path_array[i], lst_token);
		validate = validate_path(lst_exec, path);
		if (validate)
		{
			free_matrix(path_array);
			return (path);
		}
		free(path);
		i++;
	}
	free_matrix(path_array);
	update_env_list(lst_env, "?", " 127: command not found");
	printf("%s\n", "comando nao encontrado");
	return (NULL);
}

int	validate_path(t_list *lst_exec, char *path)
{
	if (*(lst_exec->node->data->execution->command_table[0]) == '\0')
		return (0);
	if (access(path, X_OK) == 0 && access(path, F_OK) == 0)
	{
		if (lst_exec)
		{
			lst_exec->node->data->execution->path = path;
			printf("%s\n", lst_exec->node->data->execution->path);
			return (1);
		}
	}
	return (0);
}

char	*create_path(char *path, t_list *lst_token)
{
	char	*temp;
	t_node	*aux;

	temp = NULL;
	if (!lst_token)
		return (NULL);
	aux = lst_token->head;
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

char	*concatenate_path(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	temp = ft_calloc(len, sizeof(char));
	while (s1[i] != '\0')
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = '/';
	i++;
	while (s2[j] != '\0')
	{
		temp[i] = s2[j];
		i++;
		j++;
	}
	return (temp);
}
