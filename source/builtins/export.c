/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:35:44 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/31 20:37:54 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static t_node	*print_for_export(t_node *nde);
static t_env	*get_env(t_env *env, char *string);
static void		free_env(t_env *env);

int	mini_export(char **exec, t_list *envp)
{
	int	iterator;
	t_env	*env;

	iterator = 0;
	if (!exec[1])
		return (runs_on_list(envp, print_for_export), 0);
	env = ft_calloc(1, sizeof(t_env));
	while(++iterator, exec[iterator])
	{
		env = get_env(env, exec[iterator]);
		update_env_list(envp, env->name, env->value);
	}
	return (free_env(env), 0);
}

static t_node	*print_for_export(t_node *nde)
{
	if (nde->data->env->value)
		return (printf("declare -x %s=%s\n", nde->data->env->name, nde->data->env->value), nde);
	return (printf("declare -x %s\n", nde->data->env->name), nde);
}

static t_env	*get_env(t_env *env, char *string)
{
	while (*string && *string != '=')
		env->name = ft_chrjoin(env->name, *string++);
	if (*string == '=')
		string++;
	while (*string)
		env->value = ft_chrjoin(env->value, *string++);
	return (env);
}

static void	free_env(t_env *env)
{
	if (env->name && *env->name)
		free(env->name);
	if (env->value && *env->value)
		free(env->value);
	free(env);
}
