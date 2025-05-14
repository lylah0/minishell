#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
// #include "../../lib/libft.h"    // votre libft avec ft_split, ft_strjoin, etc.

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static char	*createstr(char const *s, size_t len, size_t i)
{
    char	*str;
    size_t	n;

    n = 0;
    str = malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    while (n != len)
    {
        str[n] = s[i];
        i++;
        n++;
    }
    str[n] = '\0';
    return (str);
}

static int	cword(char const *s, char c)
{
    size_t	i;
    size_t	count;
    int		j;

    i = 0;
    j = 0;
    count = 0;
    while (s[i])
    {
        if (s[i] != c && j == 0)
        {
            count++;
            j = 1;
        }
        if (s[i] == c)
            j = 0;
        i++;
    }
    return (count);
}

static char	**ifone(char const *s, char c)
{
    size_t	len;
    size_t	i;
    size_t	ii;
    char	**tab;

    len = 0;
    i = 0;
    tab = (char **)malloc(sizeof(char *) * 2);
    if (!tab)
        return (NULL);
    while (s[i] == c)
        i++;
    ii = i;
    while (s[ii] != c && s[ii++])
        len++;
    tab[0] = createstr(s, len, i);
    tab[1] = NULL;
    return (tab);
}

static char	**filltab(char const *s, char c, char **tab, size_t count)
{
    size_t	u;
    size_t	j;
    size_t	len;
    size_t	i;
    size_t	ii;

    u = 0;
    j = 0;
    i = 0;
    while (u < count)
    {
        if (s[i] != c && j == 0)
        {
            ii = i;
            len = 0;
            while (s[ii] != c && s[ii])
            {
                len++;
                ii++;
            }
            tab[u++] = createstr(s, len, i);
            j = 1;
        }
        if (s[i] == c)
            j = 0;
        i++;
    }
    return (tab);
}

char	**ft_split(char const *s, char c)
{
    size_t	count;
    char	**tab;

    if (!s)
        return (NULL);
    count = cword(s, c);
    if (count == 1)
    {
        tab = ifone(s, c);
        return (tab);
    }
    tab = (char **)malloc(sizeof(char *) * (count + 1));
    if (!tab)
        return (NULL);
    tab = filltab(s, c, tab, count);
    tab[count] = NULL;
    return (tab);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	str = malloc(sizeof(char) * (i + j + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}


int execute_command(char *command, char **args, char **envp) {
	pid_t pid = fork();
	int status;

	if (pid < 0) {
		// Échec du fork
		perror("minishell");
		return (1); // code d’erreur arbitraire pour le shell
	}
	if (pid == 0) {
		// Processus enfant
		if (strchr(command, '/') != NULL) 
		{
			// Chemin absolu ou relatif fourni
			execve(command, args, envp);
			// Si on arrive ici, erreur à l'execve
			if (errno == ENOENT) 
			{
				fprintf(stderr, "%s: command not found\n", command);
				exit(127);
			} 
			else if (errno == EACCES) 
			{
				fprintf(stderr, "%s: permission denied\n", command);
				exit(126);
			} 
			else 
			{
				perror("minishell");
				exit(1);
			}
		} 
		else 
		{
			// Pas de slash -> recherche dans PATH
			char *path_env = getenv("PATH");
			char **paths = ft_split(path_env ? path_env : "", ':');
			char *fullpath = NULL;
			int i = 0;
			while (paths && paths[i]) 
			{
				fullpath = ft_strjoin(paths[i], "/");
				char *tmp = fullpath;
				fullpath = ft_strjoin(fullpath, command);
				free(tmp);
				if (access(fullpath, X_OK) == 0) 
				{
					execve(fullpath, args, envp);
					// Si execve échoue, on gère l'erreur et quitte
					if (errno == EACCES) 
					{
						fprintf(stderr, "%s: permission denied\n", fullpath);
						exit(126);
					} 
					else 
					{
						perror("minishell");
						exit(1);
					}
				}
				free(fullpath);
				i++;
			}
			// Aucune occurrence trouvée dans PATH
			fprintf(stderr, "%s: command not found\n", command);
			exit(127);
		}
	}
	// Processus parent
	waitpid(pid, &status, 0);
	// Optionnel: on peut récupérer et traiter status ici
	return (0);
}

int main(int argc, char **argv, char **envp) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
		return (1);
	}

	char **args = &argv[1];
	return execute_command(args[0], args, envp);
}