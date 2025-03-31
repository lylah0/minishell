/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:05:13 by monoguei          #+#    #+#             */
/*   Updated: 2025/03/27 16:00:16 by lylrandr         ###   ########.fr       */
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


int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**splited_input;
	t_input	*head;

	(void)ac;
	(void)av;
	(void)envp;
	init_signals();
	while (1)
	{
		input = get_user_input("minishell> ");
		splited_input = parse_input(input);
		print_tokens(splited_input);
		head = tokenize(splited_input);
//		remove_quotes(head);
		first_word(splited_input, envp);
//		tester_env(envp);
		print_all_token_types(head);
		is_env_var(head);
		print_token_list(head);
		restore_terminal();
		cleanup_memory(input, splited_input);
		init_signals();
	}
	return (0);
}
