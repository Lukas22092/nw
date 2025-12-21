#if !defined(INCLUDED_NW_CONNECTION_HPP)
#define INCLUDED_NW_CONNECTION_HPP

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

struct ServiceParameters {
  std::string host;
  const char *service;
};

class Connection {
private:
  ServiceParameters params;
  boost::asio::io_context &ctx;
  tcp::resolver resolver; // resolve the request
  websocket::stream<tcp::socket> stream;

public:
  explicit Connection(net::io_context &ctx);

  auto const resolve_and_connect();
};

#endif /* !defined(INCLUDED_NW_CONNECTION_HPP) */
