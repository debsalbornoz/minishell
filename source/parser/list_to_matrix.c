/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:30:16 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/09 19:33:25 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**list_to_matrix(t_list *lst_env)
{
	int		counter;
	char	**env;
	int		i;
	int		len;

	i = 0;
	counter = 0;
	len = 0;
	if (!lst_env)
		return (NULL);
	counter = count_nodes(lst_env);
	lst_env->node = lst_env->head;
	env = ft_calloc(counter + 1, sizeof(char *));
	if (!env)
		return (NULL);
	while (lst_env->node)
	{
		len = ft_strlen(lst_env->node->data->env->name)
			+ ft_strlen(lst_env->node->data->env->value) + 2;
		env[i] = ft_calloc(len, sizeof(char));
		if (!env[i])
			return (NULL);
		env[i] = concatenate(lst_env->node->data->env->name,
				lst_env->node->data->env->value);
		i++;
		lst_env->node = lst_env->node->next;
	}
	lst_env->node = lst_env->head;
	return (env);
}

int	count_nodes(t_list *lst_env)
{
	int	i;

	i = 0;
	lst_env->node = lst_env->head;
	while (lst_env->node)
	{
		i++;
		lst_env->node = lst_env->node->next;
	}
	return (i);
}

char	*concatenate(char *s1, char *s2)
{
	char	*temp;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	temp = ft_calloc(len, sizeof(char));
	while (s1[i] != '\0')
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = '=';
	i++;
	while (s2[j] != '\0')
	{
		temp[i] = s2[j];
		i++;
		j++;
	}
	temp[i] = '\0';
	return (temp);
}

void	free_matrix(char **envp)
{
	int	i;

	i = 0;
	if (!envp || !*envp)
		return ;
	while (envp[i] != NULL)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
