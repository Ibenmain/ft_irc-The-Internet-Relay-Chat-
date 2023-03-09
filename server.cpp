/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:47:46 by ibenmain          #+#    #+#             */
/*   Updated: 2023/03/09 23:35:29 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

server::server()
{
}

server::~server()
{
}

void	ft_print_err(std::string str)
{
	int	i;
	i = 0;
	while (str[i])
	{
		std::cout << str[i];
		i++;
	}
	exit(0);
}

void	server::runServer(char **av)
{
   on = 1;
   nfd = 1;
   int end_server = false;
   int new_sd;
   int rec;
   int len;
   int current_size;
   char buffer[256];
   int compress_arr = false;
   try
   {
	   socket_serv = socket(AF_INET, SOCK_STREAM, 0);
	   if (socket_serv < 0)
	   	throw "error: can't open the file (socket)\n";
      /*
         The socket() function creates a new socket.
         it takes 3 arguments,
            a. AF_INET: address domain of the socket.
            b. SOCK_STREAM: Type of socket. a stream socket in
            which characters are read in a continuous stream (TCP)
            c. Third is a protocol argument: should always be 0. The 
            OS will choose the most appropiate protocol.
            This will return a small integer and is used for all
            references to this socket. If the socket call fails, 
            it returns -1.
      */
      bzero((char *) &serv_add, sizeof(serv_add));
	   serv_add.sin_family = AF_INET;
      serv_add.sin_addr.s_addr = htons(INADDR_ANY);
      serv_add.sin_port = htons(stoi(std::string(av[1])));
      /*
           The variable serv_addr is a structure of sockaddr_in.
           sin_family contains a code for the address family.
           It should always be set to AF_INET.
   
           INADDR_ANY contains the IP address of the host. For 
           server code, this will always be the IP address of 
           the machine on which the server is running.
   
           htons() converts the port number from host byte order 
           to a port number in network byte order.
      */
      if (setsockopt(socket_serv, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
	   	throw "error: can't open the file (setsocketopt)\n";
      /*************************************************************/
      /* Allow socket descriptor to be reuseable                   */
      /*************************************************************/
      if (fcntl(socket_serv, F_SETFD, O_NONBLOCK) < 0)
	   	throw "error: can't open the file (fcntl)\n";
      /*************************************************************/
      /* Set socket to be nonblocking. All of the sockets for      */
      /* the incoming connections will also be nonblocking since   */
      /* they will inherit that state from the listening socket.   */
      /*************************************************************/
	   bind_result = bind(socket_serv, (struct sockaddr*)&serv_add, sizeof(serv_add));
       if (bind_result < 0)
	   	throw "error: binding socket\n";
      /*
           The bind() system call binds a socket to an address, 
           in this case the address of the current host and port number 
           on which the server will run. It takes three arguments, 
           the socket file descriptor. The second argument is a pointer 
           to a structure of type sockaddr, this must be cast to
           the correct type.
      */
	   if (listen(socket_serv, 5) < 0)
	   	throw "error: binding socket\n";
      /*
           The listen system call allows the process to listen 
           on the socket for connections. 
   
           The program will be stay idle here if there are no 
           incomming connections.
   
           The first argument is the socket file descriptor, 
           and the second is the size for the number of clients 
           i.e the number of connections that the server can
           handle while the process is handling a particular 
           connection. The maximum size permitted by most 
           systems is 5.
      */
      memset(fds, 0 , sizeof(fds));
      /*************************************************************/
      /* Initialize the pollfd structure                           */
      /*************************************************************/
      fds[0].fd = socket_serv;
      fds[0].events = POLLIN;
      /*************************************************************/
      /* Set up the initial listening socket                        */
      /*************************************************************/
   }
   catch(const char *message)
   {
      std::cerr << message;
   }
   /*************************************************************/
   /* Loop waiting for incoming connects or for incoming data   */
   /* on any of the connected sockets.                          */
   /*************************************************************/
   do {
      if (poll(fds, nfd, -1) < 0)
		   ft_print_err("error: polling socket\n");
      /***********************************************************/
      /* Call poll() and wait for it to complete.                */
      /***********************************************************/
      current_size = nfd;
      for (int i = 0; i < current_size; i++)
      {
         if (fds[i].revents == 0)
            continue;
         /*********************************************************/
         /* Loop through to find the descriptors that returned    */
         /* POLLIN and determine whether it's the listening       */
         /* or the active connection.                             */
         /*********************************************************/
         if (fds[i].revents != POLLIN)
         {
            throw "error\n";
            end_server = true;
            break;
         }
         /*********************************************************/
         /* If revents is not POLLIN, it's an unexpected result,  */
         /* log and end the server.                               */
         /*********************************************************/
         if (fds[i].fd == socket_serv)
         {
            new_sd = accept(socket_serv,NULL, NULL);
            std::cout << "new_sd= " << new_sd << "\n";
            if (new_sd < 0)
            {
               if (errno != EWOULDBLOCK)
                  end_server = true;
               break;
            }
            /*****************************************************/
            /* Accept each incoming connection. If               */
            /* accept fails with EWOULDBLOCK, then we            */
            /* have accepted all of them. Any other              */
            /* failure on accept will cause us to end the        */
            /* server.                                           */
            /*****************************************************/
            std::cout << "New incoming connection: " << new_sd << "\n";
            fds[nfd].fd = new_sd;
            fds[nfd].events = POLLIN;
            fds[nfd].revents = 0;
            nfd++;
            /*****************************************************/
            /* Add the new incoming connection to the            */
            /* pollfd structure                                  */
            /*****************************************************/
         }
         else
         {
            close_conne = false;
           
               bzero(&buffer, sizeof(buffer));
               rec = recv(fds[i].fd, buffer, sizeof(buffer), 0);
               std::cout << "client" << fds[i].fd << ": " << buffer;
               if (rec <= 0)
               {
                  if (errno != EWOULDBLOCK)
                  {
                    perror("recv() failed");
                    close_conne = true;
                  }
                  break;
               }
               len = rec;
               std::string msg = "you send: " + (std::string)buffer;
               rec = send(fds[i].fd, msg.c_str(), strlen(msg.c_str()), 0);
               if (rec < 0)
               {
                  close_conne = true;
                  break;
               }
            if (close_conne)
            {
               close(fds[i].fd);
               fds[i].fd = -1;
               compress_arr = true;
            }
         }
      }
      if (compress_arr)
      {
         compress_arr = false;
         for (int i = 0; i < nfd; i++)
         {
           if (fds[i].fd == -1)
           {
             for(int j = i; j < nfd-1; j++)
             {
               fds[j].fd = fds[j+1].fd;
             }
             i--;
             nfd--;
           }
         }
    }
   }while (end_server == false);
   for (int i = 0; i < nfd; i++)
   {
      if(fds[i].fd >= 0)
      close(fds[i].fd);
   }

}
