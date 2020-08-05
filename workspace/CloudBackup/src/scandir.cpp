#include <iostream>
#include <string>
#include <boost/filesystem.hpp>

using namespace std;

int main()
{
    string dir = "./";
    boost::filesystem::directory_iterator begin(dir);//定义目录迭代器
    boost::filesystem::directory_iterator end;

    for(; begin != end; ++begin)
    {
        //过滤目录，只考虑普通文件
        //begin->status()文件的属性信息
        //boost::filesystem::is_directory()判断文件是否是目录
        string pathname = begin->path().string();
        string name = begin->path().filename().string();
        if(boost::filesystem::is_directory(begin->status()))
        {
            cout << pathname << "is directory" << endl;
            continue;
        }
        //开始迭代获取目录下的文件名称
        //begin->path()文件名的boost::fielsystem::path对象带路径的名称
        //begin->path().filename()纯文件名称
        cout << pathname << "------" << name << endl;
    }

    return 0;
}
