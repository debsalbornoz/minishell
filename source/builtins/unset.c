

#include "../../include/builtins.h"

static void	free_node_env(t_node *envp);

int	is_valid_identifier(char *command_table)
{
	int		i;
	char	c;

	i = 0;
	c = command_table[0];
	if (!ft_is_alpha((int)c) && c != '_')
	{
		ft_putstr_fd("not a valid identifier\n", 2);
		return (0);
	}
	while (command_table[i] != '\0')
	{
		if (!ft_isalphanum(command_table[i]) && command_table[i] != '_')
		{
			ft_putstr_fd("not a valid identifier\n", 2);
			return (0);
		}
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
	while (exec++, *exec)
	{
		if (!is_valid_identifier(*exec))
		{
			ft_putstr_fd("unset: not a valid identifier\n", 2);
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
