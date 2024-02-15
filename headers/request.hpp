/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:07:20 by kali              #+#    #+#             */
/*   Updated: 2024/01/16 18:54:58 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <iostream>
# include <string>
# include <vector>

class Request
{
    public:
        std::vector<std::string> arguments;
        std::string method;
        int status;

        Request();
        ~Request();
        Request(Request const &src);
        Request &operator=(Request const &rhs);
} ;

#endif