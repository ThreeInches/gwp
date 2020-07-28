#include "udp_client.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        cout << "example" << "192.168.30.141 9000" << endl;
    }

    UdpClient client(argv[1], atoi(argv[2]));
    while(1)
    {
        string word;
        cout << "Please enter the word you want to query:" << endl;
        cin >> word;

        client.SendTo(word);
        
        string result;
        client.RecvFrom(&result);

        cout << word << " translation: " << result << endl;
    }
    return 0;
}
