/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 07:49:54 by kali              #+#    #+#             */
/*   Updated: 2024/02/08 11:51:05 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <fcntl.h>
#include <sys/epoll.h>
#include <cstdlib>
#include <cstdio>
#include <map>
 #include <algorithm>
#include <fstream>

# include "request.hpp"
# include "Client.hpp"
# include "channel.hpp"
# include "file.hpp"

class Client;
class Channel;
class File;
class Server
{
    private :
        int lstn_sock;
        int epfd;
        int port;
        std::map<int, Client*> client;
        std::vector<std::string> _nicknames;
        std::vector<std::string> _usernames;
        std::map<std::string, Channel*> _channels;
        std::string ipAddress;
        std::string password;
        sockaddr_in hserver;
        std::map<std::string, File> _files;
        
    public:
        Server();
        Server(char **av);
        ~Server();
        void createSocket();
        void createEpoll();
        std::string parseMessage(std::string message, int fd);
        Request parseRequest(std::string message);
        void bindSocket();
        void listenSocket();
        void addSocketToEpoll();
        void acceptSocket();
        void readSocket();
        void writeSocket();
        void closeSocket();
        void run();
        std::string serverCap(Request request, int fd);
        std::string connect(Request request, int fd);
        std::string nick(Request request, int fd);
        std::string user(Request request, int fd);
        std::string join(Request request, int fd);
        std::string boot(Request request, int fd);
        std::string join_message(std::string channel, int fd);
        void createChannel(std::string channel, int fd);
        void send_to_all_members(std::string channel, std::string message);
        void send_to_members(std::string channel, std::string message, int fd);
        std::string mode(Request request, int fd);
        std::string topic(Request request, int fd);
        std::string invite(Request request, int fd);
        std::string privmsg(Request request, int fd);
        std::string kick(Request request, int fd);
        std::string quit(Request request, int fd);
        std::string sendfile(Request request, int fd);
        std::string getfile(Request request, int fd);
};

#endif