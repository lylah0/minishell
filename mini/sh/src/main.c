/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:05:13 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/22 14:02:33 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_user_input(t_data *data, const char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (!line)
	{
		restore_terminal();
		data->should_exit = YES;
		return (NULL);
	}
	return (line);
}

t_input	*do_parsing(t_input *head, char **splited_input, t_data *data)
{
	head = tokenize(splited_input, data);
	is_env_var(head, data);
	return (head);
}

void	process_input(t_data *data, char *input)
{
	char	**splited_input;

	reset_signals_and_pipe(data, input);
	add_history(input);
	splited_input = parse_input(data, input);
	if (!splited_input)
		return ;
	data->env_path = search_env_value(data->env, "PATH");
	if (data->input)
		free_token_list(data->input);
	data->input = do_parsing(NULL, splited_input, data);
	exec_cmd(data, data->input);
	clean(data, splited_input, input);
}

void	main_loop(t_data *data)
{
	char	*input;

	while (1)
	{
		data->should_exit = 0;
		data->child_pid = -1;
		handle_signals_and_input(data, &input);
		if (!input)
			break ;
		if (handle_empty_or_whitespace_input(data, input))
			continue ;
		process_input(data, input);
		if (data->should_exit == 1)
			break ;
		init_signals(data);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	int		exit_code;

	(void)ac;
	(void)av;
	(void)envp;
	data = init_data();
	init_signals(data);
	init_env(data, envp);
	main_loop(data);
	exit_code = free_all(data);
	exit(exit_code);
}
