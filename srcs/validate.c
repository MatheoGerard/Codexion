#include "../header/codexion.h"

int	validate_all(t_parse_data *data)
{
	return (validate_coders_data(data) && validate_timers_data(data) && validate_scheduler(data));
}
