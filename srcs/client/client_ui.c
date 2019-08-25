/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 11:42:38 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/25 14:51:18 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

static void		display_prompt(void)
{
	ft_putstr(CYN);
	ft_putstr("FTP $>");
	ft_putstr(RESET);
}

static void		greetings(void)
{
	ft_putstr(MAG);
	ft_putstr(WELCOME_CL);
	ft_putchar('\n');
	ft_putstr(RESET);
	display_prompt();
}

static void 	handle_command_lifecycle(t_client_handler *handler)
{
	int		r;
	char	buf[BUF_SIZE];
	int		dtp_socket;

	dtp_socket = create_cli_socket(inet_ntoa(*( struct in_addr*)(handler->host->h_addr_list[0])), 4141);
	while ((r = read(handler->pi_connection.socket, buf, BUF_SIZE - 1)) != -1)
	{
		write(1, buf, r);
		if (*buf == '1')
		{
			r = read(dtp_socket, buf, BUF_SIZE);
			write(1, buf, r);
		}
		if (*buf == '2' || *buf == '5')
		{
			close(dtp_socket);
			return ;
		}
	}
}

static int 		client_listen(t_client_handler *handler)
{
	char	buf[BUF_SIZE];
	int		r;

	greetings();
	while ((r = read(0, buf, BUF_SIZE - 1)))
	{
		write(handler->pi_connection.socket, buf, r);
		handle_command_lifecycle(handler);
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
		return int_error("gethostbyname error\n");
	handler = init_client_handler(host, port);
	pi_socket = create_cli_socket(inet_ntoa(*( struct in_addr*)(host->h_addr_list[0])), port);
	if (pi_socket == -1)
		return (-1);
	handler->pi_connection.socket = pi_socket;
	return (client_listen(handler));
}