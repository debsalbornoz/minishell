/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:43:15 by jraupp            #+#    #+#             */
/*   Updated: 2024/05/23 20:01:12 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/builtins.h"

int	cd(int argc, char **argv)
{
	char	cwd[2048];

	if (argc != 2)
	{
		printf("Uso: %s <caminho_do_diretorio>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (chdir(argv[1]))
	{
		perror("Erro ao mudar o diretório");
		exit(EXIT_FAILURE);
	}
	if (getcwd(cwd, sizeof(cwd)))
		printf("Diretório atual: %s\n", cwd);
	else
	{
		perror("Erro ao obter o diretório atual");
		exit(EXIT_FAILURE);
	}
	return (0);
}
