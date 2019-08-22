/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 12:32:20 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/22 11:32:09 by lsimon           ###   ########.fr       */
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

static t_server_handler	*init()
{
	t_server_handler	*handler;

	handler = malloc(sizeof(t_server_handler));
	if (handler == NULL)
	{
		ft_putstr("Memory allocation error\n");
		return(NULL);
	}

	handler->dtp_mode = PASSIVE;
	return (handler);
}

int						server_listen(t_server_handler *handler)
{
	int		r;
	char	buf[BUF_SIZE];

	while ((r = read(handler->pi_connection.cs, buf, BUF_SIZE - 1)))
	{
		buf[r] = '\0';
		printf("%s", buf);
	}
	return (0);
}

int						connect_server(int pi_port)
{
	int					pi_socket;
	int					pi_cs;
	int					running;
	t_server_handler	*handler;
	pid_t				pid;

	handler = init();
	running = 1;
	pi_socket = create_socket(pi_port, NULL, PASSIVE);
	if (pi_socket == -1)
		return (-1);
	if ((listen(pi_socket, 42) == -1)) { // TODO: find out about backlog
		return (-1);
	}
	handler->pi_connection.socket = pi_socket;
	while (running)
	{
		pi_cs = create_cs(pi_socket);
		if (pi_cs == -1)
			return (-1);
		handler->pi_connection.cs = pi_cs;
		pid = fork();
		if (pid > 0)
			close(handler->pi_connection.cs);
		else if (pid == 0)
			server_listen(handler);
	}
	return 0;
}