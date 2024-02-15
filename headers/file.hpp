/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:05:10 by kali              #+#    #+#             */
/*   Updated: 2024/02/08 13:38:37 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HPP
# define FILE_HPP

# include "server.hpp"

class File
{
    private:
        std::string _name;
        std::string _path;
        std::string _sender;
        std::string _receiver;

    public:
        File();
        File(std::string name, std::string path, std::string sender, std::string receiver);
        ~File();
        File(const File &other);
        File &operator=(const File &other);
        std::string getName() const;
        std::string getPath() const;
        std::string getreceiver() const;

};

#endif