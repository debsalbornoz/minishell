/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:35:44 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/22 18:08:59 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static t_node	*print_for_export(t_node *nde);
static t_env	*get_env(t_env *env, char *string);
static void		free_env(t_env *env);
static int		check_name(char *name);

int	mini_export(char **exec, t_list *envp)
{
	int		iterator;
	t_env	*env;

	iterator = 0;
	if (!exec[1])
		return (runs_on_list(envp, print_for_export), 0);
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

static t_node	*print_for_export(t_node *nde)
{
	if (nde->data->env->value && is_not_ocult_var(nde->data->env->name))
	{
		return (printf("declare -x %s=\"%s\"\n",
				nde->data->env->name, nde->data->env->value), nde);
	}
	else if (is_not_ocult_var(nde->data->env->name))
		printf("declare -x %s\n", nde->data->env->name);
	return (nde);
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
