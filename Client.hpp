/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:43:37 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/17 13:58:18 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CLIENT_HPP
#define CLIENT_HPP
#include<iostream>
#include"Server.hpp"
#include"Channel.hpp"

class Server;
class Channel;

class Client
{
	private:
		std::vector<std::string> channelinvitedtoMap;
		int pwdconf;
		int is_reg;
		int is_invited;
		std::string username;
		std::string hostname;
		std::string servername;
		std::string realname;
		std::string nickname;
		std::time_t loginTimes;
		std::string holder;
	public:
		Client();
		~Client();

		void set_holder(std::string holder);
		std::string get_holder();

		
		void set_pwdconf(int pwdconf );
		void set_is_reg(int i);
		void set_is_invited(std::string channel_name);
		void set_username(std::string username);
		void set_hostname(std::string hostname);
		void set_servername(std::string servername);
		void set_realname(std::string realname);
		void set_nickname(std::string nickname);
		const int& get_pwdconf();
		const int& get_is_reg();
		const std::time_t& get_loginTimesg();
		int get_is_invited(std::string channel_name);
		const std::string& get_username();
		const std::string& get_hostname();
		const std::string& get_servername();
		const std::string& get_realname();
		const std::string& get_nickname();
};


#endif