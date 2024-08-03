

#include "../../include/minishell.h"

void	print_matrix(char **matrix);

int	program(t_list *envp)
{
	char		*input;
	t_list		tokens;
	t_list		exec;

	tokens.node = 0;
	exec.node = 0;
	readline_status(1);
	input = NULL;
	input = readline("¯\\_(ツ)_/¯: ");
	readline_status(0);
	add_history(input);
	if (!process_input(input, envp, tokens, exec))
	{
		clear_history();
		return (FALSE);
	}
	return (TRUE);
}

int	process_input(char *input, t_list *envp, t_list tokens, t_list exec)
{
	if (!input)
	{
		printf("exit\n");
		return (FALSE);
	}
	if (!*input)
	{
		clear_history();
		return (TRUE);
	}
	input = trim_start_spaces(input);
	if (!input)
		return (TRUE);
	input = expand(envp, input);
	if (!is_closed(input, envp))
		return (TRUE);
	tokens = *lexer(&tokens, input);
	if (!parser(&tokens, envp, input))
		return (TRUE);
	tokens.node = tokens.head;
	if (execute(&tokens, &exec, envp, input))
		return (FALSE);
	return (TRUE);
}

int	readline_status(int sts)
{
	static int	status;

	if (sts != -1)
		status = sts;
	return (status);
}

void	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		printf("%s\n", matrix[i]);
		i++;
	}
}
