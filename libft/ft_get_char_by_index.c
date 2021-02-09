#include "libft.h"

size_t	ft_get_char_by_index(char *str, char c)
{
    char *valid_c; 

	valid_c = ft_strchr(str, c);
	if (!valid_c)
        return (-1);
    return ((size_t)(valid_c - str));
}