#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/json.hpp>
#include <iostream>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = net::ssl;
using tcp = net::ip::tcp;
namespace json = boost::json;

class https_connection {
protected:
  ssl::context ctx_;
  tcp::resolver resolver_;
  beast::ssl_stream<beast::tcp_stream> stream_; // wrap the raw bytes in a ssl stream so it is secure
  

public:
  https_connection(net::io_context &ioc);
  ~https_connection();
};

#endif
