#include "../../includes/fdf.h"

size_t	char2len(char **char2)
{
	size_t	i; 

	i = 0;
	while (char2[i])
		i++;
	return (i);
}

size_t	char3len(char **char3)
{
	size_t	i; 

	i = 0;
	while (char3[i])
		i++;
	return (i);
}