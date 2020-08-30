#include "cloud_backup.hpp"

int main()
{
    //ternstCompressUtil(argv);
    //testDataManager();

    DataManager dama("./abc.txt");
    dama.Insert("a.txt", "a.txt");
    dama.Insert("b.txt", "b.txt.gz");
    dama.Insert("c.txt", "c.txt.gz");
    dama.Insert("d.txt", "d.txt");
    dama.Insert("e.txt", "e.txt.gz");
    dama.Storage();
    dama.InitLoad();
    std::vector<std::string> list;
    dama.GetAllName(&list);
    for(auto& e : list)
    {
        std::cout << e << std::endl;
    }
    std::cout << "------------------" <<std::endl;
    list.clear();
    dama.NonCompressList(&list);
    for(auto& e : list)
    {
        std::cout << e << std::endl;
    }
    std::cout << "------------------" <<std::endl;
    list.clear();
    dama.CompressList(&list);
    for(auto& e : list)
    {
        std::cout << e << std::endl;
    }
    return 0;
}
