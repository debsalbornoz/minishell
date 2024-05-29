/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jackson <jackson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:59:18 by codespace         #+#    #+#             */
/*   Updated: 2024/05/29 13:47:41 by jackson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	- [ ] Verificar lugar melhor para atribuir essa função:

			update_env_list(envp, "?", " 127");
			printf("%s\n", "Command not found");

	função acima estavam anteriormente em "ree_and_update_lst" depois do free.
*/

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

void	free_and_update_lst(char **path_array, t_list	*envp)
{
	(void)envp;
	free_matrix(path_array);
}
