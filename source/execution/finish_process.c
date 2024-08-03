/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:22:10 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/28 19:00:20 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	finish_process(t_list *exec, t_list *tokens, t_list *envp, char *input)
{
	int		status;
	char	*var;

	var = ft_get_env("?");
	status = ft_atoi(var);
	free_list(exec, free_lst_exec);
	free_list(tokens, free_lst_tokens);
	free_list(envp, free_lst_env);
	free(input);
	close_fds();
	exit(status);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix || !*matrix)
		return ;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	close_fds(void)
{
	struct dirent	*file;
	DIR				*directory;
	int				fd;

	directory = opendir("/proc/self/fd/");
	if (!directory)
	{
		perror("Open dir");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		file = readdir(directory);
		if (!file)
			break ;
		fd = ft_atoi(file->d_name);
		if (fd > 2 && fd < 1024)
			close(ft_atoi(file->d_name));
	}
	closedir(directory);
}

void	free_pipes(int **pipes)
{
	int	i;

	i = 0;
	while (pipes[i] != NULL)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}
