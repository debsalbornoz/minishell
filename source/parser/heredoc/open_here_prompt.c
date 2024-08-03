/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_here_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:35:58 by codespace         #+#    #+#             */
/*   Updated: 2024/07/28 17:52:33 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	open_prompt(char *eof, int flag, int fd, char *filename)
{
	char	*input;
	int		fd_stdin;
	int		result;

	result = 0;
	fd_stdin = dup(STDIN_FILENO);
	input = readline("> ");
	result = check_signals(input, filename, fd_stdin);
	if (input && ft_strcmp(input, eof))
	{
		write_in_file(input, fd, flag);
		result = 3;
	}
	else if (result == 0)
	{
		close(fd);
		free(input);
		result = 2;
	}
	return (result);
}

void	write_in_file(char *input, int fd, int flag)
{
	char	*input_expanded;

	if (flag == 0)
	{
		input_expanded = expand_input(input, 0, 0);
		free(input);
		ft_putstr_fd(input_expanded, fd);
		ft_putstr_fd("\n", fd);
		free(input_expanded);
	}
	if (flag == 1)
	{
		ft_putstr_fd(input, fd);
		ft_putstr_fd("\n", fd);
	}
}

int	open_here_file(char *filename)
{
	int	flag;
	int	fd;

	flag = 0;
	flag = flag | O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(filename, flag, 0777);
	if (fd == -1)
		return (-1);
	return (fd);
}
