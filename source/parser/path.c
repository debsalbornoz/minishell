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
	t_env	*env;
	char	**path;
	int		size;

}

int	count_paths(const char *value)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (value[i] != '\0')
	{
		if (value[i] == ':')
			counter++;
		i++;
	}
	return (counter);
}
