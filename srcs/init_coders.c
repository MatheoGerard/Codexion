#include "../header/codexion.h"

void	*routine_test()
{
	printf("I am a new thread\n");
	usleep(1000);
	return (NULL);
}

t_coders	*init_coders(int i)
{
	t_coders	*coder;

	coder = malloc(sizeof(t_coders));
	if (coder == NULL)
		return (NULL);
	if (pthread_create(&coder->id, NULL, routine_test, NULL) != 0)
	{
		printf("Error in thread create of %d coder", coder->n);
		return (NULL);
	}
	coder->n = i;
	return (coder);
}
