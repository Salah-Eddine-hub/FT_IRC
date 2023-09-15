/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tools.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:00:59 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/15 23:40:50 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_HPP
#define TOOLS_HPP
#include"iostream"
#include <sstream>
#include <sys/socket.h>


std::string strtolower(std::string str);
int is_num(std::string arg);
void inv_mssg(int sockfd, const std::string& message);
std::string int_to_string(int nb);
#endif