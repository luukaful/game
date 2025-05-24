#pragma once

#include <string>
#include <unordered_map>

class SaveParser {
public:
    SaveParser(const std::string& filename);

    // Create a new save file with default data
    void createSaveFile();

    // Load data from the save file
    bool loadSaveFile();

    // Get and set data in the save file
    std::string getValue(const std::string& key) const;
    void setValue(const std::string& key, const std::string& value);

private:
    std::string filename;
    std::unordered_map<std::string, std::string> data;
    void saveToFile();
};
