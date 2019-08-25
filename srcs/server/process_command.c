/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 11:41:58 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/25 14:06:37 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

static t_builtin	*get_builtin(char *command_name, unsigned int i)
{
	if (i == N_COMMANDS)
		return (NULL);
	if (ft_strcmp(command_name, g_command_handler_list[i].command_name) == 0)
		return &(g_command_handler_list[i].fn);
	return (get_builtin(command_name, i + 1));
}

void				process_command(t_server_handler *handler, char *command_name, char **args)
{
	t_builtin	*fn;
	int			dtp_cs;

	fn = get_builtin(command_name, 0);
	if (fn == NULL)
		reply(handler, "500 Syntax error, command unrecognized.\n");
	else
	{
		if (handler->dtp_connection.cs == -1)
		{
			dtp_cs = create_cs(handler->dtp_connection.socket);
			if (dtp_cs == -1)
				reply(handler, "425 Can't open data connection.\n");
			handler->dtp_connection.cs = dtp_cs;
		}
		else
			reply(handler, "125 Data connection already open; transfer starting.\n");
		(*fn)(handler, args);
	}

}