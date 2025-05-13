/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:05:13 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/13 12:55:56 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exit_code = 0;

char	*get_user_input(const char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (!line)
	{
		fprintf(stderr, "Error reading line\n");
		return (NULL);
	}
	if (ft_strncmp_end(line, "simulate", 9) == 0)
	{
		printf("simulate\n");
		raise(SIGINT);
	}

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
	data->input = malloc(sizeof(t_input));
	if (!data->input)
	{
		fprintf(stderr, "Error: Memory allocation failed for input\n");
		free(data);
		return (NULL);
	}
	data->input->data = NULL;
	data->env = NULL;
	data->env = malloc(sizeof(t_env));
	if (!data->env)
	{
		perror("init_data, data->env malloc");
		return (NULL);
	}
	data->copy_env = NULL;
	data->stdout_redir = 0;
	data->stdin_redir = 0;
	data->signal = malloc(sizeof(t_signal));
	if (!data->signal)
	{
		fprintf(stderr, "Error: Memory allocation failed for signal\n");
		free(data->env);
		free(data->input);
		free(data);
		return (NULL);
	}
	data->signal->sigint = OFF;
	data->signal->sigquit = OFF;
	data->child_pid = -1;
	return (data);
}


t_input	*do_parsing(t_input *head, char **splited_input, t_data *data)
{
	//print_tokens(splited_input);
	head = tokenize(splited_input, data);
	// print_all_token_types(head);
	is_env_var(head, data);
	// print_token_list(head);
	return (head);
}

void	exec_cmd(t_input *head, t_data *data, char *env_path)
{
	t_input	*curr;

	curr = head;
	if (!curr)
		return ;
	exec_pipe(curr, env_path, data);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**splited_input;
	char	*env_path;
	t_input	*head;
	t_data	*data;

	(void)ac;
	(void)env_path;
	(void)av;
	data = NULL;
	data = init_data(data);
	init_signals(data);
	init_env(data, envp);
	while (1)
	{
		data->should_exit = 0;
		data->child_pid = -1;// handler ne tente rien de foireux avant fork

		input = get_user_input("minishell> ");
		if (!input)
			break;

		if (!ft_strlen(input))
		{
			init_signals(data);
			continue;
		}

		if (data->signal->sigint == ON)
		{
			printf("SIGINT received\n");
			data->signal->sigint = OFF;
		}
		if (data->signal->sigquit == ON)
		{
			printf("SIGQUIT received\n");
			data->signal->sigquit = OFF;
		}

		add_history(input);
		splited_input = parse_input(input);
		if (!splited_input)
			continue;
		env_path = get_env_path(envp);
		head = do_parsing(head, splited_input, data);
		data->input = head;
		exec_cmd(head, data, env_path);
		if (data->should_exit)
			break;

		init_signals(data);
	}

	cleanup_memory(input, splited_input);
	exit(exit_code);
}
