#include "../header/codexion.h"

t_table	*init_table(t_parse_data *data)
{
	int	i;
	t_table	*table;
	t_coders	**coders;

	table = malloc(sizeof(t_table));
	if (table == NULL)
		return (NULL);
	coders = malloc(data->number_of_coders * sizeof(t_coders));
	if (coders == NULL)
		return (NULL);
	i = 0;
	while (i < data->number_of_coders)
	{
		coders[i] = init_coders();
		i++;
	}
	table->coders = coders;
	return (table);
}
