#include "../header/codexion.h"

void	*routine_test()
{
	printf("I am a new thread\n");
	usleep(1000);
	return (NULL);
}

t_coders	*init_coders(int i, t_table *table)
{
	t_coders	*coder;

	coder = malloc(sizeof(t_coders));
	if (coder == NULL)
		return (NULL);
	coder->data = table->data;
	if (i == 1)
	{
		coder->right = table->dongles[table->data->number_of_coders - 1];
		coder->left = table->dongles[0];
	}
	else
	{
		coder->right = table->dongles[i - 2];
		coder->left = table->dongles[i - 1];
	}
	coder->n = i;
	coder->compile_nb = 0;
	if (pthread_create(&coder->id, NULL, coders_routine, coder) != 0)
	{
		printf("Error in thread create of %d coder", coder->n);
		return (NULL);
	}
	return (coder);
}
