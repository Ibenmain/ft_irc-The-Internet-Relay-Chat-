/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:41:47 by ibenmain          #+#    #+#             */
/*   Updated: 2023/03/09 23:07:21 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int	main(int ac, char **av)
{
	(void)av;
	server server;
	try
	{
		if (ac != 3)
			throw "error: invalid argument\n";
		server.runServer(av);
	}
	catch(const char *message)
	{
		std::cerr << message;
	}
}
