#include "connection.hpp"

Connection::Connection(boost::asio::io_context &ioc)
    : ctx(ioc), resolver(ioc), stream(ioc) {}


void Connection::resolve_and_connect() {
    try 
    {
        const auto result = resolver.resolve(params.host, params.service);
        stream.connect(result);
    } 
    catch (const boost::system::system_error &e) {
        if (e.code() == boost::asio::error::host_not_found) {
            throw std::runtime_error("Custom Error: Host not found");
        }
        std::cerr << "Failure: " << e.what() << "\n";
        throw; // This rethrows the current exception "e"
    }
}
void Connection::send_request(){        
    
    try{
        http::request<http::string_body> req{http::verb::get, params.target, 11}; //verison 11 is standard
        req.set(http::field::host, params.host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        http::write(stream, req);
        beast::flat_buffer buffer; //used for reading
        http::read(stream, buffer, res);
        std::cout << res << std::endl;
        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);

       if(ec && ec != beast::errc::not_connected)
            throw beast::system_error{ec};


    }
    catch(boost::system::system_error  &e){
        if(e.code() == error::header_field_value_too_large){
            throw std::runtime_error("too much data");
        }
    }

}

