
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <iterator>
#include <random>
#include <cstdlib>
#include <ctime>

int main()
{

    std::map<std::string, std::vector<std::string>> m;
    std::map<std::pair<std::string, std::string>, std::vector<std::string>> m2;

    // read input file
    std::ifstream myfile("corpus/cap.txt");

    int i = 0;
    std::string x;
    std::string y;
    myfile >> x;

    while ((myfile >> y) /* && (i < 25) */)
    {
        if (m.count(x) > 0) {
            std::vector<std::string>& temp = m.at(x);
            temp.push_back(y);
        } else {
            m[x] = std::vector<std::string>{y};
        }
        x = y;
        ++i;
    }

    // read input file for m2
    std::ifstream myfile2("corpus/cap.txt");

    int i2 = 0;
    std::string x2;
    std::string y2;
    std::string z2;
    myfile >> x2;
    myfile >> y2;

    while (myfile2 >> z2)
    {
        if (m2.count(std::make_pair(x2, y2)) > 0) {
            std::vector<std::string>& temp = m2.at(std::make_pair(x2, y2));
            temp.push_back(z2);
        } else {
            m2[std::make_pair(x2, y2)] = std::vector<std::string>{z2};
        }
        x2 = y2;
        y2 = z2;
        ++i2;
    }

    // print markov chain map
    // for (auto& temp: m)
    // {
    //     std::cout << temp.first << ": ";
    //     std::vector<std::string>& temp2 = temp.second;
    //     for (auto& temp3: temp2)
    //     {
    //         std::cout << temp3 << ", ";
    //     }
    //     std::cout << std::endl;
    // }

    // print markov chain map V2
    // for (auto& temp: m2)
    // {
    //     std::cout << "(" << temp.first.first << ", " << temp.first.second << ") : ";
    //     std::vector<std::string>& temp2 = temp.second;
    //     for (auto& temp3: temp2)
    //     {
    //         std::cout << temp3 << ", ";
    //     }
    //     std::cout << std::endl;
    // }


    for (int j = 0; j < 5; ++j) {
        // use markov chain map
        auto startIt = m2.begin();
        std::time_t tx = std::time(0);
        std::srand(tx + j);
        std::advance(startIt, std::rand() % m.size());
        std::string firstWord = (*startIt).first.second;
        std::string wordback = (*startIt).first.first;
        std::cout << "first words: " << wordback << " " << firstWord << std::endl; 
        std::string word = firstWord;
        std::cout << wordback << " " << firstWord << " ";

        for (int i = 0; i < 100; ++i)
        {
            std::string word2;

            if (m2.count(std::make_pair(wordback, word)) > 0) {
                std::vector<std::string>& v = m2.at(std::make_pair(wordback, word));
                
                auto startIt2 = v.begin();
                std::advance(startIt2, std::rand() % v.size());
                word2 = *startIt2;

                std::cout << word2 << " ";
                wordback = word;
                word = word2;

            } else if (m.count(word) > 0) {
                std::vector<std::string>& v = m.at(word);
                
                auto startIt2 = v.begin();
                std::advance(startIt2, std::rand() % v.size());
                word2 = *startIt2;

                std::cout << word2 << " ";
                wordback = word;
                word = word2;

            } else {
                std::cout << std::endl;
                break;
            }
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    return 0;
}
