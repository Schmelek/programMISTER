#include <iostream>
#include <fstream>

int main()
{
    std::ofstream ff;
    ff.open("file.txt");
    ff << "1234 \ngalgamesh";
    ff.close();
    
    std::ifstream f;
    f.open("file.txt");
    char s[100];
    f >> s;
    
    /*std::cout << s;
    f.getline(s,100);
    f.close();*/

    f.seekg(0, f.end);
    int len = f.tellg();
    f.seekg(0, f.beg);
    f.read(s, len);
    std::cout << s;
    std::cout << len;
    return 0;
}