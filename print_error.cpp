/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 21:32:59 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/17 23:20:44 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"
#include"Channel.hpp"

void Server::error(int sockfd, const std::string& message) {
    send(sockfd, message.c_str(), message.size(), 0);
}

void Server::success(int sockfd, const std::string& message) {
    send(sockfd, message.c_str(), message.size(), 0);
}

void Channel::error(int sockfd, const std::string& message) {
    send(sockfd, message.c_str(), message.size(), 0);
}

void Channel::success(int sockfd, const std::string& message) {
    send(sockfd, message.c_str(), message.size(), 0);
}
