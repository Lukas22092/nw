#include "connection.hpp"

Connection::Connection(boost::asio::io_context &ioc)
    : ctx(ioc), resolver(ioc), stream(ioc) {}

const auto Connection::resolve_and_connect() {
    try 
    {
        const auto result = resolver.resolve(params.host, params.service);
        auto ep = net::connect(stream.next_layer(), result); //entpoint
        params.host+= ':' + std::to_string(ep.port());

        stream.set_option(websocket::stream_base::decorator([](websocket::request_type& req)
        {
          req.set(http::field::user_agent,
            std::string(BOOST_BEAST_VERSION_STRING) + "websocket-client-coro");

        }));



        
    } 
    catch (const boost::system::system_error &e) {
        if (e.code() == boost::asio::error::host_not_found) {
            throw std::runtime_error("Custom Error: Host not found");
        }
        std::cerr << "Failure: " << e.what() << "\n";
        throw; // This rethrows the current exception "e"
    }



}




int main() {
  net::io_context ioc;
  Connection conn{ioc};
  return 0;
}
