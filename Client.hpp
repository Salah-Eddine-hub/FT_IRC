/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:43:37 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/30 17:50:33 by iellyass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CLIENT_HPP
#define CLIENT_HPP
#include<iostream>
#include"server.hpp"

class Server;

class Client
{
    private:
        std::vector<std::string> channelinvitedtoMap;
        int pwdconf;
		int is_reg;
		int is_invited;
		std::string username;
		std::string hostname;
		std::string servername;
		std::string realname;
		std::string nickname;
    public:
        Client();
        ~Client();

        
        void set_pwdconf(int pwdconf );
        void inc_is_reg();
        void set_is_invited(std::string channel_name);
        void set_username(std::string username);
        void set_hostname(std::string hostname);
        void set_servername(std::string servername);
        void set_realname(std::string realname);
        void set_nickname(std::string nickname);
        const int& get_pwdconf();
        const int& get_is_reg();
        int get_is_invited(std::string channel_name);
        const std::string& get_username();
        const std::string& get_hostname();
        const std::string& get_servername();
        const std::string& get_realname();
        const std::string& get_nickname();
};


#endif