/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:35:45 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/01 21:11:42 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"




// // [ok] fonction de comparaison s1, s2
// // [ok] cree une copie de la liste juste char *name=value donc liste chainee de char *
// // [ok] fonction syntaxe env var
// // [ ] fonction tri list_copie 
// // [ok] imprimer char *
// // [ ]	imprimer syntaxe execptions
// // // //	syntaxe
// // // //		`declare -x VAR="value"`
// // // //		si pas de value,	`declare -x VAR`
// // // //		si value vide,		`declare -x VAR=""`
// // [ ] free lst
// // 	// Nom de variable (name) : MY_VAR_1 (lettres, chiffres, underscore, ne commence pas par un chiffre)
// // 	// Valeur (value) : Hello_World123 (lettres, chiffres, underscores, espaces possibles)
// // 		if syntaxe invalide
// // 			~`bash: export: 'X': not a valid identifier`
// // 			exit_status(1)
// //

/// @brief built-in `export` `export VAR=value` `export VAR` `export VAR+=value`
/// @param data 
void    b_export(t_data *data)
{
	// t_input    *curr;

	// curr = data->input;
	// 	if (!curr->next)// `export`
	// 	{
			create_env_copy_array(data);
			sort_words(data->copy_env, get_array_length(data->copy_env));
			print_copy_env(data);
		// }
		// else
		// 	printf("hello");
}

/// @brief version head -|- built-in `export` `export VAR=value` `export VAR` `export VAR+=value`
/// @param data 
void    c_export(t_input *head)
{
	t_data *data = head->data;

	if (!head->next)// `export`
	{
		create_env_copy_array(data);
		sort_words(data->copy_env, get_array_length(data->copy_env));
		print_copy_env(data);
	}
	else
		printf("hello");
}

// void	b_export(t_data *data)
// {
// 	t_env	*current;
// 	data->env = current;
// 	if (data->input->T_CMD)
// 	{
// 		copy_env_list(data->env);
// 		print_copy_env(data->copy_env);
// 	}
// 		//parcourir env, afficher dans ordre alphabetique dans le terminal
// //		syntaxe 
// //			`declare -x VAR="value"` 
// //			si pas de value,	`declare -x VAR`
// //			si value vide,		`declare -x VAR=""`
// 	}
// 	else
// 	control syntaxe
// {
// 		if ('=' present)
// 		{`````
// 			si existe deja 
// 				maj value
// 			else 
// 				ajoute VAR=value a env
// 		}
// 		else
// 		{
// 			si existe deja
// 				rien
// 			else
// 				creation valeur 
// 	}
// 	si succes exit_status 0
// }

// int main(int ac, char **av, char **envp)
// {
// 	t_data	*data = malloc(sizeof(t_data));
// 	if(!data)
// 		return 0;
// 	(void)ac;
// 	(void)av;
// 	init_env(data, envp);
// 	// b_env(data);
// 	// b_export(data);
// }