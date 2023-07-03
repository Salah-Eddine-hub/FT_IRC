/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 04:01:14 by sharrach          #+#    #+#             */
/*   Updated: 2023/07/03 16:59:07 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main(int ac, char *av[]){

	(void)av;
	if (ac != 3){
		std::cerr << "Wrong num of args" << std::endl;
		return 0;
	}
}