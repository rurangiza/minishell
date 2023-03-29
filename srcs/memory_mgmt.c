
#include "../includes/minishell.h"

void	ft_free_matrix(char **matrix)
{
	int	index;

	if (!matrix || !matrix[0])
		return ;
	index = 0;
	while (matrix[index])
		free(matrix[index++]);
	free(matrix);
}