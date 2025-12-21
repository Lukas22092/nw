#include "connection.hpp"

Connection::Connection(boost::asio::io_context &ioc)
    : ctx(ioc), resolver(ioc), stream(ioc) {}

auto const Connection::resolve() {
  try {
    return resolver.resolve(params.host, params.service);
  } catch (const boost::system::system_error &e) {
    std::cerr << "error while connecting occured\n";
  }
}

int main() {
  net::io_context ioc;
  Connection conn{ioc};
  return 0;
}
