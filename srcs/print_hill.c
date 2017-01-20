#include "lem_in.h"

static void putinput(void *osef, char **line)
{
	(void)osef;
	ft_putendl(*line);
}

void	print_hill(t_lemin *e)
{
	ft_iter(e->input, NULL, (void(*)(void *, void *))&putinput);
	ft_putendl("");
}
