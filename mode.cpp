/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 12:46:30 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/09 16:20:06 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::mode(std::vector<std::string> receiveddata, int sockfd)
{

    if (receiveddata.size() < 3)
    {
        error(sockfd, ":irc_server 461 " + usernickMap[sockfd].get_nickname() + " MODE :Not enough parameters!\n");
        return ;
    }

    receiveddata[1] = strtolower(receiveddata[1]);
    if(channelsMap.find(receiveddata[1]) != channelsMap.end()) {
        // if(!channelsMap[receiveddata[1]].get_is_member(sockfd)){
        //     error(sockfd, "Error: You are not a member of the channel!\n");
        //     return ;
        // }
        if (!channelsMap[receiveddata[1]].get_is_operator(sockfd)) {
            error(sockfd, ":irc_server 482 " + usernickMap[sockfd].get_nickname() + ' ' + channelsMap[receiveddata[1]].get_original_channel_name() + " :You're not channel operator\n");
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
                channelsMap[receiveddata[1]].broadcast(':' + usernickMap[sockfd].get_nickname() + "!localhost MODE " + channelsMap[receiveddata[1]].get_original_channel_name() +" +k " + channelsMap[receiveddata[1]].get_is_pwd_needed() + '\n', -1);
                channelsMap[receiveddata[1]].set_is_pwd_needed("");
            }
        }
        else if(receiveddata[2] == "-l") {
            channelsMap[receiveddata[1]].set_limit(0);
            channelsMap[receiveddata[1]].broadcast(':' + usernickMap[sockfd].get_nickname() + "!localhost MODE " + channelsMap[receiveddata[1]].get_original_channel_name() +" -l\n", -1);
        }
        else if(receiveddata[2] == "+o" && receiveddata.size() > 3) {
            if (channelsMap[receiveddata[1]].get_is_member(sockfd)){
                channelsMap[receiveddata[1]].set_is_operator(get_sockfd(receiveddata[3]));
                channelsMap[receiveddata[1]].broadcast(':' + usernickMap[sockfd].get_nickname() + "!irc_server MODE " + channelsMap[receiveddata[1]].get_original_channel_name() + " +o " + receiveddata[3] + '\n', -1);
            }
            else{
                if(usernickMap.find(get_sockfd(receiveddata[3])) != usernickMap.end()) {
                    error(sockfd, receiveddata[3] + ":irc_server 401 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[3] + " :No such nick/channel\n");
                    error(sockfd, receiveddata[3] + ":irc_server 441 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[3] + channelsMap[receiveddata[1]].get_original_channel_name() + " :They aren't on that channel\n");
                }
                else if (channelsMap.find(receiveddata[2]) == channelsMap.end())
                    error(sockfd, ":irc_server 403 " + usernickMap[sockfd].get_nickname() + ' ' + channelsMap[receiveddata[1]].get_original_channel_name() + " :No such channel\n");
                else
                    error(sockfd, receiveddata[3] + ":irc_server 441 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[3] + channelsMap[receiveddata[1]].get_original_channel_name() + " :They aren't on that channel\n");
            }
        }
        else if(receiveddata[2] == "-o") {
            if (channelsMap[receiveddata[1]].get_is_member(sockfd)){
                channelsMap[receiveddata[1]].remove_the_operator(get_sockfd(receiveddata[3]));
                channelsMap[receiveddata[1]].broadcast(receiveddata[3] + " is not an operator in this channel anymore!\n" , -1);
            }
            else{
                if(usernickMap.find(get_sockfd(receiveddata[3])) != usernickMap.end()) {
                    error(sockfd, receiveddata[3] + ":irc_server 401 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[3] + " :No such nick/channel\n");
                    error(sockfd, receiveddata[3] + ":irc_server 441 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[3] + channelsMap[receiveddata[1]].get_original_channel_name() + " :They aren't on that channel\n");
                }
                else if (channelsMap.find(receiveddata[2]) == channelsMap.end())
                    error(sockfd, ":irc_server 403 " + usernickMap[sockfd].get_nickname() + ' ' + channelsMap[receiveddata[1]].get_original_channel_name() + " :No such channel\n");
                else
                    error(sockfd, receiveddata[3] + ":irc_server 441 " + usernickMap[sockfd].get_nickname() + ' ' + receiveddata[3] + channelsMap[receiveddata[1]].get_original_channel_name() + " :They aren't on that channel\n");
            }
        }
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
                error(sockfd, "Error: Not enough parameters\n");
                return;
            }
            ss << receiveddata[3].substr(0,is_num(receiveddata[3]));
            ss >> limit;
            if (limit > 0)
            {
                    channelsMap[receiveddata[1]].set_limit(limit);
                    std::ostringstream oss;
                    oss << receiveddata[1] << ": limit has been set to " << limit << " users\n";
                    std::string msg = oss.str();
                    channelsMap[receiveddata[1]].broadcast(msg , -1);
            }
        }
    }
    else
        error(sockfd, "Error: Channel not found!\n");
}
