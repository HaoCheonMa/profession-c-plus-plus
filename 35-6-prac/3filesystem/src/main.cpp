#include <filesystem>
#include <vector>
#include <string>
#include <iostream>

namespace fs = std::filesystem;

auto recursiveGetFileNamesByExtension =
[](fs::path path, const std::string& extension) -> std::vector<std::string>
    {
    std::vector<std::string> result;
    try 
    {
        for (const auto& p : fs::recursive_directory_iterator(path))
            try 
            {
                if (p.is_regular_file() && p.path().extension() == extension) 
                    result.push_back(p.path().filename().string());
                
            }
            catch (const fs::filesystem_error& e)
            {
                std::cerr << "Access error: " << e.what() << std::endl;
            }
    }
    catch (const fs::filesystem_error& e) 
    {
        std::cerr << "Error catalog: " << e.what() << std::endl;
    }
    return result;
    };

int main() {
    std::string ext = ".txt";
    fs::path dir = "D:\\dir1";

    auto files = recursiveGetFileNamesByExtension(dir, ext);

    for (const auto& file : files)
        std::cout << file << '\n';

    return 0;
}
