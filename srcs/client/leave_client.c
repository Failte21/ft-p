#include "../../inc/ft_p.h"

int	leave_client(t_client_handler *handler)
{
	close(handler->pi_connection.socket);
	close(handler->pi_connection.cs);
	close(handler->dts_connection.socket);
	free(handler);
	return (0);
}