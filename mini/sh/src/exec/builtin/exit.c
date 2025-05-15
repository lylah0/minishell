/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:21:29 by monoguei          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/15 21:49:32 by monoguei         ###   ########.fr       */
=======
/*   Updated: 2025/05/15 09:24:13 by monoguei         ###   ########.fr       */
>>>>>>> export
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

#define TRUE 1
#define FALSE 0

<<<<<<< HEAD
int	str_isdigit(char *str)
{
	int	i;

	i = 0;
=======
int str_isdigit(char *str)
{
	int i = 0;

>>>>>>> export
	if (!str || !*str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

<<<<<<< HEAD
void	exit_no_arg(int in_pipe)
{
	if (!in_pipe)
		ft_putstr_fd("exit\n", 1); // Only print when not in a pipeline
=======
void	exit_no_arg()
{
	ft_putstr_fd("exit\n", 1);
>>>>>>> export
	exit(exit_code);
}

void	exit_n(char *num)
{
	int	n;

	n = (ft_atoi(num) % 256 + 256) % 256;
	ft_putstr_fd("exit\n", 1);
	exit_code = n;
	exit(exit_code);
}

void	exit_alpha(char *word)
{
	ft_putstr_fd("exit\n", 1);
<<<<<<< HEAD
	ft_printf_stderr("minishell: exit: %s: numeric argument required\n", word);
=======
	ft_printf_stderr("bash: exit: %s: numeric argument required\n", word);
>>>>>>> export
	exit_code = 2;
	exit(exit_code);
}

void	exit_multiple_arg(void)
{
<<<<<<< HEAD
	ft_printf_stderr("minishell: exit: too many arguments\n");
	exit_code = 1;
}

void	b_exit(t_data *data, t_input *current, int in_pipe)
{
	t_input	*next_token;

	(void)data;
	next_token = current->next;
	if (!next_token || next_token->type == T_PIPE || next_token->type == T_OP)
		exit_no_arg(in_pipe);
	else if (str_isdigit(next_token->token) == TRUE && (!next_token->next
			|| next_token->next->type == T_PIPE
			|| next_token->next->type == T_OP))
		exit_n(next_token->token);
	else if (str_isdigit(next_token->token) == TRUE && next_token->next
		&& next_token->next->type != T_PIPE && next_token->next->type != T_OP)
		exit_multiple_arg();
	else if (str_isdigit(next_token->token) == FALSE)
		exit_alpha(next_token->token);
}
=======
	ft_printf_stderr("bash: exit: too many arguments\n");
	ft_putstr_fd("exit\n", 1);
	exit_code = 1;
}

void	b_exit(t_data *data)
{
	// exit_code = 0;// est ce vraiment necessaire de mettre a zero ici, plutot dans la boucle dans l'init du main
	if (data->child_pid > 0)
		return ;
	if (!data->input->next)// aucun argument
		exit_no_arg();
	else if (data->input->next)
	{
		if (str_isdigit(data->input->next->token) == TRUE && !data->input->next->next)// premier arg numerique, pas de suite
			exit_n(data->input->next->token);
		else if (str_isdigit(data->input->next->token) == TRUE && data->input->next->next)// premier arg numerique, 2eme argument quelquil soit
			exit_multiple_arg();
		else if (str_isdigit(data->input->next->token) == FALSE)
			exit_alpha(data->input->next->token);
	}
}

/*
TEST

	exit 0			"exit", quit, echo $? = 0
	exit +0			"exit", quit, echo $? = 0
	exit -0			"exit", quit, echo $? = 0
	exit +-0		"exit", "bash: exit: +-0: numeric argument required", quit, echo $? = 2
	exit --1		"exit", "bash: exit: --1: numeric argument required", quit, echo $? = 2
	exit ++42		"exit", "bash: exit: ++42: numeric argument required", quit, echo $? = 2
	exit "10"		"exit", quit, echo $? = 10
	exit '+10'		"exit", quit, echo $? = 10
	exit "++10"		"exit", "bash: exit: ++10: numeric argument required", quit, echo $? = 2
	exit "-10"		"exit", quit, echo $? = 246
	exit '-10'		"exit", quit, echo $? = 246
	exit 1'2'3		"exit", quit, echo $? = 123
[ ]	exit 1'23		"missing one quote", quit, 0 --> ">" (terminal attend), quand "'" --> bash: exit: 123(\n) : numeric argument required"
	exit "1'34'6"	"exit", "bash: exit: 1'34'6: numeric argument required", quit, echo $? = 2
	exit 42,42		"exit", "bash: exit: 42,42: numeric argument required", quit, echo $? = 2
	exit -"17"		"exit", quit, echo $? = 239
	exit 99999999999999 "exit", quit, echo $? = 255
[ ]	exit 99999999999999 (\n\n)
					"exit", "bash: exit: 99999999999999 (\n\n): numeric argument required", quit, echo $? = 2
					--> (\n\n) "exit", quit, echo $? = 255
	exit 1			"exit", quit, echo $? = 1
	exit 1000		"exit", quit, echo $? = 232
	exit -10		"exit", quit, echo $? = 246
	exit -00014		"exit", quit, echo $? = 242
	exit +200		"exit", quit, echo $? = 200
	exit 00042		"exit", quit, echo $? = 42
	exit 42 42		"bash: exit: too many arguments", "exit", echo $? = 1
	exit 42 hello	"bash: exit: too many arguments", "exit", echo $? = 1
	exit exit		"exit", "bash: exit: exit: numeric argument required", quit, echo $? = 2
	exit hello		"exit", "bash: exit: hello: numeric argument required", quit, echo $? = 2
	exit hello you	"exit", "bash: exit: hello: numeric argument required", quit, echo $? = 2
	exit hello 42	"exit", "bash: exit: hello: numeric argument required", quit, echo $? = 2





bash-5.1$ exit 9999999999999


exit
moni@moni:~/Desktop/CODE$ echo $?
255
*/
>>>>>>> export
