
#include "stream.h"

void	ft_delete_stream(t_stream **stream)
{
	free((*stream)->buff);
	free((*stream));
	*stream = NULL;
}
