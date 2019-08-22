/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 14:50:21 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/22 11:48:41 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

t_client_handler	*init_client_handler(struct hostent *host, int port)
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

int					leave_client(t_client_handler *handler)
{
	close(handler->pi_connection.socket);
	close(handler->pi_connection.cs);
	close(handler->dtp_connection.socket);
	free(handler);
	return (0);
}