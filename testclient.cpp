#define ASIO_STANDALONE

#include<iostream>
#include<cstring>
#include"asio.hpp"
int des[]={36,37,38,39,40,41,42,43,61};

using namespace asio;
using namespace ip;
int main(){
    io_context ioc;
    udp::socket my_socket(ioc,udp::endpoint(udp::v4(),2333));

    std::string in;
    error_code ec;
    while(true){
        std::getline(std::cin,in);
        for(int i = 1;i<=64;++i){
            my_socket.connect(udp::endpoint(address_v4::from_string("10.0.2."+std::to_string(i)),6666),ec);
            if(!ec) my_socket.send_to(buffer(in,in.length()),udp::endpoint(address_v4::from_string("10.0.2."+std::to_string(i)),6666));
            else    std::cout<<i<<":"<<ec<<std::endl;
        }
    }
    return 0;
}