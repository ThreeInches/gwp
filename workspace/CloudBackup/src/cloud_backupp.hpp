#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <zlib.h>
#include <pthread.h>
#include <boost/filesystem.hpp>
#include "httplib.h"

using namespace std;
using namespace httplib;
namespace CloudBackupSys
{
    class FileUtil
    {
    public:
        //从文件中读取内容
        static bool Read(const string& name, string* body)
        {
            ifstream fs(name, ios::binary);
            if(fs.is_open() == false)
            {
                cout << "open file " << name << "failed" << endl;
                return false;
            }
            //获取文件大小
            int64_t fsize  = boost::filesystem::file_size(name);
            body->resize(fsize);
            fs.read(&(*body)[0], fsize);
            if(fs.good() == false)
            {
                cout << "file " << name << " read data failed!" << endl;
                return false;
            }
            fs.close();
            return true;
        }
        //向文件中写入数据
        static bool Write(const string& name, const string& body)
        {
            ofstream ofs(name, ios::binary);
            if(ofs.is_open() == false)
            {
                cout << "open file " << name << "failed!" << endl;
                return false;
            }
            ofs.write(&body[0], body.size());
            if(ofs.good() == false)
            {
                cout << "file " << name << " write data failed!" << endl;
                return false;
            }
            ofs.close();
            return true;
        }
    };

    class CompressUtil
    {
    public:
        //文件压缩
        static bool Compress(const string& src, const string& dst)
        {
            string body;
            FileUtil::Read(src, &body);

            gzFile gf = gzopen(dst.c_str(), "wb");
            if(gf == NULL)
            {
                cout << "open file " << dst << "failed!" << endl;
                return false;
            }
            //防止数据一次没有被压缩完
            int write_size = 0;
            while(write_size < body.size())
            {
                int ret = gzwrite(gf, &body[write_size], body.size() - write_size);
                if(ret < 0)
                {
                    cout << "file " <<  dst << "write copress data failed!" <<endl;
                    return false;
                }
                write_size += ret;
            }
            gzclose(gf);
            return true;
        }
        //文件解压缩
        static bool UnCompress(const string& src, const string& dst)
        {
            ofstream ofs(dst, ios::binary);
            if(ofs.is_open() == false)
            {
                cout << "open file " << dst << " failed!" << endl;
                return false;
            }
            
            gzFile gf = gzopen(src.c_str(), "rb");
            if(gf == NULL)
            {
                cout << "open file " << src << " failed!" << endl;
                ofs.close();
                return false;
            }

            char tmp[1024 *4] = { 0 };
            //返回实际读取到的解压后的数据大小
            int ret = gzread(gf, tmp, 4096);
            while(ret > 0)
            {
                ofs.write(tmp, ret);
            }
            ofs.close();
            gzclose(gf);
            return true;
        }
    };
/*
    class DataManager
    {
    public:
        //判断文件是否存在
        bool Exists(const string& name);
        //判断文件是否被压缩
        bool IsCompressed(const string& name);
        //获取未压缩文件列表
        bool NonCompressedList(vector<string>* list);
        //插入/更新数据
        bool Insert(const string& src, const string& dst);
        //获取所有文件名称
        bool GetAllName(vector<string>* list);
        //数据改变后持续化存储
        bool Storage();
        //重新启动时初始化加载原有数据
        bool InitLoad();

    private:
        string m_back_file;
        unordered_map<string, string> m_file_list;
        pthread_rwlock_t m_rwlock;
    };

    class NonHotCompress
    {
    public:
        bool Start();
    private:
        bool IsHotFile(const string& name);
    private:
        string m_gz_dir;//压缩文件的存储路径
    };

    class Server
    {
        //启动网络通信模块
        bool Start();
    private:
        //文件上传处理回调函数
        static void FileUpLoad(const httplib::Request& req, httplib::Response& resp);
        //文件列表处理回调函数
        static void List(const httplib::Request& req, httplib::Response& resp);
        //文件下载处理回调函数
        static void Download(const httplib::Request& req, httplib::Response& resp);
    private:
        string m_file_dir;
        httplib::Server m_server; 
    };
*/
}

