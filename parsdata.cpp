/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsdata.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:06:54 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/04 20:26:387 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

std::vector<std::string> Server::parsdata(std::string receiveddata) {
    std::vector<std::string> tokens;
    std::string word;
    
    int i = 0;
    while (receiveddata[i] == ' ')
        i++;
    if(receiveddata[i] == ':')
        tokens.push_back(receiveddata.substr(i + 1));
    else
    {
        while (receiveddata[i]) {
            if (receiveddata[i] == ' ' || receiveddata[i + 1] == '\0')
            {
                if (receiveddata[i + 1] == '\0')
                    word += receiveddata [i];
                if (!word.empty())
                    tokens.push_back(word);
                word = "";
            }
            else
               word += receiveddata [i];
            i++;
        }
    }

    for (size_t i = 0; i < tokens.size(); ++i) 
        std::cout << "string" << i + 1 << ": \"" << tokens[i] << "\"" << std::endl;
    return tokens;
}
