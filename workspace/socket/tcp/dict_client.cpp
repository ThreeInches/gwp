#include "tcp_client.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        cout << "example" << "192.168.30.141 9000" << endl;
        return -1;
    }

    TcpClient client(argv[1], atoi(argv[2]));
    bool ret = client.Connect();
    if(!ret)
    {
        perror("connect error");
        return -1;
    }
    while(1)
    {
        string word;
        cout << "Please enter the word you want to query:" << endl;
        cin >> word;

        client.Send(word);
        
        string result;
        client.Recv(&result);

        cout << word << " translation: " << result << endl;
    }
    return 0;
}
