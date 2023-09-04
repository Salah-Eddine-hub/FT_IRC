#include "server.hpp"


Server::Server(int serverport, std::string password) {
    this->password = password;
    this->serverport = serverport;
    int rc, on = 1;
    int listen_sd = -1, new_sd = -1;
    int end_server = 0, compress_array = 0;
    int close_conn;
    // std::string buffer(512, '\0');
    struct sockaddr_in6 addr;
    int timeout;
    struct pollfd fds[200];
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

// --------------------------------------------------------------------------------------------------------------------
    rc = ioctl(listen_sd, FIONBIO, reinterpret_cast<char *>(&on));
    if (rc < 0) {
        perror("ioctl() failed");
        close(listen_sd);
        exit(-1);
    }

    // int flags = fcntl(listen_sd, F_GETFL, 0);
    // if (flags == -1) {
    //     perror("fcntl(F_GETFL) failed");
    //     close(listen_sd);
    //     exit(-1);
    // }

    // flags = O_NONBLOCK;
    // if (fcntl(listen_sd, F_SETFL, flags) == -1) {
    //     perror("fcntl(F_SETFL) failed");
    //     close(listen_sd);
    //     exit(-1);
    // }
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
        std::cout << "1\n";

        current_size = nfds;
        for (i = 0; i < current_size; i++) {
                std::cout << "2\n";
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
                    usernickMap[new_sd] = Client();

                    fds[nfds].fd = new_sd;
                    fds[nfds].events = POLLIN ;
                    nfds++;
                } while (new_sd != -1);
            } else {
                close_conn = 0;
                
                std::string holder;
                if (fds[i].revents & POLLIN) {
                    int found_delimiter = 0;

                    while (!found_delimiter) {
                        char recv_buffer[513];
                        rc = recv(fds[i].fd, recv_buffer, sizeof(recv_buffer), 0);
                        
                        std::cout << "rc: " << rc << std::endl;
                        std::cout << "recv_buffer: '" << recv_buffer << "'" << std::endl;

                        if (rc < 0) {
                            if (errno != EWOULDBLOCK) {
                                perror("recv() failed");
                                close_conn = 1;
                            }
                            break;
                        } else if (rc == 0) {
                            std::cout << "Connection closed" << std::endl;
                            close_conn = 1;
                            break;
                        } else {
                            recv_buffer[rc] = '\0';
                            holder.append(recv_buffer, rc);
                            bzero(recv_buffer, sizeof(recv_buffer));

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



//                 if (fds[i].revents & POLLIN) {
// // --------------------------------------------------------------------------------------------------------------------
//                     // memset(buffer.data(), 0, buffer.size());
//                     memset(const_cast<char*>(buffer.data()), 0, buffer.size());
//                     // rc = recv(fds[i].fd, buffer.data(), buffer.size(), 0);
//                     rc = recv(fds[i].fd, const_cast<char*>(buffer.data()), buffer.size(), 0);

// // --------------------------------------------------------------------------------------------------------------------
//                     if (rc < 0) {
//                         perror("recv() failed");
//                         close_conn = 1;
//                     } else if (rc == 0) {
//                         std::cout << "Connection closed" << std::endl;
//                         close_conn = 1;
//                     } 
// // --------------------------------------------------------------------------------------------------------------------
//                     else {
//                         std::string holder;niyuzAzMfXCVfM0JX3fH3TBgfprA3A8T5PnyTtANvDUeAKY3N9pamoOTnu09oqD2nzw6RMQIH8VDGd0I41Tw9FUopNB1BR1v7Hg1vsrKwkcLdodsSSv5oKSoD1dY10stmM2J0BkfMu9i99w88RQgtozRDhvxGvBg9MLEtpo23b3LeNnBzvowZNOx3OmuiyaVuYwDGMuRy9jJ1Ukuc0kA2k3KUT8PxCa3rbOyAbo1m5NXj8q5WC7DLTmyMAtVECBsRaOPlEwuPyuVwGSezzaS8RKWzpKiquLc7QVL00wqX1qlHMnLLamsDZsCIq4ASS4a4ZWZ41aaDpxDyGDkeZ6UmdqruT2n02bdZ7zoK1YXz5bPXYm8TCgmHzxUU3zMSNYfMg14m4eHngG7zNfGZ7y4Q18Di5wb9tH6zuPPvgpL8ueqzbWi575hgD0uPUsl1pBa9lLjD7EBoNcfnszRvMdgNvLv7cl4Fvzvibyd8AXo7aJgHN0nDAD7FxN9aLDdKod9WUHio8JRe3lAY5xl96zQUipWbcGs0hfhylfZA5YRde9764h8XdoXftCTyKQ1nrCiBmBy7ninxIQYwFV6EAwfm6r1mSLDO6l5L465oYUpQppmqAK8aMMcuCHTRhoiBm1DQMzchMRr9RMCV9WUpXrogVPDaShMKajPuOVGgGBGXOdVVVse9rLxVR3AEhZSkVEcb5ESrZS8b1KKROPiuEMFERDeQiATG9TIqqU3KBeAkdiQFJnBsihpgqV8eLrz7NjadOcKsQQ6wwSm8AzyOvzH7VV2lNTVho5pUwdENW756PbKcfkYOywRYsEUDIzfLkyHAA5Zr2PXUCNCfbU7pi0lVOd8Gv26igMHrheYejZxnToUkTStLPiys73e8mBvbKR0E4W6Z650KeaCmRvXRUlew1vxLYmqXtMu1vcgF0fvrjWTxDeUpIYSUM7anoxoQtUqgIO1sa0snQibiyXjRUK66i4QnxiYpoljWS7mrUvfzgD9l13jKurSXeUxn1BWBcgW
//                         std::string data(buffer.data(), rc);
//                         size_t pos = data.find_first_of("\r\n");
//                         std::cout << pos << "   " << data[pos - 1] << std::endl;
//                         while (pos != std::string::npos)
//                         len = rc;
//                         data.resize(data.size() - 1);
//                         data[data.size()] = '\0';
//                         this->receiveddata = parsdata(data);
//                         if (this->receiveddata.empty())
//                             std::cout << "wrong args\n";
//                         else
//                         check_reg_and_cmds(this->receiveddata, fds[i].fd);
//                     }
// // --------------------------------------------------------------------------------------------------------------------
//                 }
                
                if (fds[i].revents & POLLOUT) {
                std::cout << "a\n";
                    rc = send(fds[i].fd, holder.c_str(), holder.size(), 0);
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

int Server::get_sockfd(std::string usernickname){
    std::map<int, Client>::iterator it;
    for (it = usernickMap.begin(); it != usernickMap.end(); it++){
        if(it->second.get_nickname() == usernickname)
            return it->first;
    }
    return -1;    
}

Server::~Server() {
    std::cout << "this is destructor for our server" << std::endl;
}
