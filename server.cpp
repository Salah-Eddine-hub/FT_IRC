/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:26:20 by sharrach          #+#    #+#             */
/*   Updated: 2023/08/20 15:02:45 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

Server::Server(int serverport, std::string password): serverport(serverport) {
    int on = 1;
    int listen_sd = -1, new_sd = -1;
    int end_server = 0, compress_array = 0;
    std::string buffer(1024, '\0');
    int nfds = 1, current_size = 0, i, j;

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

    rc = ioctl(listen_sd, FIONBIO, reinterpret_cast<char *>(&on));
    if (rc < 0) {
        perror("ioctl() failed");
        close(listen_sd);
        exit(-1);
    }

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
    timeout = (30000);

    do {
        std::cout << "Waiting on poll()..." << std::endl;
        rc = poll(fds, nfds, timeout);

        if (rc < 0) {
            perror("poll() failed");
            break;
        }

        if (rc == 0) {
            std::cout << "poll() timed out. End program." << std::endl;
            break;
        }

        current_size = nfds;
        for (i = 0; i < current_size; i++) {
            if (fds[i].revents == 0)
                continue;

            if (fds[i].revents != POLLIN) {
                std::cout << "Error! revents = " << fds[i].revents << std::endl;
                end_server = 1;
                break;
            }

            if (fds[i].fd == listen_sd) {
                do {
                    new_sd = accept(listen_sd, NULL, NULL);
                    if (new_sd < 0) {
                        if (errno != EWOULDBLOCK) {
                            perror("accept() failed");
                            end_server = 1;
                        }
                        break;
                    }
                    // Client newClient;
                    usernickMap[new_sd] = Client();

                    fds[nfds].fd = new_sd;
                    fds[nfds].events = POLLIN ;
                    nfds++;
                } while (new_sd != -1);
            } else {
                close_conn = 0;
                
                if (fds[i].revents & POLLIN) {
                    memset(buffer.data(), 0, buffer.size());
                    rc = recv(fds[i].fd, buffer.data(), buffer.size(), 0);
                    if (rc < 0) {
                        perror("recv() failed");
                        close_conn = 1;
                    } else if (rc == 0) {
                        std::cout << "Connection closed" << std::endl;
                        close_conn = 1;
                    } 
// --------------------------------------------------------------------------------------------------------------------
                    else {
                        // usernickMap[fds[i].fd] = Client();
                        // Client newClient;
                        // usernickMap[fds[i].fd] = newClient;

                        len = rc;
                        std::string data(buffer.data(), rc);
                        this->receiveddata = parsdata(data);
                        check_reg_and_cmds(this->receiveddata, password, fds[i].fd);
                    }
// --------------------------------------------------------------------------------------------------------------------
                }
                
                if (fds[i].revents & POLLOUT) {
                    rc = send(fds[i].fd, buffer.c_str(), len, 0);
                    if (rc < 0) {
                        perror("send() failed");
                        close_conn = 1;
                    }
                }

                if (close_conn) {
                    close(fds[i].fd);
                    fds[i].fd = -1;
                    compress_array = 1;
                }
            }
        }

        if (compress_array) {
            compress_array = 0;
            for (i = 0; i < nfds; i++) {
                if (fds[i].fd == -1) {
                    for (j = i; j < nfds; j++) {
                        fds[j].fd = fds[j + 1].fd;
                    }
                    i--;
                    nfds--;
                }
            }
        }
    } while (end_server == 0);

    for (i = 0; i < nfds; i++) {
        if (fds[i].fd >= 0)
            close(fds[i].fd);
    }
}


Server::~Server() {
    std::cout << "this is destructor for our server" << std::endl;
}

