/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:10:40 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/22 11:59:10 by lsimon           ###   ########.fr       */
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
# include <stdio.h>

# define BUF_SIZE 1024
# define N_COMMANDS 1

// colors
# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

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
	DS_FILE,						// Probably the only one I'll have to handle
	DS_RECORD,
	DS_PAGE
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
	int	data_port;
	int	socket;
	int	cs;
}				t_connection;

// SERVER
typedef struct	s_server_handler
{
	t_connection	pi_connection;
	t_connection 	dtp_connection;
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
	t_connection	dtp_connection;
	t_mode			dtp_mode;			// client mode for DTP connection (default should be PASSIVE)
	struct hostent	*host;
}				t_client_handler;

typedef struct	s_command_reply
{
	int 	code;
	char	*message;
}				t_command_reply;

// CLIENT
t_client_handler	*init_client_handler(struct hostent *host, int port);
void				send_command(int dest_socket, char *command_name);
int					run_client_interface(char *address, int port);
int					read_datas(t_client_handler *handler, char *datas);
int					leave_client(t_client_handler *handler);

// SERVER
int					connect_server(int pi_port);
int					leave_server(t_server_handler *handler);
int					process_command(t_server_handler *handler, char *command_name);
int					reply(t_server_handler *handler, t_command_reply *reply);
int					write_datas(t_server_handler *handler, char	*datas);
int					ls_command(t_server_handler *handler);

// COMMON
int					create_socket(int port, char *address, t_mode mode);

static t_command_handler	g_command_handler_list[N_COMMANDS] =
{
	{ "ls", ls_command }
};

// socket(2), open(2), close(2), setsockopt(2), getsockname(2)
// ◦ getprotobyname(3), gethostbyname(3)
// ◦ bind(2), connect(2), listen(2), accept(2)
// ◦ htons(3), htonl(3), ntohs(3), ntohl(3)
// ◦ inet_addr(3), inet_ntoa(3)
// ◦ send(2), recv(2), execv(2), execl(2), dup2(2), wait4(2)
// ◦ fork(2), getcwd(3), exit(3), printf(3), signal(3)
// ◦ mmap(2), munmap(2), lseek(2), fstat(2)
// ◦ opendir(3), readdir(3), closedir(3)
// ◦ chdir(2), mkdir(2), unlink(2)
// ◦ les fonctions autorisées dans le cadre de votre libft (read(2), write(2), malloc(3),
// free(3), etc... par exemple ;-) )
// ◦ select(2), FD_CLR, FD_COPY, FD_ISSET, FD_SET, FD_ZERO mais uniquement si c’est pour faire quelque chose de correct !

#endif