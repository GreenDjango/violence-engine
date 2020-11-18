/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** NetworkManager
*/

#ifndef NETWORKMANAGER_HPP_
#define NETWORKMANAGER_HPP_
/*
#include "VE/Utils/logger.hpp"
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <stdarg.h>

namespace ve {

namespace ba = boost::asio;

using Reader = boost::function<void()>;
using Writer = boost::function<void(std::string const &)>;

template <typename Socket, typename Resolver, typename Results_type, typename Endpoint>
class Link {

public:
    Link(Reader &&onRead, Writer &&onWrite)
        : _context{}, _resolv{ _context }, _onRead{ onRead }, _onWrite{ onWrite } {}

    bool isConnected() const { return (_socket && _socket->is_open()); }

    std::shared_ptr<Socket> getSocket() { return _socket; };

    void reconnect(std::string const &host, std::string const &port) {
        syslog(NOTICE, "Network", "Try to find " + host + "::" + port);
        if (isConnected())
            disconnect("Stop actual connexion, and start a new one.");
        if (_thread)
            _thread->join();
        _context.reset();
        _resolv = Resolver{ _context };
        _socket.reset(new Socket(_context));
        resolve(host, port);
        _thread.reset(new boost::thread(boost::bind(&ba::io_service::run, &_context)));
        boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
    }

    void disconnect(std::string const &msg = "") {
        if (msg.empty())
            syslog(NOTICE, "Network", "Server disconnected");
        else
            syslog(WARNING, "Network", "Disconnected: " + msg);
        if (_socket && _socket->is_open()) {
            try {
                _socket->close();
            } catch (const std::exception &e) {
                syslog(WARNING, "Network", e.what());
            }
        }
    }

    void write(const std::string &msg) { _onWrite(msg); }

private:
    void resolve(std::string const &host, std::string const &port) {
        _resolv.async_resolve(host, port,
                              [&](boost::system::error_code err, Results_type res) {
                                  if (!err)
                                      connect(res);
                                  else
                                      disconnect("Resolve hostname fail: " + err.message());
                              });
    }

    void connect(Results_type res) {
        ba::async_connect(*_socket, res,
                          [&](boost::system::error_code err, Endpoint const &) {
                              if (!err) {
                                  syslog(NOTICE, "Network", "Server connected");
                                  _onRead();
                              } else
                                  disconnect("Connect fail: " + err.message());
                          });
    }

    ba::streambuf _answer;
    ba::io_context _context;
    Resolver _resolv;
    std::shared_ptr<Socket> _socket;
    std::unique_ptr<boost::thread> _thread;
    Reader _onRead;
    Writer _onWrite;
};

using LinkTcp = Link<ba::ip::tcp::socket, ba::ip::tcp::resolver, ba::ip::tcp::resolver::results_type, ba::ip::tcp::endpoint>;
using LinkUdp = Link<ba::ip::udp::socket, ba::ip::udp::resolver, ba::ip::udp::resolver::results_type, ba::ip::udp::endpoint>;

} // namespace ve
*/
#endif /* !NETWORKMANAGER_HPP_ */