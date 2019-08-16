/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:11:21 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/16 16:43:58 by lsimon           ###   ########.fr       */
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
	ft_putstr("Usage: ./client [addr] [port]\n");
	return (1);
}

int main(int ac, char **av)
{
	int 				sock;
	int 				port;
	char				*addr;
	char				buf[BUF_SIZE];
	int					r;
	DIR					*current_dir;
	struct dirent		*p_dirent;


	if (ac != 3)
		return usage();

	addr = av[1];
	port = ft_atoi(av[2]);
	// sock = create_client(addr, port);
	// if (sock == -1)
	// 	return (1);


	// LOCAL CD
	current_dir = opendir(".");
	printf("CURRENT DIR SIZE: %ld, %ld, %s\n", current_dir->__dd_size, current_dir->__dd_len, current_dir->__dd_buf);
	while ((p_dirent = readdir(current_dir)) != NULL) {
		printf ("[%s]\n", p_dirent->d_name);
	}
	
	// write(0, current_dir->__dd_buf, current_dir->__dd_len);
	// while ((r = read(0, buf, BUF_SIZE)))
	// {
	// 	write(sock, buf, r);
	// }
	// close(sock);
	return (0);
}