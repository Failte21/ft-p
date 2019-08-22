/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 14:50:21 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/22 11:32:24 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

static t_client_handler	*init(struct hostent *host, int port)
{
	t_client_handler	*handler;

	handler = malloc(sizeof(t_client_handler));
	if (handler == NULL)
	{
		ft_putstr("Memory allocation error\n");
		return(NULL);
	}

	handler->host = host;
	handler->dtp_connection.data_port = port;
	handler->dtp_mode = PASSIVE;
	return (handler);
}

int client_listen(t_client_handler *handler)
{
	char	buf[BUF_SIZE];
	int		r;

	while ((r = read(0, buf, BUF_SIZE - 1)))
		write(handler->pi_connection.socket, buf, r);
	return (0);
}

int						connect_client(char *address, int port)
{
	int					pi_socket;
	struct hostent		*host;
	t_client_handler	*handler;
	int					running;
	pid_t				pid;

	running = 1;
	host = gethostbyname(address);
	if (host == NULL)
		return (-1);
	handler = init(host, port);
	pid = fork();
	if (pid > 0)
	{
		pi_socket = create_socket(port, address, ACTIVE);
		if (pi_socket == -1)
			return (-1);
		handler->pi_connection.socket = pi_socket;
		return (client_listen(handler));
	}
	return (0);
}