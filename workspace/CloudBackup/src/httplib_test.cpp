#include <iostream>
#include "httplib.h"

using namespace std;

void helloworld(const httplib::Request& req, httplib::Response& rsp)
{
    //rsp中的信息
    //rsp.status状态码  rsp.headers头部信息  rsp.body正文
    //rsp.set_header(const char* key, const char* val)
    //rsp.body/rsp.set_content(const char* s, size_t n, const char* content_type)
    cout << "method" << req.method << endl;
    cout << "path" << req.path << endl;
    cout << "body" << req.body << endl;

    rsp.status = 200;
    rsp.body = "<html><body><h1>Hello, World!</h1></body></html>";
    rsp.set_header("Content-Type", "text/html");
    rsp.set_header("Content-Length", to_string(rsp.body.size()));
    return;
}

int main()
{
    httplib::Server server;
    server.Get("/", helloworld);

    server.listen("0.0.0.0", 9000);
    return 0;
}
