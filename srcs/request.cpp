/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:10:50 by kali              #+#    #+#             */
/*   Updated: 2024/01/15 17:25:56 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/request.hpp"

Request::Request(): arguments(), method(), status(0)
{
}

Request::~Request()
{
}

Request::Request(Request const &src)
{
    *this = src;
}

Request &Request::operator=(Request const &rhs)
{
    if (this != &rhs)
    {
        this->arguments = rhs.arguments;
        this->method = rhs.method;
        this->status = rhs.status;
    }
    return (*this);
}