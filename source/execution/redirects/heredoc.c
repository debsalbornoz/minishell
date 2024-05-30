/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:34:28 by codespace         #+#    #+#             */
/*   Updated: 2024/05/30 20:16:41 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	get_flag(int signal);
char	*get_eof(t_node	*exec, int i);

char	*handle_heredoc(t_node *exec, int i, int j)
{
	char	*filename;
	int		fd;
	char	*eof;
	int		flag;
	(void)	i;
	eof = NULL;
	flag = get_flag(0);
	fd = 0;
	filename = get_filename(exec->data->execution->index);
	eof = exec->data->execution->eofs[j];
	if (!eof)
		return (NULL);
	fd = open(filename, flag, 0644);
	if (fd == -1)
		return (NULL);
	get_input(fd, eof, filename);
	return (filename);
}
char	*get_eof(t_node	*exec, int i)
{
	char	*eof;

	eof = NULL;
	if (exec->data->execution->redirects_and_files[i + 1] != NULL)
		eof = exec->data->execution->redirects_and_files[i + 1];
	return (eof);
}
char	*get_filename(int i)
{
	char	*filename;
	char	*number;

	number = ft_itoa(i);
	filename = ft_strjoin("./tmp/", number);
	free(number);
	return (filename);
}
//Lidar com expansão no heredoc, lidar com sinais,
void	get_input(int fd, char *eof, char *filename)
{
	char	*input;
	int		flag;

	input = NULL;
	flag = get_flag(1);
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
			//free(input);
			close(fd);
		}
		if (ft_strncmp(input, eof, ft_strlen(input)) == 0)
		{
			close(fd);
			//free(input);
			break ;
		}
	}
}

int	get_flag(int signal)
{
	int	flag;

	flag = 0;
	if (signal == 1 )
		flag = flag | O_RDWR | O_CREAT | O_APPEND;
	if (signal == 0)
		flag = flag | O_RDWR | O_CREAT | O_TRUNC;
	return (flag);
}
