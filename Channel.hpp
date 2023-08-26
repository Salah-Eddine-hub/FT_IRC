/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:53:32 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/26 16:34:42 by iellyass         ###   ########.fr       */
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
        int is_member;
        int big_boss;
    public:
        Channel();
        Channel(std::string channel_name);
        ~Channel();

        void add_member_to_channel(int sockfd, const std::string& nickname, std::string channel_name);
        
		void error(int sockfd, const std::string& message);
		void success(int sockfd, const std::string& message);

        void broadcast(const std::string& message, int excludingSocket);
		void remove_the_user(int sockfd, std::string nickname);

        const std::string& get_channel_name();
        const int& get_big_boss();
        int get_is_member(int sockfd);
        void set_big_boss(int sockfd);
        void set_channel_topic(std::string sockfd);
        const std::string& get_channel_topic();
};

#endif