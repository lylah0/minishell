/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:06:47 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 21:52:56 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include "../lib/libft.h"

# define YES 1
# define NO 0
# define TRUE 1
# define FALSE 0
# define ON 1
# define OFF 0
# define ECHOCTL 0001000

// Enumération des différents types de tokens
typedef enum s_token_type
{
	T_CMD,
	T_CMD_ARG,
	T_ARG,
	T_FILE,
	T_OP,
	T_PIPE,
	T_SKIP,
	T_WORD
}					t_token_type;

// Structure représentant un token dans la liste chaînée
typedef struct s_input
{
	char			*token;
	t_token_type	type;
	struct s_input	*next;
	struct s_input	*prev;
	struct s_data	*data;
}					t_input;

// Structure représentant une variable d'environnement
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

// Enumération des états des signaux
typedef enum e_signal_state
{
	SIGNAL_OFF,
	SIGNAL_ON
}					t_signal_state;

// Structure pour gérer les signaux
typedef struct s_signal
{
	t_signal_state	sigint;
	t_signal_state	sigquit;
}					t_signal;

// Structure principale contenant toutes les données du programme
typedef struct s_data
{
	t_input			*input;
	t_env			*env;
	t_signal		*signal;
	char			**copy_env;
	char			*env_path;
	char			**array;
	int				should_exit;
	int				exit_code;
	int				stdout_redir;
	int				stdin_redir;
	pid_t			child_pid;
	int				pipe_op;
}					t_data;

void			add_new_env_var_and_value(t_data *data, char *env_name,
					char *env_value);
void			add_env_name(t_data *data, char *env_name);
void			add_env_var(t_data *data, char *input);
int				append_to_result(char **result, char *temp);
void			append_char_to_result(char **result, char c);
void			append_str_to_result(char **result, const char *str);
void			b_cd(t_data *data);
void			b_echo(t_data *data, t_input *current);
void			b_env(t_data *data);
void			b_exit(t_data *data, t_input *current, int in_pipe);
void			b_export(t_data *data);
void			b_pwd(t_data *data);
void			b_unset(t_data *data);
char			**build_cmd_arg(t_input *token);
t_input			*cat_token(t_input *token, char *value, int len);
void			child(t_data *data, int prev_pipe, t_input *current, int fd[2]);
void			clean(t_data *data, char **splited_input, char *env_path,
					char *input);
int				compare_words(char *w1, char *w2);
int				copy_substring(char *input, char **array_ptr, int start,
					int len);
int				count_args(t_input *token);
int				count_cmd(t_input *head);
int				count_second_parsing_len(char **array);
int				count_tokens(const char *input);
char			**create_env_copy_array(t_data *data);
t_env			*create_env_node(const char *env);
t_env			*create_lle(t_data *data, char **envp);
void			exec(t_data *data, t_input *current, int in_pipe);
void			exec_cmd(t_data *data, t_input *head);
void			exec_pipe(t_data *data, t_input *head);
t_env			*exist_already_in_env(t_env *env, char *name_var);
char			*expand_token_part(char *input, int *i, t_data *data);
char			*expand_token_string(const char *src, t_data *data);
void			expand_env_var_into_array(t_data *data, char *input,
					char **array_ptr, int *k, int *j);
char			*extract_name(char *env_var);
char			*extract_plain_text(char *str, int *i);
char			*extract_value(char *env_var);
char			*extract_var_name(const char *str, int *i);
void			fill_cmd_args(char **cmd, t_input *token);
char			**fill_second_tab(char **array, char **tab_token);
char			**fill_tab(t_data *data, char *input);
t_input			*filter_args(t_input *args);
int				find_equal(char *s);
char			*find_executable(char **path, char *cmd);
char			**first_parsing(t_data *data, char *input);
int				free_all(t_data *data);
void			free_lle(t_data *data);
void			free_tab(char **tab);
void			free_token_list(t_input *head);
size_t			ft_strcat(char *dest, const char *src);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strdup_equal(const char *src);
char			*ft_strndup(const char *src, int n);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
int				ft_striswhitespace(const char *str);
int				ft_strncmp_end(char *s1, char *s2, size_t n);
void			ft_printf_stderr(const char *s, ...);
t_data			*get_data_ptr(t_data *new_data);
char			*get_env_path(char **env);
char			*get_path(char *fullpath, char *cmd);
t_input			*get_next_command(t_input *node);
char			*get_user_input(t_data *data, const char *prompt);
int				handle_normal_word(t_data *data, char *input, int *k, int i);
int				handle_parent_builtin(t_data *data, t_input *current);
void			handle_fork(t_data *data, int *prev_pipe, t_input **current,
					int *fd);
