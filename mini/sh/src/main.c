/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:05:13 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/22 14:44:34 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_input	*do_parsing(t_input *head, char **splited_input, t_data *data)
{
	head = tokenize(splited_input, data);
	is_env_var(head, data);
	return (head);
}

static int	handle_exit_command(t_data *data, char *input)
{
	char	**splited_input;

	if (ft_strnstr(input, "exit", ft_strlen(input)) != NULL)
	{
		splited_input = parse_input(data, input);
		if (!splited_input)
			return (1);
		data->input = do_parsing(NULL, splited_input, data);
		b_exit(data, data->input, 0);
		if (data->should_exit == 1)
		{
			clean(data, splited_input, input);
			return (1);
		}
		clean(data, splited_input, input);
		return (1);
	}
	return (0);
}

void	process_input(t_data *data, char *input)
{
	char	**splited_input;
	t_input	*tmp;

	(void)tmp;
	reset_signals_and_pipe(data, input);
	add_history(input);
	if (handle_exit_command(data, input))
		return ;
	splited_input = parse_input(data, input);
	if (!splited_input)
		return ;
	data->env_path = search_env_value(data->env, "PATH");
	if (data->input)
		free_token_list(data->input);
	data->input = do_parsing(NULL, splited_input, data);
	exec_cmd(data, data->input);
	tmp = data->input;
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
