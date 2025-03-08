#include "../includes/ft_sed.hpp"

void replaceInFile(const std::string& filename, const std::string& s1, const std::string& s2) {
    // Open the input file
    std::ifstream inputFile(filename.c_str());
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    // Read the entire file content into a string
    std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    // Replace all occurrences of s1 with s2
    size_t pos = 0;
    while ((pos = content.find(s1, pos)) != std::string::npos) {
        content.erase(pos, s1.length());
        content.insert(pos, s2);
        pos += s2.length();
    }

    // Create and write to the output file
    std::ofstream outputFile((filename + ".replace").c_str());
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not create file " << filename << ".replace" << std::endl;
        return;
    }
    outputFile << content;
    outputFile.close();
}