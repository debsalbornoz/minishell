/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:34:28 by codespace         #+#    #+#             */
/*   Updated: 2024/06/11 23:36:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include <unistd.h>

int handle_heredoc(t_node *exec)
{
	char	*heredoc_file;
	int		i;
	int		j;

	handle_heresignals();
	heredoc_file = NULL;
	i = -1;
	j = 0;
	if (!exec->data->exec->redir_and_files)
		return (-1);
	exec->data->exec->eofs = allocate_eof(exec);
	while (exec->data->exec->redir_and_files[++i])
	{
		if (find_heredoc(exec->data->exec->redir_and_files[i]))
		{
			if (exec->data->exec->redir_and_files[i + 1])
			{
				exec->data->exec->eofs[j]
					= ft_strdup(exec->data->exec->redir_and_files[i + 1]);
				heredoc_file = create_heredoc_file(exec, j);
				if (!heredoc_file)
					return (-1);
				free(exec->data->exec->redir_and_files[i + 1]);
				exec->data->exec->redir_and_files[i + 1] = heredoc_file;
				j++;
			}
		}
	}
	return (0);
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
	if (open_heredoc_file(fd, eof, filename) == -1)
		return (NULL);
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

int	open_heredoc_file(int fd, char *eof, char *filename)
{
	char	*input;
	int		flag;
	int		fd_in;

	fd_in = dup(0);
	input = NULL;
	flag = heredoc_flags(1);
	fd = open(filename, flag, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		if (!ft_strncmp(ft_get_env(data_env_addr(), "?"), "130", 3))
		{
			dup2(fd_in, 0);
			free(input);
			return (-1);
		}
		input = readline(">");
		if (!input)
			break ;
		if (ft_strncmp(input, eof, ft_strlen(input)))
		{
			ft_putstr_fd(input, fd);
			ft_putstr_fd("\n", fd);
		}
		if (ft_strncmp(input, eof, ft_strlen(input)) == 0)
		{
			close(fd);
			return (0);
		}
	}
	return (0);
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
v_list(envp, "?", "130");
}
