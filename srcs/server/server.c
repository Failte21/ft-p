/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:08:08 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/22 12:57:33 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

int usage()
{
	ft_putstr("Usage: ./server <port>\n");
	return (1);
}

int main(int ac, char **av)
{
	int					pi_port;

	if (ac != 2)
		return usage();

	pi_port = ft_atoi(av[1]);
	if ((connect_server(pi_port) == -1))
		return (1);
	return (0);
}