#include "../../inc/server.h"

int create_server(int port, int backlog)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putstr("Bind errir\n");
		return(-1);
	}
	listen(sock, backlog);
	return (sock);
}

int usage()
{
	ft_putstr("Usage: ./server [port]\n");
	return (1);
}

int main(int ac, char **av)
{
	int 				sock;
	int 				port;
	int 				cs;
	int					r;
	unsigned int 		cslen;
	struct sockaddr_in	csin;
	char 				buf[BUF_SIZE];



	if (ac != 2)
		return usage();

	port = ft_atoi(av[1]);
	sock = create_server(port, 42);
	if (sock == -1)
		return (1);
	cs = accept(sock, (struct sockaddr *)&csin, &cslen);
	r = read(cs, buf, BUF_SIZE - 1);
	close(cs);
	close(sock);
	return (0);
}