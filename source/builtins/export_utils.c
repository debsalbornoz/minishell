/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:53:38 by dlamark-          #+#    #+#             */
/*   Updated: 2024/08/03 05:28:08 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

char	**sort(char **envp);
char	*build_env_var2(char *name, char *value);
void	print_envp(char **envp);
char	*fill_env_name_value(char *name, char *value, char *env_var);
char	*allocate_env_var(char *name, char *value);
char	*fill_env_name(char *name, char *env_var);

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

	env_var = allocate_env_var(name, value);
	if (value)
		env_var = fill_env_name_value(name, value, env_var);
	else
		env_var = fill_env_name(name, env_var);
	return (env_var);
}

char	*fill_env_name_value(char *name, char *value, char *env_var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (name[i] != '\0')
	{
		env_var[i] = name[i];
		i++;
	}
	env_var[i] = '=';
	i++;
	env_var[i] = '\"';
	i++;
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

char	*fill_env_name(char *name, char *env_var)
{
	int	i;

	i = 0;
	while (name[i] != '\0')
	{
		env_var[i] = name[i];
		i++;
	}
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
