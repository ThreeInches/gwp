#include <thread>
#include "cloud_backupp.hpp"

void compress_test(char* argv[])
{
    CloudBackupSys::CompressUtil::Compress(argv[1], argv[2]);
    string file = argv[2];
    file += ".txt";
    CloudBackupSys::CompressUtil::UnCompress(argv[2], file.c_str());
}

void datamanger_test()
{
    CloudBackupSys::DataManager data_manger("./test.txt");
    data_manger.InitLoad();
    vector<string> list;
    data_manger.Insert("a.txt", "a.txt.gz");
    data_manger.GetAllName(&list);
    for(auto& e : list)
    {
        printf("[%s]\n", e.c_str());
    }
    list.clear();
    data_manger.NonCompressedList(&list);
    for(auto& e : list)
    {
        printf("[%s]\n", e.c_str());
    }
    /*
    data_manger.Insert("a.txt", "a.txt");
    data_manger.Insert("b.txt", "b.txt.gz");
    data_manger.Insert("c.txt", "c.txt");
    data_manger.Insert("d.txt", "d.txt.gz");
    data_manger.Storage();
    */
}

void non_compress()
{
    CloudBackupSys::NonHotCompress nhc(BACKUP_DIR, GZFILE_DIR);
    nhc.Start();
    return;
}

void thr_http_server()
{
    CloudBackupSys::Server src;
    src.Start();
    return;
}

int main(int argc, char* argv[])
{
    //compress_test(argv);
    //datamanger_test();
    //判断文件备份路径是否存在  不存在则创建
    if(boost::filesystem::exists(GZFILE_DIR) == false)
    {
        boost::filesystem::create_directory(GZFILE_DIR);
    }
    //判断压缩包存放路径是否存在，不存在则创建
    if(boost::filesystem::exists(BACKUP_DIR) == false)
    {
        boost::filesystem::create_directory(BACKUP_DIR);
    }
    thread thr_compress(non_compress);
    thread thr_server(thr_http_server);

    thr_compress.join();
    thr_server.join();
    return 0;
}
