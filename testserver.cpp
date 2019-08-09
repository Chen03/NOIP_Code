#define ASIO_STANDALONE

#include<iostream>
#include<ctime>
#include<unordered_map>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<winsock2.h>
#include<windows.h>
#include"asio.hpp"

using namespace asio;
using namespace ip;
std::array<char,10000> in;
// std::unordered_map<int,std::string> names;
std::string names[100];
HWND thishWnd;
FLASHWINFO info;

void init(){
    names[36]="lon";
    names[37]="chen";
    names[38]="÷”÷æ¡÷";
    names[39]="milk_candy";
    names[61]="kjy";

    TCHAR title[20]="Server Alpha_0.3";
    SetConsoleTitle(title);
    Sleep(40);
    thishWnd=FindWindow(NULL,title);
    info.cbSize = sizeof(info);
    info.hwnd = thishWnd;
    info.dwFlags= FLASHW_ALL;
    info.uCount = 1;
    info.dwTimeout = 1000;


}

void flash(){
    FlashWindowEx(&info);
}

std::ofstream opfile;

void save(){
    std::cout<<"Saving chat history...";
    opfile.close();
}

int main(){
    atexit(save);
    init();
    io_context ioc;
    udp::endpoint remote_endpoint;
    udp::socket socket(ioc,udp::endpoint(udp::v4(),6666));

    //get host ip
    short lcsad=0;
    std::string ipad;
    udp::resolver resolver(ioc);
    udp::resolver::iterator iter = resolver.resolve(udp::v4(),host_name(),"");
    udp::endpoint ep = *iter;
    ipad=((udp::endpoint)(*iter)).address().to_string();
    lcsad=(ipad[ipad.size()-2]-'0')*10+ipad[ipad.size()-1]-'0';
    
    std::time_t t = std::time(nullptr);
    std::tm *tim =std::localtime(&t);
    std::string time=std::to_string(tim->tm_year)+"_"+std::to_string(tim->tm_mon+1)+"_"+std::to_string(tim->tm_mday)+"_"+std::to_string(tim->tm_hour)+"_"+std::to_string(tim->tm_min)+"_"+std::to_string(tim->tm_sec);
    std::cout<<time<<std::endl;
    opfile.open("chat_history.txt",std::ios::in|std::ios::app);
    if(!opfile) std::cerr<<"Fail to open history.";
    opfile<<time<<std::endl<<std::endl;

    std::size_t length;
    address adr;
    short sad;
    std::stringstream outflow;
    std::string outl;
    bool same=false,req=false;
    while(true){
        length = socket.receive_from(buffer(in,in.size()),remote_endpoint);
        same=adr==remote_endpoint.address();
        adr=remote_endpoint.address();
        sad=atoi(adr.to_string().substr(7,2).c_str());

        //Online request
        if(in[0]=='#'){
            req=true;
            std::istringstream input(std::string(in.data(),length));
            std::string inf,val;
            input.ignore(1);
            input>>inf;
            if(inf=="ON"){
                while(input.good()){
                    val.clear();
                    input>>inf;input>>val;
                    if(inf=="NC"){
                        if(val!="#DEF") names[sad]=val;
                    }
                }
                if(names[sad].size())    outflow<<names[sad];
                else    outflow<<adr.to_string();
                outflow<<" is online.";
                same=false;
            }else if(inf=="OFF"){
                while(input.good()){
                    input>>inf;input>>val;
                }
                if(names[sad].size())    outflow<<names[sad];
                else    outflow<<adr.to_string();
                outflow<<" is offline.";
            }else req=false;
        }

        if(req){
            req=false;
        }else{
            //Write message
            //print name&ip address
            if(!same){
                outflow<<std::endl;
                if(names[sad].size())    outflow<<names[sad]<<"("<<sad<<")";
                else    outflow<<adr.to_string();
                outflow<<":"<<std::endl;
            }

            std::string sent(in.data(),length);
            //@ condition
            for(int i=0;i<sent.size();++i){
                if(sent[i]=='@'&&isdigit(sent[i+1])&&isdigit(sent[i+2])){
                    short tsad=(sent[i+1]-'0')*10+sent[i+2]-'0';
                    if(names[tsad].size()){
                        sent=sent.substr(0,i)+"@"+names[tsad]+sent.substr(i+3,sent.size()-3);
                        // outflow.write(tmp.c_str(),tmp.size());
                        // length=0;
                        i+=2;
                    }
                    if(tsad==lcsad){
                        flash();
                    }
                }
            }

            outflow.write(sent.c_str(),sent.length());
        }
        
        while(outflow.good()){
            getline(outflow,outl);
            std::cout<<outl<<std::endl;
            opfile<<outl<<std::endl;
        }
        outflow.clear();
    }
    return 0;
}
