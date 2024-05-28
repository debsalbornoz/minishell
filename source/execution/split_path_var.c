/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jackson <jackson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:16:13 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/26 08:21:42 by jackson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**split_path(t_list *lst_env)
{
	char	**path;
	int		size;
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!lst_env)
		return (NULL);
	value = return_value(lst_env, "PATH");
	size = count_paths(value);
	path = ft_calloc((size + 1), sizeof(char *));
	while (i < size)
	{
		path[i] = get_path(&value[j], 0, 0, 0);
		j += get_len(&value[j]) + 1 ;
		i++;
	}
	path[i] = NULL;
	free(value);
	return (path);
}

int	count_paths(const char *value)
{
	int	i;
	int	counter;

	i = 0;
	counter = 1;
	if (!value)
		return (0);
	while (value[i] != '\0')
	{
		if (value[i] == ':')
			counter++;
		i++;
	}
	return (counter);
}

char	*return_value(t_list *lst_env, char *name)
{
	char	*temp;

	temp = 0;
	if (!lst_env)
		return (NULL);
	lst_env->node = lst_env->head;
	while (lst_env->node)
	{
		if (!ft_strncmp(lst_env->node->data->env->name, name,
				ft_strlen(lst_env->node->data->env->name)))
			temp = ft_strdup(lst_env->node->data->env->value);
		lst_env->node = lst_env->node->next;
	}
	return (temp);
}

char	*get_path(char *value, int i, int len, int j)
{
	char	*temp;

	temp = 0;
	while (value[j] != '\0')
	{
		if (value[j] != ':' && value[j] != '\0')
		{
			len = get_len(value);
			temp = ft_calloc(len + 1, sizeof(char));
			while (i < len && value[j])
			{
				temp[i] = value[j];
				i++;
				j++;
			}
		}
		if (value[j] == ':' || value[j] == '\0')
		{
			if (value[j] == ':')
				j++;
			break ;
		}
		value++;
	}
	return (temp);
}

int	get_len(char *value)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (value[i] != '\0')
	{
		if (value[i] != ':' && value[i] != '\0')
			counter++;
		if (value[i] == ':' || value[i] == '\0')
			break ;
		i++;
	}
	return (counter);
}
