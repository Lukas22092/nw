#if !defined(INCLUDED_NW_CONNECTION_HPP)
#define INCLUDED_NW_CONNECTION_HPP

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/dynamic_body.hpp>
#include <boost/asio/ssl.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error = beast::http::error;

struct ServiceParameters {
  std::string host =  "api.hypixel.net";;
  const char *service = "443"; // HTTPS Standard
  const char* target = "/v2/skyblock/auctions";

};

class Connection {
private:

  http::response<http::dynamic_body> res;
  ServiceParameters params;
  boost::asio::io_context &ctx;
  tcp::resolver resolver; // resolve the request
  beast::tcp_stream stream;
public:
  explicit Connection(net::io_context &ctx);

  void resolve_and_connect();

  void send_request();
};

#endif /* !defined(INCLUDED_NW_CONNECTION_HPP) */
