// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   signaux.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/03/03 07:36:08 by monoguei          #+#    #+#             */
// /*   Updated: 2025/05/13 10:34:04 by monoguei         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../minishell.h"

/// ===============================
/// Gestion du contexte global
/// ===============================
t_data	*get_data_ptr(t_data *new_data)
{
	static t_data *saved = NULL;

	if (new_data)
		saved = new_data;
	return (saved);
}

/// ===============================
/// Handler pour SIGINT (Ctrl+C)
/// ===============================
void	handler_sigint(int signum)
{
	t_data *data = get_data_ptr(NULL);
	(void)signum;

	if (data && data->signal)
		data->signal->sigint = ON;

	// Si un enfant est actif, on lui envoie le SIGINT !
	if (data && data->child_pid > 0)
	{
		fprintf(stderr, "[SIGINT] kill pid: %d\n", data->child_pid);
		kill(data->child_pid, SIGINT);// envoie sigint a child actif
	}

	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}


/// ===============================
/// Handler pour SIGQUIT (Ctrl+\)
/// ===============================
void	handler_sigquit(int signum)
{
	t_data *data = get_data_ptr(NULL);
	(void)signum;

	if (data && data->signal)
		data->signal->sigquit = ON;
	// Aucun affichage volontaire (comme bash)
}

/// ===============================
/// Initialisation des signaux
/// ===============================
void	init_signals(t_data *data)
{
	get_data_ptr(data);
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, handler_sigquit);
}
