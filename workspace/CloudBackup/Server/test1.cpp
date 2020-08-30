#include <iostream>
#include "httplib.h"

void helloworld(const httplib::Request& req, httplib::Response& rsp)
{
    std::cout << "method" << req.method << std::endl;
    std::cout << "path" << req.path << std::endl;
    std::cout << "body" << req.body << std::endl;

    rsp.status = 200;
    rsp.body = "<hetml><body>Hello,World<br></body></html>";
    rsp.set_header("Content-Type", "text/html");
    rsp.set_header("Content-Length", std::to_string(rsp.body.size()));
}

int main()
{
    httplib::Server srv;
    srv.Get("/", helloworld);
    
    srv.listen("0.0.0.0", 9000);
    return 0;
}
