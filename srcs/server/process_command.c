/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 11:41:58 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/17 11:58:02 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

static t_builtin	*get_builtin(char *command_name, unsigned int i)
{
	if (i == N_COMMANDS)
		return (NULL);
	if (ft_strcmp(command_name, g_command_handler_list[i].command_name))
		return g_command_handler_list[i].fn;
	return (get_builtin(command_name, i + 1));
}

int					process_command(t_server_handler *handler, char *command_name)
{
	t_builtin	*fn;

	fn = get_builtin(command_name, 0);
	if (fn == NULL)
		return (-1); // TODO: print error || return command error
	return ((*fn)(handler));
}