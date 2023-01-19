#include <iostream>

#include <asio.hpp>

asio::io_context io_context;

asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), 8080);

asio::ip::tcp::acceptor acceptor(io_context, endpoint);

typedef std::shared_ptr<asio::ip::tcp::socket> socket_ptr;
socket_ptr sock;

std::vector<char> data(100);

void do_read() {
    asio::async_read(*sock, asio::buffer(data.data(), 10), [](std::error_code ec, size_t length) {
        if (!ec) {
            printf("%s\n", data.data());

            do_read();
        } else {
            printf("%s\n", ec.message().data());
        }
    });
}

void do_accept() {
    acceptor.async_accept([](std::error_code ec, asio::ip::tcp::socket socket) {
        if (!ec) {
            printf("new connection detected\n");
            
            sock = std::make_shared<asio::ip::tcp::socket>(std::move(socket));

            do_read();

            do_accept();
        } else {
            printf("%s\n", ec.message().data());
        }
    });
}

int main() {
    std::cout << "hello world" << std::endl;
           
    do_accept();
    
    io_context.run();
    
    return 0;
}