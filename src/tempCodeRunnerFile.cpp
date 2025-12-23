#include "hypixel_connection.hpp"

int main() {
        net::io_context ioc;
        hypixel_connection conn(ioc);

        conn.connect();
        conn.fetch_auctions();
        auto bazaar = conn.fetch_bazaar();

        auto res = json::parse(bazaar).as_object();
        
        auto vec = conn.get_all_orders(res);

    
    }
    
