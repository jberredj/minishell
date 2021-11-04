#include <stdlib.h>
#include "libft/includes/libft.h"
#include <stdio.h>

void	create_en_elem_from_str(char *str)
{
	size_t	equal_loc;
	char	*value;

	value = ft_strchr(str, '=');
	if (!value && *(value + 1) && value != str)
		return (NULL);
	equal_loc = (size_t)((value - str));
	value++;
	printf("%ld\n", equal_loc);
}

int main(int ac, char **av)
{
	create_en_elem_from_str(av[1]);
	return (0);
}