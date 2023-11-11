#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <memory>
#include <string>


namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;

using tcp = net::ip::tcp;


class Listener
{
    net::io_context& ioc;
    tcp::acceptor acceptor;
    public:
        Listener(net::io_context& ioc,
        unsigned short int port):ioc(ioc),
        acceptor(ioc,{net::ip::make_address("127.0.0.1"),port}){};
    void asyncAccept()
    {
        acceptor.async_accept(ioc, [&](boost::system::error_code ec,
        tcp::socket socket){

            std::cout << "conneciton accepted" << std::endl;
            asyncAccept();


        });
    }
};

int main ()
{
     const short port =  8083;
     net::io_context ioc{}; 
     std::make_shared<Listener>(ioc,port) ->asyncAccept();
     ioc.run();  
    return 0 ;
}