/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:00:59 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/27 20:50:06 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Tools.hpp"

std::string strtolower(std::string str) {
    for (size_t i = 0; i < str.size(); ++i)
        str[i] = tolower(str[i]);
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
            return 0;
        i++;
    }
    return 1;
}
