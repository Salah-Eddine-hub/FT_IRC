/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   authenticate.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:17:36 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/06 13:29:21 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

int Server::check_authenticate(int sockfd, std::vector<std::string> tokens)
{
    if (usernickMap[sockfd].get_is_reg() != 2 && usernickMap[sockfd].get_pwdconf()) {
        if(usernickMap[sockfd].get_is_reg() != 2 && (tokens[0] != "user" && tokens[0] != "nick"))
            error(sockfd, "Please confirme your identity first by using 'USER' and 'NICK' commands\n");
        if (!tokens.empty() && strtolower(tokens[0]) == "user")
            user(tokens, sockfd);
        else if (!tokens.empty() && strtolower(tokens[0]) == "nick")
            nick(tokens, sockfd);
    }
    return 1;
}
