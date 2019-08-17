/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 12:32:20 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/17 15:33:34 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"


static int				create_cs(int socket)
{
	int 				cs;
	unsigned int 		cslen;
	struct sockaddr_in	csin;

	cs = accept(socket, (struct sockaddr *)&csin, &cslen);
	if (cs == -1)
		ft_putstr("CS error");
	return (cs);
}

static int 				create_socket(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putstr("Bind error\n");
		return(-1);
	}
	return (sock);
}

static t_server_handler	*init(int pi_socket, int dts_socket, int pi_cs)
{
	t_server_handler	*handler;

	handler = malloc(sizeof(t_server_handler));
	if (handler == NULL)
	{
		ft_putstr("Memory allocation error\n");
		return(NULL);
	}

	handler->dtp_mode = ACTIVE;
	handler->dts_connection.socket = dts_socket;
	handler->pi_connection.socket = pi_socket;
	handler->pi_connection.cs = pi_cs;
	return (handler);
}

t_server_handler		*connect_server(int pi_port)
{
	int					pi_socket;
	int					dts_socket;
	int					pi_cs;

	pi_socket = create_socket(pi_port);
	dts_socket = create_socket(DATA_PORT);
	if (pi_socket == -1 || dts_socket == -1)
		return (NULL);
	listen(pi_socket, 42);					// TODO: find out about backlog
	pi_cs = create_cs(pi_socket);
	if (pi_cs == -1)
		return (NULL);	
	return (init(pi_socket, dts_socket, pi_cs));
}