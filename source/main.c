/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:51:39 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/26 20:07:22 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*lst_env;
	char **path;
	int		i;
	char **matrix;
	lst_env = NULL;
	path = NULL;
	i  = 0;
	(void)argv;
	if (argc > 1)
		return (0);
	init_data_env_addr(envp);
	lst_env = *data_env_addr();
	handle_signal(lst_env);
	path = split_path(lst_env);
	while (program(lst_env))
		;
	lst_env->node = lst_env->head;
	matrix = list_to_matrix(lst_env);
	while(matrix[i])
	{
		printf("%s\n", matrix[i]);
		i++;
	}
	free_list(lst_env, free_lst_env);
	free(lst_env);
	free_path(path);
	free_matrix(matrix);
	return (EXIT_SUCCESS);
}
