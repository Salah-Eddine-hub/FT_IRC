/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 04:01:14 by sharrach          #+#    #+#             */
/*   Updated: 2023/08/15 17:46:05 by iellyass         ###   ########.fr       */
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