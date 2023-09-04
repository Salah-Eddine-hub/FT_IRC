/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:07:35 by sharrach          #+#    #+#             */
/*   Updated: 2023/09/02 12:07:59 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void RecordLoginTime(const std::string& username) {
    loginTimes[username] = std::chrono::system_clock::now();
}

// Function to get login time duration
std::string GetLoginTime(const std::string& username) {
    if (loginTimes.find(username) != loginTimes.end()) {
        auto loginTime = loginTimes[username];
        auto currentTime = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::minutes>(currentTime - loginTime);
        return std::to_string(duration.count()) + " minutes";
    } else {
        return "User " + username + " has not logged in.";
    }
}