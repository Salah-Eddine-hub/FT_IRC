/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsdata.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:06:54 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/30 19:39:40 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

std::vector<std::string> Server::parsdata(std::string receiveddata) {
    std::vector<std::string> tokens;
    std::string word;
    
    int i = 0;
    int j = 0;
    while (receiveddata[i])
    {  
        if(receiveddata[i] == ' '){
            i++;
            continue;
        }
        if(receiveddata[i] == ':')
        {
            while (receiveddata[i]){
                word += receiveddata [i];
                i++;
                j++;
            }
            tokens.push_back(word);
        }
        if(receiveddata[i] != ':')
        {
            while (receiveddata[i]){
                if (receiveddata[i] == ' ' || receiveddata[i + 1] == '\0')
                {

                    if (receiveddata[i + 1] == '\0')
                        word += receiveddata [i];
                    if (!word.empty())
                        tokens.push_back(word);
                    word = "";
                    break;
                }
                word += receiveddata [i];
                i++;
                j++;
            }
        }
        i++;
    }

    for (size_t i = 0; i < tokens.size(); ++i) 
        std::cout << "string" << i + 1 << ": \"" << tokens[i] << "\"" << std::endl;
    return tokens;
}