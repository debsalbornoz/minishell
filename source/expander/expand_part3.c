
#include "../../include/minishell.h"

static void	expand_operator(t_exp *exp, t_env *tmp);
static int	is_operator(char c);
static int	value_len(char *value);

char	*var_expand(t_exp *cur, t_env *var)
{
	char	*res;
	t_exp	exp;
	t_env	tmp;

	tmp = *var;
	exp = *cur;
	res = ft_calloc(1, ft_strlen(exp.input) - ft_strlen(tmp.name)
			+ value_len(tmp.value));
	exp.temp = res;
	while (*&exp.input != *&cur->temp)
		*exp.temp++ = *exp.input++;
	exp.input++;
	while (tmp.value && *tmp.value)
		expand_operator(&exp, &tmp);
	while (exp.input && *(exp.input)
		&& tmp.name && *tmp.name && *exp.input == *tmp.name)
	{
		exp.input++;
		tmp.name++;
	}
	while (*exp.input)
		*exp.temp++ = *exp.input++;
	return (free(cur->input), res);
}

static void	expand_operator(t_exp *exp, t_env *tmp)
{
	if (is_operator(*(tmp->value)))
	{
		*exp->temp++ = '\'';
		*exp->temp++ = *tmp->value++;
		*exp->temp++ = '\'';
	}
	else
		*exp->temp++ = *tmp->value++;
}

static int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

static int	value_len(char *value)
{
	char	sig_quote;
	char	*tmp_value;
	int		qty_operators;

	sig_quote = 0;
	tmp_value = value;
	qty_operators = 0;
	while (ft_str_exist(tmp_value) && *tmp_value)
	{
		sig_quote = process_quotes(sig_quote, *tmp_value);
		if (!sig_quote && is_operator(*tmp_value))
			qty_operators++;
		tmp_value++;
	}
	return ((qty_operators * 2) + ft_strlen(value));
}
