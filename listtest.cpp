#include <iostream>
#include "list.h"

int main()
{
    List list;
    list.push_back(5);
    list.push_back(6);
    list.push_back(10);
    list.push_back(21);
    std:: cout << list.head->value << "\n"; //push_back checker [true answer = 5]

    
    
    std:: cout << list[1] << "\n";//operator checker [true answer = 6]
    std:: cout << list[4] << "\n";//operator checker [true answer = There is no such a node]
    
    
    
    
    std:: cout << list.get_size() << "\n";//get_size checker [true answer = 4]
    
    
    
    list.pop_front();
    std:: cout << list.head->value << "\n";//pop_front checker [true answer = 6]

    
    
    list.push_front(99);
    std:: cout << list.head->value << "\n";//push_front checker [true answer = 99]
    
    
    
    //list.pop_back();
    //std:: cout << list[list.size - 1] << "\n";//pop_back checker [true answer = 10]
    
    
    
    list.clear();
    std:: cout << list.get_size() << "\n";//clear checker [true answer = 0]

    
    
    for (int i = 0; i < 6; i++)
        {
        list.push_front(i);
        }
    
    
    
    list.insert(15, 1);//insert checker 15 appears after 5
    for (int i = 0; i < list.size; i++)
        {
        std:: cout << list[i] << " ";
        }
    std:: cout << "\n";    

    
    
    list.remove(1);//remove checker 15 disappears
    for (int i = 0; i < list.size; i++)
        {
        std:: cout << list[i] << " ";
        }
    std:: cout << "\n";

    return 0;
}