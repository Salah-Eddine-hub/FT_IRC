/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tools.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:00:59 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/07 15:33:08 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_HPP
#define TOOLS_HPP
#include"iostream"
#include <sstream>
#include <sys/socket.h>


std::string strtolower(std::string str);
int str_search(std::string str, char c);
int is_num(std::string arg);
void error(int sockfd, const std::string& message);
void success(int sockfd, const std::string& message);
std::string int_to_string(int nb);
#endif