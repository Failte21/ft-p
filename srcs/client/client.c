/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:11:21 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/17 15:40:58 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

int usage()
{
	ft_putstr("Usage: ./server [addr] [port]\n");
	return (1);
}

int client_listen(t_client_handler *handler)
{
	write(handler->pi_connection.socket, "hello server", 5);
	while(1)
	{
		
	}
	return (0);
}

int main(int ac, char **av)
{
	int 				port;
	char				*address;
	t_client_handler	*handler;

	if (ac != 3)
		return usage();

	address = av[1];
	port = ft_atoi(av[2]);
	handler = connect_client(address, port);
	printf("HERE");
	if (handler == NULL)
		return (1);
	return (client_listen(handler) + leave_client(handler));
}