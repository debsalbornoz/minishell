int		program(void)
{
	t_list	list;
	char	*input;

	input = readline("¯\\_(ツ)_/¯: ");
	if (!*input)
		return (FALSE);
	list = *init_list(&list);
	list = *tokenization(&list, input);
	print_list(&list);
	free_list(&list);
	return (FALSE);
}t_list	*tokenization(t_list *list, char *input)
{
	char	signal;
	char	*temp;
	int		i;
	
	temp = 0;
	signal = 0;
	i = 0;
	
	input = trim_start_spaces(input);
	while (input[i] != '\0')
	{
		signal = process_quotes(signal, input[i]);
		temp = form_word(list, signal, input, temp, i);
		temp = process_delimiter(list, signal, input, temp,i);
		if(is_heredoc(input[i], input[i + 1]) || is_append(input[i], input[i + 1]))
			i++;
		temp = form_word(list, signal, input, temp, i);
		i++;
	}
	return (list);
}char	*form_word(t_list *list, int signal, char *input, char *temp, int i)
{
	if ((temp && !input[i + 1])
		|| (temp && !signal && is_delimiter(input[i])))
	{
		list = add_node(list, temp);
		temp = 0;
	}
	return (temp);
}