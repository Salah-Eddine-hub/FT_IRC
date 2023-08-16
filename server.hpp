/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:08:41 by sharrach          #+#    #+#             */
/*   Updated: 2023/08/15 18:05:45 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <sys/time.h>
#include <errno.h>
// ishould know about this headers
#include <sys/types.h>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/poll.h>
#include <sys/ioctl.h>
#include <map>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>

class Server{
public:
	Server(int serverport, std::string pass);
	~Server();
	int check_authenticate(int sockfd, std::string buffer);
	int user_cmd(int sockfd, std::vector<std::string> tokens);
	int nick_cmd(int sockfd, std::vector<std::string> tokens);
	int check_pass(std::string receiveddata, std::string password);
private:
	std::map<int, std::pair<std::string, std::string> > usernameMap;
    int serverport;
	int password;
    int is_reg;
	std::string username;
	std::string hostname;
	std::string servername;
	std::string realname;
	std::string nickname;
};
#endif