
#include "../includes/minishell.h"

void	ft_free_matrix(char **matrix)
{
	int	index;

	index = 0;
	if (!matrix)
		return ;
	while (matrix[index])
		free(matrix[index++]);
	free(matrix);
}