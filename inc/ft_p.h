/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:10:40 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/17 10:34:47 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H

# include "../libft/libft.h"
# include <sys/socket.h>
# include <netdb.h>
# include <unistd.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# define BUF_SIZE 1024

typedef enum	e_data_type
{
	ASCII,						// Mandatory type (More for bonuses with line feed conversion)
}				t_data_type;

typedef enum	e_transmission_mode
{
	FORMAT,						// Don't really know what to do with this so far
	COMPRESS,
	NO_PROCESS
}				t_transmission_mode;

typedef enum	e_data_structure	
{
	FILE,						// Probably the only one I'll have to handle
	RECORD,
	PAGE
}				t_data_structure;

typedef struct	s_data_connection_parameters
{
	int					data_port;
	t_transmission_mode	transmission_mode;
	t_data_type			data_type;
	t_data_structure	data_structure;
}				t_data_connection_parameters;



typedef struct	s_commmand
{
	t_data_connection_parameters	*connection_parameters;		// Only mandatory for data related commands (EX: put)
	char							command_name[5];			// Ex: ls
}				t_command;

typedef enum	e_mode
{
	ACTIVE,
	PASSIVE
}				t_mode;

typedef struct	s_server_handler
{
	int		socket_control;		// socket in use for PI communication
	int 	socket_data;		// socket in use for DTP communication
	t_mode	dtp_mode;			// server mode for DTP connection (default should be ACTIVE)
}				t_server_handler;

typedef struct	s_command_reply
{
	int 	code;
	char	*message;
}				t_command_reply;

#endif