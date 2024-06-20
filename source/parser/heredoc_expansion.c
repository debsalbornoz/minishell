/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 23:43:41 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/19 17:53:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*extract_var_value(int counter, char *input);

char	*expand_input(char *input)
{
	int		i;
	char	*input_expanded;
	int		counter;
	char	*env_value;
	char	*str;

	i = 0;
	input_expanded = NULL;
	env_value = NULL;
	str = NULL;
	while (input[i] != '\0')
	{
		if (input[i] == '$' && input[i + 1] != '\0')
		{
			counter = get_var_len(&input[i + 1]);
			env_value = extract_var_value(counter, &input[i + 1]);
			input_expanded = ft_strjoin_free(input_expanded, env_value);
			i += counter + 1;
		}
		else
		{
			counter = get_substr_len(&input[i]);
			str = extract_substr(&i, counter, input);
			input_expanded = ft_strjoin_free(input_expanded, str);
		}
	}
	return (input_expanded);
}

char	*extract_substr(int *i, int counter, char *input)
{
	char	*str;

	str = ft_calloc(counter + 1, sizeof(char));
	ft_strlcpy(str, &input[*i], counter + 1);
	*i += counter;
	return (str);
}

char	*extract_var_value(int counter, char *input)
{
	char	*env_var;
	char	*env_value;

	env_var = ft_calloc(counter + 1, sizeof(char));
	ft_strlcpy(env_var, input, counter + 1);
	env_value = ft_get_env(env_var);
	free(env_var);
	return (env_value);
}

int	get_var_len(char *input)
{
	int	i;

	i = 0;
	while (input[i] != ' ' && input[i] != '$' && input[i] != '\0')
		i++;
	return (i);
}

int	get_substr_len(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '$' && input[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;
	size_t	len_s1;
	size_t	len_s2;

	result = NULL;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	result = (char *) ft_calloc(len_s1 + len_s2 + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, len_s1 + len_s2 + 1);
	ft_strlcat(result, s2, len_s1 + len_s2 + 1);
	free(s1);
	free(s2);
	return (result);
}

/*
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
		{
			str = get_str(&i, counter, input);
			if (input_expanded)
				input_expanded = ft_strjoin(input_expanded, str);
		}
		if (input[i] == '$' && input[i + 1])
		{
			env_value = get_env_str(&i, counter, input);
			if (input_expanded)
				input_expanded = ft_strjoin(input_expanded, env_value);
		}
		if (str && env_value && !input_expanded)
			input_expanded = ft_strjoin(str, env_value);
		i++;
	}
	input_expanded = return_input_expanded(str, env_value, input_expanded);
	return (input_expanded);
}

char	*return_input_expanded(char	*str, char	*env_value,
	char *input_expanded)
{
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
		*i += counter;
	return (env_value);
}

char	*get_str(int *i, int counter, char *input)
{
	char	*str;

	(void) input;
	str = NULL;
	str = ft_calloc(counter + 1, sizeof(char));
	ft_strlcpy(str, &input[*i], counter + 1);
	if (input[*i + counter])
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
*/
