/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pass.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:52:11 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/15 18:20:34 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

int Server::check_pass(std::string data, std::string password)
{
    std::vector<std::string> tokens;
    std::istringstream iss(data);
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
    if(this->password != 1){
        if(tokens[0] != "pass"){
            return (std::cout << "please use 'pass' command to enter the password and have full access of the server's channels and commands!" << std::endl), 0;
        }
        else {
            if(tokens.size() != 2)
                return (std::cout << "error: Wrong number of arguments!" << std::endl), 0;
            else {
                if(tokens[1] != password)
                    return (std::cout << "error: Wrong password!" << std::endl), 0;
                else{
                    std::cout << "password correct! Enjoy chatting!" << std::endl;
                    this->password = 1;
                }
            }
        }
    }
    return 1;
}
