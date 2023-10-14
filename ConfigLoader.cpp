#pragma once
struct ConfigLoader {
    const std::string FILE_NAME = "grinder.ini";
    std::vector<std::string>* lines = new std::vector<std::string>;
    long m_lastTimeFileEdited = 0;

    ConfigLoader() {
        reloadFile();
    }

    //features
    bool FEATURE_AIMBOT_ON = true;
    bool FEATURE_SENSE_ON = true;
    bool FEATURE_TRIGGERBOT_ON = true;

    //sense
    float SENSE_ENEMY_VISIBLE_COLOR_RED = 0;
    float SENSE_ENEMY_VISIBLE_COLOR_GREEN = 10;
    float SENSE_ENEMY_VISIBLE_COLOR_BLUE = 0;
    float SENSE_ENEMY_INVISIBLE_COLOR_RED = 10;
    float SENSE_ENEMY_INVISIBLE_COLOR_GREEN = 0;
    float SENSE_ENEMY_INVISIBLE_COLOR_BLUE = 0;
    float SENSE_ENEMY_LOCKEDON_COLOR_RED = 10;
    float SENSE_ENEMY_LOCKEDON_COLOR_GREEN = 0;
    float SENSE_ENEMY_LOCKEDON_COLOR_BLUE = 0;

    void loadVariables(std::string key, std::string val) {
        //features
        FEATURE_AIMBOT_ON = (key.compare("FEATURE_AIMBOT_ON") != 0) ? FEATURE_AIMBOT_ON : toBool(val);
        FEATURE_SENSE_ON = (key.compare("FEATURE_SENSE_ON") != 0) ? FEATURE_SENSE_ON : toBool(val);
        FEATURE_TRIGGERBOT_ON = (key.compare("FEATURE_TRIGGERBOT_ON") != 0) ? FEATURE_TRIGGERBOT_ON : toBool(val);
        //sense
        SENSE_ENEMY_VISIBLE_COLOR_RED = (key.compare("SENSE_ENEMY_VISIBLE_COLOR_RED") != 0) ? SENSE_ENEMY_VISIBLE_COLOR_RED : stoi(val);
        SENSE_ENEMY_VISIBLE_COLOR_GREEN = (key.compare("SENSE_ENEMY_VISIBLE_COLOR_GREEN") != 0) ? SENSE_ENEMY_VISIBLE_COLOR_GREEN : stoi(val);
        SENSE_ENEMY_VISIBLE_COLOR_BLUE = (key.compare("SENSE_ENEMY_VISIBLE_COLOR_BLUE") != 0) ? SENSE_ENEMY_VISIBLE_COLOR_BLUE : stoi(val);
        SENSE_ENEMY_INVISIBLE_COLOR_RED = (key.compare("SENSE_ENEMY_INVISIBLE_COLOR_RED") != 0) ? SENSE_ENEMY_INVISIBLE_COLOR_RED : stoi(val);
        SENSE_ENEMY_INVISIBLE_COLOR_GREEN = (key.compare("SENSE_ENEMY_INVISIBLE_COLOR_GREEN") != 0) ? SENSE_ENEMY_INVISIBLE_COLOR_GREEN : stoi(val);
        SENSE_ENEMY_INVISIBLE_COLOR_BLUE = (key.compare("SENSE_ENEMY_INVISIBLE_COLOR_BLUE") != 0) ? SENSE_ENEMY_INVISIBLE_COLOR_BLUE : stoi(val);
        SENSE_ENEMY_LOCKEDON_COLOR_RED = (key.compare("SENSE_ENEMY_LOCKEDON_COLOR_RED") != 0) ? SENSE_ENEMY_LOCKEDON_COLOR_RED : stoi(val);
        SENSE_ENEMY_LOCKEDON_COLOR_GREEN = (key.compare("SENSE_ENEMY_LOCKEDON_COLOR_GREEN") != 0) ? SENSE_ENEMY_LOCKEDON_COLOR_GREEN : stoi(val);
        SENSE_ENEMY_LOCKEDON_COLOR_BLUE = (key.compare("SENSE_ENEMY_LOCKEDON_COLOR_BLUE") != 0) ? SENSE_ENEMY_LOCKEDON_COLOR_BLUE : stoi(val);
    }

