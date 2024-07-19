/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:07:45 by codespace         #+#    #+#             */
/*   Updated: 2024/06/29 16:07:20 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	check_access_input(char *redirect, char *file, t_list *envp);
static int	check_access_output(char *redirect, char *file, t_list *envp);

int	handle_redirect(t_node *exec, t_list *envp, int fd_in, int fd_out)
{
	int	i;

	i = 0;
	if (!exec->data->exec->redir_and_files)
		return (0);
	while (exec->data->exec->redir_and_files[i])
	{
		if (find_output(exec->data->exec->redir_and_files[i])
			|| find_append(exec->data->exec->redir_and_files[i]))
		{
			dup2(fd_out, 1);
			if (open_file(exec->data->exec->redir_and_files, i, 1, envp) == -1)
				return (-1);
		}
		if (find_input(exec->data->exec->redir_and_files[i])
			|| find_heredoc(exec->data->exec->redir_and_files[i]))
		{
			dup2(fd_in, 0);
			if (open_file(exec->data->exec->redir_and_files, i, 0, envp) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	open_file(char **redir_and_files, int i, int flag, t_list *envp)
{
	int	fd;

	fd = 0;
	if (redir_and_files[i + 1])
	{
		fd = open(redir_and_files[i + 1],
				set_flag(redir_and_files[i]),
				0644);
		if (fd == -1)
		{
			if (check_access_input(redir_and_files[i],
					redir_and_files[i + 1], envp) == -1
				|| check_access_output(redir_and_files[i],
					redir_and_files[i + 1],
					envp) == -1)
				return (-1);
		}
		if (flag == 0)
			dup2(fd, 0);
		if (flag == 1)
			dup2(fd, 1);
		close(fd);
	}
	return (0);
}

static int	check_access_input(char *redirect, char *file, t_list *envp)
{
	struct stat st;

	if (find_heredoc(redirect) || find_input(redirect))
	{
		if (access(file, F_OK) == -1)
		{
			update_env_list(envp, "?", "1");
			ft_putstr_fd("No such file or directory\n", 2);
			return (-1);
		}
		else if (stat(file, &st) == 0)
		{
			if ((st.st_mode & S_IFMT) == S_IFDIR)
			{
				update_env_list(envp, "?", "1");
				ft_putstr_fd("Is a directory\n", 2);
				return (-1);
			}
		}
		else if (access(file, R_OK) == -1)
		{
			update_env_list(envp, "?", "1");
			ft_putstr_fd("Permission denied\n", 2);
			return (-1);
		}

	}
	return (0);
}

static int	check_access_output(char *redirect, char *file, t_list *envp)
{
	struct stat st;

	if (find_output(redirect) || find_append(redirect))
	{
		if (access(file, F_OK) == -1)
		{
			update_env_list(envp, "?", "1");
			ft_putstr_fd("No such file or directory\n", 2);
			return (-1);
		}
		else if (stat(file, &st) == 0)
		{
			if ((st.st_mode & S_IFMT) == S_IFDIR)
			{
				update_env_list(envp, "?", "1");
				ft_putstr_fd("Is a directory\n", 2);
				return (-1);
			}
		}
		else if (access(file, W_OK) == -1)
		{
			update_env_list(envp, "?", "1");
			ft_putstr_fd("Permission denied\n", 2);
			return (-1);
		}
	}
	return (0);
}

int	set_flag(char *redirect)
{
	int	flag;

	flag = 0;
	if (find_output(redirect))
		flag = flag | O_WRONLY | O_CREAT | O_TRUNC;
	if (find_append(redirect))
		flag = flag | O_WRONLY | O_CREAT | O_APPEND;
	if (find_input(redirect) || find_heredoc(redirect))
		flag = flag | O_RDONLY;
	return (flag);
}
