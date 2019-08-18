/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 12:32:20 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/18 13:18:50 by lsimon           ###   ########.fr       */
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

static t_server_handler	*init(int pi_socket, int dtp_socket, int pi_cs)
{
	t_server_handler	*handler;

	handler = malloc(sizeof(t_server_handler));
	if (handler == NULL)
	{
		ft_putstr("Memory allocation error\n");
		return(NULL);
	}

	handler->dtp_mode = ACTIVE;
	handler->dtp_connection.socket = dtp_socket;
	handler->pi_connection.socket = pi_socket;
	handler->pi_connection.cs = pi_cs;
	return (handler);
}

t_server_handler		*connect_server(int pi_port)
{
	int					pi_socket;
	int					pi_cs;

	pi_socket = create_socket(pi_port, NULL, PASSIVE);
	if (pi_socket == -1)
		return (NULL);
	listen(pi_socket, 42);					// TODO: find out about backlog
	pi_cs = create_cs(pi_socket);
	if (pi_cs == -1)
		return (NULL);	
	return (init(pi_socket, 0, pi_cs));
}