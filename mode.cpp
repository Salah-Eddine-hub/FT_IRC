/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 12:46:30 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/30 19:22:32 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::mode(std::vector<std::string> receiveddata, int sockfd)
{

    if (receiveddata.size() < 3)
    {
        error(sockfd, "Error: not enough arguments!\n");
        return ;
    }   
    
    if(channelsMap.find(receiveddata[1]) != channelsMap.end()) {
        if(!channelsMap[receiveddata[1]].get_is_member(sockfd)){
            error(sockfd, "Error: You are not a member of the channel!\n");
            return ;
        }
        if (!channelsMap[receiveddata[1]].get_is_operator(sockfd)) {
            error(sockfd, "Error: You are not an OP in this channel!\n");
            return ;
        }
            if(receiveddata[2] == "+i") {
                channelsMap[receiveddata[1]].set_is_invite_only(1);
                channelsMap[receiveddata[1]].broadcast(receiveddata[1] + " sets to invites only!\n" , -1);
            }
            else if(receiveddata[2] == "-i") {
                channelsMap[receiveddata[1]].set_is_invite_only(0);
                channelsMap[receiveddata[1]].broadcast(receiveddata[1] + " is open for everyone to join!\n" , -1);
            }
            else if(receiveddata[2] == "+t") {
                channelsMap[receiveddata[1]].set_is_topic_restricted(1);
                channelsMap[receiveddata[1]].broadcast(receiveddata[1] + ": topic is restricted to only the channel's OPS!\n" , -1);
            }
            else if(receiveddata[2] == "-t") {
                channelsMap[receiveddata[1]].set_is_topic_restricted(0);
                channelsMap[receiveddata[1]].broadcast(receiveddata[1] + ": topic can be set by everyone!\n" , -1);
            }
            else if(receiveddata[2] == "-k") {
                if (receiveddata.size() > 3){
                    channelsMap[receiveddata[1]].set_is_pwd_needed("");
                    channelsMap[receiveddata[1]].broadcast(receiveddata[1] + ": Users can join the channel without providing any password!\n" , -1);
                }
            }
            else if(receiveddata[2] == "-l") {
                channelsMap[receiveddata[1]].set_limit(0);
                channelsMap[receiveddata[1]].broadcast(receiveddata[1] + ": No user limit has been set to this channel!\n" , -1);
            }
            else if(receiveddata[2] == "+o") {
                if (channelsMap[receiveddata[1]].get_is_member(sockfd)){
                    channelsMap[receiveddata[1]].set_is_operator(get_sockfd(receiveddata[3]));
                    channelsMap[receiveddata[1]].broadcast(receiveddata[3] + " is now an operator in this channel!\n" , -1);
                }
                else
                    error(sockfd, receiveddata[3] + " is not a member to this channel!\n");
            }
            else if(receiveddata[2] == "-o") {
                if (channelsMap[receiveddata[1]].get_is_member(sockfd)){
                    channelsMap[receiveddata[1]].remove_the_operator(get_sockfd(receiveddata[3]));
                    channelsMap[receiveddata[1]].broadcast(receiveddata[3] + " is not an operator in this channel anymore!\n" , -1);
                }
                else
                    error(sockfd, receiveddata[3] + " is not a member to this channel!\n");
            }
            if(receiveddata[2] == "+k" && receiveddata.size() > 3) {
                if(receiveddata[3].size() > 23)
                    receiveddata[3].resize(23);
                channelsMap[receiveddata[1]].set_is_pwd_needed(receiveddata[3]);
                channelsMap[receiveddata[1]].broadcast(receiveddata[1] + ": Users need to provide the correct password to join the channel!\n", -1);
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
