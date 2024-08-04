/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:57:17 by dlamark-          #+#    #+#             */
/*   Updated: 2024/08/04 10:51:08 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	syntax_error(t_list *tokens, t_list	*envp, char *input)
{
	if (redirect_error(tokens) || pipe_error(tokens)
		|| dot_error(tokens) || its_braces(tokens))
	{
		ft_putstr_fd("Syntax error\n", 2);
		update_env_list(envp, "?", "2");
		free_list(tokens, free_lst_tokens);
		free(input);
		return (1);
	}
	if (dot_error(tokens) == 2)
	{
		ft_putstr_fd("Syntax error\n", 2);
		update_env_list(envp, "?", "127");
		free_list(tokens, free_lst_tokens);
		free(input);
		return (1);
	}
	return (0);
}

int	dot_error(t_list	*tokens)
{
	char	*str;

	str = tokens->head->data->token->value;
	if ((!ft_strncmp(str, ".", ft_strlen(str))
			|| !ft_strncmp(str, "\'.\'", ft_strlen(str))
			|| !ft_strncmp(str, "\".\"", ft_strlen(str)))
		&& tokens->head->next == NULL)
		return (1);
	if ((!ft_strncmp(str, "..", ft_strlen(str))
			|| !ft_strncmp(str, "\'..\'", ft_strlen(str))
			|| !ft_strncmp(str, "\"..\"", ft_strlen(str)))
		&& tokens->head->next == NULL)
		return (2);
	return (0);
}

int	its_braces(t_list *tokens)
{
	t_node	*aux;

	if (!tokens)
		return (-1);
	aux = tokens->head;
	while (aux)
	{
		if (aux == tokens->head)
		{
			if (aux->next == NULL)
			{
				if (ft_strncmp("{", aux->data->token->value,
						ft_strlen(aux->data->token->value)) == 0
					|| ft_strncmp("}", aux->data->token->value,
						ft_strlen(aux->data->token->value)) == 0)
					return (1);
			}
			if (ft_strncmp("}", aux->data->token->value,
					ft_strlen(aux->data->token->value)) == 0)
				return (1);
		}
		aux = aux->next;
	}
	return (0);
}
