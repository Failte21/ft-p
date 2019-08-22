/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 11:38:56 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/22 14:35:43 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

int		ls_command(t_server_handler *handler, char **args)
{
	while (*args != NULL)
		args = args + 1;
	send(handler->pi_connection.cs, "ls command", 10, 0);
	return (0);
}