/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 14:50:21 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/18 13:59:08 by lsimon           ###   ########.fr       */
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

static t_client_handler	*init(int pi_socket, int dtp_socket, int pi_cs, struct hostent *host)
{
	t_client_handler	*handler;

	handler = malloc(sizeof(t_client_handler));
	if (handler == NULL)
	{
		ft_putstr("Memory allocation error\n");
		return(NULL);
	}

	handler->host = host;
	handler->dtp_mode = ACTIVE;
	handler->dtp_connection.socket = dtp_socket;
	handler->pi_connection.socket = pi_socket;
	handler->pi_connection.cs = pi_cs;
	return (handler);
}

t_client_handler		*connect_client(char *address, int pi_port)
{
	int					pi_socket;
	struct hostent		*host;

	host = gethostbyname(address);
	pi_socket = create_socket(pi_port, address, ACTIVE);
	if (pi_socket == -1)
		return (NULL);
	// listen(dtp_socket, 42);						// TODO: find out about backlog
	return (init(pi_socket, 0, 0, host));
}