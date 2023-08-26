/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:44:43 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/25 17:08:22 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Client.hpp"

Client::Client() {
    this->pwdconf = 0;
    this->is_reg = 0;
    this->is_mode = 0;
}

void Client::set_pwdconf(int pwdconf) {
    this->pwdconf = pwdconf;
}

void Client::inc_is_reg() {
    this->is_reg++;
}

void Client::set_is_mode(int mode) {
    this->is_mode = mode;
}

void Client::set_username(std::string username) {
    this->username = username;
}

void Client::set_hostname(std::string hostname) {
    this->hostname = hostname;
}

void Client::set_servername(std::string servername) {
    this->servername = servername;
}

void Client::set_realname(std::string realname) {
    this->realname = realname;
}

void Client::set_nickname(std::string nickname) {
    this->nickname = nickname;
}

// -------------------------------------------------------

const int& Client::get_pwdconf(){
    return (this->pwdconf);
}

const int& Client::get_is_reg(){
    return (this->is_reg);
}

const int& Client::get_is_mode(){
    return (this->is_mode);
}

const std::string& Client::get_username(){
    return (this->username);
}

const std::string& Client::get_hostname(){
    return (this->hostname);
}

const std::string& Client::get_servername(){
    return (this->servername);
}

const std::string& Client::get_realname(){
    return (this->realname);
}

const std::string& Client::get_nickname(){
    return (this->nickname);
}



Client::~Client() {}
