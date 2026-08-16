#include "../header/codexion.h"

t_table	*init_table(t_parse_data *data)
{
	int	i;
	t_table	*table;
	t_dongle	**dongles;
	t_coders	**coders;

	table = malloc(sizeof(t_table));
	if (table == NULL)
		return (NULL);
	dongles = malloc(data->number_of_coders * sizeof(t_dongle));
	if (dongles == NULL)
		return (NULL);
	i = 0;
	while (i < data->number_of_coders)
	{
		dongles[i] = init_dongle(i + 1);
		i++;
	}
	table->dongles = dongles;
	coders = malloc(data->number_of_coders * sizeof(t_coders));
	if (coders == NULL)
		return (NULL);
	i = 0;
	while (i < data->number_of_coders)
	{
		coders[i] = init_coders(i + 1);
		i++;
	}
	table->coders = coders;
	return (table);
}
