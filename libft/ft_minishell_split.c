/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 23:51:01 by yviavant          #+#    #+#             */
/*   Updated: 2020/10/28 16:08:13 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
typedef struct		s_split
{
	int				k;
}					t_split;

static void	ft_leah(char **str, int index)
{
	while (index)
	{
		free(str[index]);
		index--;
	}
	free(str);
}

int     protection(char const *s, int i, char c, t_split *split)
{
    while (s[i] && s[++i] != c) //++copy->i; //on decale de 1 car on est sur le " ouvrant
	{
		if (s[i] == '\\')
        {
            i++;
            split->k++;
        }
        split->k++;
	}
    i++;
    split->k = split->k + 2;
    return (i);
}

static int	ft_count_words(char const *s, char c, t_split *split)
{
	int		i;
	int		count_words;

	i = -1;
	count_words = 0;
	while (s[++i])
    {
        while (s[i] == '\'' || s[i] == '"')
		{
			while (s[i] == '"')
				i = protection(s, i, '"', split);
			while (s[i] == '\'')
				i = protection(s, i, '\'', split);
		}
        if (s[i] == '\\')
			i++;
        if (s[i] == c && s[i + 1] != c)
			count_words++;
    }
    count_words++;
	return (count_words);
}

static int	ft_malloc_words(char const *s, char c, char **str, int words, t_split *split)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (++i < words)
	{
		split->k = 0;
		while (s[++j] && s[j] != c)
		{
            while (s[j] == '\'' || s[j] == '"')
		    {
			    while (s[j] == '"')
				    j = protection(s, j, '"', split);
			    while (s[j] == '\'')
				    j = protection(s, j, '\'', split);
		    }
            if (s[j] == '\\')
            {
                j++;
                split->k++;
            }
            if (s[j] == '\0' || s[j] == c)
                break;
            split->k++;
		}
        while (s[j] && s[j] == c)
			j++;
        j--;
        //printf("pour le word numero = %d y a %d caracteres\n", i, split->k);
		if ((str[i] = (char *)malloc(sizeof(char) * (split->k + 1))) == NULL)
		{
			ft_leah(str, i);
			return (0);
		}
	}
	return (1);
}

static void	ft_write_words(char const *s, char c, char **str, int words)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	while (++i < words)
	{
		k = 0;
		while (s[j] && s[j] == c)
			j++;
		while (s[j] && s[j] != c) // tant que y a pas de ';'
        {
            while (s[j] == '\'' || s[j] == '"')
		    {
			    if (s[j] == '"')
                {
                    str[i][k++] = s[j++];
                    while (s[j] && s[j] != '"')
                        str[i][k++] = s[j++];
                    str[i][k++] = s[j++];
                }
			    if (s[j] == '\'')
                {
                    str[i][k++] = s[j++];
                    while (s[j] && s[j] != '\'')
                        str[i][k++] = s[j++];
                    str[i][k++] = s[j++];
                }
		    }
            if (s[j] == c || s[j] == '\0')
                break;
			str[i][k++] = s[j++];
        }
		str[i][k] = '\0';
	}
}

char		**ft_minishell_split(char const *s, char c)
{
	char	**str;
	int		count_words;
	t_split split;

	if (!s)
		return (NULL);
	count_words = ft_count_words(s, c, &split);
	if ((str = (char **)malloc(sizeof(char *) * (count_words + 1))) == NULL)
		return (NULL);
	if (!ft_malloc_words(s, c, str, count_words, &split))
		return (NULL);
	ft_write_words(s, c, str, count_words);
	str[count_words] = 0;
	return (str);
}
/*
int     main()
{
    int i = -1;
    char **recup;
    char const *s;
    s = "echo 'bonjour;' ; echo coucou";
    recup = ft_split(s, ';');
    while (recup[++i])
        printf("%s\n", recup[i]);
}*/