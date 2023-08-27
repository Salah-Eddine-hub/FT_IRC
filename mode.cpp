/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 12:46:30 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/27 20:50:30 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

void Server::mode(std::vector<std::string> receiveddata, int sockfd)
{

    if(channelsMap.find(receiveddata[1]) != channelsMap.end()) {
        if(!channelsMap[receiveddata[1]].get_is_member(sockfd)){
            error(sockfd, "Error: You are not a member of the channel!\n");
            return ;
        }
        if (channelsMap[receiveddata[1]].get_big_boss() != sockfd) {
            error(sockfd, "Error: You are not an OP in this channel!\n");
            return ;
        }
        if (receiveddata.size() == 3) {
            if(receiveddata[2] == "+i") {
                channelsMap[receiveddata[1]].set_is_invite_only(1);
                success(sockfd, receiveddata[1] + " sets to invites only!\n");
            }
            else if(receiveddata[2] == "-i") {
                channelsMap[receiveddata[1]].set_is_invite_only(0);
                success(sockfd, receiveddata[1] + " is open for everyone to join!\n");
            }
            else if(receiveddata[2] == "+t") {
                channelsMap[receiveddata[1]].set_is_topic_restricted(1);
                success(sockfd, receiveddata[1] + ": topic is restricted to only the channel's OPS!\n");
            }
            else if(receiveddata[2] == "-t") {
                channelsMap[receiveddata[1]].set_is_topic_restricted(0);
                success(sockfd, receiveddata[1] + ": topic can be set by everyone!\n");
            }
            else if(receiveddata[2] == "-k") {
                channelsMap[receiveddata[1]].set_is_pwd_needed("");
                success(sockfd, receiveddata[1] + ": Users can join the channel without providing any password!\n");
            }
            else if(receiveddata[2] == "-l") {
                channelsMap[receiveddata[1]].set_limit(0);
                success(sockfd, receiveddata[1] + ": No user limit has been set to this channel!\n");
            }
        }

        if (receiveddata.size() >= 4) {
            if(receiveddata[2] == "+k") {
                std::string pwd;
                for (size_t i = 3; i < receiveddata.size(); i++){
                    size_t firstnonspace = receiveddata[i].find_first_not_of(" ");
                        if (firstnonspace != std::string::npos)
                            receiveddata[i] = receiveddata[i].substr(firstnonspace);
                    pwd += receiveddata[i] + ' ';
                }
                pwd.resize(pwd.size() - 1);
                channelsMap[receiveddata[1]].set_is_pwd_needed(pwd);
                success(sockfd, receiveddata[1] + ": Users need to provide the correct password to join the channel!\n");
            }
            else if(receiveddata[2] == "+l" && receiveddata.size() == 4) {
                std::stringstream ss;
                int limit;
                
                if(receiveddata[3].empty()){
                    error(sockfd, "Error: limit must be numuric only!\n");
                    return ;
                }
                if(!is_num(receiveddata[3])){
                    error(sockfd, "Error: limit must be numuric only!\n");
                    return ;
                }
                ss << receiveddata[3];
                ss >> limit;
                if (limit < 1)
                    error(sockfd, "Error: limit can't be set below 1\n");
                else{
                    std::cout << channelsMap[receiveddata[1]].get_current_users() << std::endl;
                    if (channelsMap[receiveddata[1]].get_current_users() > limit)
                        error(sockfd, "Error: limit can't be set below the cuurect users!\n");
                    else
                        channelsMap[receiveddata[1]].set_limit(limit);
                }
            }
            else 
                error(sockfd, "Error: wrong arguments!\n");
        }
        else 
            error(sockfd, "Error: wrong arguments!\n");
    }
    else
        error(sockfd, "Error: Channel not found!\n");
}

    // if (receiveddata.size() == 3) {
    // if (receiveddata.size() == 3) {
    //     if(channelsMap.find(receiveddata[1]) != channelsMap.end())
    //     {
    //         if(!channelsMap[receiveddata[1]].get_is_member(sockfd))
    //             error(sockfd, "Error: You are not a member of the channel!\n");
    //         else if (channelsMap[receiveddata[1]].get_big_boss() != sockfd)
    //             error(sockfd, "Error: You are not an OP in this channel!\n");
    //         else{
    //             if(receiveddata[2] == "+i") {
    //                 channelsMap[receiveddata[1]].set_is_invite_only(1);
    //                 success(sockfd, receiveddata[1] + " sets to invites only!\n");
    //             }
    //             else if(receiveddata[2] == "-i") {
    //                 channelsMap[receiveddata[1]].set_is_invite_only(0);
    //                 success(sockfd, receiveddata[1] + " is open for everyone to join!\n");
    //             }
    //             else if(receiveddata[2] == "+t") {
    //                 channelsMap[receiveddata[1]].set_is_topic_restricted(1);
    //                 success(sockfd, receiveddata[1] + ": topic is restricted to only the channel's OPS!\n");
    //             }
    //             else if(receiveddata[2] == "-t") {
    //                 channelsMap[receiveddata[1]].set_is_topic_restricted(0);
    //                 success(sockfd, receiveddata[1] + ": topic can be set by everyone!\n");
    //             }
    //             else if(receiveddata[2] == "-k") {
    //                 channelsMap[receiveddata[1]].set_is_pwd_needed("");
    //                 success(sockfd, receiveddata[1] + ": Users can join the channel without providing any password!\n");
    //             }
    //             else if(receiveddata[2] == "-l") {
    //                 channelsMap[receiveddata[1]].set_limit(-1);
    //                 success(sockfd, receiveddata[1] + ": No user limit has been set to this channel!\n");
    //             }
    //         }
    //     }
    //     else
    //         error(sockfd, "Error: Channel not found!\n");
    // }
    // else if (receiveddata.size() >= 4) {
    //     std::string pwd;
    //     for (size_t i = 3; i < receiveddata.size(); i++){
    //         size_t firstnonspace = receiveddata[i].find_first_not_of(" ");
    //             if (firstnonspace != std::string::npos)
    //                 receiveddata[i] = receiveddata[i].substr(firstnonspace);
    //         pwd += receiveddata[i] + ' ';
    //     }
    //     pwd.resize(pwd.size() - 1);
    //     if(channelsMap.find(receiveddata[1]) != channelsMap.end())
    //     {
    //         if(!channelsMap[receiveddata[1]].get_is_member(sockfd))
    //             error(sockfd, "Error: You are not a member of the channel!\n");
    //         else if (channelsMap[receiveddata[1]].get_big_boss() != sockfd)
    //             error(sockfd, "Error: You are not an OP in this channel!\n");
    //         else{
    //             if(receiveddata[2] == "+k") {
    //                 channelsMap[receiveddata[1]].set_is_pwd_needed(pwd);
    //                 success(sockfd, receiveddata[1] + ": Users need to provide the correct password to join the channel!\n");
    //             }
    //         }
    //     }
    //     else
    //         error(sockfd, "Error: Channel not found!\n");
    // }


