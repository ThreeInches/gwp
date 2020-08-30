#include "cloud_backupp.hpp"

int main()
{
   CloudBackupSys::DataManager da("abc.txt");
   da.Insert("a.txt", "a.txt");
   da.Insert("b.txt", "e.txt.gz");
   da.Insert("c.txt", "b.txt");
   da.Insert("d.txt", "c.txt.gz");
   da.Insert("e.txt", "d.txt");
   da.Insert("f.txt", "f.txt.gz");
   da.Insert("g.txt", "g.txt");
    return 0;
}
