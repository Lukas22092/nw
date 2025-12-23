
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

std::vector<item_statistics> hypixel_connection::get_all_orders(boost::json::object& json_obj) {
    auto const& products = json_obj["products"].as_object();
    std::vector<item_statistics> res;
    res.reserve(products.size()); 

    for (auto const& field : products) {
        auto const& product_data = field.value().as_object();
        item_statistics stats;
        stats.id = field.key();

        auto const& sell_sum = product_data.at("sell_summary").as_array();
        if (!sell_sum.empty()) {
            stats.best_sell_price = sell_sum.at(0).as_object().at("pricePerUnit").to_number<double>();
        } else {
            stats.best_sell_price = 0.0;
        }
        auto const& buy_sum = product_data.at("buy_summary").as_array();
        if (!buy_sum.empty()) {
            stats.best_buy_price = buy_sum.at(0).as_object().at("pricePerUnit").to_number<double>();
        } else {
            stats.best_buy_price = 0.0;
        }

        res.push_back(stats);
    }
    return res;
}
std::unordered_map<std::string, boost::json::object> hypixel_connection::get_item_recipes()
{       
    std::ifstream input_filestream;
    for (const auto & entry : std::filesystem::directory_iterator(item_folder_path))
    {
        std::string temp;

        //use a stringbuffer here to store the whole lines in a string.
        //after storing it in a string, we can convert it to a json object.
        //the name of the recipe can be the first element of the map, the 
        //recipe will be the 2nd element of the map.
        input_filestream.open(entry.path().string()); //open the file 
        while(getline(input_filestream, temp))
        { 

        }


        std::cout << entry << std::endl;}

    }
    


