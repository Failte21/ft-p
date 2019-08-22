/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 11:42:38 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/22 11:59:22 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

static void		display_prompt(void)
{
	ft_putstr(CYN);
	ft_putstr("FTP $>");
	ft_putstr(RESET);
}

static int 		client_listen(t_client_handler *handler)
{
	char	buf[BUF_SIZE];
	int		r;

	display_prompt();
	while ((r = read(0, buf, BUF_SIZE - 1)))
	{
		write(handler->pi_connection.socket, buf, r);
		display_prompt();
	}
	return (0);
}

int				run_client_interface(char *address, int port)
{
	int					pi_socket;
	struct hostent		*host;
	t_client_handler	*handler;
	int					running;

	running = 1;
	host = gethostbyname(address);
	if (host == NULL)
		return (-1);
	handler = init_client_handler(host, port);
	pi_socket = create_socket(port, address, ACTIVE);
	if (pi_socket == -1)
		return (-1);
	handler->pi_connection.socket = pi_socket;
	return (client_listen(handler));
}