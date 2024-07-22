/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:46:24 by jraupp            #+#    #+#             */
/*   Updated: 2024/07/22 19:24:44 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "utils.h"
# include "structs.h"
# include <limits.h>
# include "env_list.h"
# include "builtins.h"
# include "../library/lib.h"
# include <sys/types.h>
# include <sys/stat.h>

int		readline_status(int sts);

/* --- source/main --- */
// program.c
int		program(t_list *lst_env);
int		process_input(char *input, t_list *envp, t_list tokens, t_list exec);
int		readline_status(int sts);

//signals.c
void	handle_sigint(int signal);
void	set_error(t_list *lst_env);
void	handle_signal(void);

/* --- source/expander/ --- */
// expand_part1.c
char	*expand(t_list *lst_env, char *input);
char	*search_name(t_list *lst_env, t_exp *exp);

// expand_part2.c
char	*process_dollar(t_exp *exp);
char	*process_heredoc(t_exp *exp);
char	*process_doble_quote(t_list *lst_env, t_exp *exp);
char	*var_expand(t_exp *cur, t_env *var);
char	*var_is_null(char *value, char sig);

/* --- source/lexer/ --- */
//lexer.c
t_list	*lexer(t_list *tokens, char *input);
char	*trim_start_spaces(char *input);
char	process_quotes(char signal, char input);

// process_delimiter.c
int		process_delimiter(t_list *tokens, int signal, char *input, int i);
t_list	*process_redirect(t_list *tokens, char *input, int i);
t_list	*process_redirect_input(t_list *tokens, char *input, int i);
t_list	*process_redirect_output(t_list *tokens, char *input, int i);

// process_word.c
int		process_word(t_list *tokens, int signal, char *input, int i);
int		get_token_len(char *input, int signal, int inside_quotes);
int		is_empty_quotes(char signal, char *input);

/* --- source/parser/ --- */
//parser.c
int		parser(t_list *tokens, t_list	*envp, char *input);

//pipe_error.c
int		pipe_error(t_list	*tokens);
int		check_first_and_last_pipe(t_list	*tokens);
int		check_pipe_after_redirect(t_list	*tokens);

//quotes.c
int		is_closed(char *input, t_list *envp);
int		count_characters_inside_quotes(const char *str,
			int *i, char signal, int inside_quotes);
int		count_characters_outside_quotes(const char *str,
			int *i, int inside_quotes);
void	print_fatal_error(char *input, t_list *envp);

//redirect_error.c
int		find_redirect(int type);
int		redirect_error(t_list	*tokens);
int		redirect_at_end(t_list *tokens);

//remove_quotes.c
t_list	*remove_quotes(t_list *tokens);
t_node	*replace_str(t_node *node);
char	*unquote_str(char *str, char *temp, int i, int j);
int		find_new_len(const char *str, int len, int i, int counter);

//syntax_error.c
int		syntax_error(t_list *tokens, t_list	*lst_env, char *input);
int		redirect_error(t_list	*tokens);
int		dot_error(t_list	*tokens);
int		its_braces(t_list *tokens);

/* --- source/parser/heredoc --- */
//handle_heredoc.c
t_list	*process_heredoc_tokens(t_list *tokens);
char	*handle_heredoc(t_node *token, char *eof, char *filename);
int		setup_heredoc_env(char *filename);
char	*remove_eof_quotes(char *eof);
char	*get_filename(int i);

//heredoc_expansion.c
char	*expand_input(char *input, int i, int counter);
char	*extract_substr(int *i, int counter, char *input);
char	*ft_strjoin_free(char *s1, char *s2);

//heredoc_signals.c
void	handle_heredoc_signals(void);
void	handle_ctrlc_heredoc(int signal);
int		check_signals(char *input, char *filename, int fd_in);

//heredoc_utils.c
int		is_quoted(char *eof);
int		get_substr_len(char *input);
int		get_var_len(char *input);
char	*extract_var_value(int counter, char *input);

//open_here_prompt.c
int		open_prompt(char *eof, int flag, int fd, char *filename);
void	write_in_file(char *input, int fd, int flag);
int		open_here_file(char *filename);

/* --- source/parser/type_assignment --- */
//builtins.c
t_node	*is_builtin(t_node *node);
int		identify_builtin(char *token, char *builtin, int token_len);
int		compare_quoted_strings(char *token, char *builtin);

//commands_and_arguments.c
t_node	*is_command_part1(t_node *head);
t_node	*is_command_part2(t_node *node);
t_node	*is_argument(t_node *node);
t_node	*is_command_part3(t_node *tokens);

// files.c
t_node	*is_file(t_node *node);
t_node	*is_heredoc_key(t_node *node);

