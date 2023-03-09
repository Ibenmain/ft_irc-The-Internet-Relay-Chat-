/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:48:03 by ibenmain          #+#    #+#             */
/*   Updated: 2023/03/08 20:13:00 by ibenmain         ###   ########.fr       */
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
    /* --Structures for handling internet addresses-- */
public:
    server();
    ~server();
    void    runServer();
};
void	ft_print_err(std::string str);
#endif