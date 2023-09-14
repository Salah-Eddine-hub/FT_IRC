/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:55:14 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/14 15:53:55 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

Channel::Channel() {}

Channel::Channel(std::string channel_name) {
    this->original_channel_name = channel_name;
    this->channel_name = strtolower(channel_name);
    this->is_invite_only = 0;
    this->is_topic_restricted = 0;
    this->is_pwd_needed = "";
    this->limit = 0;
    this->curr_users = 0;
    this->is_operator = 0;
}


Channel::~Channel() {}


// ---------------------------------------------------------------

const std::string& Channel::get_channel_name(){
    return (this->channel_name);
}

const std::string& Channel::get_original_channel_name(){
    return (this->original_channel_name);
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

int Channel::get_is_operator(int sockfd){
    std::vector<int>::iterator it = std::find(this->opsMap.begin(), this->opsMap.end(), sockfd);

    if(it != this->opsMap.end())
        return 1;
    return 0;
}
// --------------------------------------------------------------------------------------------------

void Channel::set_is_operator(int is_op) {
    std::vector<int>::iterator it = std::find(this->opsMap.begin(), this->opsMap.end(), is_op);

    if(it == this->opsMap.end())
        this->opsMap.push_back(is_op);
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

void Channel::remove_the_user(int sockfd, std::string channel_name, std::string nickname, std::string op)
{
    std::vector<int>::iterator it = std::find(membersMap.begin(), membersMap.end(), sockfd);
    
    if(it != membersMap.end()){
        broadcast(':' + op + "!localhost KICK " + channel_name + ' ' + nickname + " :" + op + "\n", -1);
        membersMap.erase(it);
        this->dec_current_users();
    }
}

void Channel::leave_the_channel(int sockfd, std::string nickname, std::string chnnelname)
{
    std::vector<int>::iterator it = std::find(membersMap.begin(), membersMap.end(), sockfd);
    
    if(it != membersMap.end()){
        broadcast(':' + nickname + "!irc_server PART " + chnnelname + "\n", -1);
        membersMap.erase(it);
        this->dec_current_users();
    }
    else
        inv_mssg(sockfd, ":irc_server 442 " + nickname + ' ' + chnnelname + " :You're not on that channel\n");
}

void Channel::remove_the_operator(int sockfd)
{
    std::vector<int>::iterator it = std::find(opsMap.begin(), opsMap.end(), sockfd);
    
    if(it != opsMap.end()){
        opsMap.erase(it);
    }
}

void Channel::broadcast(const std::string& message, int excludingsockfd) {
    for (size_t i = 0; i < this->membersMap.size(); ++i) {
        if(excludingsockfd == -1)
            inv_mssg(this->membersMap[i], message);
        else if (this->membersMap[i] != excludingsockfd)
            inv_mssg(this->membersMap[i], message);
        }
}

void Channel::add_member_to_channel(int sockfd, const std::string& nickname, std::string channel_name, std::map<int, Client>& usernickMap){

    std::vector<int>::iterator it = std::find(this->membersMap.begin(), this->membersMap.end(), sockfd);
    if(it != this->membersMap.end())
        return ;
    else if(this->get_limit() > 0 && (this->get_limit() <= this->get_current_users()))
        inv_mssg(sockfd, ":irc_server 471 " + usernickMap[sockfd].get_nickname() + ' ' + this->get_original_channel_name() + " :Cannot join channel (+l)\n");
    else{

        this->membersMap.push_back(sockfd);
        std::string users;
        for (size_t i = membersMap.size() - 1;  i > 0; i--)
        {
            users += usernickMap[membersMap[i]].get_nickname() + " ";
        }
        
        inv_mssg(sockfd, ':' + nickname + "!localhost JOIN :" + channel_name + "\n");
        inv_mssg(sockfd, ":irc_server 353 " + nickname + " = " + this->get_original_channel_name() + " :" + users + '@' + usernickMap[membersMap[0]].get_nickname() + "\n");
        inv_mssg(sockfd, ":irc_server 366 " + nickname + ' ' + channel_name + " :End of /NAMES list.\n");
        std::string msg = ':' + nickname + "!localhost JOIN :" + channel_name + '\n';
        broadcast(msg, sockfd);
        this->inc_current_users();
    }
    return ;
}