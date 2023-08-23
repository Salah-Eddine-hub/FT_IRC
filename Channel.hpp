/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:53:32 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/21 20:54:36 by iellyass         ###   ########.fr       */
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
		std::vector<int> members;
        std::string channel_name;
        std::string channel_topic;
    public:
        Channel();
        Channel(std::string channel_name);
        ~Channel();

        void add_member_to_channel(int sockfd, const std::string& nickname, std::string channel_name);
        
		void error(int sockfd, const std::string& message);
		void success(int sockfd, const std::string& message);

        void broadcast(const std::string& message, int excludingSocket);

        const std::string& get_channel_name();
};

#endif