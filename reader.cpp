//Compare two directories
#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>

void Magic(std::vector<std::string> &vec, std::string path)
{
    int y = path.size() + 1;
    for (const auto & entry : std::filesystem::directory_iterator(path)) //Copies the entire path (including the filename)
        vec.push_back(entry.path());
    for (int i = 0; i < vec.size(); i++) //Truncates and leaves the filename
        vec.at(i).erase(0,y);
    std::sort(vec.begin(), vec.end());
}

void Compare(std::vector<std::string> &vec1, std::vector<std::string> &vec2) //Compares filenames in 2 vectors
{
    for (int i = 0; i < vec1.size(); i++)
        for (int z = 0; z < vec2.size(); z++)
            if (vec1.at(i) == vec2.at(z))
            {
                vec1.at(i) = "";
                vec2.at(z) = "";
                break;
            }
}

void Write(std::vector<std::string> vec1, std::vector<std::string> vec2, std::string path1, std::string path2) //Outputs missing file(name)s to .txt files
{
    int found = path1.find_last_of("/\\");
    path1.erase(path1.begin(), path1.begin()+found+1);
    found = path2.find_last_of("/\\");
    path2.erase(path2.begin(), path2.begin()+found+1);
    std::ofstream output(path1+"_1.txt");
    for(const auto & str : vec1)
        if(str != "")
            output << str << std::endl;
    output.close();
    std::ofstream out(path2+"_2.txt");
    for(const auto & str : vec2)
        if(str != "")
            out << str << std::endl;
    output.close();
}

int main()
{
    std::vector<std::string> dir1, dir2;
    std::string path1, path2;
    std::cout << "Enter 1st path: " << std::endl; //Path to 1st directory
    std::cin >> path1;
    std::cout << "Enter 2nd path: " << std::endl; //Path to 2st directory
    std::cin >> path2;
    Magic(dir1, path1);
    Magic(dir2, path2);
    Compare(dir1, dir2);
    Write(dir1, dir2, path1, path2);
    return 0;
}