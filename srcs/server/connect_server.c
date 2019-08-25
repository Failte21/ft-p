/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 12:32:20 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/25 14:07:19 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

static t_server_handler	*init()
{
	t_server_handler	*handler;

	handler = malloc(sizeof(t_server_handler));
	if (handler == NULL)
		return (ptr_error("malloc error\n"));

	handler->dtp_mode = PASSIVE;
	handler->dtp_connection.cs = -1;
	return (handler);
}

void					process_eol(char *s)
{
	if (*s == '\n')
		*s = '\0';
	if (s != NULL && *s != '\0')
		process_eol(s + 1);
}
int						wait_for_commands(t_server_handler *handler)
{
	int		r;
	char	buf[BUF_SIZE];
	char	**split;
	char	*tmp;

	while ((r = read(handler->pi_connection.cs, buf, BUF_SIZE - 1)))
	{
		buf[r] = '\0';

		tmp = buf;
		process_eol(tmp);
		split = ft_strsplit(buf, ' ');
		process_command(handler, *split, split + 1);
	}
	return (0);
}

int						connect_server(int pi_port)
{
	int					pi_socket;
	int					dtp_socket;
	int					pi_cs;
	int					running;
	t_server_handler	*handler;
	pid_t				pid;

	handler = init();
	running = 1;
	pi_socket = create_srv_socket(pi_port);
	dtp_socket = create_srv_socket(4141);
	if (pi_socket == -1 || dtp_socket == -1)
		return (-1);
	if ((listen(pi_socket, 42) == -1) || listen(dtp_socket, 42) == -1) { // TODO: find out about backlog
		return (-1);
	}
	handler->pi_connection.socket = pi_socket;
	handler->dtp_connection.socket = dtp_socket;
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
			wait_for_commands(handler);
	}
	return 0;
}