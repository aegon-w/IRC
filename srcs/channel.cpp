/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:46:33 by kali              #+#    #+#             */
/*   Updated: 2024/02/07 13:22:37 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/server.hpp"

Channel::Channel( Client *o, std::string name)
{
    this->_owner = o;
    this->_name = name;
    this->_onlinemembers = 1;
    this->_members.push_back(o);
    this->_topic = "No topic";
    this->_Date = time(0);
    this->limit_channel = 4;
    this->_op = false;
    this->_i = false;
    this->_k = false;
    this->_l = false;
    this->_t = false;
}

Channel::~Channel()
{
    this->_members.clear();
    this->_banlist.clear();
}

Channel::Channel(const Channel &other)
{
    *this = other;
}

Channel &Channel::operator=(const Channel &other)
{
    this->_owner = other._owner;
    this->_onlinemembers = other._onlinemembers;
    this->_members = other._members;
    this->_name = other._name;
    this->_topic = other._topic;
    this->_banlist = other._banlist;
    this->_Date = other._Date;
    return (*this);
}

void Channel::addMember(Client *member)
{
    this->_members.push_back(member);
    this->_onlinemembers++;
}

void Channel::removeMember(Client *member)
{
    for (size_t i = 0; i < this->_members.size(); i++)
    {
        if (this->_members[i] == member)
        {
            std::string message = "QUIT " + member->getnickname() + " has left the channel\n";
            this->_members.erase(this->_members.begin() + i);
            this->_onlinemembers--;
            sendToAllMembers(message);
            return ;
        }
    }
}

void Channel::setTopic(std::string topic)
{
    this->_topic = topic;
}

void Channel::update_onlinemembers()
{
    this->_onlinemembers = this->_members.size();
}

std::string Channel::getTopic()
{
    return (this->_topic);
}

std::string Channel::getName()
{
    return (this->_name);
}

int Channel::getonlinemembers()
{
    return (this->_onlinemembers);
}

std::string Channel::intToString(int value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

bool Channel::isMember(Client *member)
{
    for (size_t i = 0; i < this->_members.size(); i++)
    {
        if (this->_members[i] == member)
            return (true);
    }
    return (false);
}

std::string Channel::getCreationDate()
{
    std::string date = ctime(&_Date);
    date.erase(date.size() - 1);
    return (date + " by " + this->_owner->getnickname());
}

std::string Channel::getOwner()
{
    return (this->_owner->getnickname());
}

void Channel::sendToAllMembers(std::string message)
{
    int x = this->_members.size();
    for (int i = 0; i < x; i++)
    {
        if (this->_members[i]->getauthentification() == 1)
            send(this->_members[i]->getfd(), message.c_str(), message.size(), 0);
    }
}

int Channel::getfd(int i)
{
    return (this->_members[i]->getfd());
}

void Channel::sendToMembers(std::string message, int fd)
{
    int x = this->_members.size();
    for (int i = 0; i < x; i++)
    {
        if (this->_members[i]->getauthentification() == 1 && this->_members[i]->getfd() != fd)
            send(this->_members[i]->getfd(), message.c_str(), message.size(), 0);
    }
}

void Channel::setop(Client *member)
{
    this->_operators.push_back(member->getfd());
    this->_op = true;
    this->_i = true;
    this->_k = true;
    this->_l = true;
    this->_t = true;
}

void Channel::invite_or_not(std::string invite)
{
    if (invite == "+i")
        this->_i = true;
    else if (invite == "-i")
        this->_i = false;
}

std::string Channel::getinvite()
{
    if (this->_i == true)
        return ("+i");
    return ("-i");
}

bool Channel::isop(Client *member)
{
    for (size_t i = 0; i < this->_operators.size(); i++)
    {
        if (this->_operators[i] == member->getfd())
            return (true);
    }
    return (false);
}

void Channel::set_topic_or_not(std::string topic)
{
    if (topic == "+t")
        this->_t = true;
    else if (topic == "-t")
        this->_t = false;
}

std::string Channel::addoperator(std::string user)
{
    for (size_t i = 0; i < this->_members.size(); i++)
    {
        if (this->_members[i]->getnickname() == user)
        {
            this->_operators.push_back(this->_members[i]->getfd());
            setop(this->_members[i]);
            return ("Good : " + user + " is now an operator\n");
        }
    }
    return ("Error : " + user + " is not in the channel\n");
}

std::string Channel::removeoperator(std::string user)
{
    for (size_t i = 0; i < this->_members.size(); i++)
    {
        if (this->_members[i]->getnickname() == user)
        {
            for (size_t j = 0; j < this->_operators.size(); j++)
            {
                if (this->_operators[j] == this->_members[i]->getfd())
                {
                    this->_operators.erase(this->_operators.begin() + j);
                    return ("Good : " + user + " is no longer an operator\n");
                }
            }
            return ("Error : " + user + " is not an operator\n");
        }
    }
    return ("Error : " + user + " is not in the channel\n");
}

void Channel::setlimit(std::string limit)
{
    if (limit == "0")
    {
        this->_l = false;
        this->limit_channel = 4;
    }
    else
        {this->_l = true;
        this->limit_channel = std::stoi(limit);}
}

int Channel::getlimit()
{
    return (this->limit_channel);
}

void Channel::set_key(std::string key)
{
    if (key == "")
        this->_k = false;
    else
        this->_k = true;
    this->_password = key;
}

std::string Channel::get_key()
{
    return (this->_password);
}

bool Channel::get_t()
{
    return (this->_t);
}

// Path: srcs/client.cpp