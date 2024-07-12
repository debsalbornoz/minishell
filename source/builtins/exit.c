/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jackson <jackson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:35:24 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/08 14:31:37 by jackson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int			is_sig(char chr);
static int			is_dig(char chr);
static long long	zatoi(const char *arg);
static int			valid_nbr(char *arg);

int	mini_exit(char **exec, t_list *envp)
{
	unsigned long long	nbr;

	nbr = 0;
	printf("exit\n");
	if (!ft_str_exist(*(exec + 1)))
		return (update_env_list(envp, "?", "0"), 1);
	else if (ft_str_exist(*(exec + 2)))
		return (printf(" too many arguments\n"),
			update_env_list(envp, "?", "1"), 0);
	if (valid_nbr(*(exec + 1)))
		return (printf("exit: non-numerical argument\n"),
			update_env_list(envp, "?", "2"), 0);
	nbr = zatoi(*(exec + 1));
	if (nbr > 255)
		return (nbr % 256);
	else
		return (nbr);
}

static int	is_sig(char chr)
{
	return (chr == '+' || chr == '-');
}

static int	is_dig(char chr)
{
	return (chr >= '0' && chr <= '9');
}

static long long	zatoi(const char *arg)
{
	int			sig;
	long long	res;

	sig = 1;
	res = 0;
	if (is_sig(*arg))
	{
		if (*arg++ == '-')
			sig *= -1;
	}
	while (*arg && is_dig(*arg))
		res = res * 10 + (*arg++ - '0');
	return (res * sig);
}

static int	valid_nbr(char *arg)
{
	int		i;
	char	*arg_tmp;

	i = -1;
	arg_tmp = arg;
	if (!ft_str_exist(arg_tmp))
		return (1);
	while (++i, *arg_tmp)
	{
		if (!i && !(is_sig(*arg_tmp) || is_dig(*arg_tmp))
			&& is_sig(*arg_tmp) && !*(arg_tmp + 1))
			return (1);
		else if ((i && !is_dig(*arg_tmp)) || i > 17)
			return (1);
		arg_tmp++;
	}
	return (0);
}
