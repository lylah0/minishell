/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:05:13 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/10 11:30:58 by monoguei         ###   ########.fr       */
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

void	exec_cmd(t_input *head, t_data *data, char *env_path)
{
	t_input	*curr;

	curr = head;
	if (!curr)
		return;
	if (is_builtin(head->token))
		kind_of_token(data, head);
	else
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
	(void)av;
	init_signals();
	data = NULL;
	data = init_data(data);
	init_env(data, envp);
	while (1)
	{
		input = get_user_input("minishell> ");
		splited_input = parse_input(input);
		// print_tokens(splited_input);
		head = tokenize(splited_input);
//		remove_quotes(head);
		first_word(splited_input, envp);
		data->input = head;
		
		// b_export(data);
		print_all_token_types(head);
		is_env_var(head);
		print_token_list(head);
		kind_of_token(data, head);
		//exit
		restore_terminal();
		init_signals();
		if (!ft_strlen(input))
		{
			restore_terminal();
			init_signals();
		}
		else
		{
			splited_input = parse_input(input);
			env_path = get_env_path(envp);
			init_env(data, envp);
			head = do_parsing(head, splited_input);
			data->input = head;
			exec_cmd(head, data, env_path);
			restore_terminal();
			cleanup_memory(input, splited_input);
			init_signals();
		}
	}
	// cleanup_memory(input, splited_input);// [ ] builtin exit
	return (0);
}
