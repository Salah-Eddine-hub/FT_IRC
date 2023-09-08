/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:19:10 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/08 19:06:51 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

int Server::is_valide_name(std::string channel_name, int sockfd){

    for (size_t i = 0; i < channel_name.size() - 1; i++)
    {
        if(!isalnum(channel_name[i + 1]) && channel_name[i + 1] != '_'){
            error(sockfd, "Error: Invalide channel name!\n");
            return 0;
        }
    }
    return 1;
}

void creating_channel()
{

}


void Server::join(std::vector<std::string> receiveddata, int sockfd) {

    if (receiveddata.size() < 2){
        error(sockfd, ":irc_server 461 " + usernickMap[sockfd].get_nickname() + " JOIN :Not enough parameters\n");
        return ;
    }
    if (receiveddata[1][0] != '#' || receiveddata[1].size() < 2) {
        error(sockfd, "Error: Syntax error!\n");
        return ;
    }
    if(!is_valide_name(receiveddata[1], sockfd))
        return ;
    if (channelsMap.find(strtolower(receiveddata[1])) != channelsMap.end()) 
    {
        std::string tmpreceiveddata1 = receiveddata[1];
        receiveddata[1] = strtolower(receiveddata[1]);
        if (channelsMap[receiveddata[1]].get_is_invite_only() && !usernickMap[sockfd].get_is_invited(receiveddata[1])){
            error(sockfd, ":irc_server 473 " + usernickMap[sockfd].get_nickname() + ' ' + channelsMap[receiveddata[1]].get_original_channel_name() + " :Cannot join channel (+i)\n");
            return ;
        }
        // if (channelsMap[receiveddata[1]].get_is_pwd_needed().empty() && receiveddata.size() != 2) 
        //     error(sockfd, "Error: Wrong number of arguments!\n");
        // if (!channelsMap[receiveddata[1]].get_is_pwd_needed().empty() && receiveddata.size() < 3 && !channelsMap[receiveddata[1]].get_is_member(sockfd))
        //     error(sockfd, "Error: Wrong number of arguments. You need a password to join this channel!\n");
        else if (!channelsMap[receiveddata[1]].get_is_pwd_needed().empty()) 
        {
            std::string pwd;
            for (size_t i = 2; i < receiveddata.size(); i++){
                size_t firstnonspace = receiveddata[i].find_first_not_of(" ");
                    if (firstnonspace != std::string::npos)
                        receiveddata[i] = receiveddata[i].substr(firstnonspace);
                pwd += receiveddata[i] + ' ';
            }            
            pwd.resize(pwd.size() - 1);
            if (channelsMap[receiveddata[1]].get_is_pwd_needed() == pwd)
                channelsMap[receiveddata[1]].add_member_to_channel(sockfd, usernickMap[sockfd].get_nickname(), tmpreceiveddata1 , usernickMap);
            else
                error(sockfd, ":irc_server 475 " + usernickMap[sockfd].get_nickname() + ' ' + channelsMap[receiveddata[1]].get_original_channel_name() + " :Cannot join channel (+k)\n");
        }
        else
            channelsMap[receiveddata[1]].add_member_to_channel(sockfd, usernickMap[sockfd].get_nickname(), tmpreceiveddata1 , usernickMap);
    }
    else {
        // :hh1!~a@49fb-d1fa-ed7e-5417-3c35.253.197.ip JOIN :#hh
        // :punch.wa.us.dal.net 353 hh1 = #hh :@hh1 
        // // :punch.wa.us.dal.net 366 hh1 #hh :End of /NAMES list.
        // std::cout << receiveddata[1]<< "----------------------------\n";

        // std::cout << receiveddata[1] << "----------------------------\n";
        // :hh3!~d@49fb-d1fa-ed7e-5417-3c35.253.197.ip JOIN :#hH
        // :punch.wa.us.dal.net 353 hh3 = #hh :hh3 hh2 @hh1 
        // :punch.wa.us.dal.net 366 hh3 #hH :End of /NAMES list.
        // success(sockfd, ':' + usernickMap[sockfd].get_nickname() + "!localhost JOIN :" + receiveddata[1] + "\n");
        // success(sockfd, ":irc_server 353 " + usernickMap[sockfd].get_nickname() + " = " + receiveddata[1] + ":@" + receiveddata[1] + "\n");
        // success(sockfd, ":irc_server 353 " + usernickMap[sockfd].get_nickname() + receiveddata[1] + ":End of /NAMES list.\n");
        channelsMap[strtolower(receiveddata[1])] = Channel(receiveddata[1]);
        channelsMap[strtolower(receiveddata[1])].add_member_to_channel(sockfd, usernickMap[sockfd].get_nickname(), receiveddata[1], usernickMap);
        channelsMap[strtolower(receiveddata[1])].set_is_operator(sockfd);
    }
    return ;
}
