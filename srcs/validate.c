#include "../header/codexion.h"

int	validate_all(t_parse_data *data)
{
	if (validate_coders_data(data) 
			&& validate_timers_data(data) 
			&& validate_scheduler(data)
			&& validate_dongle_cooldown(data)
			&& validate_number_compiles(data))
	{
		return (1);
	}
	free_all(data);
	return (0);
}
