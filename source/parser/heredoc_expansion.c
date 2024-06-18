/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 23:43:41 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/18 14:07:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		count_var_size(char *input);
char	*get_env_value(int counter, char *input);
int		get_input_len(char *input);
char	*get_str(int *i, int counter, char *input);

char	*return_var(char *input)
{
	int		i;
	int		counter;
	char	*env_value;
	char	*input_expanded;
	char	*str;

	i = 0;
	counter = 0;
	env_value = NULL;
	input_expanded = NULL;
	str = NULL;
	while (input[i] != '\0')
	{
		counter = get_input_len(input);
		if (counter > 0)
			str = get_str(&i, counter, input);
		if (input[i] == '$' && input[i + 1])
			env_value = get_env_str(&i, counter, input);
		if (str && env_value)
			input_expanded = ft_strjoin(str, env_value);
		i++;
	}
	if (!str && env_value)
		input_expanded = env_value;
	if (str && !env_value)
		input_expanded = str;
	return (input_expanded);
}

char	*get_env_str(int *i, int counter, char *input)
{
	char	*env_value;

	env_value = NULL;
	counter = count_var_size(&input[*i + 1]);
	env_value = get_env_value(counter, &input[*i + 1]);
	if (input[*i + counter])
		*i += counter - 1;
	return (env_value);
}

char	*get_str(int *i, int counter, char *input)
{
	char	*str;

	(void) input;
	str = NULL;
	str = ft_calloc(counter + 1, sizeof(char));
	ft_strlcpy(str, &input[*i], counter + 1);
	if (input[*i + counter - 1])
		*i += counter;
	return (str);
}

int	count_var_size(char *input)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (input[i] != 13 && input[i] != 32
		&& input[i] != '$' && input[i] != '\0')
	{
		counter++;
		i++;
	}
	return (counter);
}

char	*get_env_value(int counter, char *input)
{
	char	*env_var;
	char	*env_value;

	env_var = NULL;
	env_var = ft_calloc((counter + 1), sizeof(char));
	ft_strlcpy(env_var, input, counter + 1);
	env_value = ft_get_env(env_var);
	free (env_var);
	return (env_value);
}

int	get_input_len(char *input)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (input[i] != '$' && input[i] != '\0')
	{
		counter++;
		i++;
	}
	return (counter);
}
