/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:35:45 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/08 20:36:44 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

int find_equal(char *s)
{
	int i = 0;
	
	while(s[i])
	{
		if (s[i] == '=')
			return i;
		i++;
	}
	return 0;
}


char	*extract_name(char *env_var)
{
	char	*new_name;
	int		end;

	end = find_equal(env_var);
	new_name = ft_strndup(env_var, end);
	if (!new_name)
		return NULL;
	return (new_name);
}

char	*extract_value(char *env_var)
{
	char	*new_value;
	char	*end;

	end = ft_strchr(env_var, '=');
	new_value = ft_strdup(end + 1);
	if (!new_value)
		return NULL;
	return (new_value);
}

/// @brief builtin affiche, ajoute ou maj environnement 
/// @example `export` `export NAME` `export NAME=` `export NAME=value` `export NAME1=value NAME2=value`
/// @param data 
void	b_export(t_data *data)
{
	t_input *arg;
	char	*new_name;
	char	*new_value;

	arg = data->input;
	
	if (!arg->next)
		print_export(data);
	else 
	{

		while (arg->next)
		{
			if (ft_strchr(arg->next->token, '=') == NULL)// pas de '='
				add_env_name(data, arg->next->token);
			else// si '='
			{
				new_value = extract_value(arg->next->token);
				new_name = extract_name(arg->next->token);
				printf("new_name %s, new_value %s\n", new_name, new_value);
				if (search_env_name(data->env, new_name) == NULL) // pas trouve, new value
				{
					printf("name not found\n");
					add_new_env_var_and_value(data, new_name, new_value);
				}	
				else // existe deja
				{
					printf("env nam found\n");
					update_env_value(data->env, new_name, new_value);
				}
			}
			arg->next = arg->next->next;
		}
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