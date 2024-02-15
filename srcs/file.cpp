/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:33:55 by kali              #+#    #+#             */
/*   Updated: 2024/02/08 13:41:02 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/file.hpp"

File::File()
{
}
File::File(std::string name, std::string path, std::string sender, std::string receiver)
{
    this->_name = name;
    this->_path = path;
    this->_sender = sender;
    this->_receiver = receiver;
}

File::~File()
{
}

File::File(const File &other)
{
    *this = other;
}

File &File::operator=(const File &other)
{
    if (this != &other)
    {
        this->_name = other._name;
        this->_path = other._path;
        this->_sender = other._sender;
        this->_receiver = other._receiver;
    }
    return (*this);
}

std::string File::getName() const
{
    return (this->_name);
}

std::string File::getPath() const
{
    return (this->_path);
}

std::string File::getreceiver() const
{
    return (this->_receiver);
}