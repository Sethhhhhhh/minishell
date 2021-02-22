#include "../../includes/minishell.h"

int		simple_quote(char *whole_cmd, t_copy *copy)
{
	if (copy->i == (strlen(whole_cmd) -1)) // si le ' ouvrant est le dernier caractere de la chaine
	{
		printf("erreur \' au bout de la chaine\n");
		return (-1);
	}
/*AJOUT*/	
	if (whole_cmd[copy->i + 1] == '\'' && (whole_cmd[copy->i + 2] == ' ' || whole_cmd[copy->i + 2] == '\0'))
		copy->cmd[++copy->j] = '\0';
/*AJOUT*/
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
/*AJOUT*/	
	if (whole_cmd[copy->i + 1] == '\'' && (whole_cmd[copy->i + 2] == ' ' || whole_cmd[copy->i + 2] == '\0'))
		copy->args[i][++copy->j] = '\0';
/*AJOUT*/
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
/*AJOUT*/
	if ((whole_cmd[copy->i + 1] == '\'' && whole_cmd[copy->i + 2] == ' ') && !str) // cas de : echo bonjour 1>'' pas normal //et : echo bonjour 1> "hey"'' pas normal
	{
		str[redir->i] = ' ';
		str[redir->i + 1] = 0;
		copy->i = copy->i + 2;
		return (-1);
	}
/*AJOUT*/
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '\'') //++copy->i; //on decale de 1 car on est sur le ' ouvrant
		str[++redir->i] = whole_cmd[copy->i];
	if ((copy->i == strlen(whole_cmd)) && whole_cmd[copy->i] != '\'') // si y a pas de ' fermant
	{
		printf("erreur pas de \' fermant\n");
		return (-1);
	}
/*AJOUT*/
	str[redir->i + 1] = 0;
	copy->i++; // on decale de 1 car on est sur le ' fermant
	if (whole_cmd[copy->i] != ' ')
		return (1);
	return (-1);
/*AJOUT*/
}

int		double_quote(char *whole_cmd, t_copy *copy)
{
	int j;
	if (copy->i == (strlen(whole_cmd) -1)) // si le " ouvrant est le dernier caractere de la chaine
	{
		printf("erreur \" au bout de la chaine lol\n");
		return (-1);
	}
/*AJOUT*/
	if (whole_cmd[copy->i + 1] == '"' && (whole_cmd[copy->i + 2] == ' ' || whole_cmd[copy->i + 2] == '\0'))
		copy->cmd[++copy->j] = '\0';
/*AJOUT*/
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '"') //++copy->i; //on decale de 1 car on est sur le " ouvrant
	{
		j = 0;
		if (whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] != '\\') // $ conserve sa signification speciale
			j = environnement(whole_cmd, copy, 0, 0);
		if (whole_cmd[copy->i] == '\\')
		{
			if (whole_cmd[copy->i + 1] == '$' || whole_cmd[copy->i + 1] == '\\' // si \ suivit de " $ ou \ garde sa signification
					|| whole_cmd[copy->i + 1] == '"')
				copy->i++;
		}
		if (j != 1)
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
	int j;
	if (copy->i == (strlen(whole_cmd) -1)) // si le " ouvrant est le dernier caractere de la chaine
	{
		printf("erreur \" au bout de la chaine \n");
		return (-1);
	}
	//printf("ca rentre\n");
	//printf("copy->i = %d\n", copy->i);
/*AJOUT*/
	if (whole_cmd[copy->i + 1] == '"' && (whole_cmd[copy->i + 2] == ' ' || whole_cmd[copy->i + 2] == '\0'))
		copy->args[i][++copy->j] = '\0';
/*AJOUT*/
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '"') //++copy->i; //on decale de 1 car on est sur le " ouvrant
	{
		j = 0;
		if (whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] != '\\') // $ conserve sa signification speciale
			j = environnement(whole_cmd, copy, 1, i);
		if (whole_cmd[copy->i] == '\\')
		{
			if (whole_cmd[copy->i + 1] == '$' || whole_cmd[copy->i + 1] == '\\' // si \ suivit de " $ ou \ garde sa signification
					|| whole_cmd[copy->i + 1] == '"')
				copy->i++;
		}
		if (j != 1)
			copy->args[i][++copy->j] = whole_cmd[copy->i];
	}
	if ((copy->i == strlen(whole_cmd)) && whole_cmd[copy->i] != '"') // si y a pas de " fermant
	{
		printf("erreur pas de \" fermant\n");
		return (-1);
	}
	copy->i++; // on decale de 1 car on est sur le " fermant
	//printf("whole_cmd[copy->i] = %c\n", whole_cmd[copy->i]);
	return (1);
}

int		double_quote_redir(char *whole_cmd, t_copy *copy, t_redir *redir, char *str, int std)
{
	if (copy->i == (strlen(whole_cmd) -1)) // si le " ouvrant est le dernier caractere de la chaine
	{
		printf("erreur \" au bout de la chaine\n");
		return (-1);
	}
/*AJOUT*/
	if ((whole_cmd[copy->i + 1] == '"' && whole_cmd[copy->i + 2] == ' ') && !str) // cas de : echo bonjour 1>"" pas normal ou de : echo bonjour 1> "hey""" pas normal
	{
		str[redir->i] = ' ';
		str[redir->i + 1] = 0;
		copy->i = copy->i + 2;
		return (-1);
	}
/*AJOUT*/
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
/*AJOUT*/
	str[redir->i + 1] = 0;
	copy->i++; // on decale de 1 car on est sur le " fermant
	if (whole_cmd[copy->i] != ' ')
		return (1);
	return (-1);
/*AJOUT*/
}