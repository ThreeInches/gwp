#include <thread>
#include "cloud_backup.hpp"

void thr_http_server()
{
    Server srv;
    srv.Start();
    return;
}
void non_compress_hot()
{
    NonHotCompress ncm;
    ncm.Start();
    return;
}

int main()
{
    if(boost::filesystem::exists(GZFILE_DIR) == false)
    {
        boost::filesystem::create_directory(GZFILE_DIR);
    }
    if(boost::filesystem::exists(BACKUP_DIR) == false)
    {
        boost::filesystem::create_directory(BACKUP_DIR);
    }

    std::thread thr_server(thr_http_server);
    std::thread thr_compress(non_compress_hot);
    thr_server.join();
    thr_compress.join();
    return 0;
}
