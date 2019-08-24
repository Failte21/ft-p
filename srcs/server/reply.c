/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 15:34:49 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/24 15:42:07 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

int	reply(t_server_handler *handler, char *reply)
{
	write(handler->pi_connection.cs, reply, ft_strlen(reply));
	return (0);
}