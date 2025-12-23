#include "hypixel_connection.hpp"




namespace json = boost::json;





int main() {
        net::io_context ioc;
        hypixel_connection conn(ioc);

        conn.connect();
        conn.fetch_auctions();
        auto bazaar = conn.fetch_bazaar();

        auto res = json::parse(bazaar).as_object();
        
        auto const& products = res["products"].as_object();

        for (auto const& field : products) {
            auto const& product_data = field.value().as_object();

            // 2. Get the "buy_summary" array
            auto const& buy_summary = product_data.at("buy_summary").as_array();
            auto const& sell_summary = product_data.at("sell_summary").as_array();

            std::cout << "Product: " << field.key() << "\n";

            for (auto const& order_val : sell_summary) {
                auto const& order = order_val.as_object();

                double price = order.at("pricePerUnit").as_double();
                int64_t amount = order.at("amount").as_int64();
            std::cout << "  - sell Price: " << price << " | Amount: " << amount << "\n";
            }

            std::cout << "--------------------------\n";
        


            for (auto const& order_val : buy_summary) {
                auto const& order = order_val.as_object();
                
                double price = order.at("pricePerUnit").as_double();
                int64_t amount = order.at("amount").as_int64();
                
                std::cout << "  - buy Price: " << price << " | Amount: " << amount << "\n";
            }

            std::cout << "--------------------------\n";
        }
    }
    
