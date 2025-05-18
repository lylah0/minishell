/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:05:13 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/18 13:05:01 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*init_data(void)
{
    t_data *data = malloc(sizeof(t_data));
    if (!data)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return (NULL);
    }
    data->input = NULL;
    data->env = NULL;
    data->copy_env = NULL;
    data->stdout_redir = 0;
    data->stdin_redir = 0;
    data->should_exit = 0;
    data->child_pid = -1;
    data->exit_code = 0;
	data->signal = NULL;

    // Allouer la structure signal
    data->signal = malloc(sizeof(t_signal));
    if (!data->signal)
    {
        fprintf(stderr, "Error: Memory allocation failed for signal\n");
        free(data);
        return (NULL);
    }
    data->signal->sigint = OFF;
    data->signal->sigquit = OFF;

    return data;
}

t_input	*do_parsing(t_input *head, char **splited_input, t_data *data)
{
	// print_tokens(splited_input);
	head = tokenize(splited_input, data);
	// print_all_token_types(head);
	is_env_var(head, data);
	// print_token_list(head);
	return (head);
}

void	exec_cmd(t_data *data, t_input *head, char *env_path)
{
	t_input	*curr;

	curr = head;
	if (!curr)
		return ;
	exec_pipe(data, curr, env_path);
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
	data = init_data();
	init_signals(data);
	init_env(data, envp);
	while (1)
	{
		data->should_exit = 0;
		data->child_pid = -1; // handler ne tente rien de foireux avant fork
		if (data->signal->sigquit == OFF)
			input = get_user_input(data, "minishell> ");
		else 
			continue;
		if (!input)
			break ;
		if (!ft_strlen(input))
		{
			init_signals(data);
			continue ;
		}
		if (data->signal->sigint == ON)
			data->signal->sigint = OFF;
		if (data->signal->sigquit == ON)
			data->signal->sigquit = OFF;
		add_history(input);
		splited_input = parse_input(data, input);
		if (!splited_input)
			continue ;
		env_path = get_env_path(envp);
		if (data->input)
			free_token_list(data->input);
		head = do_parsing(head, splited_input, data);
		data->input = head;
		exec_cmd(data, head, env_path);
		clean(data, splited_input, env_path, input);// regarde pourquoi ca empeche 
		if (data->should_exit == 1)
			break ;
		init_signals(data);
	}
	// cleanup_memory(input, splited_input);
	int exit_code = free_all(data);
	exit(exit_code);
}
