/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:36:27 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/21 18:07:07 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static void	free_node_env(t_node *envp);

int	ft_is_alpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	else
		return (1);
}

int	ft_isalphanum(char c)
{
	if (ft_isdigit(c) || ft_isalpha(c))
		return (1);
	else
		return (0);
}

int	is_valid_identifier(char *command_table)
{
	int		i;
	char	c;

	i = 0;
	c = command_table[0];
	if (!ft_is_alpha((int)c) && c != '_')
	{
		return (0);
	}
	while (command_table[i] != '\0')
	{
		if (!ft_isalphanum(command_table[i]) && command_table[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	mini_unset(char **exec, t_list *envp)
{
	t_node	*unset_var;
	int		return_value;

	unset_var = envp->node;
	return_value = 0;
	while (++exec, ft_str_exist(*exec))
	{
		if (!is_valid_identifier(*exec))
		{
			write(2, "not a valid identifier\n", 23);
			return_value = 1;
		}
		if (exist_var(envp, *exec))
		{
			if (envp->node == envp->head)
			{
				envp->head = envp->node->next;
				free_node_env(envp->node);
			}
			else
			{
				unset_var = envp->node->next;
				envp->node->next = envp->node->next->next;
				free_node_env(unset_var);
			}
		}
	}
	return (return_value);
}

static void	free_node_env(t_node *envp)
{
	free(envp->data->env->name);
	free(envp->data->env->value);
	free(envp->data->env);
	free(envp->data);
	free(envp);
}
