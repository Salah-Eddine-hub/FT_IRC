#include "server.hpp"

// int Server::check_authenticate(int sockfd, std::string buffer)
// {
//     std::vector<std::string> tokens;
//     std::istringstream iss(buffer);
//     std::string holder;

//     std::map<int, std::string>::iterator it = this->usernameMap.find(sockfd);
//     std::cout << "sockfd: " << sockfd << std::endl;
//     if (it == usernameMap.end()) {
//         // while (getline(iss, holder, ' ')) {
//         //     tokens.push_back(holder);
//         // }
//         // while (getline(iss, holder, ' ')) {
//         //     size_t firstNonSpace = holder.find_first_not_of(" \t\n\r");
//         //     size_t lastNonSpace = holder.find_last_not_of(" \t\n\r");
            
//         //     if (firstNonSpace != std::string::npos) {
//         //         holder = holder.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
//         //         tokens.push_back(holder);
//         //     }
//         // }
//         while (std::getline(iss, holder, ' ')) {
//             if (!holder.empty()) {
//                 if (holder.back() == '\n')
//                     holder.pop_back();
//                 tokens.push_back(holder);
//             }
//         }
//         // while (getline(iss, holder, ' ')) {
//         //     size_t firstNonSpace = holder.find_first_not_of(" \t\n\r");
//         //     size_t lastNonSpace = holder.find_last_not_of(" \t\n\r");
                    
//         //     if (firstNonSpace != std::string::npos) {
//         //         holder = holder.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
//         //         if (!holder.empty()) { // Check if the token is not empty after trimming
//         //             tokens.push_back(holder);
//         //         }
//         //     }
//         // }
//         // tokens[0] = tokens[0].substr(0, 4);
//         for (size_t i = 0; i < tokens.size(); i++)
//             std::cout << i << "--------: " << tokens[i] << " tokens.size() :" << tokens.size() << std::endl;
//         if (!tokens.empty() && tokens[0] == "USER") {
//             if (tokens.size() != 5){
//                 std::cout << "before\n";
//                 std::cout << "USER:: wrong number of arguments" << std::endl;
//                 return 0;
//             }
//             else{
//                 std::cout << "else\n";
//                 this->username = tokens[1];
//                 this->hostname = tokens[2];
//                 this->servername = tokens[3];
//                 this->realname = tokens[4];
//                 usernameMap[sockfd] = realname;
//                 std::cout << "usernameMap[sockfd]: " << usernameMap[sockfd] <<std::endl;
//                 std::cout <<  "USER hh :" << this->username << this->hostname << this->servername << this->realname << std::endl;
//             }        
//         }
//     }
//     else {
//         std::cout << "sockfd " << sockfd << " is already associated with username: " << it->second << std::endl;
//         return 1;
//     }

//     return 1;
// }

// int Server::check_authenticate(int sockfd, std::string buffer)
// {
//     std::map<int, std::string> usernameMap;
//     std::vector<std::string> tokens;
//     std::istringstream iss(buffer);
//     std::string holder;

//     std::map<int, std::string>::iterator it = usernameMap.find(sockfd);
//     std::cout << "sockfd: " << sockfd << std::endl;
//     if (it == usernameMap.end()) {
//         std::cout << "Existing sockfd " << sockfd << " associated with username: " << it->second << std::endl;
//         return 1; // Return or perform desired action
//     }
//     while (std::getline(iss, holder, ' ')) {
//         if (!holder.empty()) {
//             if (holder.back() == '\n') {
//                 holder.pop_back(); // Remove newline character
//             }
//             tokens.push_back(holder);
//         }
//     }
//     for (size_t i = 0; i < tokens.size(); i++)
//     {
//         std::cout << i << "--------: " << tokens[i] << " tokens.size() :" << tokens.size() << std::endl;
//     }
//     // std::cout << "check_authenticate: " << tokens[0] << ", tokens.size()" << tokens.size() << std::endl;
//     if(tokens[0] == "USER"){
//         std::cout <<"user dkhol \n";
//         if (tokens.size() != 5){
//             std::cout << "USER:: wrong number of arguments" << std::endl;
//             return 0;
//         }
//         else{
//             this->username = tokens[1];
//             this->hostname = tokens[2];
//             this->servername = tokens[3];
//             this->realname = tokens[4];
//             usernameMap[sockfd] = realname;
//             std::cout << "usernameMap[sockfd]: " << usernameMap[sockfd] <<std::endl;
//             std::cout << sockfd <<  "USER hh :" << this->username << this->hostname << this->servername << this->realname << std::endl;
//         }
//     }

//     else if(tokens[0] == "NICK"){
//         std::cout <<"nick dkhol \n";
//         if (tokens.size() != 2){
//             std::cout << "NICK:: wrong number of arguments" << std::endl;
//             return 0;
//         }
//         else{
//             this->nickname = tokens[1];
//             std::cout << sockfd << " NICK hh :" << this->nickname << std::endl;
//         }
//     }
//     // int i = sockfd;
//     // std::string command, username, hostname, servername, realname;

//     // iss >> command >> username >> hostname >> servername;
//     // std::getline(iss, realname);
//     // std::cout << "aaaaaaaaaaaaaaaaa" << command << username << hostname << servername << std::endl;
//     // std::cout << "servername" << servername << std::endl;
//     // std::cout << "realname" << realname << std::endl;
//     // std::cout << buffer << " Welcome to our irc server, please confirme your identity by using commands USER and NICK" << std::endl;
//     // if (buffer.length() >= 5 && strncmp(buffer.c_str(), "USER", 4) == 0)
//     // {
//     //     std::cout << i << "khdmat\n";
//     // }
//     std::cout << "return " << std::endl;
//     return 1;
// }

Server::Server(int serverport, std::string password): serverport(serverport) {
    int len, rc, on = 1;
    int listen_sd = -1, new_sd = -1;
    int end_server = 0, compress_array = 0;
    int close_conn;
    std::string buffer(1024, '\0');
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

                    fds[nfds].fd = new_sd;
                    fds[nfds].events = POLLIN;
                    nfds++;

                } while (new_sd != -1);
            } else {
                close_conn = 0;

                do {
                    rc = recv(fds[i].fd, buffer.data(), buffer.size(), 0);
//------------------------------------------------------------------------------------------------ version c++98
                    // rc = recv(fds[i].fd, static_cast<void*>(const_cast<char*>(buffer.data())), buffer.size(), 0);
//------------------------------------------------------------------------------------------------ version c++98
                    std::cout << buffer << " asd "<< rc << std::endl;
                    if (rc < 0) {
                        if (errno != EWOULDBLOCK) {
                            perror("recv() failed");
                            close_conn = 1;
                        }
                        break;
                    }
                    if (rc == 0) {
                        std::cout << "Connection closed" << std::endl;
                        close_conn = 1;
                        break;
                    }
                    std::string receiveddata(buffer.data(), rc);
                    std::cout << "Received data: " << receiveddata << std::endl;
                    len = rc;
                    std::cout << len << " bytes received" << std::endl;
                    if(this->is_reg != 2 && check_pass(receiveddata, password))
                        check_authenticate(fds[i].fd, receiveddata);
                    else if(this->is_reg == 2 && this->password == 1)
                        std::cout << "Registration already completed!" << std::endl;
                    rc = send(fds[i].fd, buffer.c_str(), len, 0);
                    if (rc < 0) {
                        perror("send() failed");
                        close_conn = 1;
                        break;
                    }
                } while (1);

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
