/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whichcmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:06:54 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/17 21:54:26 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

std::vector<std::string> Server::parsdata(std::string receiveddata)
{
    std::vector<std::string> tokens;
    std::istringstream iss(receiveddata);
    std::string holder;

    while (std::getline(iss, holder, ' ')) {
    if (!holder.empty()) {
        if (holder.back() == '\n')
            holder.pop_back();
//------------------------------------------------------------------------------------------------ version c++98
        // if (!holder.empty() && holder[holder.length() - 1] == '\n')
        //     holder.resize(holder.length() - 1);
//------------------------------------------------------------------------------------------------ version c++98
            tokens.push_back(holder);
        }
    }
    return tokens;
}