/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:15:48 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/11 23:34:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include <stdio.h>
#include <unistd.h>

void	handle_ctrlc_heredoc(int signal);
void	handle_heresignals(void);

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


