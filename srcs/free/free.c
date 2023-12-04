#include "../../includes/fdf.h"

void	free_char1(char **a_char1)
{
	free(*a_char1);
	*a_char1 = NULL;
}

void	free_char2(char ***a_char2)
{
	size_t	i;
	char	**char2;

	i = 0;
	char2 = *a_char2;
	while (char2[i])
	{
		free(char2[i]);
		char2[i] = NULL;
		i++;
	}
	free(char2);
	char2 = NULL;

}

void	free_char3(char ****a_char3)
{
	size_t	i;
	char	***char3;

	i = 0;
	char3 = *a_char3;
	while (char3[i])
	{
		free_char2(char3[i]);
		char3[i] = NULL;
		i++;
	}
	free(char3);
	char3 = NULL;
}

