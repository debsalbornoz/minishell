/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:07:45 by codespace         #+#    #+#             */
/*   Updated: 2024/05/31 15:43:41 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	handle_redirect(t_node *exec)
{
	int		i;

	i = 0;
	if (!exec->data->exec->redirs_files)
		return ;
	while (exec->data->exec->redirs_files[i])
	{
		if (find_output(exec->data->exec->redirs_files[i])
			|| find_append(exec->data->exec->redirs_files[i]))
			open_file(exec, i, 1);
		if (find_input(exec->data->exec->redirs_files[i]) || \
			ft_strncmp("<<", \
			exec->data->exec->redirs_files[i], 2) == 0)
			open_file(exec, i, 0);
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
	if (find_input(redirect) || ft_strncmp("<<", redirect, 2) == 0)
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
	if (exec->data->exec->redirs_files[i + 1])
	{
		fd = open(exec->data->exec->redirs_files[i + 1],
				set_flag(exec->data->exec->redirs_files[i]), 0644);
		if (fd == -1)
			return ;
		if (flag == 0)
		{
			fd = dup2(fd, 0);
			exec->data->exec->input = fd;
		}
		if (flag == 1)
		{
			fd = dup2(fd, 1);
			exec->data->exec->output = fd;
		}
	}
}
