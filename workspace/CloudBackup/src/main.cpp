#include "cloud_backupp.hpp"

int main(int argc, char* argv[])
{
    CloudBackupSys::CompressUtil::Compress(argv[1], argv[2]);
    string file = argv[2];
    file += ".txt";
    CloudBackupSys::CompressUtil::UnCompress(argv[2], file.c_str());
    return 0;
}
