/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:00:59 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/07 15:31:58 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Tools.hpp"

std::string strtolower(std::string str) {
    for (size_t i = 0; i < str.size(); ++i)
        str[i] = tolower(str[i]);
    return str;
}

std::string int_to_string(int nb) {
    std::stringstream ss;
    std::string str;

    ss << nb;
    ss >> str;
    return str;
}

int str_search(std::string str, char c){

    for (size_t i = 0; i < str.length(); i++){
        if(str[i] == c)
            return i;
    }
    return -1;
}

int is_num(std::string arg)
{
    int i = 0;
    while (arg[i])
    {
        if (!isdigit(arg[i]))
            return i;
        i++;
    }
    return i;
}


void error(int sockfd, const std::string& message) {
    send(sockfd, message.c_str(), message.size(), 0);
}

void success(int sockfd, const std::string& message) {
    send(sockfd, message.c_str(), message.size(), 0);
}