int				handle_special_cases(const char *src, int *i, char **result);
void			handle_operator(char **tab_token, char **array, int *index,
					int i);
void			handler_sigint(int signum);
void			handler_sigquit(int signum);
char			*handle_double_quote(char *str, int *i, t_data *data);
char			*handle_env_variable(t_data *data, char *str, int *i);
int				handle_empty_or_whitespace_input(t_data *data, char *input);
int				handle_token_logic(const char *input, int *i, int *len);
char			*handle_quoted_token(char *quoted_str);
char			*handle_single_quote(char *str, int *i);
void			handle_signals_and_input(t_data *data, char **input);
void			heredoc(t_input *current);
void			heredoc_append(t_input *current, t_data *data);
int				has_next_cmd(t_input *node);
bool			has_redirection(t_input *current);
void			if_n_op(t_data *data, char *input, int *k, int *i);
void			if_operator(char *input, char **array, int *k, int i);
void			if_quotes(char *input, char **array, int *k, int *i);
void			init_env(t_data *data, char **envp);
t_data			*init_data(void);
void			init_signals(t_data *data);
t_signal		*init_signal_struct(void);
bool			in_quotes(char *str, int index);
int				is_builtin(char *cmd);
int				is_cmd(char *token, char **env);
void			is_cmd_arg(t_input *token);
void			is_env_var(t_input *input, t_data *data);
int				is_open_quotes(char *input);
int				is_parent_builtin(char *token);
bool			is_safe_to_exec_in_parent(t_input *current);
bool			is_valid_env_name_var_syntax(char *s);
bool			is_valid_env_value_syntax(char *s);
int				kind_of_token(t_data *data, t_input *input, int in_pipe);
t_env			*lle_last(t_env *env);
t_env			*lle_new(char *name, char *value);
void			lle_add_back(t_env **env, t_env *new1);
void			lle_del_one(t_env **env, char *env_to_del);
void			lle_to_array(t_data *data);
int				lle_size(t_env *env);
char			**malloc_second_parsing(int len);
char			*my_getenv(t_data *data, char *var_name);
int				open_redirection_file(t_input *current);
char			**parse_input(t_data *data, char *input);
void			parse_and_expand_token(t_input *token, t_data *data);
void			parent(int *prev_pipe, t_input **current, int fd[2]);
void			print_copy_env(t_data *data);
void			print_export(t_data *data);
void			print_lle(t_data *data);
void			print_token_list(t_input *head);
int				quotes(char *input, int *k, int *in_quote, char *quote_char);
void			redir(t_input *current, t_data *data);
char			**second_parsing(char **array);
t_env			*search_env_name(t_env *env, char *name);
char			*search_env_value(t_env *env, char *name);
void			simple_redir(t_input *current, t_data *data);
void			sort_words(char **words, int len);
void			split_env(const char *env, char **name, char **value);
void			swap_words(char **a, char **b);
char			**split_path(char *fullpath);
int				str_isdigit(char *str);
char			*strjoin_name_equal_value(char *name, char *value);
t_input			*tokenize(char **input, t_data *data);
t_token_type	get_token_type(t_input *token, char *input, t_data *data);
int				quotes(char *input, int *k, int *in_quote,
					char *quote_char);
void			redir(t_input *current, t_data *data);
void			reset_signals_and_pipe(t_data *data, char *input);
void			restore_terminal(void);
t_env			*update_env_value(t_data *data, char *env_to_update,
					char *new_value);
void			validate_redirections(t_data *data, t_input *current);
int				while_quotes(const char *input, int i);
int				word_len(char *input);

#endif