#include "connection.hpp"


int main()
{
    net::io_context ctx;

    Connection connection(ctx);
    connection.resolve_and_connect();
    connection.send_request();
}