/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:15:48 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/05 20:38:16 by dlamark-         ###   ########.fr       */
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

void	handle_heresignals(void)
{
	signal(SIGINT, handle_ctrlc_heredoc);
}

void	handle_ctrlc_heredoc(int signal)
{
	t_list	*envp;

	(void)signal;
	envp = data_env_addr();
	close(STDIN_FILENO);
	printf("\n");
	update_env_list(envp, "?", "130");
}
