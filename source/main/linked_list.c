/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:51:10 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/16 14:26:40 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void aux_print_list(int type);

t_list	*init_list(t_list *list)
{
	list->node = 0;
	list->head = list->node;
	list->tail = list->node;
	return (list);
}

t_list	*add_node(t_list *list, char *value)
{
	if (!list->node)
	{
		list->node = ft_calloc (1, sizeof(t_node_env));
		list->head = list->node;
	}
	else
	{
		list->node = list->tail;
		list->node->next = ft_calloc (1, sizeof(t_node_env));
		list->node = list->node->next;
	}
	list->tail = list->node;
	list->node->value = ft_strdup(value);
	return (list);
}

void	print_list(t_list *list)
{
	if (list->node)
	{
		list->node = list->head;
		while (list->node && list->node->next)
		{
			aux_print_list(list->node->type);
			printf("%s\n", list->node->value);
			list->node = list->node->next;
		}
		aux_print_list(list->node->type);
		printf("%s\n", list->node->value);
	}
}

/*void	free_list(t_list *list)
{
	if (list->node)
	{
		list->node = list->head;
		while (list->node && list->node->next)
		{
			list->head = list->node->next;
			list->node->prev = NULL;
			free(list->node->value);
			free(list->node);
			list->node = list->head;
		}
		free(list->node->value);
		free(list->node);
	}
}
*/

void	free_list(t_list *list)
{
	t_node_token	*next_node;

	if (list)
	{
		while (list->node)
		{
            next_node = list->node->next;
            if (list->node->value)
                free(list->node->value);
            free(list->node); 
            list->node = next_node;
        }
        list->head = NULL;
        list->node = NULL;
    }
}

static void aux_print_list(int type)
{
	switch (type)
	{
		case DELIMITER:
			printf("type: delimiter, value: ");
			break;
		case REDIRECT:
			printf("type: redirect, value: ");
			break;
		case INPUT:
			printf("type: input, value: ");
			break;
		case HEREDOC:
			printf("type: heredoc, value: ");
			break;
		case OUTPUT:
			printf("type: output, value: ");
			break;
		case APPEND:
			printf("type: append, value: ");
			break;
		case PIPE:
			printf("type: pipe, value: ");
			break;
		case WORD:
			printf("type: word, value: ");
			break;
		case COMMAND:
			printf("type: command, value: ");
			break;
		case EXECUTABLE:
			printf("type: executable, value: ");
			break;
		case BUILTIN:
			printf("type: builtin, value: ");
			break;
		case ECHO:
			printf("type: echo, value: ");
			break;
		case CD:
			printf("type: cd, value: ");
			break;
		case PWD:
			printf("type: pwd, value: ");
			break;
		case EXPORT:
			printf("type: export, value: ");
			break;
		case UNSET:
			printf("type: unset, value: ");
			break;
		case ENV:
			printf("type: env, value: ");
			break;
		case EXIT:
			printf("type: exit, value: ");
			break;
		case ARGUMENT:
			printf("type: argument, value: ");
			break;
		case FILES:
			printf("type: files - value: ");
			break;
		case INPUT_FILE:
			printf("type: input_file - value: ");
			break;
		case OUTPUT_FILE:
			printf("type: output_file - value: ");
			break;
		case FLAG:
			printf("type: flag - value: ");
			break;
		case HEREDOC_KEY:
			printf("type: heredoc_key - value: ");
			break;
		case VARIABLE:
			printf("type: variable - value: ");
			break;
		case ERROR:
			printf("type: error - value: ");
			break;
	}
}
