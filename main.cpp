/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 04:01:14 by sharrach          #+#    #+#             */
/*   Updated: 2023/09/12 11:55:35 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int main(int ac, char *av[]){
	std::string port;
	if (ac != 3){
		std::cerr << "Wrong num of args" << std::endl;
		return 0;
	}
	port = av[1];
	// std::cout << av[1]<<std::endl;
	// if (port[0] == '"' && port[port.length() - 1] == '"') {
	// 	port = port.substr(1, port.length() - 2);
	// }
	if(port.find_first_not_of("0123456789") != std::string::npos){
		std::cerr << "Error: invalid port" << std::endl;
		return 0;
	}
	int myport;
	myport = atoi(port.c_str());
	std::cout << myport << std::endl;
	if(!myport || myport > 6669 || myport < 6660){
		std::cerr << "Error: incorect port." << std::endl;
		return 0;
	}
	Server server(myport, av[2]);
	return 0;
}