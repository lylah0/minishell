/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:35:45 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/08 18:16:49 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

void	print_export(t_data *data);
void	add_env_name(t_data *data, char *name)
{
	(void)data;
	(void)name;
	return ;
}
void	add_new_env_var_and_value(t_data *data, char *arg)
{
	(void)data;
	(void)arg;
	return ;
}
void	update_env_var(t_data *data, char *arg)
{
	(void)data;
	(void)arg;
	return ;
}

/// @brief builtin affiche, ajoute ou maj environnement 
/// @example `export` `export NAME` `export NAME=` `export NAME=value` `export NAME1=value NAME2=value`
/// @param data 
void	b_export(t_data *data)
{
	t_input *arg;

	arg = data->input;
	if (!arg->next)
		print_export(data);
	while (arg->next)
	{
		if (ft_strchr(arg->next->token, '=') == NULL)// pas de '='
			add_env_name(data, arg->next->token);
		else// si '='
		{
			if (search_env_name(data->env, arg->next->token) == NULL) // pas trouve, new value
				add_new_env_var_and_value(data, arg->next->token);
			else // existe deja
				update_env_var(data, arg->next->token);
		}
		arg->next = arg->next->next;
	}
}


/*	 ______________________
    |___REPRENDRE EXPORT___|

	La regle est de tout reecrire par moi-meme. 
	Ca devrais etre facile. Sinon ca vaut la peine de le refaire

(1)	- cree le tableau depuis une liste chainee (refaire)
	- imprimer le tableau (refaire)
	- tester !

(2)	- trier tableau (refaire si possible)
	- tester !!!

(3)	- ajout/mise a jour dune variable environnement
	- nexiste pas : ajouter NAME, NAME="", NAME=value
	- existe : maj value;
	- plusieurs d'un coup :)

	version manuel du test (ne dependant pas du shell) POUR CHAQUE ETAPE, UNE A UNE !!!
	- tester depuis "init_env" afin que je nai pas besoin dutiliser le terminal pour tester. 
	- ensuite tester depuis le terminal `export NAME=value`

*/