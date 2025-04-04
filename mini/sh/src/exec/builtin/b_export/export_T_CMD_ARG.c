/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_T_CMD_ARG.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:48:31 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/03 11:48:22 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

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
			if (c == '_' || ft_isalnum(c) || c == '=')
				i++;
			else
			{
				printf("export_T_CMD_ARG.c > is_valid_env_var_syntaxe1\t");
				ft_putstr_fd("bash: export: '", 1);
				ft_printf("%s", s);
				ft_putendl_fd("': not a valid identifier", 1);
				return (FALSE);
			}
		}
		printf("export_T_CMD_ARG.c > is_valid_env_var_syntaxe2\tSUCCESS is a valid SYNTAX env_var(%s) :)\n", s);
		return (TRUE);
	}
	printf("export_T_CMD_ARG.c > is_valid_env_var_syntaxe3\t");
	ft_putstr_fd("bash: export: '", 1);
	ft_printf("%s", s);
	ft_putendl_fd("': not a valid identifier", 1);
	return (FALSE);
}

/// @brief add or maj
/// @param input 
void	add_env_var(t_data *data, char *input)
{
	t_env	*current = data->env;
	char	*separator;	
	
	// current = exist_already_in_env(data->env, data->input->next->token);// current == NULL si input na pas ete trouve dans env
	if (!current)
	{
		current = malloc(sizeof(t_env));
		if (!current)
		{
			printf("export_T_CMD_ARG.c > add_env_var \tERROR current malloc\n");
			free(current);
			return ;
		}
		printf("export_T_CMD_ARG.c > add_env_var \tSUCCESS current malloc\n");
		current->next = NULL;
	}
	separator = ft_strchr(input, '=');
	if (separator)// maj value
	{
		char *extracted_name = ft_substr(input, 0, separator - input);
		current->name = extracted_name;
		printf("export_T_CMD_ARG.c > add_env_var :\tSUCCESS name(%s) extracted from imput(%s) :)\n", extracted_name, input);
		printf("export_T_CMD_ARG.c > add_env_var :\tcurrent->name(%s)\n", current->name);
		current->next = NULL;
		print_env_linked_list(data);
	}
	
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
	
	[x] si diff/new name -> new env_var
	  	[x] malloc t_env (new node)
		[x] creer name
		  	[x] si '=' --> extraire name
			[x] env->name = name (extrait ou pas)
	[ ] si value existe ('=' dans input), remplacer value par new_value	
		[ ] condition : if '=' present dans input	
		[ ] extraire value de input
		[ ] remplacer value par new_value
		[ ] break ; ?

		[ ] fonction extraction name et value ?
			[ ] if strchr '=' found
			  		extract_name
					extract_value
		
		Pour l-instant, si je fais export USER=moni -> il se passe rien. Ca rentre meme pas dans b_export (pas de printf de syntaxe ok)
		jai ajouter des printf dans b_export. probleme resolu avec la condition is valid syntax qui laissait pas passer le '='
		[x] extraire name de NAME=user, actuellement
		  		export_T_CMD_ARG.c > add_env_var : SUCCESS name(USER=moni) extracted from imput(USER=moni) :)
				  ok j'ai demande a copilot... le dernier param etait input - separator. je devait faire l'inverse
				  char *extracted_name = ft_substr(input, 0, separator - input); 105 . 110 . 112 --> 110 - 112 = -2... jai pas compris

		[ ] la new_var s'ajoute a env
[ ]			pour l'instant : (si pas de = dans arg, segv [ ])
					minishell> export ens=dd
					cmd
					export_T_CMD_ARG.c > is_valid_env_var_syntaxe2  SUCCESS is a valid SYNTAX env_var(ens=dd) :)
					export_T_CMD_ARG.c > exist_already_in_env :     no match env_name_linked_list / env_name_input_token 
					export_T_CMD_ARG.c > add_env_var        SUCCESS current malloc
					export_T_CMD_ARG.c > add_env_var :      SUCCESS name(ens) extracted from imput(ens=dd) :)
					export_T_CMD_ARG.c > add_env_var :      current->name(ens)
					export.c > b_export :    export avec arg, input = T_CMD_ARG + T_ARG
					Token type: T_CMD_ARG
					Token type: T_ARG
			le probleme : ne s'affiche pas dans l'env.
			Reflexion : se copie dans un env temporaire ? pour tester je print envlinkedlist directement dans la fonction apres current.name =  extractedname
				t_env *current = NULL; -> = data->env				--> 0 diff
			On dirait que current.name s'enregistre ailleurs... est ce que j'ai lie le new_node a la linkedlist_env ?
				je commente is already in env car ca mod le current
					minishell> export _______ewfew
					cmd
					export_T_CMD_ARG.c > is_valid_env_var_syntaxe2  SUCCESS is a valid SYNTAX env_var(_______ewfew) :)
					export_T_CMD_ARG.c > add_env_var         current->name(GJS_DEBUG_TOPICS) devient input(_______ewfew)
					export.c > b_export :    export avec arg, input = T_CMD_ARG + T_ARG
					Token type: T_CMD_ARG
					Token type: T_ARG

					minishell> export
					cmd
					[21]    19943 segmentation fault (core dumped)  ./minishell
					➜  sh git:(moni) ✗ 


[ ] finaliser condition is_valid_syntax 
  	(accepte '=' (nec pour valider un NAME=value) MAIS si plusieurs '=' ???)
		*/