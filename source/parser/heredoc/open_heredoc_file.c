/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:35:58 by codespace         #+#    #+#             */
/*   Updated: 2024/06/29 17:22:26 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*get_filename(int i)
{
	char	*filename;
	char	*index;

	filename = NULL;
	index = ft_itoa(i);
	filename = ft_strjoin("/tmp/", index);
	free(index);
	return (filename);
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

int	open_prompt(char *eof, int flag, int fd, char *filename)
{
	char	*input;
	int		fd_stdin;
	int		result;

	result = 0;
	fd_stdin = dup(STDIN_FILENO);
	input = readline("> ");
	result = check_signals(input, filename, fd_stdin);
	if (input && ft_strncmp(input, eof, ft_strlen(input)))
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
		input_expanded = expand_input(input);
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

char	*expand_input(char *input)
{
	int		i;
	char	*input_expanded;
	int		counter;
	char	*env_value;
	char	*str;

	i = 0;
	str = NULL;
	while (input[i] != '\0')
	{
		if (input[i] == '$' && input[i + 1] != '\0')
		{
			counter = get_var_len(&input[i + 1]);
			env_value = extract_var_value(counter, &input[i + 1]);
			input_expanded = ft_strjoin_free(input_expanded, env_value);
			i += counter + 1;
		}
		else
		{
			counter = get_substr_len(&input[i]);
			str = extract_substr(&i, counter, input);
			input_expanded = ft_strjoin_free(input_expanded, str);
		}
	}
	return (input_expanded);
}
