/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:46:54 by sharrach          #+#    #+#             */
/*   Updated: 2023/08/24 13:25:30 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <iostream>
#include <chrono>
#include <map>
#include <string>

std::map<std::string, std::chrono::time_point<std::chrono::system_clock>> loginTimes;

void TrackTime(const std::string& username) {
    loginTimes[username] = std::chrono::system_clock::now();
    std::cout << username << " logged in.\n";
}

void DisplayTime(const std::string& username) {
    if (loginTimes.find(username) != loginTimes.end()) {
        auto loginTime = loginTimes[username];
        auto currentTime = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::minutes>(currentTime - loginTime);
        std::cout << username << " has been logged in for " << duration.count() << " minutes.\n";
    } else {
        std::cout << "User " << username << " has not logged in.\n";
    }
}

int main() {
    std::string command, username;

    while (true) {
        std::cout << "Enter command (login, display, quit): ";
        std::cin >> command;

        if (command == "login") {
            std::cout << "Enter username: ";
            std::cin >> username;
            TrackTime(username);
        } else if (command == "display") {
            std::cout << "Enter username: ";
            std::cin >> username;
            DisplayTime(username);
        } else if (command == "quit") {
            break;
        } else {
            std::cout << "Invalid command. Available commands: login, display, quit\n";
        }
    }

    return 0;
}