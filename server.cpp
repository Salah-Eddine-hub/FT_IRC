/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:08:22 by sharrach          #+#    #+#             */
/*   Updated: 2023/07/03 14:08:38 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

Server::Server() {
    std::cout << "this is constructor for our server" << std::endl;
//    int sockfd = socket(domain, type, protocol);
//------------------------------------------------------------------------------------------------------------
int on = 1;
int listen_sd = -1;
listen_sd = socket(AF_INET6, SOCK_STREAM, 0);
if (listen_sd < 0){
    perror("Socket() failed");
    exit(-1);
}
//------------------------------------------------------------------------------------------------------------
int rc = setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
if (rc < 0){
    perror("setsockopt() faild");
    close (listen_sd);
    exit (-1);
}
//------------------------------------------------------------------------------------------------------------
rc = ioctl(listen_sd, FIONBIO, (char *)&on);
if (rc < 0){
    perror("iocltl() faild");
    close (listen_sd);
    exit (-1);
}
//------------------------------------------------------------------------------------------------------------
struct sockaddr_in6 addr;
memset(&addr, 0, sizeof(addr));
addr.sin6_family = AF_INET6;
memcpy(&addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));
addr.sin6_port = htons(serverport); // here put the port of the server that is in the requirement to handle it
rc = bind(listen_sd, (struct sockaddr *)&addr, sizeof(addr));
if (rc < 0){
    perror("bind() failed");
    close(listen_sd);
    exit (-1);
}
//------------------------------------------------------------------------------------------------------------
rc = listen(listen_sd, 32);
if (rc < 0){
    perror("listen() failed");
    close(listen_sd);
    exit(-1);
}
//------------------------------------------------------------------------------------------------------------
struct pollfd fds[200];
memset(fds, 0, sizeof(fds));
//------------------------------------------------------------------------------------------------------------
fds[0].fd = listen_sd;
fds[0].events = POLLIN;
//------------------------------------------------------------------------------------------------------------
int timeout;
timeout = (3 * 60 * 1000);
//------------------------------------------------------------------------------------------------------------
int nfds = 1;
int current_size = nfds;
int end_server = false;
int new_sd = -1;
int close_conn;
int len;
char buffer[80];
int compress_array = false;
do {
        std::cout << "Waiting on poll().." << std::endl;
        rc = poll(fds, nfds, timeout);
        if (rc < 0){
            perror("poll() failed");
            break;
        }
        if (rc == 0){
            std::cout << "poll() timeout. End programe hh" << std::endl;
            break;
        }
        for(int i = 0; i < current_size; i++){
            if(fds[i].revents == 0)
                    continue;
            if (fds[i].revents != POLLIN){
                std::cout << "Error! revents = " << fds[i].revents;
                end_server = true;
                break;
            }
            if (fds[i].fd == listen_sd){
                std::cout << "listening socket is readable" << std::endl;
                do {
                    new_sd = accept(listen_sd, NULL, NULL);
                    if (new_sd < 0){
                        if (errno != EWOULDBLOCK){
                            perror("accept() failed");
                            end_server = true;
                        }
                        break;
                    }
                    std::cout << "Neww incoming connection " << new_sd;
                    fds[nfds].fd = new_sd;
                    fds[nfds].events = POLLIN;
                    nfds++;
                }
                while(new_sd != -1)
                    ;
            }
            else{
                std::cout << "Descriptor" << fds[i].fd << "is readable" << std::endl;
                close_conn = false;
                do{
                    rc = recv(fds[i].fd, buffer, sizeof(buffer), 0);
                    if (rc < 0){
                        if (errno != EWOULDBLOCK){
                            perror("rec() failed");
                            close_conn = true;
                        }
                        break;
                    }
                    if (rc == 0){
                        std::cout << "connection closed" << std::endl;
                        close_conn = true;
                        break;
                    }
                    len = rc;
                    std::cout << len << "bytes received" << std::endl;
                    rc = send(fds[i].fd, buffer, len, 0);
                    if (rc < 0){
                        perror("send() failed");
                        close_conn = true;
                        break;
                    }
                }
                while(true)
                    ;
                if (close_conn){
                    close(fds[i].fd);
                    fds[i].fd = -1;
                    compress_array = true;
                }
            }
        }
        if (compress_array){
            compress_array = false;
            for(int i = 0; i < nfds; i++){
                if (fds[i].fd == -1){
                    for(int j = i; j < nfds; j++){
                        fds[j].fd = fds[j +1].fd;
                    }
                    i--;
                    nfds--;
                }
            }
        }
    }
    while(end_server == false)
        ;
    for(int i = 0; i < nfds; i++){
        if(fds[i].fd >= 0)
            close(fds[i].fd);
    }
}


Server::~Server() {
    std::cout << "this is destructor for our server" << std::endl;
}