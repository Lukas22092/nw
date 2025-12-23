#include "hypixel_connection.hpp"


int main() {
        net::io_context ioc;
        hypixel_connection conn(ioc);
        conn.connect();
        conn.fetch_auctions();
        conn.fetch_bazaar();
    }
