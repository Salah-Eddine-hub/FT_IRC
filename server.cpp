/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:09:18 by sharrach          #+#    #+#             */
/*   Updated: 2023/09/14 14:02:57 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

Server::Server(int serverport, std::string password) {

	if (password.empty() || password.find_first_not_of(' ') == std::string::npos){
		std::cerr << "No password detected" << std::endl;
		exit (-1);
	}
	this->password = password;
	this->serverport = serverport;
	on = 1;
	listen_sd = -1;
	new_sd = -1;
	end_server = 0;
	compress_array = 0;
	nfds = 1, 
	current_size = 0;

	listen_sd = socket(AF_INET6, SOCK_STREAM, 0);
	if (listen_sd < 0) {
		perror("socket() failed");
		exit(-1);
	}

	rc = setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char *>(&on), sizeof(on));
	if (rc < 0) {
		perror("setsockopt() failed");
		close(listen_sd);
		exit(-1);
	}

// --------------------------------------------------------------------------------------------------------------------

	int flags = fcntl(listen_sd, F_GETFL, 0);
	if (flags == -1) {
		perror("fcntl(F_GETFL) failed");
		close(listen_sd);
		exit(-1);
	}

	flags = O_NONBLOCK;
	if (fcntl(listen_sd, F_SETFL, flags) == -1) {
		perror("fcntl(F_SETFL) failed");
		close(listen_sd);
		exit(-1);
	}
// --------------------------------------------------------------------------------------------------------------------

	memset(&addr, 0, sizeof(addr));
	addr.sin6_family = AF_INET6;
	memcpy(&addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));
	addr.sin6_port = htons(serverport);
	rc = bind(listen_sd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr));
	if (rc < 0) {
		perror("bind() failed");
		close(listen_sd);
		exit(-1);
	}

	rc = listen(listen_sd, 32);
	if (rc < 0) {
		perror("listen() failed");
		close(listen_sd);
		exit(-1);
	}

	memset(fds, 0, sizeof(fds));

	fds[0].fd = listen_sd;
	fds[0].events = POLLIN;
	timeout = 30000 * 30000;
	while (end_server == 0)
	{
		rc = poll(fds, nfds, timeout);

		if (rc < 0) {
			perror("poll() failed");
			break;
		}

		if (rc == 0) {
			std::cout << "poll() timed out. End program." << std::endl;
			break;
		}
		else if (fds[0].revents == POLLIN)
		{
			std::cout << "newclient\n";
			new_sd = accept(listen_sd, NULL, NULL);
			if (new_sd < 0) {
				if (errno != EWOULDBLOCK) {
					perror("accept() failed");
					end_server = 1;
				}
				break;
			}
			usernickMap[new_sd] = Client();

			std::cout << nfds << "\n";
			fds[nfds].fd = new_sd;
			fds[nfds].events = POLLIN ;
			nfds++;
		}
		
		current_size = nfds;
		for (i = 1; i < current_size; i++) {
			if (fds[i].revents == 0)
				continue;
			new_sd = accept(listen_sd, NULL, NULL);
			if (fds[i].fd == listen_sd) {
			} 
			else {
				close_conn = 0;
				
				std::string holder;
				if (fds[i].revents & POLLIN) {
					int found_delimiter = 0;

					while (!found_delimiter) {
						char recv_buffer[513];
						bzero(recv_buffer, sizeof(recv_buffer));
						rc = recv(fds[i].fd, recv_buffer, sizeof(recv_buffer), 0);
						if (rc == -1) {
								perror("recv() failed");
								close_conn = 1;
							break;
						} 
						else if (rc == 0) {
							std::cout << "Connection closed" << std::endl;
							close_conn = 1;
							break;
						} 
						else {
							recv_buffer[rc] = '\0';
							holder.append(recv_buffer, rc);

							size_t pos = std::string::npos;
							if (holder.find("\r\n") != std::string::npos) {
								pos = holder.find("\r\n");
							}
							else if (holder.find("\n") != std::string::npos) {
								pos = holder.find("\n");
							}
							if (pos != std::string::npos) {
								found_delimiter = 1;
								std::string data = holder.substr(0, pos);
								this->receiveddata = parsdata(data);
								if (this->receiveddata.empty())
									std::cout << "wrong args\n";
								else
									check_reg_and_cmds(this->receiveddata, fds[i].fd);
							}
						}
					}
				}
				if (fds[i].revents & POLLOUT) {
					rc = send(fds[i].fd, holder.c_str(), holder.size(), 0);
					if (rc < 0) {
						perror("send() failed");
						close_conn = 1;
					}
				}

				if (close_conn) {
					usernickMap.erase(fds[i].fd);
					close(fds[i].fd);
					compress_array = 1;
				}
			}
		}

		if (compress_array) {
			compress_array = 0;
			for (i = 0; i < nfds; i++) {
				if (fds[i].fd == -1) {
					for (j = i; j < nfds; j++)
						fds[j].fd = fds[j + 1].fd;
					i--;
					nfds--;
				}
			}
		}
	}
	for (i = 0; i < nfds; i++) {
		if (fds[i].fd >= 0)
			close(fds[i].fd);
	}
}

int Server::get_sockfd(std::string usernickname){
	std::map<int, Client>::iterator it;
	for (it = usernickMap.begin(); it != usernickMap.end(); it++){
		if(it->second.get_nickname() == usernickname)
			return it->first;
	}
	return -1;    
}

std::map<std::string, std::string> Server::get_channel_and_key(const std::vector<std::string>& receiveddata) {
    std::map<std::string, std::string> channelAndkey;

    if (receiveddata.size() == 2) {
        std::istringstream schannel(receiveddata[1]);

        std::string channel;

        while (std::getline(schannel, channel, ','))
                channelAndkey[channel] = "";
    }
    else if (receiveddata.size() >= 3) {
        std::istringstream schannel(receiveddata[1]);
        std::istringstream skey(receiveddata[2]);

        std::string channel;
        std::string key;

        while (std::getline(schannel, channel, ',')) {
            if (std::getline(skey, key, ','))
                channelAndkey[channel] = key;
            else
                channelAndkey[channel] = "";
        }
    }
	return channelAndkey;
}

Server::~Server() {
	std::cout << "this is destructor for our server" << std::endl;
}
