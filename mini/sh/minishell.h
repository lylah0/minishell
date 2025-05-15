/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:41:45 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/15 16:24:16 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft.h"
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# include <string.h>

# define TRUE 1
# define FALSE 0

extern int			exit_code;

// signals.c
__sighandler_t		handler_sigint(void);
void				init_signals(void);
void				restore_terminal(void);

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

typedef struct s_input
{
	char			*token;
	t_token_type	type;
	struct s_input	*next;
	struct s_input	*prev;
	struct s_data	*data;
}					t_input;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	t_input *input; // ligne de commande
	t_env *env;     // tableau envp
	char			**copy_env;
	int				should_exit;
	int				stdout_redir;
	int				stdin_redir;
}					t_data;

// FONCTIONS LYLAH
// fonctions parsing
char				**fill_tab(char *input, char **array);
void				if_n_op(char *input, char **array, int *k, int *i);
void				if_operator(char *input, char **array, int *k, int i);
int					word_len(char *input);
char				**first_parsing(char *input);
char				**second_parsing(char **array);
char				**parse_input(char *input);
char				**fill_second_tab(char **array, char **tab_token);
int					handle_non_operator(char **tab_token, char *array,
						int *index);
void				handle_operator(char **tab_token, char **array, int *index,
						int i);
void				if_quotes(char *input, char **array, int *k, int *i);
int					while_quotes(char *input, int i);
char				**malloc_second_parsing(int len);
int					is_open_quotes(char *input);
void				is_env_var(t_input *input, t_data *data);
char				*handle_quoted_token(char *quoted_str);
void				print_token_list(t_input *head);
char				*handle_double_quote(char *str, int *i, t_data *data);
char				*handle_env_variable(char *str, int *i);
char				*extract_plain_text(char *str, int *i);
char				*expand_token_string(const char *src, t_data *data);
char				*extract_var_name(const char *str, int *i);
bool				in_quotes(char *str, int index);

// fonctions execution

int					is_builtin(char *cmd);
char				**build_cmd_arg(t_input *token);
int					count_cmd(t_input *head);
void				exec_pipe(t_input *head, char *env_path, t_data *data);
void				parent(int *prev_pipe, t_input **current, int fd[2],
						t_data **data);
void				child(int prev_pipe, t_input *current, int fd[2],
char				*env_path, t_data *data);
t_input				*get_next_command(t_input *node);
int					has_next_cmd(t_input *node);
void				exec(t_input *current, t_data *data, char *env_path, int in_pipe);
int					is_parent_builtin(char *token);
bool				is_safe_to_exec_in_parent(t_input *current);
t_input				*filter_args(t_input *input);

// fonctions redirection

void				simple_redir(t_input *current, t_data *data);
void				redir(t_input *current, t_data *data);
void				heredoc_append(t_input *current, t_data *data);
void				heredoc(t_input *current);
void				validate_redirections(t_input *current);
bool				has_redirection(t_input *current);

// fonctions token

int					is_cmd(char *token, char **env);
t_input				*tokenize(char **input, t_data *data);
t_token_type		get_token_type(t_input *token, char *input, t_data *data);
void				is_cmd_arg(t_input *token);
// int			num_var(t_input *token);
void				parse_and_expand_token(t_input *token, t_data *data);
char				*handle_single_quote(char *str, int *i);
char				*my_getenv(t_data *data, char *var_name);

// fonctions exit code

// fonctions path
char				**split_path(char *fullpath);
char				*find_executable(char **path, char *cmd);
char				*get_path(char *fullpath, char *cmd);
char				*get_env_path(char **env);

// fonctions main [ ] a renommer
void				print_token_type(t_input *token);
void				print_all_token_types(t_input *head);
void				print_tokens(char **tokens);

// FONCTIONS EXEC + MONI

/// built-in
void				b_echo(t_input *cmd);
void				b_env(t_data *data);
void				b_exit(t_data *data, t_input *current, int in_pipe);
void				b_export(t_data *data);
char				*extract_name(char *input);
void				b_pwd(t_data *data);
void				b_unset(t_data *data);
void				b_cd(t_data *data);
int					kind_of_token(t_data *data, t_input *input, int in_pipe);
t_env				*update_env_value(t_env *env, char *env_to_update, char *new_value);

// init_environment // b_export
void				free_lle(t_data *data);
void				print_lle(t_data *data);
t_env				*create_lle(char **envp);
void				swap_words(char **a, char **b);
int					compare_words(char *w1, char *w2);
void				sort_words(char **words, int len);
void				print_copy_env(t_data *data);
void				create_env_copy_array(t_data *data);
int					get_array_length(char **array);
bool				is_valid_env_var_syntax(char *s);
void				b_export(t_data *data);
void				init_env(t_data *data, char **envp);
void				add_env_var(t_data *data, char *input);
void				print_export(t_data *data);
void				add_env_name(t_data *data, char *env_name);
void				add_new_env_var_and_value(t_data *data, char *env_name, char *env_value);

// t_env	*add_env_var(t_data *data, char *input);

t_env				*exist_already_in_env(t_env *env, char *name_var);
void lle_del_one(t_env **env, char *env_to_del);

void				free_lle(t_data *data);
void				print_lle(t_data *data);
t_env				*create_lle(char **envp);
void				swap_words(char **a, char **b);
int					compare_words(char *w1, char *w2);
void				sort_words(char **words, int len);
void				print_copy_env(t_data *data);
void				create_env_copy_array(t_data *data);
int					get_array_length(char **array);
bool				is_valid_env_var_syntax(char *s);
void				b_export(t_data *data);
void				init_env(t_data *data, char **envp);
void				add_env_var(t_data *data, char *input);
t_env				*exist_already_in_env(t_env *env, char *name_var);

// // init_arg
// void init_input(t_input *input);

// utils.c
void				cleanup_memory(char *line, char **splited_line);
char				*ft_strdup_equal(const char *src);
size_t				ft_strcat(char *dest, const char *src);
int					ft_strncmp_end(char *s1, char *s2, size_t n);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
char				*ft_strcpy(char *dest, const char *src);
t_input				*cat_token(t_input *token, char *value, int len);

// signals.c
__sighandler_t		handler_sigint(void);
void				init_signals(void);
void				restore_terminal(void);

// UTILS/lle
t_env				*search_env_name(t_env *env, char *name);
void				lle_add_back(t_env **env, t_env *new1);
void				lle_add_front(t_env **env, t_env *new1);
void				lle_del_one(t_env **env, char *env_to_del);
void				lle_iter(t_env *env, void (*f)(void *));
t_env				*lle_last(t_env *env);
t_env 				*lle_new(char *name, char *value);
int					lle_size(t_env *env);
char				*search_env_value(t_env *env, char *name);
void				ft_printf_stderr(const char *s, ...);

char				*ft_strndup(const char *src, int n);


// content devient name par defaut, a adapter si beosin

#endif
