/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 04:01:14 by sharrach          #+#    #+#             */
/*   Updated: 2023/08/13 14:33:02 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int main(int ac, char *av[]){
	int port;
	if (ac != 3){
		std::cerr << "Wrong num of args" << std::endl;
		return 0;
	}
	port = atoi(av[1]);
	std::cout << port << std::endl;
	if(!port){
		std::cerr << "Error: uncorect port." << std::endl;
		return 0;
	}
	Server server(port, av[2]);
	return 0;
}