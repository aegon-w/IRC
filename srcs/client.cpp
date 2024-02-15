/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:37:11 by kali              #+#    #+#             */
/*   Updated: 2024/02/06 21:25:18 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Client.hpp"

Client::Client(): _isConnected(0), _clientFd(0), _username(""), _nickname(""), _HOST("mhmmed.ml"), _id(""), _channel("")
{
}
Client::Client(int fd): _isConnected(0), _clientFd(fd), _username(""), _nickname(""), _HOST("mhmmed.ml"), _id("")
{
}

Client::~Client()
{
}

Client::Client(Client const &src)
{
    *this = src;
}

Client &Client::operator=(Client const &rhs)
{
    if (this != &rhs)
    {
        this->_isConnected = rhs._isConnected;
        this->_clientFd = rhs._clientFd;
        this->_username = rhs._username;
        this->_nickname = rhs._nickname;
        this->_id = rhs._id;
    }
    return (*this);
}

void    Client::setauthentification(bool x)
{
    //here i have a SEGV when i try to set _isConnected to 1
    this->_isConnected = x;
}

bool    Client::getauthentification(void) const
{
    return (this->_isConnected);
}

void    Client::setnickname(std::string nickname)
{
    this->_nickname = nickname;
}

std::string Client::getnickname(void) const
{
    return (this->_nickname);
}

void   Client::setusername(std::string username)
{
    this->_username = username;
}

std::string Client::getusername(void) const
{
    return (this->_username);
}

void Client::setchannel(std::string channel)
{
    this->_channel = channel;
}

std::string Client::getchannel(void) const
{
    return (this->_channel);
}

int Client::getfd(void)
{
    return (this->_clientFd);
}

