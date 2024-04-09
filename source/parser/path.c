/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:16:13 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/06 17:28:04 by dlamark-         ###   ########.fr       */
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
	if(!lst_env)
		return (NULL);
	value = return_value(lst_env, "PATH");
	size = count_paths(value);
	path = ft_calloc((size + 1), sizeof(char *));
	while (i < size)
	{
		path[i] = get_path(&value[j]);
		j += get_len(&value[j]) + 1 ;
		printf("%s\n", path[i]);
		i++;
	}
	path[i] = NULL;
	free(value);
	return(path);
}

int	count_paths(const char *value)
{
	int	i;
	int	counter;

	i = 0;
	counter = 1;
	if(!value)
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
	char *temp;
	if(!lst_env)
		return (NULL);
	lst_env->node = lst_env->head;
	while(lst_env->node)
	{
		if(!ft_strncmp(lst_env->node->data->env->name, name, ft_strlen(lst_env->node->data->env->name)))
			temp = ft_strdup(lst_env->node->data->env->value);
		lst_env->node = lst_env->node->next;
	}
	return (temp);
}

char *get_path(char *value)
{
	char *temp;
	int	i;
	int len;
	int j;

	i = 0;
	len = 0;
	j = 0;
	if(!value)
		return (NULL);
	while(value[j] != '\0')
	{
		if(value[j] != ':' && value[j] != '\0')
		{
			//precisa dar free
			len = get_len(value);
			temp = ft_calloc(len + 1, sizeof(char));
			while(i < len && value[j])
			{
				temp[i] = value[j];
				i++;
				j++;
			}
		}
		if(value[j] == ':' || value[j] == '\0')
		{
			if(value[j] == ':')
				j++;
			break;
		}
		value++;
	}
	return(temp);
}

int get_len(char *value)
{
	int counter;
	int i;

	counter = 0;
	i = 0;
	while(value[i] != '\0')
	{
		if(value[i] != ':' && value[i] != '\0')
			counter++;
		if(value[i] == ':' || value[i] == '\0')
			break;
		i++;
	}
	return(counter);
}

void free_path(char **path)
{
	int i;

	i = 0;
	if(!path || !*path)
		return;
	while(path[i] != NULL)
	{
		free(path[i]);
		i++;
	}
	free(path);
}
