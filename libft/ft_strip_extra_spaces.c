#include "libft.h"

static size_t   _len_without_extra_spaces(char *str)
{
    size_t  i;
    size_t  len;
    char    found_space;

    len = ft_strlen(str);
    while (str[len - 1] && ft_isspace(str[len - 1]))
        len--;
    str[len] = '\0';
    i = 0;
    while (str[i] && ft_isspace(str[i]))
        i++;
    len -= i;
    i--;
    found_space = 0;
    while (str[++i])
    {
        if (ft_isspace(str[i]) && !found_space)
            found_space = 1;
        else if (ft_isspace(str[i]))
            len--;
        else
            found_space = 0;
    }
    return (len);
}

void	_copy(char **new, char *str, size_t i)
{
	size_t	j;
	size_t	k;

	k = 0;
    j = 0;
    while (str[i])
    {
        if ((ft_isspace(str[i]) && !k))
        {
            k = 1;
            (*new)[j++] = str[i];
        }
        else if (!ft_isspace(str[i]))
        {
            k = 0;
            (*new)[j++] = str[i];
        }
        i++;
    }
    (*new)[j] = '\0';
}

char *ft_strip_extra_spaces(char *str)
{
    char    *new;
    size_t  i;
    size_t  k;
    size_t  len;

    len = _len_without_extra_spaces(str);
    new = (char *)malloc(sizeof(char) * (len + 1));
    if (!new)
        return (NULL);
    k = ft_strlen(str);
    while (str[k - 1] && ft_isspace(str[k - 1]))
        k--;
    str[k] = '\0';
    i = 0;
    while (str[i] && ft_isspace(str[i]))
        i++;
    _copy(&new, str, i);
    return (new);
}
