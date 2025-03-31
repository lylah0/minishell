// implique quon sait deja que cest une c
// int	is_a_builtin(char *cmd)

int	kind_of_token(char *input)
{
	if (ft_strncmp_end((const char *)input, "echo", 4) == 0)
	{
		printf("\n%s = cmd\n", input);
		echo(input);
		return (0);
	}	
	else if (ft_strncmp_end((const char *)input, "cd", 2) == 0)
	{
		printf("\n%s = cmd\n", input);
		return (0);
	}
	else if (ft_strncmp_end((const char *)input, "pwd", 3) == 0)
	{
		printf("\n%s = cmd\n", input);
		return (0);
	}
	else if (ft_strncmp_end((const char *)input, "env", 3) == 0)
	{
		printf("\n%s = cmd\n", input);
		return (0);
	}
	else if (ft_strncmp_end((const char *)input, "export", 6) == 0)
	{
		printf("\n%s = cmd\n", input);
		return (0);
	}
	else if (ft_strncmp_end((const char *)input, "unset", 5) == 0)
	{
		printf("\n%s = cmd\n", input);
		return (0);
	}
	else // pas forcement arg, peut etre path/bin
		printf("%s = arg\n\n", input);
	return (1);
}

void	execution(char *splited_line, char *argv, char **envp)
{
	if (kind_of_token(splited_line) == 1)
	{
		printf("execve");
		execve(splited_line, (char * const *)argv, envp);
	}
	return ;
}

void	display_input(char **splited_line)
{
	int	i;
	i = 0;
	printf("splited_line[%d]: %s\n", i, splited_line[i]);
	// execution(splited_line[i], splited_line[i + 1], environ->envp);
	sleep(1);
}

char	**split_input(char *line)
{
	char	**splited_line;

	splited_line = ft_split(line, ' ');
	if (!splited_line)
	{
		fprintf(stderr, "Error splitting line\n");
		free(line);
		return (NULL);
	}
	return (splited_line);
}
