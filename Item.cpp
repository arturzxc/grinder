#pragma once

std::vector<std::string*> names;
std::vector<std::string*> sigNames;

std::string printUnprintable(const std::string& input) {
    std::string result;
    for (char c : input) {
        if (c < 32 || c >= 127) result += "|x" + std::to_string(static_cast<unsigned int>(c));
        else result += c;
    }
    return result;
}

std::string findMostFrequentString(const std::vector<std::string*>& sigNames) {
    std::unordered_map<std::string, int> frequencyMap;
    for (const std::string* strPtr : sigNames) {
        if (strPtr != nullptr) {
            frequencyMap[*strPtr]++;
        }
    }
    std::string mostFrequentString;
    int maxCount = 0;
    for (const auto& entry : frequencyMap) {
        if (entry.second > maxCount) {
            maxCount = entry.second;
            mostFrequentString = entry.first;
        }
    }
    return mostFrequentString;
}



struct Item {
    int index;
    long base;
    std::string name;
    std::string sigName;
    bool isProp;

    Item(int index) {
        this->index = index;
    }

    void reset() {
        base = 0;
        isProp = false;
    }

    void readMemory() {
        reset();
        base = mem::ReadLong(off::REGION + off::ENTITY_LIST + ((index + 1) << 5));
        if (base == 0) { reset();return; }
        name = mem::ReadString(base + off::NAME);
        sigName = printUnprintable(mem::ReadString(base + off::SIGNIFIER_NAME));
        names.push_back(&name);
        sigNames.push_back(&sigName);
    }




    bool searchedFor() {
        return isValid()
            && isProp;
    }

    bool isValid() {
        return base != 0;
    }

    bool startsWith(const std::string& fullString, const std::string& startString) {
        return fullString.compare(0, startString.length(), startString) == 0;
    }




};



