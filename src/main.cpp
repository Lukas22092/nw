#include "hypixel_connection.hpp"
#include <filesystem>




int main() {
    
        net::io_context ioc;
        hypixel_connection conn(ioc);

        conn.connect();
        conn.fetch_auctions();
        auto bazaar = conn.fetch_bazaar();

        auto res = json::parse(bazaar).as_object();
        
        auto vec = conn.get_all_orders(res);

        
        for(const auto& n : vec){
            std::cout << n.id << ": " << n.best_buy_price << "  " << n.best_sell_price  <<  "  " << n.best_buy_price/n.best_sell_price<< "\n";
        }
        
        for (const auto & entry : std::filesystem::directory_iterator(conn.item_folder_path))
    {
        std::cout << entry << std::endl;}
    }
    