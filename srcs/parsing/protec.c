#include "../../includes/minishell.h"

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

int		simple_quote_arg(char *whole_cmd, t_copy *copy, size_t i)
{
	if (copy->i == (strlen(whole_cmd) -1)) // si le ' ouvrant est le dernier caractere de la chaine
	{
		printf("erreur \' au bout de la chaine\n");
		return (-1);
	}
	if (whole_cmd[copy->i + 1] == '\'')
		copy->args[i][++copy->j] = ' ';
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '\'') //++copy->i; //on decale de 1 car on est sur le ' ouvrant
		copy->args[i][++copy->j] = whole_cmd[copy->i];
	if ((copy->i == strlen(whole_cmd)) && whole_cmd[copy->i] != '\'') // si y a pas de ' fermant
	{
		printf("erreur pas de \' fermant\n");
		return (-1);
	}
	copy->i++; // on decale de 1 car on est sur le ' fermant
	return (1);
}

int		simple_quote_redir(char *whole_cmd, t_copy *copy, int i, t_redir *redir, char *str)
{
	if (copy->i == (strlen(whole_cmd) -1)) // si le ' ouvrant est le dernier caractere de la chaine
	{
		printf("erreur \' au bout de la chaine\n");
		return (-1);
	}
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '\'') //++copy->i; //on decale de 1 car on est sur le ' ouvrant
		str[++redir->i] = whole_cmd[copy->i];
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
		printf("erreur \" au bout de la chaine \n");
		return (-1);
	}
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '"') //++copy->i; //on decale de 1 car on est sur le " ouvrant
	{
		if (whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] != '\\') // $ conserve sa signification speciale
			environnement(whole_cmd, copy, 0, 0);
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

int		double_quote_arg(char *whole_cmd, t_copy *copy, size_t i)
{
	if (copy->i == (strlen(whole_cmd) -1)) // si le " ouvrant est le dernier caractere de la chaine
	{
		printf("erreur \" au bout de la chaine \n");
		return (-1);
	}
	if (whole_cmd[copy->i + 1] == '"')
		copy->args[i][++copy->j] = ' ';
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '"') //++copy->i; //on decale de 1 car on est sur le " ouvrant
	{
		if (whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] != '\\') // $ conserve sa signification speciale
			environnement(whole_cmd, copy, 1, i);
		if (whole_cmd[copy->i] == '\\')
		{
			if (whole_cmd[copy->i + 1] == '$' || whole_cmd[copy->i + 1] == '\\' // si \ suivit de " $ ou \ garde sa signification
					|| whole_cmd[copy->i + 1] == '"')
				copy->i++;
		}
		copy->args[i][++copy->j] = whole_cmd[copy->i];
	}
	if ((copy->i == strlen(whole_cmd)) && whole_cmd[copy->i] != '"') // si y a pas de " fermant
	{
		printf("erreur pas de \" fermant\n");
		return (-1);
	}
	copy->i++; // on decale de 1 car on est sur le " fermant
	return (1);
}

int		double_quote_redir(char *whole_cmd, t_copy *copy, t_redir *redir, char *str, int std)
{
	if (copy->i == (strlen(whole_cmd) -1)) // si le " ouvrant est le dernier caractere de la chaine
	{
		printf("erreur \" au bout de la chaine\n");
		return (-1);
	}
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '"') //++copy->i; //on decale de 1 car on est sur le " ouvrant
	{
		if (whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] != '\\') // $ conserve sa signification speciale
			environnement_redir(whole_cmd, copy, std, redir);
		if (whole_cmd[copy->i] == '\\')
		{
			if (whole_cmd[copy->i + 1] == '$' || whole_cmd[copy->i + 1] == '\\' // si \ suivit de " $ ou \ garde sa signification
					|| whole_cmd[copy->i + 1] == '"')
				copy->i++;
		}
		str[++redir->i] = whole_cmd[copy->i];
	}
	if ((copy->i == strlen(whole_cmd)) && whole_cmd[copy->i] != '"') // si y a pas de " fermant
	{
		printf("erreur pas de \" fermant\n");
		return (-1);
	}
	copy->i++; // on decale de 1 car on est sur le " fermant
	return (1);
}