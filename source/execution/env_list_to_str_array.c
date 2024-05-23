/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_str_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/23 12:26:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**env_list_to_str_array(t_list *lst_env)
{
	char	**envp;
	int		i;
	int		nodes;
	t_node	*aux;

	if (!lst_env)
		return (NULL);
	i = 0;
	aux = lst_env->head;
	nodes = count_nodes(lst_env);
	aux = lst_env->head;
	envp = ft_calloc(nodes + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	while (aux)
	{
		envp[i] = build_env_var(aux->data->env->name,
				aux->data->env->value);
		i++;
		aux = aux->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	*build_env_var(char *name, char *value)
{
	char	*env_var;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(name) + ft_strlen(value) + 2;
	env_var = ft_calloc(len, sizeof(char));
	while (name[i] != '\0')
	{
		env_var[i] = name[i];
		i++;
	}
	env_var[i] = '=';
	i++;
	while (value[j] != '\0')
	{
		env_var[i] = value[j];
		i++;
		j++;
	}
	env_var[i] = '\0';
	return (env_var);
}
