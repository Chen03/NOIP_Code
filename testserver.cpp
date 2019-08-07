#define ASIO_STANDALONE

#include<iostream>
#include<unordered_map>
#include"asio.hpp"

using namespace asio;
using namespace ip;
std::array<char,10000> in;
std::unordered_map<int,std::string> names;

void init_name(){
    names[36]="lon";
    names[37]="chen";
    names[38]="÷”÷æ¡÷";
    names[39]="milk_candy";
    names[61]="kjy";
}

int main(){
    init_name();
    io_context ioc;
    udp::endpoint remote_endpoint;
    udp::socket socket(ioc,udp::endpoint(udp::v4(),6666));

    std::size_t length;
    address adr;
    short sad;
    bool same=false;
    while(true){
        length = socket.receive_from(buffer(in,in.size()),remote_endpoint);
        same=adr==remote_endpoint.address();
        adr=remote_endpoint.address();
        sad=atoi(adr.to_string().substr(7,2).c_str());
        // if(!same)   std::cout<<adr.to_string()<<":"<<std::endl;
        if(!same){
            std::cout<<std::endl;
            if(names.find(sad)!=names.end())    std::cout<<names[sad]<<":"<<std::endl;
            else std::cout<<adr.to_string()<<":"<<std::endl;
        }
        std::cout.write(in.data(),length);
        std::cout<<std::endl;
    }
    return 0;
}