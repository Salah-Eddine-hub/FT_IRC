/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:53:32 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/17 13:58:18 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include <iostream>
#include "Server.hpp"
#include "Client.hpp"

class Client;
class Channel
{
	private:
		std::vector<int> membersMap;
		std::vector<int> opsMap;
		std::string channel_name;
		std::string original_channel_name;
		std::string channel_topic;
		std::string is_pwd_needed;
		int is_topic_restricted;
		int is_invite_only;
		int limit;
		int curr_users;
		int is_operator;
	public:
		Channel();
		Channel(std::string channel_name);
		~Channel();

		void add_member_to_channel(int sockfd, const std::string& nickname, std::string channel_name, std::map<int, Client>& usernickMap, std::string clientip, std::string localhost);

		void broadcast(const std::string& message, int excludingSocket);
		void remove_the_user(int sockfd, std::string channel_name, std::string nickname, std::string op, std::string reason, std::string username, std::string clientip);
		void leave_the_channel(int sockfd, std::string nickname, std::string chnnelname, std::string username, std::string localhost);
		void leave_the_server(int sockfd);
		void remove_the_operator(int sockfd);

		const std::string& get_channel_topic();
		const std::string& get_channel_name();
		const std::string& get_original_channel_name();
		int get_is_member(int sockfd);
		int get_is_invite_only();
		int get_is_topic_restricted();
		std::string get_is_pwd_needed();
		int get_limit();
		int get_current_users();
		int get_is_operator(int sockfd);

		void set_channel_topic(std::string sockfd);
		void set_is_invite_only(int is_invite_only);
		void set_is_topic_restricted(int is_topic_restricted);
		void set_is_pwd_needed(std::string is_pwd_needed);
		void set_limit(int limit);
		void inc_current_users();
		void dec_current_users();
		void set_is_operator(int mode);
};

#endif