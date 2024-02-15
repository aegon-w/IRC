/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 04:17:51 by kali              #+#    #+#             */
/*   Updated: 2024/01/28 07:50:18 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/header.hpp"

int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cerr << "Check your args!" << std::endl;
        exit(1);
    }
    Server server = Server(av);

    server.run();
    return (0);
}