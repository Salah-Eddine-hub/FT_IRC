/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 12:46:30 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/12 13:46:49 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::mode(std::vector<std::string> receiveddata, int sockfd)
{

    if (receiveddata.size() < 3)
    {
        inv_mssg(sockfd, ":irc_server 461 " + usernickMap[sockfd].get_nickname() + " MODE :Not enough parameters!\n");
        return ;
    }

    receiveddata[1] = strtolower(receiveddata[1]);
    if(channelsMap.find(receiveddata[1]) != channelsMap.end()) {
        if (!channelsMap[receiveddata[1]].get_is_operator(sockfd)) {
            inv_mssg(sockfd, ":irc_server 482 " + usernickMap[sockfd].get_nickname() + ' ' + channelsMap[receiveddata[1]].get_original_channel_name() + " :You're not channel operator\n");
            return ;
        }
        if(receiveddata[2] == "+i") {
            channelsMap[receiveddata[1]].set_is_invite_only(1);
            channelsMap[receiveddata[1]].broadcast(':' + usernickMap[sockfd].get_nickname() + "!localhost MODE " + channelsMap[receiveddata[1]].get_original_channel_name() +" +i\n", -1);
        }
        else if(receiveddata[2] == "-i") {
            channelsMap[receiveddata[1]].set_is_invite_only(0);
            channelsMap[receiveddata[1]].broadcast(':' + usernickMap[sockfd].get_nickname() + "!localhost MODE " + channelsMap[receiveddata[1]].get_original_channel_name() +" -i\n", -1);
        }
        else if(receiveddata[2] == "+t") {
            channelsMap[receiveddata[1]].set_is_topic_restricted(1);
            channelsMap[receiveddata[1]].broadcast(':' + usernickMap[sockfd].get_nickname() + "!localhost MODE " + channelsMap[receiveddata[1]].get_original_channel_name() +" +t\n", -1);
        }
        else if(receiveddata[2] == "-t") {
            channelsMap[receiveddata[1]].set_is_topic_restricted(0);
            channelsMap[receiveddata[1]].broadcast(':' + usernickMap[sockfd].get_nickname() + "!localhost MODE " + channelsMap[receiveddata[1]].get_original_channel_name() +" -t\n", -1);
        }
        else if(receiveddata[2] == "-k") {
            if (receiveddata.size() > 3){
                channelsMap[receiveddata[1]].broadcast(':' + usernickMap[sockfd].get_nickname() + "!localhost MODE " + channelsMap[receiveddata[1]].get_original_channel_name() +" -k " + channelsMap[receiveddata[1]].get_is_pwd_needed() + '\n', -1);
                channelsMap[receiveddata[1]].set_is_pwd_needed("");
            }
        }
        else if(receiveddata[2] == "-l") {
            channelsMap[receiveddata[1]].set_limit(0);
            channelsMap[receiveddata[1]].broadcast(':' + usernickMap[sockfd].get_nickname() + "!localhost MODE " + channelsMap[receiveddata[1]].get_original_channel_name() +" -l\n", -1);
        }

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

        else if(receiveddata[2] == "+o" && receiveddata.size() > 3) {
            if(usernickMap.find(get_sockfd(receiveddata[3])) == usernickMap.end()) {
                inv_mssg(sockfd, ":irc_server 401 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[3] + " :No such nick/channel\n");
                inv_mssg(sockfd, ":irc_server 441 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[3] + ' ' + channelsMap[receiveddata[1]].get_original_channel_name() + " :They aren't on that channel\n");
            }
            else if(!channelsMap[strtolower(receiveddata[1])].get_is_member(get_sockfd(receiveddata[3])))
                inv_mssg(sockfd, ":irc_server 441 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[3] + ' ' + channelsMap[receiveddata[1]].get_original_channel_name() + " :They aren't on that channel\n");
            else {
                channelsMap[receiveddata[1]].set_is_operator(get_sockfd(receiveddata[3]));
                channelsMap[receiveddata[1]].broadcast(':' + usernickMap[sockfd].get_nickname() + "!localhost MODE " + channelsMap[receiveddata[1]].get_original_channel_name() + " +o " + receiveddata[3] + '\n', -1);
            }
        }
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

        else if(receiveddata[2] == "-o" && receiveddata.size() > 3) {
            if(usernickMap.find(get_sockfd(receiveddata[3])) == usernickMap.end()) {
                inv_mssg(sockfd, ":irc_server 401 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[3] + " :No such nick/channel\n");
                inv_mssg(sockfd, ":irc_server 441 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[3] + ' ' + channelsMap[receiveddata[1]].get_original_channel_name() + " :They aren't on that channel\n");
            }
            else if(!channelsMap[strtolower(receiveddata[1])].get_is_member(get_sockfd(receiveddata[3])))
                inv_mssg(sockfd, ":irc_server 441 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[3] + ' ' + channelsMap[receiveddata[1]].get_original_channel_name() + " :They aren't on that channel\n");
            else {
                channelsMap[receiveddata[1]].remove_the_operator(get_sockfd(receiveddata[3]));
                channelsMap[receiveddata[1]].broadcast(':' + usernickMap[sockfd].get_nickname() + "!localhost MODE " + channelsMap[receiveddata[1]].get_original_channel_name() + " -o " + receiveddata[3] + '\n', -1);
            }
        }
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

        if(receiveddata[2] == "+k" && receiveddata.size() > 3) {
            if(receiveddata[3].size() > 23)
                receiveddata[3].resize(23);
            channelsMap[receiveddata[1]].set_is_pwd_needed(receiveddata[3]);
            channelsMap[receiveddata[1]].broadcast(':' + usernickMap[sockfd].get_nickname() + "!localhost MODE " + channelsMap[receiveddata[1]].get_original_channel_name() +" +k " + receiveddata[3] + '\n', -1);
        }
        else if(receiveddata[2] == "+l") {
            std::stringstream ss;
            int limit = 0;
            if (receiveddata.size() < 4){
                inv_mssg(sockfd, ":irc_server 461 " + usernickMap[sockfd].get_nickname() + "MODE +l :Not enough parameters\n");
                return;
            }
            ss << receiveddata[3].substr(0,is_num(receiveddata[3]));
            ss >> limit;
            if (limit > 0)
            {
                    channelsMap[receiveddata[1]].set_limit(limit);
                    std::ostringstream oss;
                    oss << usernickMap[sockfd].get_nickname() << "!localhost MODE "<< channelsMap[receiveddata[1]].get_original_channel_name() << " +l " << limit << " \n";
                    channelsMap[receiveddata[1]].broadcast(oss.str() , -1);
            }
        }
    }
    else
        inv_mssg(sockfd, ":irc_server 403 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[1] + " :No such channel\n");
}
