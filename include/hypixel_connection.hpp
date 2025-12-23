#ifndef HYPIXEL_CONNECTION_HPP
#define HYPIXEL_CONNECTION_HPP

#include "connection.hpp"
#include <map>
#include <tuple>
#include <fstream>


struct item_statistics {
    std::string id;
    double crafting_cost = 0;
    double best_buy_price;
    double best_sell_price;
};

class hypixel_connection : public https_connection{
    private:
    const std::string host = "api.hypixel.net";
    const std::string port = "443";
    std::vector<item_statistics> all_orders;
    std::map<std::string, boost::json::object> item_recipes;

    public:
    std::string item_folder_path = "/Users/lukas/Desktop/proj/items";
    //constructor inheritance -> a alternative way would be to use a constructor
    //with an initializer list
    using https_connection::https_connection;
    void connect();        
    void fetch_auctions();   
    std::string fetch_bazaar();
    std::vector<item_statistics> get_all_orders(boost::json::object& json_obj);
    std::unordered_map<std::string, boost::json::object> get_item_recipes();
};



#endif