/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:57:16 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/23 18:31:09 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::privmsg(std::vector<std::string> receiveddata, int sockfd){

    for (std::map<int, Client>::iterator it = usernickMap.begin(); it != usernickMap.end(); ++it) {
        if(receiveddata.size() >= 3){
            if(it->second.get_nickname() == receiveddata[1]){
                std::string msg;
                for (size_t j = 2; j < receiveddata.size() ; j++){
                        size_t firstnonspace = receiveddata[j].find_first_not_of(" ");
                            if (firstnonspace != std::string::npos)
                            receiveddata[j] = receiveddata[j].substr(firstnonspace);
                        msg += receiveddata[j] + ' ';
                    }
                msg = "You received message from " + usernickMap[sockfd].get_nickname() + ": " + msg;
                success(it->first, (msg + '\n'));
            }
            else if(it->second.get_nickname() != receiveddata[1] && it != usernickMap.end())
                error(sockfd, "Error: User not found!\n");
        }
        else 
            error(sockfd, "Error: wrong arguments!\n");
    }
    return ;
}
