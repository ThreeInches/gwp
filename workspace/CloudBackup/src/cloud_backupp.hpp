#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <zlib.h>
#include <pthread.h>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "httplib.h"

#define NONHOT_TIME 10//最后一次访问时间在10秒以外进行压缩存储
#define INTERVAL_TIME 30//检测间隔时间
#define BACKUP_DIR "./backup/"//文件的备份路径
#define GZFILE_DIR "./gzfile/"//压缩包的存储路径
#define DATA_FILE "./list.backup/"//数据管理模块的数据备份文件名称

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
                cout << "open file " << name << " failed" << endl;
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
                cout << "open file " << name << " failed!" << endl;
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
            while(write_size < (int)body.size())
            {
                int ret = gzwrite(gf, &body[write_size], body.size() - write_size);
                if(ret == 0)
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

            char tmp[4096] = { 0 };
            //返回实际读取到的解压后的数据大小
            int ret;
            while((ret = gzread(gf, tmp, 4096)) > 0)
            {
                ofs.write(tmp, ret);
            }
            ofs.close();
            gzclose(gf);
            return true;
        }
    };

    class DataManager
    {
    public:
        DataManager(const string& path)
            :m_back_file(path)
        {
            pthread_rwlock_init(&m_rwlock, NULL);
        }

        ~DataManager()
        {
            pthread_rwlock_destroy(&m_rwlock);
        }

    public:
        //判断文件是否存在
        bool Exists(const string& name)
        {
            pthread_rwlock_rdlock(&m_rwlock);
            auto it = m_file_list.find(name);
            if(it == m_file_list.end())
            {
                pthread_rwlock_unlock(&m_rwlock);
                return false;
            }
            pthread_rwlock_unlock(&m_rwlock);
            return true;
        }
        //判断文件是否被压缩
        bool IsCompressed(const string& name)
        {
            pthread_rwlock_rdlock(&m_rwlock);
            auto it = m_file_list.find(name);
            if(it == m_file_list.end())
            {
                pthread_rwlock_unlock(&m_rwlock);
                return false;
            }

            if(it->first == it->second)
            {
                pthread_rwlock_unlock(&m_rwlock);
                return false;
            }
            pthread_rwlock_unlock(&m_rwlock);
            return true;
        }
        //获取未压缩文件列表
        bool NonCompressedList(vector<string>* list)
        {
            pthread_rwlock_rdlock(&m_rwlock);
            for(auto it = m_file_list.begin(); it != m_file_list.end(); it++)
            {
                if(it->first == it->second)
                {
                    list->push_back(it->first);
                }
            }
            pthread_rwlock_unlock(&m_rwlock);
            return true;
        }
        //插入/更新数据
        bool Insert(const string& src, const string& dst)
        {
            pthread_rwlock_wrlock(&m_rwlock);
            m_file_list[src] = dst;
            pthread_rwlock_unlock(&m_rwlock);
            Storage();//数据更新以后持久化存储
            return true;
        }
        //获取所有文件名称
        bool GetAllName(vector<string>* list)
        {
            pthread_rwlock_rdlock(&m_rwlock);
            for(auto it = m_file_list.begin(); it != m_file_list.end(); it++)
            {
                list->push_back(it->first);
            }
            pthread_rwlock_unlock(&m_rwlock);
            return true;
        }
        //根据源文件名称获取压缩包名称
        bool GetGzName(const string& src, string* dst)
        {
            auto it = m_file_list.find(src);
            if(it == m_file_list.end())
            {
                return false;
            }
            *dst = it->second;
            return true;
        }
        //数据改变后持续化存储
        bool Storage()
        {
            //数据对象的序列化存储
            stringstream tmp;
            pthread_rwlock_rdlock(&m_rwlock);
            for(auto it = m_file_list.begin(); it != m_file_list.end(); it++)
            {
                tmp << it->first << " " << it->second << "\r\n";
            }
            pthread_rwlock_unlock(&m_rwlock);
            FileUtil::Write(m_back_file, tmp.str());
            return true;
        }
        //重新启动时初始化加载原有数据
        bool InitLoad()
        {
            string body;
            if(FileUtil::Read(m_back_file, &body) == false)
            {
                return false;
            }

            vector<string> list;
            boost::split(list, body, boost::is_any_of("\r\n"), boost::token_compress_off); 
            for(auto& i : list)
            {
                size_t pos = i.find(" ");
                if(pos == string::npos)
                {
                    continue;
                }
                string key = i.substr(0, pos);
                string value = i.substr(pos + 1);
                Insert(key, value);
            }
            return true;
        }

    private:
        string m_back_file;
        unordered_map<string, string> m_file_list;
        pthread_rwlock_t m_rwlock;
    };

    DataManager data_manager(DATA_FILE);
    class NonHotCompress
    {
    public:
        NonHotCompress(const string& bu_dir, const string& gz_dir)
            :m_bu_dir(bu_dir)
            ,m_gz_dir(gz_dir)
        {

        }

        bool Start()
        {
            while(1)
            {
                //获取未压缩文件列表
                vector<string> list;
                data_manager.NonCompressedList(&list);
                for(size_t i = 0; i < list.size(); i++)
                {
                    //判断是否是热点文件
                    bool ret = IsHotFile(list[i]);
                    if(ret == false)
                    {
                        string s_name = list[i];
                        string d_name = list[i] + ".gz";
                        string src_name = m_bu_dir + s_name;
                        string dst_name = m_gz_dir + d_name;
                        //对非热点文件进行压缩
                        if(CompressUtil::Compress(src_name, dst_name))
                        {
                            //更新文件，并删除原文件
                            data_manager.Insert(s_name, d_name);
                            unlink(src_name.c_str());
                        }
                    }
                }
                sleep(INTERVAL_TIME); 
            }
            return true;
        }

    private:
        bool IsHotFile(const string& name)
        {
            time_t cur_t = time(NULL);
            struct stat st;
            if(stat(name.c_str(), &st) < 0)
            {
                cout << "get file" << name << "stat failed!" << endl;
                return false;
            }
            if((cur_t - st.st_atime) > NONHOT_TIME)
            {
                return false;
            }

            return true;
        }

    private:
        string m_bu_dir;//压缩前文件所在路径
        string m_gz_dir;//压缩文件的存储路径
    };

    class Server
    {
    public:
        //启动网络通信模块
        bool Start()
        {
            m_server.Put("/upload", FileUpload);
            m_server.Get("/list", FileList);
            //正则表达式：.*匹配任意字符串 ()捕捉这个字符串
            m_server.Get("/download/(.*)", FileDownload);

            m_server.listen("0.0.0.0", 9000);
            return true;
        }
    private:
        //文件上传处理回调函数
        //set_content(正文数据， 正文数据长度， 正文类型(Content-Type))
        static void FileUpload(const httplib::Request& req, httplib::Response& rsp)
        {
            string filename = req.matches[1];//捕捉到的文件名称
            string pathname = BACKUP_DIR + filename;//文件路径
            FileUtil::Write(pathname, req.body);//向文件写入数据，文件不存在则会创建
            data_manager.Insert(filename, filename);
            rsp.status = 200;
            return;
        }
        //文件列表处理回调函数
        static void FileList(const httplib::Request& req, httplib::Response& rsp)
        {
            vector<string> list;
            data_manager.GetAllName(&list);
            stringstream tmp;
            tmp << "<html><body><hr />";
            for(size_t i = 0; i < list.size(); i++)
            {
                tmp << "<a href='/download" << list[i] << "'>" << list[i] << "</a>";
                tmp << "<hr />";
            }
            tmp << "<hr /></body><html>";
            rsp.set_content(tmp.str().c_str(), tmp.str().size(), "text/html");
            rsp.status = 200;
            return;
        }
        //文件下载处理回调函数
        static void FileDownload(const httplib::Request& req, httplib::Response& rsp)
        {
            //判断文件是否存在
            string filename = req.matches[1];
            if(data_manager.Exists(filename) == false)
            {
                rsp.status = 404;
                return;
            }
            //判断文件是否已经压缩
            string pathname = BACKUP_DIR + filename;
            if(data_manager.IsCompressed(filename))
            {
                //解压文件
               string gzfile;
               data_manager.GetGzName(filename, &gzfile);
               string gzpathname = GZFILE_DIR + gzfile;//压缩包路径
               CompressUtil::UnCompress(gzpathname, pathname);
               unlink(gzpathname.c_str());//删除压缩包
               data_manager.Insert(filename, filename);
            }
            FileUtil::Read(pathname, &rsp.body);
            rsp.set_header("Content-Type", "application/ocet-stream");//二进制流下载
            rsp.status = 200;
            return;
        }
    private:
        string m_file_dir;
        httplib::Server m_server; 
    };
}

