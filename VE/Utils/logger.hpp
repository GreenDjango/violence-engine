/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Syslog
*/

#ifndef SYSLOG_HPP_
#define SYSLOG_HPP_

#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>

namespace ve {

enum logLevel {
    CRITICAL,
    WARNING,
    NOTICE,
    DEBUG
};

void syslog(logLevel loglevel, std::string const &module, std::string const &message) {
#ifdef NDEBUG
    if (loglevel == logLevel::NOTICE || loglevel == logLevel::DEBUG)
        return;
#endif
    auto time = std::time(nullptr);

    std::cout << std::put_time(std::localtime(&time), "\033[0;32m[%T]\033[0m ")
              << "\033[0;35m" << module << ":\033[0m ";

    if (loglevel == logLevel::CRITICAL)
        std::cout << "\033[1;31m";
    if (loglevel == logLevel::WARNING)
        std::cout << "\033[1;33m";
    if (loglevel == logLevel::NOTICE)
        std::cout << "\033[1m";
    if (loglevel == logLevel::DEBUG)
        std::cout << "\033[90m";
    std::cout << message << "\033[0m\n";
}

} // namespace ve

#endif /* !SYSLOG_HPP_ */
