/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 11:41:58 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/24 18:29:28 by lsimon           ###   ########.fr       */
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
	int			s;

	fn = get_builtin(command_name, 0);
	ft_putstr("1.0\n");
	s = create_srv_socket(4141);
	// if (s == -1)
	// 	reply(handler, "500 error");
	if (fn == NULL)
		reply(handler, "500 Syntax error, command unrecognized.\n");
	else
	{
		reply(handler, "200 Command okay.\n");
		(*fn)(handler, args);
	}
}