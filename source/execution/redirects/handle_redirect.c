/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:07:45 by codespace         #+#    #+#             */
/*   Updated: 2024/05/30 15:34:57 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	open_file(t_node *exec, int i, int flag);

void	handle_redirect(t_node *exec)
{
	int		i;

	i = 0;
	if (!exec->data->execution->redirects_and_files)
		return ;
	while (exec->data->execution->redirects_and_files[i])
	{
		if (find_output(exec->data->execution->redirects_and_files[i])
			|| find_append(exec->data->execution->redirects_and_files[i]))
			open_file(exec, i, 1);
		if (find_input(exec->data->execution->redirects_and_files[i]))
			open_file(exec, i, 0);
		if (find_heredoc(exec->data->execution->redirects_and_files[i]))
			handle_heredoc(exec, i);
		i++;
	}
	return ;
}

int	set_flag(char *redirect)
{
	int	flag;

	flag = 0;
	if (find_output(redirect))
		flag = flag | O_WRONLY | O_CREAT | O_TRUNC;
	if (find_append(redirect))
		flag = flag | O_WRONLY | O_CREAT | O_APPEND;
	if (find_input(redirect))
		flag = flag | O_RDONLY;
	return (flag);
}

void	close_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

void	open_file(t_node *exec, int i, int flag)
{
	int	fd;

	fd = 0;
	if (exec->data->execution->redirects_and_files[i + 1])
	{
		fd = open(exec->data->execution->redirects_and_files[i + 1],
				set_flag(exec->data->execution->redirects_and_files[i]), 0644);
		if (fd == -1)
			return ;
		if (flag == 0)
		{
			fd = dup2(fd, 0);
			exec->data->execution->input = fd;
		}
		if (flag == 1)
		{
			fd = dup2(fd, 1);
			exec->data->execution->output = fd;
		}
	}
}
