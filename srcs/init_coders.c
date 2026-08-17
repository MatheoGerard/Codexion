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
	if (pthread_create(&coder->id, NULL, routine_test, NULL) != 0)
	{
		printf("Error in thread create of %d coder", coder->n);
		return (NULL);
	}
	coder->n = i;
	printf("j suis le coder %d\n", coder->n);
	printf("j ai %d a droite\n", coder->right->n);
	printf("j ai %d a gauche\n", coder->left->n);
	return (coder);
}
