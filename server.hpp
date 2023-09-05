/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:08:41 by sharrach          #+#    #+#             */
/*   Updated: 2023/09/05 17:37:43 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <string.h>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <sys/time.h>
#include <errno.h>
#include <sys/types.h>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/poll.h>
#include <sys/ioctl.h>
#include <map>
#include <algorithm>

#include <sstream>
#include <fcntl.h>
#include <vector>
// #include <bits/stdc++.h>
#include "Channel.hpp"
#include"Client.hpp"
#include"Tools.hpp"

class Client;

class Server{
	public:
		Server(int serverport, std::string pass);
		~Server();
		int check_authenticate(int sockfd, std::vector<std::string> tokens);
		int check_pass(std::vector<std::string> receiveddata, int sockfd);
		std::vector<std::string> parsdata(std::string receiveddata);
		void check_reg_and_cmds(std::vector<std::string> receiveddata, int sockfd);

		void user(std::vector<std::string> receiveddata, int sockfd);
		void nick(std::vector<std::string> receiveddata, int sockfd);
		void join(std::vector<std::string> receiveddata, int sockfd);
		void list(std::vector<std::string> receiveddata, int sockfd);
		void privmsg(std::vector<std::string> receiveddata, int sockfd);
		void kick(std::vector<std::string> receiveddata, int sockfd);
		void invite(std::vector<std::string> receiveddata, int sockfd);
		void topic(std::vector<std::string> receiveddata, int sockfd);
		void mode(std::vector<std::string> receiveddata, int sockfd);
		void part(std::vector<std::string> receiveddata, int sockfd);

		int is_valide_name(std::string channel_name, int sockfd);
		int is_valide_nickname(std::string &nickname, int sockfd);
		void exec_cmds(std::vector<std::string> receiveddata, int sockfd);
		int get_sockfd(std::string usernickname);
		int all_cmds(std::vector<std::string> receiveddata, int sockfd);

	private:
		std::map<int, Client> usernickMap;
		std::map<std::string, Channel> channelsMap;
		std::vector<std::string> receiveddata;
		int serverport;
		std::string password;
};
#endif