/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:40:46 by kali              #+#    #+#             */
/*   Updated: 2024/02/07 11:49:56 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include <vector>
# include <sstream>
# include <sys/socket.h>

# include "server.hpp"
# include "Client.hpp"

class Client;
class Channel
{
    private:
        Client *_owner;
        int _onlinemembers;
        std::vector<Client*> _members;
        std::string _name;
        std::string _topic;
        std::vector<int> _operators;
        std::vector<std::string> _banlist;
        time_t _Date;
        bool _l;
        bool _op;
        bool _k;
        bool _t;
        bool _i;
        int limit_channel;
        std::string _password;

    public:
        Channel( Client *o, std::string name);
        ~Channel();
        Channel(const Channel &other);
        Channel &operator=(const Channel &other);
        void addMember(Client *member);
        void removeMember(Client *member);
        void setTopic(std::string topic);
        void update_onlinemembers();
        std::string getTopic();
        std::string getName();
        std::string intToString(int value);
        int getonlinemembers();
        bool isMember(Client *member);
        std::string getCreationDate();
        void sendToAllMembers(std::string message);
        int getfd(int i);
        void sendToMembers(std::string message, int fd);
        void setop(Client *member);
        void invite_or_not(std::string invite);
        std::string getOwner();
        std::string getinvite();
        bool isop(Client *member);
        void set_topic_or_not(std::string topic);
        std::string addoperator(std::string user);
        std::string removeoperator(std::string user);
        void setlimit(std::string limit);
        int getlimit();
        void set_key(std::string key);
        std::string get_key();
        bool get_t();
};

#endif