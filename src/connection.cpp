#include "connection.hpp"

//sets up the connection for a arbatary https website.
https_connection::https_connection(net::io_context& ioc)
        : ctx_(ssl::context::tlsv12_client),
          resolver_(ioc),
          stream_(ioc, ctx_) 
    {
        ctx_.set_default_verify_paths();
        ctx_.set_verify_mode(ssl::verify_peer);
    }

//this destroctor can trow! i learned that destructors should never throw?
https_connection::~https_connection(){
    //Shutdown
    beast::error_code ec;
    stream_.shutdown(ec);
    if(ec == net::error::eof || ec == ssl::error::stream_truncated) ec = {};
    if(ec) throw beast::system_error{ec};

}