//path.c
t_node	*is_path(t_node *node);

// type_assignment.c
t_list	*type_assignment(t_list *tokens);

/* --- execution --- */
//builtins.c
int		handle_builtins(char **cmd_table,
			t_list *envp, int type, union u_func f);
int		execute_builtins(t_node *exec, t_list *envp);

//exec_utils.c
int		find_file(int type);
int		is_file_redirect_or_pipe(int type);
int		validate_command(t_node *exec);
int		is_simple_command(t_list *tokens);

//execute_multiple_commands.c
int		fork_and_execute_command(int *std_fds,
			int **pipes, t_node *node, int *pid);
int		handle_multi_exec(t_list *exec, int num_pipes, int **pipes, int *pids);
int		execute_multiple_commands(t_list *exec, t_list *tokens,
			t_list *envp, char *input);

//execute_simple_command.c
int		execute_simple_command(t_list *exec,
			t_list *tokens, t_list *envp, char *input);

//execution.c
int		execute(t_list *lst_tokens, t_list *lst_exec,
			t_list *lst_env, char *input);
int		handle_execution(t_node *exec, t_list *envp);
void	restore_file_descriptors(int fd_in, int fd_out);

//finish_proccess.c
void	finish_process(t_list *exec, t_list *tokens, t_list *envp, char *input);
void	free_matrix(char **matrix);
void	close_fds(void);
void	free_pipes(int **pipes);

//handle_wait.c
void	wait_for_children(t_list *envp, int *pids, int num_process);
void	free_strs(char *status, char *last_command, int flag);
char	*update_signal_sts(int status, char *sts);
char	*update_sts(char *sts, int status);

//pipe.c
void	setup_pipes(int command_index, int fd_in,
			int fd_out, int **pipes);
int		count_pipes(t_list *exec);
int		**create_pipes(int num_pipes);
void	close_pipes(int command_index, int **pipes, int num_pipes);
int		count_pipes2(int **pipes);

/* --- source/execution/create lst exec--- */

//create_lst_exec.c

//command_table.c
void	create_command_table(t_list *tokens, t_list *exec);
char	**allocate_cmd_table(t_node *tokens);
void	allocate_multi_cmd_table(t_list *tokens, t_list *exec);
void	create_simple_cmd_table(t_list *tokens, t_list *exec);
void	create_multi_cmd_table(t_list *tokens, t_list *exec);
void	fill_command_table(t_list *tokens, t_list *exec);

//create_lst_exec.c
t_list	*create_lst_exec(t_list *tokens, t_list *exec, t_list *envp);
t_list	*initialize_lst_exec(t_list *tokens, t_list *exec, t_list *envp);
void	get_index(t_list *exec);

//create_path.c
char	*create_absolute_path(char **path_array,
			char **command_table, t_node *exec);
char	*concatenate_path(char *path, char *command);

//env_list_to_str_array.c
char	**env_list_to_str_array(t_list *lst_env);
char	*build_env_var(char *s1, char *s2);

//save_redirects_and_files.c
void	save_redirects_and_files(t_list *exec, t_list *tokens);
char	**allocate_redir_and_files(t_node *tokens);
char	**get_redirects_and_files(t_node **tokens, char **redir_and_files);
void	create_simple_redir_table(t_list	*tokens, t_list *exec);
void	allocate_multi_redir_table(t_node *aux_exec,
			t_node *aux_tokens, int counter);
void	create_multi_redir_table(t_list *tokens, t_list *exec);
char	**allocate_redir_table(t_node *tokens);
void	fill_redir_and_files(t_list *tokens, t_list *exec);

//split_path.c
char	**split_path(t_list *envp);
int		count_paths(const char *value);
char	*return_value(t_list *envp, char *name);
char	*get_path(char *value, int i, int len, int j);
int		get_len(char *value);

//validate_path.c
void	find_path(t_list *tokens, t_list *exec, t_list *envp);
char	*validate_path(char **command_table, t_node *exec, t_list *envp);
int		check_command_validity(char *command,
			t_list *envp, char **command_table);
int		is_executable(t_node *exec, char *path);
int		is_absolute_path(char **command_table);

/* --- source/execution/redirects--- */
//handle_redirect.c
int		handle_redirect(t_node *exec, t_list *envp, int fd_in, int fd_out);
int		open_file(char **redir_and_files, int i, int flag, t_list *envp);
int		set_flag(char *redirect);

//redirect_utils.c
int		find_output(char *str);
int		find_append(char *str);
int		find_input(char *str);
int		find_heredoc(char *str);
void	handle_heresignals(void);
char	*ft_get_env(char *name);

#endif
