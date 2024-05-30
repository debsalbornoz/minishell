/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:34:28 by codespace         #+#    #+#             */
/*   Updated: 2024/05/30 16:05:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	handle_heredoc(t_node *exec, int i)
{
	char	*filename;
	int		fd;
	int		flag;
	char	*eof;
	char	*input;

	(void)input;
	flag = 0;
	flag = flag | O_WRONLY | O_CREAT | O_TRUNC;
	filename = get_filename(exec->data->execution->index);
	if (exec->data->execution->redirects_and_files[i + 1] != NULL)
		eof = exec->data->execution->redirects_and_files[i + 1];
	if (!eof)
		return ;
	fd = open(filename, flag, 0644);
	if (fd == -1)
		return ;
	exec->data->execution->input = fd;
	get_input(fd, eof);
	fd = dup2(fd, 0);


	char buffer[1000];
	close(fd);
	fd = open(filename, flag, 0644);
	read(fd, buffer, 1000);

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

void	get_input(int fd, char *eof)
{
	char	*input;
	(void)	fd;
	input = NULL;
	while (1)
	{
		input = readline(">");
		if (ft_strncmp(input, eof, ft_strlen(input)))
		{
			ft_putstr_fd(input, fd);
			ft_putstr_fd("\n", fd);
			free(input);
		}
		if (ft_strncmp(input, eof, ft_strlen(input)) == 0)
		{
			free(input);
			break ;
		}
	}
}
