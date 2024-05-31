/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:59:18 by codespace         #+#    #+#             */
/*   Updated: 2024/05/27 16:43:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_file(int type)
{
	if (type == OUTPUT_FILE || type == INPUT_FILE
		|| type == APPEND_FILE || type == HEREDOC_KEY)
		return (1);
	return (0);
}

int	is_file_redirect_or_pipe(int type)
{
	if (find_file(type) || find_redirect(type) || type == PIPE)
		return (1);
	else
		return (0);
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

void	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		printf("%s , ", matrix[i]);
		i++;
	}
}
