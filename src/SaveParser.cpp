#include "SaveParser.h"
#include <fstream>
#include <iostream>
#include <json.hpp>

using json = nlohmann::json;

SaveParser::SaveParser(const std::string& filename) : filename(filename) {}

void SaveParser::createSaveFile() {
    data = {
        {"speler_naam", "default"},
    };
    saveToFile();
}

bool SaveParser::loadSaveFile() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open save file: " << filename << std::endl;
        return false;
    }

    try {
        json j;
        file >> j;
        data = j.get<std::unordered_map<std::string, std::string>>();
    } catch (const std::exception& e) {
        std::cerr << "Error reading save file: " << e.what() << std::endl;
        return false;
    }

    return true;
}

void SaveParser::saveToFile() {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open save file for writing: " << filename << std::endl;
        return;
    }

    try {
        json j = data;
        file << j.dump(4); // Pretty print with 4 spaces
    } catch (const std::exception& e) {
        std::cerr << "Error writing save file: " << e.what() << std::endl;
    }
}

std::string SaveParser::getValue(const std::string& key) const {
    auto it = data.find(key);
    if (it != data.end()) {
        return it->second;
    }
    return "";
}

void SaveParser::setValue(const std::string& key, const std::string& value) {
    data[key] = value;
    saveToFile();
}
