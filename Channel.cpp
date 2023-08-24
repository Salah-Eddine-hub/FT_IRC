/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:55:14 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/24 20:35:38 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

Channel::Channel() {}

Channel::Channel(std::string channel_name) {
    this->channel_name = channel_name;
    this->is_member;
    
}


void Channel::broadcast(const std::string& message, int excludingsockfd) {
    for (size_t i = 0; i < this->members.size(); ++i)
        if (this->members[i] != excludingsockfd)
            success(this->members[i], message);
}

void Channel::add_member_to_channel(int sockfd, const std::string& nickname, std::string channel_name){
    std::vector<int>::iterator it = std::find(this->members.begin(), this->members.end(), sockfd);

    if(it != this->members.end())
        error(sockfd, "and you are already a member of this channel!\n");
    else{
        std::string msg = nickname + " just joind the channel!\n";
        broadcast(msg, sockfd);
        msg = "You joind the channel " + channel_name + '\n';
        success(sockfd, msg);
        this->members.push_back(sockfd);
    }
    return ;
}


// void Channel::add_member_to_channel(int sockfd, const std::string& nickname, std::string channel_name){

//     if()
//         error(sockfd, "and you are already a member of this channel!\n");
//     else{
//         std::string msg = nickname + " just joind the channel!\n";
//         broadcast(msg, sockfd);
//         msg = "You joind the channel " + channel_name + '\n';
//         success(sockfd, msg);
//         this->members.push_back(sockfd);
//     }
//     return ;
// }

const std::string& Channel::get_channel_name(){
    return (this->channel_name);
}

const int& Channel::get_is_member() {
    return (is_member);
}

const int& Channel::set_is_member(int is_member) {
    this->is_member = is_member;
}

Channel::~Channel() {}
