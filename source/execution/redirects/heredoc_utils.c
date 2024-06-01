/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:15:48 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/01 18:16:41 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**allocate_eof(t_node *exec)
{
	int		counter;
	t_node	*aux;
	char	**eof;
	int		i;

	i = 0;
	aux = exec;
	counter = 0;
	eof = NULL;
	while (aux->data->exec->redir_and_files[i])
	{
		if (find_heredoc(aux->data->exec->redir_and_files[i])
			&& aux->data->exec->redir_and_files[i + 1])
			counter++;
		i++;
	}
	if (counter > 0)
		eof = ft_calloc(counter + 1, sizeof(char *));
	return (eof);
}
