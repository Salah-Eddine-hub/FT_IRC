/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:55:14 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/26 14:03:14 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

Channel::Channel() {}

Channel::Channel(std::string channel_name) {
    this->channel_name = channel_name;
    this->is_member = 0;
    this->big_boss = 0;
}


void Channel::broadcast(const std::string& message, int excludingsockfd) {
    for (size_t i = 0; i < this->membersMap.size(); ++i)
        if (this->membersMap[i] != excludingsockfd)
            success(this->membersMap[i], message);
}

void Channel::add_member_to_channel(int sockfd, const std::string& nickname, std::string channel_name){
    std::vector<int>::iterator it = std::find(this->membersMap.begin(), this->membersMap.end(), sockfd);

    if(it != this->membersMap.end())
        error(sockfd, "You are already a member of this channel!\n");
    else{
        std::string msg = nickname + " just joind the channel!\n";
        broadcast(msg, sockfd);
        msg = "You joind the channel " + channel_name + '\n';
        success(sockfd, msg);
        this->membersMap.push_back(sockfd);
    }
    return ;
}

const std::string& Channel::get_channel_name(){
    return (this->channel_name);
}

void Channel::set_big_boss(int sockfd){
    this->big_boss = sockfd;
}

const int& Channel::get_big_boss(){
    return (this->big_boss);
}

int Channel::get_is_member(int sockfd) {
    std::vector<int>::iterator it = std::find(this->membersMap.begin(), this->membersMap.end(), sockfd);
    if(it != this->membersMap.end())
        return 1;
    return 0;
}

void Channel::remove_the_user(int sockfd, std::string nickname)
{
    std::vector<int>::iterator it = std::find(membersMap.begin(), membersMap.end(), sockfd);
    
    if(it != membersMap.end()){
        membersMap.erase(it);
        success(sockfd, "You have been kicked from the channel:" + get_channel_name() + "!\n");
        broadcast(nickname + " got kicked from the channel!\n", sockfd);
    }
}

Channel::~Channel() {}
