/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsdata.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:06:54 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/24 17:36:55 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include"server.hpp"

std::vector<std::string> Server::parsdata(std::string receiveddata)
{
    std::vector<std::string> tokens;
    std::istringstream iss(receiveddata);
    std::string holder;

//     // while (std::getline(iss, holder, ' ')) {
//     //     if (!holder.empty()) {
//     //         if (holder.back() == '\n')
//     //             holder.pop_back();
//     //         tokens.push_back(holder);
//     //     }
//     // }

// // issam test :hh 3ndak qwer : fads
    int is_col = 0;
    std::string holder2;
    while (std::getline(iss, holder, ' ')) {
        if (!holder.empty()){
            if (holder.back() == '\n')
                holder.pop_back();
            if (str_search(holder, ':') == 0) {
                std::cout << holder<< "    1\n";
                tokens.push_back(holder.substr(1));
                is_col = 1;
            }
            else if (str_search(holder, ':') > 0){
                // working on it
            }
            else {
                if(is_col == 0)
                    tokens.push_back(holder);
                else if (!tokens.empty()) 
                    tokens.back() += " " + holder;
            }
        }
    }
    return tokens;
}
