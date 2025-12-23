
#include "hypixel_connection.hpp"

void hypixel_connection::connect() {
    if(!SSL_set_tlsext_host_name(stream_.native_handle(), host.c_str())) {
        throw beast::system_error(beast::error_code(static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()));
    }

    // connect to the underlaying tcp stream. the stream is stored in the parent class
    auto const results = resolver_.resolve(host, port);
    beast::get_lowest_layer(stream_).connect(results);
    
    //ssL andshake
    stream_.handshake(ssl::stream_base::client);
}

void hypixel_connection::fetch_auctions() {
    // We assume connect() was already called
    http::request<http::string_body> req{http::verb::get, "/v2/skyblock/auctions", 11};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, "BoostBeastClient/1.0");

    http::write(stream_, req);

    beast::flat_buffer buffer;
    http::response<http::dynamic_body> res;
    http::read(stream_, buffer, res);

    std::cout << "Auctions received!" << std::endl;
}

std::string hypixel_connection::fetch_bazaar() {
    // using the open stream to send another request
    http::request<http::string_body> req{http::verb::get, "/v2/skyblock/bazaar", 11};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, "BoostBeastClient/1.0");

    http::write(stream_, req);

    beast::flat_buffer buffer;
    http::response<http::string_body> res;  
    http::read(stream_, buffer, res);

   return res.body();
}