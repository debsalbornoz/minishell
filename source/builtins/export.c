/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:35:44 by dlamark-          #+#    #+#             */
/*   Updated: 2024/08/01 22:59:36 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static t_env	*get_env(t_env *env, char *string);
static void		free_env(t_env *env);
static int		check_name(char *name);
char			**handle_sort_envp(t_list *lst_env);

int	mini_export(char **exec, t_list *envp)
{
	int		iterator;
	t_env	*env;

	iterator = 0;
	if (!exec[1])
		return (handle_sort_envp(envp), 0);
	env = ft_calloc(1, sizeof(t_env));
	while (++iterator, exec[iterator])
	{
		if (!is_valid_first_char(*exec[iterator]))
			return (ft_putstr_fd(" not a valid identifier\n", 2),
				free_env(env), 1);
		env = get_env(env, exec[iterator]);
		if (ft_str_exist(env->name) && check_name(env->name))
			return (ft_putstr_fd(" not a valid identifier\n", 2),
				free_env(env), 1);
		update_env_list(envp, env->name, env->value);
		if (ft_free_str(env->name))
			env->name = 0;
		if (ft_free_str(env->value))
			env->value = 0;
	}
	return (free_env(env), 0);
}

static t_env	*get_env(t_env *env, char *string)
{
	while (*string && *string != '=')
		env->name = ft_chrjoin(env->name, *string++);
	if (*string == '=' && !*(string + 1))
	{
		env->value = ft_strdup("");
		string++;
	}
	else if (*string == '=')
		string++;
	while (*string)
		env->value = ft_chrjoin(env->value, *string++);
	return (env);
}

static void	free_env(t_env *env)
{
	if (ft_free_str(env->name))
		env->name = 0;
	if (ft_free_str(env->value))
		env->value = 0;
	if (env)
		free(env);
}

static int	check_name(char *name)
{
	char	*name_tmp;
	int		iterator;

	iterator = -1;
	name_tmp = name;
	while (++iterator, *name_tmp)
	{
		if (!iterator && !is_valid_first_char(*name_tmp))
			return (1);
		if (!is_valid_char(*name_tmp))
			return (1);
		name_tmp++;
	}
	return (0);
}

char	**handle_sort_envp(t_list *lst_env)
{
	int		i;
	int		nodes;
	char	**env_arr;
	t_node	*aux;

	i = 0;
	nodes = count_nodes(lst_env);
	aux = lst_env->head;
	env_arr = ft_calloc((nodes + 1), sizeof(char *));
	while (aux)
	{
		env_arr[i] = build_env_var2(aux->data->env->name,
				aux->data->env->value);
		aux = aux->next;
		i++;
	}
	env_arr[nodes] = NULL;
	env_arr = sort(env_arr);
	print_envp(env_arr);
	free_matrix(env_arr);
	return (NULL);
}
