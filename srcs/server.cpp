/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 08:03:46 by kali              #+#    #+#             */
/*   Updated: 2024/02/07 11:43:22 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/server.hpp"


#define MAX_EVENTS 20
#define MAX_BUFFER_SIZE 4096

Server::Server(): client() {}

Server::Server(char **av): client()
{
    this->port = atoi(av[1]);
    this->password = av[2];
    this->lstn_sock = 0;
    this->epfd = 0;
    this->ipAddress = "127.0.0.1";
    this->hserver.sin_family = AF_INET;
    this->hserver.sin_port = htons(this->port);
    inet_pton(AF_INET, this->ipAddress.c_str(), &this->hserver.sin_addr); 
    // this->password = password;
}

Server::~Server()
{
    close(this->lstn_sock);
    close(this->epfd);

    //free client
    for (std::map<int, Client*>::iterator it = this->client.begin(); it != this->client.end(); ++it)
    {
        delete it->second;
    }
}

void Server::createSocket()
{
    //create a socket
    this->lstn_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (this->lstn_sock < 0)
    {
        std::cerr << "Can't create a socket" << std::endl;
        exit(1);
    }
}

void Server::createEpoll()
{
    //establish the epoll instance
    this->epfd = epoll_create1(0);
    if (this->epfd < 0)
    {
        std::cerr << "Can't create epoll instance" << std::endl;
        exit(1);
    }
}

void Server::bindSocket()
{
    //bind the socket to IP/port
    int bindRes = bind(this->lstn_sock, (sockaddr*)&this->hserver, sizeof(this->hserver));
    if (bindRes < 0)
    {
        std::cerr << "Can't bind to IP/port" << std::endl;
        exit(1);
    }
}

void Server::listenSocket()
{
    //mark the socket for listening in
    int listenRes = listen(this->lstn_sock, SOMAXCONN);
    if (listenRes < 0)
    {
        std::cerr << "Can't listen" << std::endl;
        exit(1);
    }
}

void Server::addSocketToEpoll()
{
    //add the listener to the epoll instance
    epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = this->lstn_sock;
    int s = epoll_ctl(this->epfd, EPOLL_CTL_ADD, this->lstn_sock, &ev);
    if (s < 0)
    {
        std::cerr << "Can't add listener to epoll instance" << std::endl;
        exit(1);
    }
}

static int make_socket_non_blocking(int sfd)
{
    int flags, s;

    flags = fcntl(sfd, F_GETFL, 0);
    if(flags == -1)
    {
        std::cerr << "fcntl Error" << std::endl;
        return -1;
    }

    flags |= O_NONBLOCK;
    s = fcntl(sfd, F_SETFL, flags);
    if(s == -1)
    {
        std::cerr << "fcntl Error" << std::endl;
        return -1;
    }
    return 0;
}

void Server::acceptSocket()
{
    //accept a connection
    int s;
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
    int clientSocket = accept(this->lstn_sock, (sockaddr*)&client, &clientSize);
    if (clientSocket < 0)
    {
        std::cerr << "Problem with client connecting!" << std::endl;
        exit(1);
    }
    s = getnameinfo((sockaddr*)&client, sizeof(client), hbuf, sizeof(hbuf), sbuf, sizeof(sbuf), NI_NUMERICHOST | NI_NUMERICSERV);
    if (s == 0)
    {
        std::cout << "Accepted connection on descriptor " << clientSocket << "(host=" << hbuf << ", port=" << sbuf << ")" << std::endl;
    }
    s = make_socket_non_blocking(clientSocket);
    //add the new connection to the epoll instance
    epoll_event ev;
    ev.events = EPOLLIN ;
    ev.data.fd = clientSocket;
    s = epoll_ctl(this->epfd, EPOLL_CTL_ADD, clientSocket, &ev);
    if (s < 0)
    {
        std::cerr << "Can't add client to epoll instance" << std::endl;
        exit(1);
    }
}

void Server::readSocket()
{
    while(1)
    {
        epoll_event events[MAX_EVENTS];
        int nfds = epoll_wait(this->epfd, events, MAX_EVENTS, -1);
        if (nfds == -1)
        {
            std::cerr << "Can't wait for events" << std::endl;
            exit(1);
        }
        for(int i = 0; i < nfds; i++)
        {
            if (events[i].data.fd == this->lstn_sock)
                this->acceptSocket();
            else
            {
                // Initialize the buffer
                char buffer[MAX_BUFFER_SIZE];

                // Inside your event loop
                if (events[i].events & EPOLLIN) {
                    int totalBytesReceived = 0;
                    int bytesIn = recv(events[i].data.fd, buffer + totalBytesReceived, MAX_BUFFER_SIZE - totalBytesReceived, 0);
                    if (bytesIn <= 0) {
                        if (bytesIn == 0) {
                            // Client disconnected
                            epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
                            std::cout << "Client disconnected" << std::endl;
                            close(events[i].data.fd);
                            // ! kick client from channel if the owner of the channel is disconnected
                            if (this->client[events[i].data.fd] != NULL && this->client[events[i].data.fd]->getauthentification() == 1 && this->client[events[i].data.fd]->getchannel() != "")
                                    this->_channels[this->client[events[i].data.fd]->getchannel()]->removeMember(this->client[events[i].data.fd]);
                            delete this->client[events[i].data.fd];
                            this->client.erase(events[i].data.fd);
                        }
                        break;
                    }
                    else {
                        totalBytesReceived += bytesIn;
                        if (bytesIn < MAX_BUFFER_SIZE) {
                            // Full message received
                            // printf("**********Received: %s\n", buffer);
                            std::string res = parseMessage(buffer, events[i].data.fd);
                            //std::cout << "Received: " << std::string(buffer, totalBytesReceived) << std::endl;
                            send(events[i].data.fd, res.c_str(), res.length(), 0);
                            bzero(buffer, MAX_BUFFER_SIZE);
                            break;
                        }
                        else {
                            // Message too long
                            char msg[87] = "to much character used.\nSubscribe to use our IRC model as you like.\n<DM NOW (599$)!!>\n";
                            send(events[i].data.fd, msg, 87, 0);
                            break;  
                        }
                    }
                }
            }
        }
    }
}


void    Server::run()
{
    this->createSocket();
    this->createEpoll();
    this->bindSocket();
    this->listenSocket();
    this->addSocketToEpoll();
    this->readSocket();
}