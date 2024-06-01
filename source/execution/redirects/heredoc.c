/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:34:28 by codespace         #+#    #+#             */
/*   Updated: 2024/06/01 16:45:32 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	handle_heredoc(t_node *exec)
{
	char	*heredoc_file;
	int		i;
	int		j;

	heredoc_file = NULL;
	i = 0;
	j = 0;
	if (!exec->data->exec->redir_and_files)
		return ;
	exec->data->exec->eofs = allocate_eof(exec);
	while (exec->data->exec->redir_and_files[i])
	{
		if (find_heredoc(exec->data->exec->redir_and_files[i]))
		{
			if (exec->data->exec->redir_and_files[i + 1])
			{
				exec->data->exec->eofs[j]
					= ft_strdup(exec->data->exec->redir_and_files[i + 1]);
				heredoc_file = create_heredoc_file(exec, j);
				free(exec->data->exec->redir_and_files[i + 1]);
				exec->data->exec->redir_and_files[i + 1] = heredoc_file;
				j++;
			}
		}
		i++;
	}
}

char	*create_heredoc_file(t_node *exec, int j)
{
	char	*filename;
	int		fd;
	char	*eof;
	int		flag;

	eof = NULL;
	flag = heredoc_flags(0);
	fd = 0;
	filename = get_filename(exec->data->exec->index);
	eof = exec->data->exec->eofs[j];
	if (!eof)
		return (NULL);
	fd = open(filename, flag, 0644);
	if (fd == -1)
	{
		printf("?\n");
		return (NULL);
	}
	open_heredoc_file(fd, eof, filename);
	return (filename);
}

char	*get_filename(int i)
{
	char	*filename;
	char	*number;

	number = ft_itoa(i);
	filename = ft_strjoin("/tmp/", number);
	free(number);
	return (filename);
}

void	open_heredoc_file(int fd, char *eof, char *filename)
{
	char	*input;
	int		flag;

	input = NULL;
	flag = heredoc_flags(1);
	while (1)
	{
		input = readline(">");
		if (ft_strncmp(input, eof, ft_strlen(input)))
		{
			fd = open(filename, flag, 0644);
			if (fd == -1)
				return ;
			ft_putstr_fd(input, fd);
			ft_putstr_fd("\n", fd);
			close(fd);
		}
		if (ft_strncmp(input, eof, ft_strlen(input)) == 0)
		{
			close(fd);
			break ;
		}
	}
}

int	heredoc_flags(int signal)
{
	int	flag;

	flag = 0;
	if (signal == 1)
		flag = flag | O_RDWR | O_CREAT | O_APPEND;
	if (signal == 0)
		flag = flag | O_RDWR | O_CREAT | O_TRUNC;
	return (flag);
}
