#ifndef HYPIXEL_CONNECTION_HPP
#define HYPIXEL_CONNECTION_HPP

#include "connection.hpp"
#include <boost/lexical_cast.hpp>
class hypixel_connection : public https_connection{
    private:
    const std::string host = "api.hypixel.net";
    const std::string port = "443";

    public:
    //constructor inheritance -> a alternative way would be to use a constructor
    //with an initializer list
    using https_connection::https_connection;
    
    void connect();        
    void fetch_auctions();   
    std::string fetch_bazaar(); 
    
};

#endif