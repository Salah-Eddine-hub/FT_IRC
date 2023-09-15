/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:08:41 by sharrach          #+#    #+#             */
/*   Updated: 2023/09/15 11:39:49 by iellyass         ###   ########.fr       */
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
#include "Channel.hpp"
#include"Client.hpp"
#include"Tools.hpp"


#include <arpa/inet.h>

class Client;

class Server {
	public:
		Server(int serverport, std::string pass);
		~Server();
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
		void user_registered(int sockfd);
		void part(std::vector<std::string> receiveddata, int sockfd);

		int is_valide_name(std::string channel_name);
		int is_valide_nickname(std::string &nickname, int sockfd);
		int is_valide_username(std::string nickname);
		void exec_cmds(std::vector<std::string> receiveddata, int sockfd);
		int get_sockfd(std::string usernickname);
		std::map<std::string, std::string> get_channel_and_key(const std::vector<std::string>& receiveddata);

		void DisplayTime(const std::string username, int sockfd);

		std::string ClientIp(int client);
	
	private:
		std::map<int, Client> usernickMap;
		std::map<std::string, Channel> channelsMap;
		std::map<std::string, std::time_t> loginTimes;
		std::vector<std::string> receiveddata;
		int serverport;
		std::string password;
		struct sockaddr_in addr;
		struct pollfd fds[200];
		int rc;
		int on;
		int listen_sd;
		int new_sd;
		int end_server;
		int compress_array;
		int close_conn;
		int timeout;
		int nfds;
		int current_size;
		int j;
		int i;

};
#endif