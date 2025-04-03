/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_T_CMD_ARG.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:48:31 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/03 10:00:29 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief check if env var name syntax is valid
/// @param s env var name 
/// @return 
bool is_valid_env_var_syntax(char *s)
{
	int		i;
	char	c;

	i = 0;
	if (s[i] == '_' || ft_isalpha(s[i]) == TRUE)
	{
		i++;
		while (s[i])
		{
			c = s[i];
			if (c == '_' || ft_isalnum(c) == TRUE)
				i++;
			else
				return (FALSE);
		}
		return (TRUE);
	}
	ft_putstr_fd("bash: export: '", 1);
	ft_printf("%s", s);
	ft_putendl_fd("': not a valid identifier", 1);
	return (FALSE);
}

/// @brief add or maj
/// @param input 
void	add_env_var(t_data *data, char *input)
{
	t_env	*current = NULL;
	char	*separator;	
	
	current = exist_already_in_env(data->env, data->input->next->token);// current == NULL si input na pas ete trouve dans env
	if (!current)
	{
		current = malloc(sizeof(t_env));
		if (!current)
		{
			printf("export_T_CMD_ARG.c > add_env_var :\terror : current malloc\n");
			free(current);
			return ;
		}
		printf("export_T_CMD_ARG.c > add_env_var :\tSUCCESS new_env_var(%s) created :)", input);
		current->next = NULL;
	}
	// separator = ft_strchr(input, '=');
	// if (separator)// maj value
	// {
	// 	current->name = ft_substr(input, separator, separator - input);
	// 	current->value = ft_strdup(separator + 1);
	// }
	else// rien du tout...
	{
		printf("export_T_CMD_ARG.c > add_env_var\t current->name(%s) devient input(%s)\n", current->name, input);
		current->name = ft_strdup(input);// [ ] maj donc double malloc non ?
		current->value = NULL;
	}
	// if (!current->name || (!current->value))
	// if (!current->name || (separator && !current->value))
	// 	{
	// 		printf("export_T_CMD_ARG.c > add_env_var :\terror : current name/value not found\n");
	// 		free(current->name);
	// 		return ;
	// 	}
	// current->next = NULL;
}

t_env *exist_already_in_env(t_env *env, char *name_var)
{
	if (!name_var || !env)
		return (NULL);
	while (env)
	{
		if (ft_strncmp(env->name, name_var, ft_strlen(name_var)) == 0)
		{
			printf("export_T_CMD_ARG.c > exist_already_in_env :\tenv_var with name %s found befor %s\n", env->name, env->next->name);
			return (env);
		}
		else
			env = env->next;
	}
	printf("export_T_CMD_ARG.c > exist_already_in_env :\tno match env_name_linked_list / env_name_input_token \n");
	
	return (NULL);
}

/*
___La ou jen suis le 02.04.2025, 20:20 :___

[ ] Reparer la fonction permettant de creer une variable qui sajoute a lenv, soit add_env_var.
	[x] Reparer exist_already_in_env : identifier correctement les matchs input/name_env
	{
		_ex_: export_T_CMD_ARG.c > exist_already_in_env :     env->name : -USER-      name_var : -USER-
			* ft_strcmp
				jai remplace par ft_strcmp_end 						-> 0 diff
				jai remplace le dernier parametre par 2			 	-> 0 diff
				jai remplace par la vraie fonction (strncmp) 		-> 0 diff
			* la boucle
				elle tourne, cest ok, je voit avec le print pour chaque ligne
			* condition if
				remplacer par == FALSE								-> 0 diff
					note : interessant... la condition nest jamais ni vrai ni fausse
					print result condition							-> diff nombre, neg, pos, et 0 une seule fois !
					remplacer FALSE par == 0						-> 0 diff
						even if == 0, entre pas dans la boucle
						copilot : if (ft_strncmp(env->name, name_var, ft_strlen(name_var)) == 0)
		la reponse : probleme de parenthese... 
	}
	reflexion : si match -> return (env) -> devient current (add_env_var)
		NAME=value
		|				
		|--> same NAME -->	  no value --- nothing
		| 				->	same value --- nothing
		|				->	diff value ->> maj value
		|									
		|
		|								
		|-->  new NAME	-->   no value ->> add NAME
 		|				 ->	with value ->> add NAME=value
		|				 -> empty valu ->> add NAME=""
	
	[ ] si diff/new name -> new env_var
	  	[x] malloc t_env (new node)
		[ ] creer name
		  	[ ] si '=' --> extraire name
			[ ] env-name = name (extrait ou pas)
	[ ] si value existe ('=' dans input), remplacer value par new_value	
		[ ] condition : if '=' present dans input	
		[ ] extraire value de input
		[ ] remplacer value par new_value
		[ ] break ; ?

		[ ] fonction extraction name et value ?
*/