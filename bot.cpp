
#include "server.hpp"
#include <chrono>

// void Server::TrackTime(const std::string& username) {
//     loginTimes[username] = std::time(NULL);
//     std::cout << username << " logged in.\n";
// }

void Server::DisplayTime(const std::string& username, int sockfd) {
    
    // std::map<int, Client>::iterator it = loginTimes.find(username);
    if (username.empty())
    {
        error(sockfd, "wrong args.\n");
        return ;
    }
    if (usernickMap.find(get_sockfd(username)) != usernickMap.end()) {
        std::time_t loginTime = usernickMap[sockfd].get_loginTimesg();
        std::cout << "loginTime time " <<  loginTime  << std::endl;
        std::time_t currentTime = std::time(NULL);
        std::cout << "here " <<  currentTime << std::endl;
        std::time_t duration = currentTime - loginTime;
        std::cout << "here2 " << duration << std::endl;
        int minutes = static_cast<int>(duration / 60);
        std::cout << minutes << std::endl;
        std::stringstream ss;
        std::string str_min;
        ss << minutes;
        ss >> str_min;
        success(sockfd, username + " has been logged in for " +  str_min + " minutes.\n");
        // std::cout << username << " has been logged in for " << minutes << " minutes.\n";
    }
    else {
        error(sockfd, "User " + username + " not found.\n");
    }
}