#include <iostream>
#include "hashSet.cpp"
#include <string>

int main()
{
    hashSet<std::string> dict = hashSet<std::string>();
    dict.add("renee");
    dict.add("andre");
    dict.add("dan");
    dict.add("preston");
    dict.add("chan");
    dict.add("christina");
    std::cout << dict<<std::endl;
    dict.remove("dan");
    dict.remove("preston");
    std::cout << dict<<std::endl;
    std::cout<<"num of keys: "<<dict.size()<<std::endl;
    std::cout<<"is renee in set? "<<dict.hasKey("renee")<<std::endl;
    std::cout<<"is dan in set? "<<dict.hasKey("dan")<<std::endl;

    /*

    This prints the following to the console:
    {chan, christina, dan, renee, andre, preston}
    {chan, christina, renee, andre}
    num of keys: 4
    is renee in set? 1
    is dan in set? 0

    */

  return 0;
}
