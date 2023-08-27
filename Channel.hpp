/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:53:32 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/27 16:57:14 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include<iostream>
// #include"server.hpp"

// class Server;

class Channel
{
    private:
		std::vector<int> membersMap;
        std::string channel_name;
        std::string channel_topic;
        std::string is_pwd_needed;
        int is_topic_restricted;
        int is_invite_only;
        int big_boss;
        int limit;
        int curr_users;
    public:
        Channel();
        Channel(std::string channel_name);
        ~Channel();

        void add_member_to_channel(int sockfd, const std::string& nickname, std::string channel_name);
        
		void error(int sockfd, const std::string& message);
		void success(int sockfd, const std::string& message);

        void broadcast(const std::string& message, int excludingSocket);
		void remove_the_user(int sockfd, std::string nickname);

        const std::string& get_channel_topic();
        const std::string& get_channel_name();
        int get_is_member(int sockfd);
        int get_big_boss();
        int get_is_invite_only();
        int get_is_topic_restricted();
        std::string get_is_pwd_needed();
        int get_limit();
        int get_current_users();
        
        void set_channel_topic(std::string sockfd);
        void set_big_boss(int sockfd);
        void set_is_invite_only(int is_invite_only);
        void set_is_topic_restricted(int is_topic_restricted);
        void set_is_pwd_needed(std::string is_pwd_needed);
        void set_limit(int limit);
        void inc_current_users();
        void dec_current_users();
};

#endif