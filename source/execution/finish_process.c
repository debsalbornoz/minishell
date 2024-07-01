/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:22:10 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/01 13:45:52 by codespace        ###   ########.fr       */
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
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
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
