#include "../header/codexion.h"

void	*routine_test()
{
	printf("I am a new thread\n");
	return (NULL);
}

t_coders	*init_coders()
{
	t_coders	*coder;

	coder = malloc(sizeof(t_coders));
	if (coder == NULL)
		return (NULL);
	pthread_create(&coder->id, NULL, routine_test, NULL);
	coder->name = 'a';
	return (coder);
}
