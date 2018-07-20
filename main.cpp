#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "nltool.h"

int main()
{
    int maxcount{};
    std::string line, description, terminate;
    std::map<std::string, int> wordDictionary;
    std::map<std::string, int> letterDictionary;
    std::vector<std::string> bow;
    std::ifstream myfile;
    std::ofstream outfile;
    try
    {
        myfile.open("./res/product.txt");
        while (!myfile.eof() && maxcount < 2000000)
        {
            std::getline(myfile, line);
            line = trim(clean(toLower(trim(line))));
            description = splitSentence(line, "|")[3];

            bow = splitSentence(description);
            for (int i = 0; i < bow.size(); i++)
            {
                if (wordDictionary.count(bow[i]))
                {
                    wordDictionary[bow[i]] += 1;
                }
                else
                {
                    wordDictionary[bow[i]] = 1;
                }
            }
            if(maxcount % 100000 == 0)
            {
                std::cout << maxcount << std::endl;
            }
            maxcount += 1;
        }
    }
    catch(std::exception e)
    {
        std::cout << "There was an error opening the input file" << std::endl;
        std::cout <<  e.what() << std::endl;
    }
    try
    {
        outfile.open("./res/out.txt");
        for (const auto& item : wordDictionary)
        {
            outfile << item.first + ";" + std::to_string(item.second) << std::endl;
        }
    }
    catch (std::exception e)
    {
        std::cout << "There was an error opening the output file" << std::endl;
        std::cout <<  e.what() << std::endl;
    }
    return 0;
}
