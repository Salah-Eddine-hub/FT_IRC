/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pass.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:52:11 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/17 11:16:19 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

int Server::check_pass(std::vector<std::string> receiveddata, int sockfd)
{
	if(!usernickMap[sockfd].get_pwdconf()){
		if(strtolower(receiveddata[0]) != "pass")
			return 0;
		else {
			if(receiveddata.size() != 2)
				return (inv_mssg(sockfd, ':' + localhostcheck() + " 461 PASS :Not enough parameters\n")), 0;
			else {
				if(receiveddata[1] != this->password)
					return (inv_mssg(sockfd, ':' + localhostcheck() + " 464 * :Password incorrect\n")), 0;
				else{
					usernickMap[sockfd].set_pwdconf(1);
					return 0;
				}
			}
		}
	}
	return 1;
}
