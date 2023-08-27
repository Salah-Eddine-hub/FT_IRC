/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:55:14 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/27 20:56:11 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

Channel::Channel() {
    this->big_boss = 0;
    this->is_invite_only = 0;
    this->is_topic_restricted = 0;
    this->is_pwd_needed = "";
    this->limit = 0;
    this->curr_users = 0;
}

Channel::Channel(std::string channel_name) {
    this->channel_name = channel_name;
    this->big_boss = 0;
    this->is_invite_only = 0;
    this->is_topic_restricted = 0;
    this->is_pwd_needed = "";
    this->limit = 0;
    this->curr_users = 0;
}


Channel::~Channel() {}


// ---------------------------------------------------------------

const std::string& Channel::get_channel_name(){
    return (this->channel_name);
}

int Channel::get_big_boss(){
    return (this->big_boss);
}

const std::string& Channel::get_channel_topic(){
    return (this->channel_topic);
}

int Channel::get_is_invite_only(){
    return (this->is_invite_only);
}

int Channel::get_is_member(int sockfd) {
    std::vector<int>::iterator it = std::find(this->membersMap.begin(), this->membersMap.end(), sockfd);
    if(it != this->membersMap.end())
        return 1;
    return 0;
}

int Channel::get_is_topic_restricted(){
    return(this->is_topic_restricted);
}

std::string Channel::get_is_pwd_needed(){
    return(this->is_pwd_needed);
}

int Channel::get_limit(){
    return(this->limit);
}

int Channel::get_current_users(){
    return(this->curr_users);
}
// --------------------------------------------------------------------------------------------------

void Channel::set_big_boss(int sockfd){
    this->big_boss = sockfd;
}

void Channel::set_channel_topic(std::string channel_topic){
    this->channel_topic = channel_topic;
}

void Channel::set_is_invite_only(int is_invite_only){
    this->is_invite_only = is_invite_only;
}

void Channel::set_is_topic_restricted(int is_topic_restricted){
    this->is_topic_restricted = is_topic_restricted;
}

void Channel::set_is_pwd_needed(std::string is_pwd_needed){
    this->is_pwd_needed = is_pwd_needed;
}

void Channel::set_limit(int limit){
    this->limit = limit;
}

// --------------------------------------------------------------------------------------------------

void Channel::inc_current_users(){
    this->curr_users++;
}

void Channel::dec_current_users(){
    this->curr_users--;
}

// ---------------------------------------------------------------

void Channel::remove_the_user(int sockfd, std::string nickname)
{
    std::vector<int>::iterator it = std::find(membersMap.begin(), membersMap.end(), sockfd);
    
    if(it != membersMap.end()){
        membersMap.erase(it);
        success(sockfd, "You have been kicked from the channel:" + get_channel_name() + "!\n");
        broadcast(nickname + " got kicked from the channel!\n", sockfd);
        this->dec_current_users();
    }
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
    else if(this->get_limit() > 0 && (this->get_limit() <= this->get_current_users()))
        error(sockfd, "Error: user limit for the channel has been reached!\n");
    else{
        std::string msg = nickname + " just joind the channel!\n";
        broadcast(msg, sockfd);
        msg = "You joind the channel " + channel_name + '\n';
        success(sockfd, msg);
        this->membersMap.push_back(sockfd);
        this->inc_current_users();
    }
    return ;
}