    void print() {
        printf("\n==================== GRINDER SETTINGS LOADED ========================\n");
        //features
        printf("FEATURE_AIMBOT_ON\t\t\t\t\t%s\n", FEATURE_AIMBOT_ON ? "YES" : "NO");
        printf("FEATURE_SENSE_ON\t\t\t\t\t%s\n", FEATURE_SENSE_ON ? "YES" : "NO");
        printf("FEATURE_TRIGGERBOT_ON\t\t\t\t\t%s\n", FEATURE_TRIGGERBOT_ON ? "YES" : "NO");
        //sense
        printf("SENSE_ENEMY_VISIBLE_COLOR_RED\t\t\t\t%.0f\n", SENSE_ENEMY_VISIBLE_COLOR_RED);
        printf("SENSE_ENEMY_VISIBLE_COLOR_GREEN\t\t\t\t%.0f\n", SENSE_ENEMY_VISIBLE_COLOR_GREEN);
        printf("SENSE_ENEMY_VISIBLE_COLOR_BLUE\t\t\t\t%.0f\n", SENSE_ENEMY_VISIBLE_COLOR_BLUE);
        printf("SENSE_ENEMY_INVISIBLE_COLOR_RED\t\t\t\t%.0f\n", SENSE_ENEMY_INVISIBLE_COLOR_RED);
        printf("SENSE_ENEMY_INVISIBLE_COLOR_GREEN\t\t\t%.0f\n", SENSE_ENEMY_INVISIBLE_COLOR_GREEN);
        printf("SENSE_ENEMY_INVISIBLE_COLOR_BLUE\t\t\t%.0f\n", SENSE_ENEMY_INVISIBLE_COLOR_BLUE);
        printf("SENSE_ENEMY_LOCKEDON_COLOR_RED\t\t\t\t%.0f\n", SENSE_ENEMY_LOCKEDON_COLOR_RED);
        printf("SENSE_ENEMY_LOCKEDON_COLOR_GREEN\t\t\t%.0f\n", SENSE_ENEMY_LOCKEDON_COLOR_GREEN);
        printf("SENSE_ENEMY_LOCKEDON_COLOR_BLUE\t\t\t\t%.0f\n", SENSE_ENEMY_LOCKEDON_COLOR_BLUE);

        printf("=====================================================================\n\n");
    }

    void reloadFile() {
        if (loadFileIntoVector()) {
            parseLines();
            print();
        }
    }

    void parseLines() {
        for (int i = 0; i < lines->size(); i++) {
            std::vector<std::string> lineParts = split(lines->at(i));
            // line key
            std::string key(lineParts.at(0));
            trim(key);
            if (key.empty()) throw "Cannot parse the config. Bad key";
            // line value
            std::string value(lineParts.at(1));
            trim(value);
            if (value.empty()) throw "Cannot parse the config. Bad value";
            loadVariables(key, value);
        }
    }

    bool loadFileIntoVector() {
        struct stat result;
        if (stat(FILE_NAME.c_str(), &result) == 0) {
            long modTime = result.st_mtime;
            bool fileNeedsReload = modTime > m_lastTimeFileEdited;
            m_lastTimeFileEdited = modTime;
            if (!fileNeedsReload) return false;
        }
        lines->clear();
        std::string str;
        std::ifstream myFile(FILE_NAME);
        while (getline(myFile, str)) {
            trim(str);
            if (str.empty()) continue;
            if (str.rfind("#", 0) == 0) continue;
            lines->push_back(str);
        }
        myFile.close();
        return true;
    }

    bool toBool(std::string str) {
        if (toLowerCase(str) == "y") return true;
        if (toLowerCase(str) == "n") return false;
        if (toLowerCase(str) == "yes") return true;
        if (toLowerCase(str) == "no") return false;
        if (toLowerCase(str) == "1") return true;
        if (toLowerCase(str) == "0") return false;
        throw  std::invalid_argument("Cannot parse string to boolean: " + str);
    }

    void trim(std::string& s) {
        ltrim(s);
        rtrim(s);
    }

    void ltrim(std::string& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
            { return !std::isspace(ch); }));
    }

    void rtrim(std::string& s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
            { return !std::isspace(ch); })
            .base(),
            s.end());
    }

    std::vector<std::string> split(std::string s) {
        std::stringstream ss(s);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> tokens(begin, end);
        return tokens;
    }

    std::string toLowerCase(const std::string& input) {
        std::string result = input;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
};