/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:07:45 by codespace         #+#    #+#             */
/*   Updated: 2024/05/23 20:16:06 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_output(char *str);
int	find_append(char *str);
int	find_input(char *str);
int	find_heredoc(char *str);

void handle_redirect(t_node *exec)
{
	int		fd;
	int		i;

	i = 0;
	if (!exec->data->execution->redirects_and_files)
		return ;
	while (exec->data->execution->redirects_and_files[i])
	{
		if (find_output(exec->data->execution->redirects_and_files[i])
			|| find_append(exec->data->execution->redirects_and_files[i]))
		{
			if (exec->data->execution->redirects_and_files[i + 1])
			{
				fd = open(exec->data->execution->redirects_and_files[i + 1], set_flag(exec->data->execution->redirects_and_files[i]), 0644);
				if ( fd == -1)
					printf("???\n");
				fd = dup2(fd, 1);
				exec->data->execution->output = fd;
			}
		}
		if (find_input(exec->data->execution->redirects_and_files[i])
			|| find_heredoc(exec->data->execution->redirects_and_files[i]))
		{
			if (exec->data->execution->redirects_and_files[i + 1])
			{
				fd = open(exec->data->execution->redirects_and_files[i + 1], set_flag(exec->data->execution->redirects_and_files[i]), 0644);
				fd = dup2(fd, 0);
				exec->data->execution->input  = fd;
			}
		}
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
	if (find_heredoc(redirect) || find_input(redirect))
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

void	free_token(t_node *node)
{
	free(node->data->token->value);
	free(node->data->token);
	free(node->data);
	free(node);
}

int	find_output(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 1)
	{
		if (ft_strncmp(str, ">", len) == 0)
			return (1);
	}
	return (0);
}
int	find_append(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 2)
	{
		if (ft_strncmp(str, ">>", len) == 0)
			return (1);
	}
	return (0);
}

int	find_input(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 1)
	{
		if (ft_strncmp(str, "<", len) == 0)
			return (1);
	}
	return (0);
}

int	find_heredoc(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 2)
	{
		if (ft_strncmp(str, "<<", len) == 0)
			return (1);
	}
	return (0);
}
