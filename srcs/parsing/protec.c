#include "../../includes/minishell.h"
#include <string.h>
#include <unistd.h>

//#ifndef BUFFER_SIZE
//#define BUFFER_SIZE 300
//#endif

void	environnement()
{
	printf("appel a variable d'environnement\n");
	//verifier si la variable d'environnement existe, sinon il faudra imprimer un \n (ex : echo $wshh ou wshh existe pas)
}

int		simple_quote(char *whole_cmd, t_copy *copy)
{
	if (copy->i == (strlen(whole_cmd) -1)) // si le ' ouvrant est le dernier caractere de la chaine
	{
		printf("erreur \' au bout de la chaine\n");
		return (-1);
	}
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '\'') //++copy->i; //on decale de 1 car on est sur le ' ouvrant
		copy->cmd[++copy->j] = whole_cmd[copy->i];
	if ((copy->i == strlen(whole_cmd)) && whole_cmd[copy->i] != '\'') // si y a pas de ' fermant
	{
		printf("erreur pas de \' fermant\n");
		return (-1);
	}
	copy->i++; // on decale de 1 car on est sur le ' fermant
	return (1);
}

int		double_quote(char *whole_cmd, t_copy *copy)
{
	if (copy->i == (strlen(whole_cmd) -1)) // si le " ouvrant est le dernier caractere de la chaine
	{
		printf("erreur \" au bout de la chaine\n");
		return (-1);
	}
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '"') //++copy->i; //on decale de 1 car on est sur le " ouvrant
	{
		if (whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] != '\\') // $ conserve sa signification speciale
			environnement();
		if (whole_cmd[copy->i] == '\\')
		{
			if (whole_cmd[copy->i + 1] == '$' || whole_cmd[copy->i + 1] == '\\' // si \ suivit de " $ ou \ garde sa signification
					|| whole_cmd[copy->i + 1] == '"')
				copy->i++;
		}
		copy->cmd[++copy->j] = whole_cmd[copy->i];
	}
	if ((copy->i == strlen(whole_cmd)) && whole_cmd[copy->i] != '"') // si y a pas de " fermant
	{
		printf("erreur pas de \" fermant\n");
		return (-1);
	}
	copy->i++; // on decale de 1 car on est sur le " fermant
	return (1);
}

char	*args(char *whole_cmd, t_copy *copy, size_t i)// retrouver les arguments dans whole_cmd et mettre dans un char**
{
	char c;
	copy->args[i] = NULL;
	copy->j = -1;

	if (!(whole_cmd))
		return (NULL);
	if (!(copy->args[i] = malloc(sizeof(char) * (strlen(whole_cmd) + 1))))
		return (NULL);
	while (whole_cmd[copy->i] && whole_cmd[copy->i] == ' ')
		copy->i++;
	copy->i--;
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != ' ')
	{
		c = 'x';
		if (whole_cmd[copy->i] == '\'')
			c = '\'';
		else if (whole_cmd[copy->i] == '"')
			c = '"';
		if (whole_cmd[copy->i] == c)
		{
			while (whole_cmd[copy->i] == '"')
				if ((double_quote(whole_cmd, copy)) == -1)
					return (NULL);
			while (whole_cmd[copy->i] == '\'')
				if ((simple_quote(whole_cmd, copy)) == -1)
					return (NULL);
		}
		if (whole_cmd[copy->i] == '\\')
			copy->i++;
		if (whole_cmd[copy->i] == '>' && whole_cmd[copy->i - 1] != '\\')
			if (redir_out(whole_cmd, copy) == -1)
				return (NULL);
		copy->args[i][++copy->j] = whole_cmd[copy->i];
	}
	copy->args[i][copy->j + 1] = 0;
	return (copy->args[i]);
}

int		options(char *whole_cmd, t_copy *copy)
{
	char	**tmp;
	char	*arg;
	size_t	i;
	size_t	j;

	i = 0;
	while (1)
	{
		if (i > 0)
			tmp = copy->args;
		if (!(copy->args = (char **)malloc(sizeof(char *) * (i + 1))))
			return (0);
		if (i > 0)
		{
			j = i - 1;
			while (j)
			{
				copy->args[j] = ft_strdup(tmp[j]);
				j--;
			}
			while (j < i)
			{
				free(tmp[j]);
				j++;
			}
		}
		arg = args(whole_cmd, copy, i);
		if (!arg || !arg[0])
			break;
		printf("%s\n", copy->args[i]);
		i++;
	}
	return (1);
}

char	*cmd(char *whole_cmd) // retrouver la commande dans whole_cmd (peut etre une variable d'environnement)
{
	char c;
	t_copy copy;
	copy.i = 0;
	copy.j = -1;
	copy.cmd = NULL;

	if (!(whole_cmd))
		return (NULL);
	if (!(copy.cmd = malloc(sizeof(char) * (strlen(whole_cmd) + 1))))
		return (NULL);
	while (whole_cmd[copy.i] && whole_cmd[copy.i] == ' ')
		copy.i++;
	copy.i--;
	while (whole_cmd && whole_cmd[++copy.i] != ' ')
	{
		c = 'x';
		if (whole_cmd[copy.i] == '\'')
			c = '\'';
		else if (whole_cmd[copy.i] == '"')
			c = '"';
		if (whole_cmd[copy.i] == c)
		{
			while (whole_cmd[copy.i] == '"')
				if ((double_quote(whole_cmd, &copy)) == -1)
					return (NULL);
			while (whole_cmd[copy.i] == '\'')
				if ((simple_quote(whole_cmd, &copy)) == -1)
					return (NULL);
		}
		if (whole_cmd[copy.i] == '\\')
			copy.i++;
		copy.cmd[++copy.j] = whole_cmd[copy.i];
	}
	copy.cmd[copy.j + 1] = 0;
	printf("cmd = %s\n", copy.cmd);
	options(whole_cmd, &copy);
	return (copy.cmd);
}

int		main(int argc, char **argv, char **env)
{
	//char *str;
	char buff[100 + 1];
	int ret;
	ret = read(0, buff, 100);
	buff[ret - 1] = 0;
	cmd(buff);
}
