/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:08:08 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/18 09:37:07 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

int usage()
{
	ft_putstr("Usage: ./server [port]\n");
	return (1);
}

int server_listen(t_server_handler *handler)
{
	int		r;
	char	buf[BUF_SIZE];

	while ((r = read(handler->pi_connection.cs, buf, BUF_SIZE - 1)))
	{
		buf[r] = '\0';
		printf("%s\n", buf);
	}
	return (0);
}

int main(int ac, char **av)
{
	int					pi_port;
	t_server_handler	*handler;

	if (ac != 2)
		return usage();

	pi_port = ft_atoi(av[1]);
	handler = connect_server(pi_port);
	if (handler == NULL)
		return (1);
	return (server_listen(handler) + leave_server(handler));
}