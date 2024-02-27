/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:01:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/02/20 17:54:09 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[]) {
    char *str;
    t_tokens *token;
    t_tokens *temp;

    token = NULL;
    argv = NULL;

    if (argc == 1 && argv == NULL) {
        while (1) {
            str = readline("$");
            init_tokenization(&token, str);
            temp = token;

            while (temp != NULL) {
                printf("%s\n %s\n", temp->type, temp->value);
                temp = temp->next;
            }
        }
    }

    return 0;
}
