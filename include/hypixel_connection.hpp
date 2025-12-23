#ifndef HYPIXEL_CONNECTION_HPP
#define HYPIXEL_CONNECTION_HPP

#include "connection.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/json/src.hpp>
#include <map>
#include <tuple>

struct item_statisics{
    std::string item_name;
    std::tuple<int,int64_t> buy_order_price_amount;
    std::tuple<int,int64_t> sell_order_price_amount;
};


class hypixel_connection : public https_connection{
    private:
    const std::string host = "api.hypixel.net";
    const std::string port = "443";
    std::vector<item_statisics> all_orders;

    public:
    //constructor inheritance -> a alternative way would be to use a constructor
    //with an initializer list
    using https_connection::https_connection;
    void connect();        
    void fetch_auctions();   
    std::string fetch_bazaar();
    std::vector<item_statisics> get_all_orders(boost::json::object& json_obj);
    const std::vector<item_statisics> get_all_orders() const;
};

#endif