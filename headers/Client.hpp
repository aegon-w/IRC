/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 04:05:28 by kali              #+#    #+#             */
/*   Updated: 2024/02/06 21:24:53 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP


# include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

# include "server.hpp"
# include "Client.hpp"

class Client
{
    private :
        bool _isConnected;
        int _clientFd;
        std::string _username;
        std::string _nickname;
        const std::string _HOST;
        std::string _id;
        //channel where the client is connected
        std::string _channel;
        
    public :
        Client();
        Client(int fd);
        ~Client();
        Client(Client const &src);
        Client &operator=(Client const &rhs);

        void    setauthentification(bool x);
        bool    getauthentification(void) const;
        void    setnickname(std::string nickname);
        std::string getnickname(void) const;
        void   setusername(std::string username);
        std::string getusername(void) const;
        void setchannel(std::string channel);
        std::string getchannel(void) const;
        int getfd(void);
};

#endif