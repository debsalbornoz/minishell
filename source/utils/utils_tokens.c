/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:03:17 by jraupp            #+#    #+#             */
/*   Updated: 2024/04/24 15:00:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	aux_print_tokens(int type);
static void	aux_print_tokens_delimiter(int type);
static void	aux_print_tokens_builtin(int type);
static void	aux_print_tokens_argument(int type);

t_node	*print_lst_tokens(t_node *node)
{
	aux_print_tokens(node->data->token->type);
	printf("%s\n", node->data->token->value);
	return (node);
}

static void	aux_print_tokens(int type)
{
	aux_print_tokens_delimiter(type);
	aux_print_tokens_builtin(type);
	aux_print_tokens_argument(type);
}

static void	aux_print_tokens_delimiter(int type)
{
	if (type == DELIMITER)
		printf("type: delimiter,	value: ");
	else if (type == REDIRECT)
		printf("type: redirect,	value: ");
	else if (type == INPUT)
		printf("type: input,	value: ");
	else if (type == HEREDOC)
		printf("type: heredoc,	value: ");
	else if (type == OUTPUT)
		printf("type: output,	value: ");
	else if (type == APPEND)
		printf("type: append,	value: ");
	else if (type == PIPE)
		printf("type: pipe,	value: ");
}

static void	aux_print_tokens_builtin(int type)
{
	if (type == WORD)
		printf("type: word,	value: ");
	else if (type == COMMAND)
		printf("type: command,	value: ");
	else if (type == EXECUTABLE)
		printf("type: executable,	value: ");
	else if (type == BUILTIN)
		printf("type: builtin,	value: ");
	else if (type == ECHO)
		printf("type: echo,	value: ");
	else if (type == CD)
		printf("type: cd,	value: ");
	else if (type == PWD)
		printf("type: pwd,	value: ");
	else if (type == EXPORT)
		printf("type: export,	value: ");
	else if (type == UNSET)
		printf("type: unset,	value: ");
	else if (type == ENV)
		printf("type: env,	value: ");
	else if (type == EXIT)
		printf("type: exit,	value: ");
}

static void	aux_print_tokens_argument(int type)
{
	if (type == ARGUMENT)
		printf("type: argument,	value: ");
	else if (type == FILES)
		printf("type: files,	value: ");
	else if (type == INPUT_FILE)
		printf("type: input_file,	value: ");
	else if (type == OUTPUT_FILE)
		printf("type: output_file,	value: ");
	else if (type == APPEND_FILE)
		printf("type: append_file,	value: ");
	else if (type == FLAG)
		printf("type: flag,	value: ");
	else if (type == HEREDOC_KEY)
		printf("type: heredoc_key,	value: ");
	else if (type == ERROR)
		printf("type: error,	value: ");
	else if (type == PATH)
		printf("type: path,	value: ");
}
