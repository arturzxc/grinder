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
    bool FEATURE_NORECOIL_ON = true;

    //norecoil    
    int NORECOIL_PITCH_REDUCTION = 15;
    int NORECOIL_YAW_REDUCTION = 17;

    //aimbot
    bool AIMBOT_ACTIVATED_BY_ATTACK = true;
    bool AIMBOT_ACTIVATED_BY_ADS = false;
    std::string AIMBOT_ACTIVATED_BY_BUTTON = "XK_Shift_L";
    int AIMBOT_SMOOTH = 20;
    int AIMBOT_SMOOTH_EXTRA_BY_DISTANCE = 1000;
    float AIMBOT_FOV = 5.0000;
    float AIMBOT_DEADZONE = 0.0100;
    int AIMBOT_MAX_DISTANCE = 100;
    int AIMBOT_MIN_DISTANCE = 1;

    //sense
    bool SENSE_ENEMY_COLOR_SHIELD_BASED = true;

    float SENSE_ENEMY_VISIBLE_COLOR_RED = 0;
    float SENSE_ENEMY_VISIBLE_COLOR_GREEN = 10;
    float SENSE_ENEMY_VISIBLE_COLOR_BLUE = 0;
    int SENSE_ENEMY_VISIBLE_BODY_STYLE = 112;
    int SENSE_ENEMY_VISIBLE_BORDER_STYLE = 108;
    int SENSE_ENEMY_VISIBLE_BORDER_WIDTH = 60;

    float SENSE_ENEMY_INVISIBLE_COLOR_RED = 10;
    float SENSE_ENEMY_INVISIBLE_COLOR_GREEN = 0;
    float SENSE_ENEMY_INVISIBLE_COLOR_BLUE = 0;
    int SENSE_ENEMY_INVISIBLE_BODY_STYLE = 112;
    int SENSE_ENEMY_INVISIBLE_BORDER_STYLE = 108;
    int SENSE_ENEMY_INVISIBLE_BORDER_WIDTH = 45;

    float SENSE_ENEMY_LOCKEDON_COLOR_RED = 0;
    float SENSE_ENEMY_LOCKEDON_COLOR_GREEN = 0;
    float SENSE_ENEMY_LOCKEDON_COLOR_BLUE = 10;
    int SENSE_ENEMY_LOCKEDON_BODY_STYLE = 112;
    int SENSE_ENEMY_LOCKEDON_BORDER_STYLE = 108;
    int SENSE_ENEMY_LOCKEDON_BORDER_WIDTH = 120;

    void loadVariables(std::string key, std::string val) {
        //features
        FEATURE_AIMBOT_ON = (key.compare("FEATURE_AIMBOT_ON") != 0) ? FEATURE_AIMBOT_ON : toBool(val);
        FEATURE_SENSE_ON = (key.compare("FEATURE_SENSE_ON") != 0) ? FEATURE_SENSE_ON : toBool(val);
        FEATURE_TRIGGERBOT_ON = (key.compare("FEATURE_TRIGGERBOT_ON") != 0) ? FEATURE_TRIGGERBOT_ON : toBool(val);
        FEATURE_NORECOIL_ON = (key.compare("FEATURE_NORECOIL_ON") != 0) ? FEATURE_NORECOIL_ON : toBool(val);

        //norecoil        
        NORECOIL_PITCH_REDUCTION = (key.compare("NORECOIL_PITCH_REDUCTION") != 0) ? NORECOIL_PITCH_REDUCTION : stoi(val);
        NORECOIL_YAW_REDUCTION = (key.compare("NORECOIL_YAW_REDUCTION") != 0) ? NORECOIL_YAW_REDUCTION : stoi(val);

        //aimbot
        AIMBOT_ACTIVATED_BY_ATTACK = (key.compare("AIMBOT_ACTIVATED_BY_ATTACK") != 0) ? AIMBOT_ACTIVATED_BY_ATTACK : toBool(val);
        AIMBOT_ACTIVATED_BY_ADS = (key.compare("AIMBOT_ACTIVATED_BY_ADS") != 0) ? AIMBOT_ACTIVATED_BY_ADS : toBool(val);
        AIMBOT_ACTIVATED_BY_BUTTON = (key.compare("AIMBOT_ACTIVATED_BY_BUTTON") != 0) ? AIMBOT_ACTIVATED_BY_BUTTON : trimConstructive(val);
        AIMBOT_SMOOTH = (key.compare("AIMBOT_SMOOTH") != 0) ? AIMBOT_SMOOTH : stoi(val);
        AIMBOT_SMOOTH_EXTRA_BY_DISTANCE = (key.compare("AIMBOT_SMOOTH_EXTRA_BY_DISTANCE") != 0) ? AIMBOT_SMOOTH_EXTRA_BY_DISTANCE : stoi(val);
        AIMBOT_FOV = (key.compare("AIMBOT_FOV") != 0) ? AIMBOT_FOV : stod(val);
        AIMBOT_DEADZONE = (key.compare("AIMBOT_DEADZONE") != 0) ? AIMBOT_DEADZONE : stod(val);

        //sense        
        SENSE_ENEMY_COLOR_SHIELD_BASED = (key.compare("SENSE_ENEMY_COLOR_SHIELD_BASED") != 0) ? SENSE_ENEMY_COLOR_SHIELD_BASED : toBool(val);

        SENSE_ENEMY_VISIBLE_COLOR_RED = (key.compare("SENSE_ENEMY_VISIBLE_COLOR_RED") != 0) ? SENSE_ENEMY_VISIBLE_COLOR_RED : stoi(val);
        SENSE_ENEMY_VISIBLE_COLOR_GREEN = (key.compare("SENSE_ENEMY_VISIBLE_COLOR_GREEN") != 0) ? SENSE_ENEMY_VISIBLE_COLOR_GREEN : stoi(val);
        SENSE_ENEMY_VISIBLE_COLOR_BLUE = (key.compare("SENSE_ENEMY_VISIBLE_COLOR_BLUE") != 0) ? SENSE_ENEMY_VISIBLE_COLOR_BLUE : stoi(val);
        SENSE_ENEMY_VISIBLE_BODY_STYLE = (key.compare("SENSE_ENEMY_VISIBLE_BODY_STYLE") != 0) ? SENSE_ENEMY_VISIBLE_BODY_STYLE : stoi(val);
        SENSE_ENEMY_VISIBLE_BORDER_STYLE = (key.compare("SENSE_ENEMY_VISIBLE_BORDER_STYLE") != 0) ? SENSE_ENEMY_VISIBLE_BORDER_STYLE : stoi(val);
        SENSE_ENEMY_VISIBLE_BORDER_WIDTH = (key.compare("SENSE_ENEMY_VISIBLE_BORDER_WIDTH") != 0) ? SENSE_ENEMY_VISIBLE_BORDER_WIDTH : stoi(val);

        SENSE_ENEMY_INVISIBLE_COLOR_RED = (key.compare("SENSE_ENEMY_INVISIBLE_COLOR_RED") != 0) ? SENSE_ENEMY_INVISIBLE_COLOR_RED : stoi(val);
        SENSE_ENEMY_INVISIBLE_COLOR_GREEN = (key.compare("SENSE_ENEMY_INVISIBLE_COLOR_GREEN") != 0) ? SENSE_ENEMY_INVISIBLE_COLOR_GREEN : stoi(val);
        SENSE_ENEMY_INVISIBLE_COLOR_BLUE = (key.compare("SENSE_ENEMY_INVISIBLE_COLOR_BLUE") != 0) ? SENSE_ENEMY_INVISIBLE_COLOR_BLUE : stoi(val);
        SENSE_ENEMY_INVISIBLE_BODY_STYLE = (key.compare("SENSE_ENEMY_INVISIBLE_BODY_STYLE") != 0) ? SENSE_ENEMY_INVISIBLE_BODY_STYLE : stoi(val);
        SENSE_ENEMY_INVISIBLE_BORDER_STYLE = (key.compare("SENSE_ENEMY_INVISIBLE_BORDER_STYLE") != 0) ? SENSE_ENEMY_INVISIBLE_BORDER_STYLE : stoi(val);
        SENSE_ENEMY_INVISIBLE_BORDER_WIDTH = (key.compare("SENSE_ENEMY_INVISIBLE_BORDER_WIDTH") != 0) ? SENSE_ENEMY_INVISIBLE_BORDER_WIDTH : stoi(val);

        SENSE_ENEMY_LOCKEDON_COLOR_RED = (key.compare("SENSE_ENEMY_LOCKEDON_COLOR_RED") != 0) ? SENSE_ENEMY_LOCKEDON_COLOR_RED : stoi(val);
        SENSE_ENEMY_LOCKEDON_COLOR_GREEN = (key.compare("SENSE_ENEMY_LOCKEDON_COLOR_GREEN") != 0) ? SENSE_ENEMY_LOCKEDON_COLOR_GREEN : stoi(val);
        SENSE_ENEMY_LOCKEDON_COLOR_BLUE = (key.compare("SENSE_ENEMY_LOCKEDON_COLOR_BLUE") != 0) ? SENSE_ENEMY_LOCKEDON_COLOR_BLUE : stoi(val);
        SENSE_ENEMY_LOCKEDON_BODY_STYLE = (key.compare("SENSE_ENEMY_LOCKEDON_BODY_STYLE") != 0) ? SENSE_ENEMY_LOCKEDON_BODY_STYLE : stoi(val);
        SENSE_ENEMY_LOCKEDON_BORDER_STYLE = (key.compare("SENSE_ENEMY_LOCKEDON_BORDER_STYLE") != 0) ? SENSE_ENEMY_LOCKEDON_BORDER_STYLE : stoi(val);
        SENSE_ENEMY_LOCKEDON_BORDER_WIDTH = (key.compare("SENSE_ENEMY_LOCKEDON_BORDER_WIDTH") != 0) ? SENSE_ENEMY_LOCKEDON_BORDER_WIDTH : stoi(val);
    }

    void print() {
        printf("\n==================== GRINDER SETTINGS LOADED ========================\n");

        //features
        printf("FEATURE_AIMBOT_ON\t\t\t\t\t%s\n", FEATURE_AIMBOT_ON ? "YES" : "NO");
        printf("FEATURE_SENSE_ON\t\t\t\t\t%s\n", FEATURE_SENSE_ON ? "YES" : "NO");
        printf("FEATURE_TRIGGERBOT_ON\t\t\t\t\t%s\n", FEATURE_TRIGGERBOT_ON ? "YES" : "NO");
        printf("FEATURE_NORECOIL_ON\t\t\t\t\t%s\n", FEATURE_NORECOIL_ON ? "YES" : "NO");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        //norecoil
        printf("NORECOIL_PITCH_REDUCTION\t\t\t\t%d\n", NORECOIL_PITCH_REDUCTION);
        printf("NORECOIL_YAW_REDUCTION\t\t\t\t\t%d\n", NORECOIL_YAW_REDUCTION);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        //aimbot
        printf("AIMBOT_ACTIVATED_BY_ATTACK\t\t\t\t%s\n", AIMBOT_ACTIVATED_BY_ATTACK ? "YES" : "NO");
        printf("AIMBOT_ACTIVATED_BY_ADS\t\t\t\t\t%s\n", AIMBOT_ACTIVATED_BY_ADS ? "YES" : "NO");
        printf("AIMBOT_ACTIVATED_BY_BUTTON\t\t\t\t%s\n", AIMBOT_ACTIVATED_BY_BUTTON.c_str());
        printf("AIMBOT_SMOOTH\t\t\t\t\t\t%.d\n", AIMBOT_SMOOTH);
        printf("AIMBOT_SMOOTH_EXTRA_BY_DISTANCE\t\t\t\t%.d\n", AIMBOT_SMOOTH_EXTRA_BY_DISTANCE);
        printf("AIMBOT_FOV\t\t\t\t\t\t%.4f\n", AIMBOT_FOV);
        printf("AIMBOT_DEADZONE\t\t\t\t\t\t%.4f\n", AIMBOT_DEADZONE);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        //sense        
        printf("SENSE_ENEMY_COLOR_SHIELD_BASED\t\t\t\t%s\n", SENSE_ENEMY_COLOR_SHIELD_BASED ? "YES" : "NO");
        printf("SENSE_ENEMY_VISIBLE_COLOR_RED\t\t\t\t%.0f\n", SENSE_ENEMY_VISIBLE_COLOR_RED);
        printf("SENSE_ENEMY_VISIBLE_COLOR_GREEN\t\t\t\t%.0f\n", SENSE_ENEMY_VISIBLE_COLOR_GREEN);
        printf("SENSE_ENEMY_VISIBLE_COLOR_BLUE\t\t\t\t%.0f\n", SENSE_ENEMY_VISIBLE_COLOR_BLUE);
        printf("SENSE_ENEMY_VISIBLE_BODY_STYLE\t\t\t\t%.d\n", SENSE_ENEMY_VISIBLE_BODY_STYLE);
        printf("SENSE_ENEMY_VISIBLE_BORDER_STYLE\t\t\t%.d\n", SENSE_ENEMY_VISIBLE_BORDER_STYLE);
        printf("SENSE_ENEMY_VISIBLE_BORDER_WIDTH\t\t\t%.d\n", SENSE_ENEMY_VISIBLE_BORDER_WIDTH);
        printf("SENSE_ENEMY_INVISIBLE_COLOR_RED\t\t\t\t%.0f\n", SENSE_ENEMY_INVISIBLE_COLOR_RED);
        printf("SENSE_ENEMY_INVISIBLE_COLOR_GREEN\t\t\t%.0f\n", SENSE_ENEMY_INVISIBLE_COLOR_GREEN);
        printf("SENSE_ENEMY_INVISIBLE_COLOR_BLUE\t\t\t%.0f\n", SENSE_ENEMY_INVISIBLE_COLOR_BLUE);
        printf("SENSE_ENEMY_INVISIBLE_BODY_STYLE\t\t\t%.d\n", SENSE_ENEMY_INVISIBLE_BODY_STYLE);
        printf("SENSE_ENEMY_INVISIBLE_BORDER_STYLE\t\t\t%.d\n", SENSE_ENEMY_INVISIBLE_BORDER_STYLE);
        printf("SENSE_ENEMY_INVISIBLE_BORDER_WIDTH\t\t\t%.d\n", SENSE_ENEMY_INVISIBLE_BORDER_WIDTH);
        printf("SENSE_ENEMY_LOCKEDON_COLOR_RED\t\t\t\t%.0f\n", SENSE_ENEMY_LOCKEDON_COLOR_RED);
        printf("SENSE_ENEMY_LOCKEDON_COLOR_GREEN\t\t\t%.0f\n", SENSE_ENEMY_LOCKEDON_COLOR_GREEN);
        printf("SENSE_ENEMY_LOCKEDON_COLOR_BLUE\t\t\t\t%.0f\n", SENSE_ENEMY_LOCKEDON_COLOR_BLUE);
        printf("SENSE_ENEMY_LOCKEDON_BODY_STYLE\t\t\t\t%.d\n", SENSE_ENEMY_LOCKEDON_BODY_STYLE);
        printf("SENSE_ENEMY_LOCKEDON_BORDER_STYLE\t\t\t%.d\n", SENSE_ENEMY_LOCKEDON_BORDER_STYLE);
        printf("SENSE_ENEMY_LOCKEDON_BORDER_WIDTH\t\t\t%.d\n", SENSE_ENEMY_LOCKEDON_BORDER_WIDTH);

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

    std::string trimConstructive(std::string& s) {
        ltrim(s);
        rtrim(s);
        return s;
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