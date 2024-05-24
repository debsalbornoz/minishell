/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:39:14 by jraupp            #+#    #+#             */
/*   Updated: 2024/05/23 20:02:04 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	mini_exit(int argc, char **argv)
{
	pid_t ppid = atoi(argv[1]);

	if (argc != 2)
	{
		fprintf(stderr, "Uso: %s <PID do pai>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (kill(ppid, SIGTERM) == -1)
	{
		perror("Erro ao enviar sinal");
		exit(EXIT_FAILURE);
	}
}
