/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:05:13 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/07 15:47:02 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_user_input(const char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (!line)
	{
		fprintf(stderr, "Error reading line\n");
		return (NULL);
	}
	add_history(line);
	return (line);
}

t_data	*init_data(t_data *data)
{
	data = malloc(sizeof(t_data));
	if (!data)
	{
		fprintf(stderr, "Error: Memory allocation failed\n");
		return (NULL);
	}
	data->input = NULL;
	data->input = malloc(sizeof(char) * 1024);
	if (!data->input)
	{
		fprintf(stderr, "Error: Memory allocation failed for input\n");
		free(data);
		return (NULL);
	}
	data->env = NULL;
	data->env = malloc(sizeof(t_env));
	if (!data->env)
		return NULL;
	data->copy_env = NULL;
	data->exit_status = 0;
	return (data);
}

t_input	*do_parsing(t_input *head, char **splited_input)
{
//	print_tokens(splited_input);
	head = tokenize(splited_input);
//	print_all_token_types(head);
	is_env_var(head);
//	print_token_list(head);
	return (head);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**splited_input;
	char	*env_path;
	t_input	*head;
	t_data	*data;
	(void)ac;
	(void)av;
	(void)envp;
	(void)data;
	init_signals();
	data = NULL;
	data = init_data(data);
	while (1)
	{
		input = get_user_input("minishell> ");
		splited_input = parse_input(input);
		env_path = get_env_path(envp);
		init_env(data, envp);
		head = do_parsing(head, splited_input);
		exec_pipe(head, env_path);
		restore_terminal();
		cleanup_memory(input, splited_input);
		init_signals();
	}
	return (0);
}
