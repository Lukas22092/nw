#ifndef HYPIXEL_CONNECTION_HPP
#define HYPIXEL_CONNECTION_HPP

#include "connection.hpp"
#include <map>
#include <tuple>

struct item_statistics {
    std::string id;
    double best_buy_price;
    double best_sell_price;
};

class hypixel_connection : public https_connection{
    private:
    const std::string host = "api.hypixel.net";
    const std::string port = "443";
    std::vector<item_statistics> all_orders;

    public:
    //constructor inheritance -> a alternative way would be to use a constructor
    //with an initializer list
    using https_connection::https_connection;
    void connect();        
    void fetch_auctions();   
    std::string fetch_bazaar();
    std::vector<item_statistics> get_all_orders(boost::json::object& json_obj);
};

#endif