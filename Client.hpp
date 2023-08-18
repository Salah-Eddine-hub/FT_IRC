/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iellyass <iellyass@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:43:37 by iellyass          #+#    #+#             */
/*   Updated: 2023/08/18 21:55:24 by iellyass         ###   ########.fr       */
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
        int pwdconf;
		int is_reg;
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
        void set_username(std::string username);
        void set_hostname(std::string hostname);
        void set_servername(std::string servername);
        void set_realname(std::string realname);
        void set_nickname(std::string nickname);
        int get_pwdconf();
        int get_is_reg();
        std::string get_username();
        std::string get_hostname();
        std::string get_servername();
        std::string get_realname();
        std::string get_nickname();
};


#endif