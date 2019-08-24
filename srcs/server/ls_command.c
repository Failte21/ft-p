/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 11:38:56 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/24 15:57:56 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

int					ls_command(t_server_handler *handler, char **args)
{
	char	*params[] = {"", NULL};

	if (args == NULL)
		args = NULL;
	return exec_builtin(handler, "/bin/ls", params);
}