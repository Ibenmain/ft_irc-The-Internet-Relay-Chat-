/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:48:03 by ibenmain          #+#    #+#             */
/*   Updated: 2023/03/09 23:12:57 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/poll.h>
#include <errno.h>
#include<fcntl.h>


class server
{
private:
    struct sockaddr_in  serv_add;
    int	socket_serv;
	int bind_result;
    int on;
    int nfd;
    int close_conne;
    struct pollfd fds[1024];
public:
    server();
    ~server();
    void    runServer(char **av);
};
void	ft_print_err(std::string str);
#endif