/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:44:43 by iellyass          #+#    #+#             */
/*   Updated: 2023/09/16 21:15:30 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Client.hpp"

Client::Client() {
	this->pwdconf = 0;
	this->is_reg = 0;
	this->is_invited = 0;
	this->username = "";
	this->hostname = "";
	this->servername = "";
	this->realname = "";
	this->nickname = "";
	this->holder = "";
	this->loginTimes = std::time(NULL);
}

void Client::set_pwdconf(int pwdconf) {
	this->pwdconf = pwdconf;
}

void Client::set_is_reg(int i) {
	this->is_reg = i;
}

void Client::set_is_invited(std::string channel_name) {
	std::vector<std::string>::iterator it = std::find(this->channelinvitedtoMap.begin(), this->channelinvitedtoMap.end(), channel_name);

	if(it == this->channelinvitedtoMap.end())
		this->channelinvitedtoMap.push_back(channel_name);
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

void Client::set_holder(std::string holder){
	this->holder = holder;
}



// -------------------------------------------------------

const int& Client::get_pwdconf(){
	return (this->pwdconf);
}

const int& Client::get_is_reg(){
	return (this->is_reg);
}

const std::time_t& Client::get_loginTimesg(){
	return (this->loginTimes);
}

int Client::get_is_invited(std::string channel_name){
	std::vector<std::string>::iterator it = std::find(this->channelinvitedtoMap.begin(), this->channelinvitedtoMap.end(), channel_name);

	if(it != this->channelinvitedtoMap.end())
		return 1;
	return 0;
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


std::string Client::get_holder(){
	return (this->holder);
}



Client::~Client() {}
