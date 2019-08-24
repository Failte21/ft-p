/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_pi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 11:53:19 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/24 11:56:18 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

int	read_pi(t_client_handler *handler)
{
	int 	r;
	char	buf[BUF_SIZE];

	while ((r = read(handler->pi_connection.socket, buf, BUF_SIZE - 1)) != -1)
	{
		buf[r] = '\0';
		write(1, buf, r);
	}
}