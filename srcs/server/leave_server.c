/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 12:54:29 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/17 16:22:38 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

int	leave_server(t_server_handler *handler)
{
	close(handler->pi_connection.socket);
	close(handler->pi_connection.cs);
	close(handler->dtp_connection.socket);
	free(handler);
	return (0);
}