/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** PathManager
*/

#ifndef PATHMANAGER_HPP_
#define PATHMANAGER_HPP_

#include <exception>
#include <string>

#ifdef __linux__
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#elif _WIN32
#endif

namespace ve {

class PathManager {
public:
    PathManager()
        : _currentDir{ _applicationDirPath() } {}

    static std::string const &getBinaryDir() {
        static std::string currentDir = _applicationDirPath();
        return currentDir;
    }

    static std::string const getAbs(std::string const path) {
        return getBinaryDir() + path;
    }

private:
    std::string _currentDir;

    static std::string _applicationDirPath() {
#ifdef __linux__
        char buff[PATH_MAX + 1] = { '\0' };
        ssize_t len = readlink("/proc/self/exe", buff, PATH_MAX);
        if (len < 0)
            perror("readlink");
        char *pos;
        if ((pos = strrchr(buff, '/')) && *(pos + 1) != '\0') {
            *(pos + 1) = '\0';
            return std::string{ buff };
        }
        return "./";
#elif _WIN32
        throw std::exception();
        return "";
#else
        throw std::exception();
        return "";
#endif
    }
};

} // namespace ve

#endif /* !PATHMANAGER_HPP_ */
