/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:11:21 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/16 12:16:29 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

int create_client(char *addr, int port)
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
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putstr("Connection error\n");
		return(-1);
	}
	return (sock);
}

int usage()
{
	ft_putstr("Usage: ./server [addr] [port]\n");
	return (1);
}

int main(int ac, char **av)
{
	int 				sock;
	int 				port;
	char				*addr;

	if (ac != 3)
		return usage();

	addr = av[1];
	port = ft_atoi(av[2]);
	sock = create_client(addr, port);
	if (sock == -1)
		return (1);
	write(sock, "bonjour\n", 8);
	close(sock);
	return (0);
}