/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_assignment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:26:00 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/12 21:57:31 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*is_command(t_list *tokens)
{
	tokens->node = tokens->head;
	if (tokens->node)
	{
		while (tokens->node != NULL)
		{
			if (tokens->head->type == WORD)
				tokens->node->type = COMMAND;
			if (tokens->node->type == PIPE)
				if (tokens->node->next && tokens->node->next->type != PIPE && tokens->node->next->type != OUTPUT && tokens->node->next->type != INPUT && tokens->node->next->type != HEREDOC && tokens->node->next->type != APPEND )
					tokens->node->next->type = COMMAND;
			tokens->node = tokens->node->next;
		}
	}
	tokens->node = tokens->head;
	return(tokens);
}

t_list 	*type_assignment(t_list *tokens)
{
	
	tokens = is_command(tokens);
	// is_argument(tokens);
	return(tokens);
}

/*
void is_builtin(t_list *tokens)
{
	char *builtins[] = {"echo", "pwd", "cd", "env", "exit", NULL};
	int i;

	while(tokens->node != NULL)
	{
		i = 0;
		while(builtins[i] != NULL)
		{
			if(ft_strlcmp(tokens->node->value, builtins[i]))
			{
				tokens->node->type = BUILTIN;
			}
			i++;
		}
		tokens->node = tokens->node->next;

	}
}

int ft_strlcmp(char *s1, char *s2)
{
	int len_s1 = ft_strlen(s1);
	int len_s2 = ft_strlen(s2);
	int i = 0;
	char signal = 0;
	int j;
	signal = process_quotes(signal,s1[i]);
	if(!signal)
	{
		if(len_s1 == len_s2)
		{
			while(s1[i] == s2[i])
				i++;
			if(s1[i] != s2[i])
				return(0);
			return(1);
		}
		return(0);
	}
	if(signal)
	{
		i = 0;
		j = 1;
		if(is_quote(s1[0]) && is_quote(s1[len_s1 - 1]))
		{
			if((len_s1 - 2) == len_s1)
			{
				while(s2[i] != '\0')
				{
					if(s1[j] != s2[i])
						return(0);
					i++;
					j++;
				}
				return(1);
			}
		}
	}
		return(0);
}


// void	is_argument(t_list *tokens)
//{
// 	tokens->node = tokens->head;
// 	while (tokens->node != NULL)
// 	{
// 		if (tokens->node->type == COMMAND)
// 		{
// 			if (tokens->node->type)
// 			{
// 				while (tokens->node->next->type != PIPE
// 					&& tokens->node->next->type != REDIRECT
// 					&& tokens->node->next != NULL)
// 				{
// 						tokens->node->next->type = ARGUMENT;
// 						tokens->node = tokens->node->next;
// 				}
// 			}
// 		}
// 		tokens->node = tokens->node->next;
// 	}
// }


*/
