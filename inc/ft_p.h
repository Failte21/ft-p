/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:10:40 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/17 14:57:46 by lsimon           ###   ########.fr       */
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
# include <stdlib.h>

# define BUF_SIZE 1024
# define N_COMMANDS 1
# define DATA_PORT 4242

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
	char							*command_name;				// Ex: ls
}				t_command;

typedef enum	e_mode
{
	ACTIVE,
	PASSIVE
}				t_mode;

typedef struct	s_connection
{
	int	socket;
	int	cs;
}				t_connection;

// SERVER
typedef struct	s_server_handler
{
	t_connection	pi_connection;
	t_connection 	dts_connection;
	t_mode			dtp_mode;			// server mode for DTP connection (default should be ACTIVE)
}				t_server_handler;

typedef	int		(*t_builtin)(t_server_handler *);

typedef struct	s_command_handler
{
	char			*command_name;
	t_builtin		fn;
}				t_command_handler;

// CLIENT
typedef struct	s_client_handler
{
	t_connection	pi_connection;
	t_connection	dts_connection;
	t_mode			dtp_mode;			// client mode for DTP connection (default should be PASSIVE)
}				t_client_handler;

typedef struct	s_command_reply
{
	int 	code;
	char	*message;
}				t_command_reply;

// CLIENT
t_client_handler	*connect_client(char *address, int pi_port);
void				send_command(int dest_socket, char *command_name);
int					read_datas(t_client_handler *handler, char *datas);
int					leave_client(t_client_handler *handler);

// SERVER
t_server_handler	*connect_server(int pi_port);
int					leave_server(t_server_handler *handler);
int					process_command(t_server_handler *handler, char *command_name);
int					reply(t_server_handler *handler, t_command_reply *reply);
int					write_datas(t_server_handler *handler, char	*datas);
int					ls_command(t_server_handler *handler);

static t_command_handler	g_command_handler_list[N_COMMANDS] =
{
	{ "ls", ls_command }
};

#endif