/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsdata.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:06:54 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/30 14:02:58 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

// std::vector<std::string> Server::parsdata(std::string receiveddata) {
//     std::vector<std::string> tokens;
//     std::string word;
//     int i = 0;
//     int j = 0;
//     int start = 0;

//     while (receiveddata[i])
//     {
//         if (receiveddata[i - 1] == ' ' && (receiveddata[i] != ':' || receiveddata[i] != ' '))
//             j = i;
//         if (receiveddata[i] == ':')
//         {
//             if (j != 0 && receiveddata[i - 1] != ' '){
//                 if (receiveddata[j] != ':')
//                     tokens.push_back(receiveddata.substr(j, i - j));
//             }
//             i++;
//             word = "";
//             while(receiveddata[i] != ':' && receiveddata[i] != '\0')
//             {
//                 // int is_char = 0;
//                 // if(receiveddata[i - 1] == ':')
//                 // {
//                 //     while (receiveddata[i] == ' ' && is_char == 0 && receiveddata[i + 1] != ':')
//                 //     {
//                 //         if (receiveddata[i + 1] != ' '){
//                 //             is_char = 1;
//                 //             i = i + 1;
//                 //             break;
//                 //         }
//                 //         else
//                 //             i++;
//                 //     }
//                 // }
//                 word += receiveddata[i];
//                 i++;
//             }
//             // std::istringstream iss(word);
//             // std::string holder;
//             // word = "";
//             // while (std::getline(iss, holder, ' '))
//             //     if (!holder.empty())
//             //         word += holder + ' ';
//             // word.resize(word.size() - 1);
//             tokens.push_back(word);
//             continue;
//         }
//         else if(receiveddata[i] == ' ' || receiveddata[i + 1] == '\0')
//         {
//             int end = i;
//             if (receiveddata[i + 1] == '\0' && receiveddata[i] != ' '){
//                 if(receiveddata.substr(start, end - start + 1) != "\n")
//                     tokens.push_back(receiveddata.substr(start, end - start + 1));
//             }            
//             else if (!receiveddata.substr(start, end - start).empty() && receiveddata.substr(start, end - start) != " "){
//                 tokens.push_back(receiveddata.substr(start, end - start));
//             }
//             start = end + 1;
//         }
//         i++;
//     }
//     for (size_t i = 0; i < tokens.size(); ++i) 
//         std::cout << "string" << i + 1 << ": \"" << tokens[i] << "\"" << std::endl;
//     return tokens;
// }

//  part cmd         
//  #hh = #Hh = #HH

std::vector<std::string> Server::parsdata(std::string receiveddata) {
    std::vector<std::string> tokens;
    std::string word;
    
    int i = 0;
    int j = 0;
    while (receiveddata[i])
    {  
        if(receiveddata[i] == ' '){
            i++;
            std::cout << "spaces\n";
            continue;
        }
        if(receiveddata[i] == ':')
        {
            while (receiveddata[i]){
                // std::cout << "chars\n";
                word += receiveddata [i];
                i++;
                j++;
            }
            tokens.push_back(word);
        }
        if(receiveddata[i] != ':')
        {
            while (receiveddata[i]){
                   std::cout << "-----------------------\n";
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
            // tokens.push_back(word);
        }
        i++;
    }

    for (size_t i = 0; i < tokens.size(); ++i) 
        std::cout << "string" << i + 1 << ": \"" << tokens[i] << "\"" << std::endl;
    return tokens;
}