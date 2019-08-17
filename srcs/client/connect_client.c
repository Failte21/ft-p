/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 14:50:21 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/17 15:40:22 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

// static int				create_cs(int socket)
// {
// 	int 				cs;
// 	unsigned int 		cslen;
// 	struct sockaddr_in	csin;

// 	cs = accept(socket, (struct sockaddr *)&csin, &cslen);
// 	if (cs == -1)
// 		ft_putstr("CS ERROR");
// 	return (cs);
// }

static int 				create_socket(int port, char *address)
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
	sin.sin_addr.s_addr = inet_addr(address);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putstr("Connection error\n");
		return(-1);
	}
	return (sock);
}

static t_client_handler	*init(int pi_socket, int dts_socket, int pi_cs)
{
	t_client_handler	*handler;

	handler = malloc(sizeof(t_client_handler));
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

t_client_handler		*connect_client(char *address, int pi_port)
{
	int					pi_socket;
	int					dts_socket;
	int					dts_cs;

	pi_socket = create_socket(pi_port, address);
	dts_socket = 0; // create_socket(DATA_PORT, address);
	if (pi_socket == -1 || dts_socket == -1)
		return (NULL);
	// listen(dts_socket, 42);						// TODO: find out about backlog
	dts_cs = 0; // create_cs(dts_socket);
	if (dts_cs == -1)
		return (NULL);
	return (init(pi_socket, dts_socket, dts_cs));
}