/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:53:38 by dlamark-          #+#    #+#             */
/*   Updated: 2024/08/01 22:58:26 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

char	**handle_sort_envp(t_list *lst_env);
char	**sort(char **envp);
char	*build_env_var2(char *name, char *value);
void	print_envp(char **envp);
void	free_matrix(char **matrix);

void	handle_sort_envp(t_list *lst_env)
{
	int		i;
	int		nodes;
	char	**env_arr;
	t_node	*aux;

	i = 0;
	nodes = count_nodes(lst_env);
	aux = lst_env->head;
	env_arr = ft_calloc((nodes + 1), sizeof(char *));
	if (!env_arr)
		return ;
	while (aux)
	{
		env_arr[i] = build_env_var2(aux->data->env->name, aux->data->env->value);
		aux = aux->next;
		i++;
	}
	env_arr[nodes] = NULL;
	print_envp(env_arr);
	free_matrix(env_arr);
}

char	**sort(char **envp)
{
	char	*temp;
	int		swapped;
	int		i;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (envp[i + 1])
		{
			if (ft_strncmp(envp[i], envp[i + 1], ft_strlen(envp[i])) > 0)
			{
				temp = envp[i];
				envp[i] = envp[i + 1];
				envp[i + 1] = temp;
				swapped = 1;
			}
			i++;
		}
	}
	return (envp);
}

char	*build_env_var2(char *name, char *value)
{
	char	*env_var;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_strlen(value) == 0)
		len = ft_strlen(name) + ft_strlen(value) + 1;
	else
		len = ft_strlen(name) + ft_strlen(value) + 4;
	env_var = ft_calloc(len, sizeof(char));
	while (name[i] != '\0')
	{
		env_var[i] = name[i];
		i++;
	}
	if (value && value[j] != '\0')
	{
		env_var[i] = '=';
		i++;
		env_var[i] = '\"';
		i++;
	}
	while (value && value[j] != '\0')
	{
		env_var[i] = value[j];
		i++;
		j++;
	}
	env_var[i] = '\"';
	i++;
	env_var[i] = '\0';
	return (env_var);
}

void	print_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "?", 1) != 0
			&& ft_strncmp(envp[i], "_", 1) != 0)
		{
			ft_printf("declare -x %s\n", envp[i]);
		}
		i++;
	}
}
