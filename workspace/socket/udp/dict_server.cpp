#include "udp_server.hpp"
#include <iostream>
#include <unordered_map>

unordered_map<string, string> g_dict;

void Translate(const string& request, string* resp)
{
    auto it = g_dict.find(request);
    if(it == g_dict.end())
    {
        *resp = "not find!\n";
        return ;
    }

    *resp = it->second;
}

int main(int argc, char* argv[])
{
   if(argc != 3)
   {
       cout << "example:" << "192.168.30.141 9000" << endl;
       return 1;
   }

   g_dict.insert(make_pair("苹果", "apple"));
   g_dict.insert(make_pair("香蕉", "banana"));
   g_dict.insert(make_pair("橘子", "orange"));
   g_dict.insert(make_pair("榴莲", "durian"));
   g_dict.insert(make_pair("葡萄", "grapes"));
   g_dict.insert(make_pair("火龙果", "pitaya"));
    
   UdpServer server;
   server.Start(argv[1], atoi(argv[2]), Translate);
   return 0;
}
