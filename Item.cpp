#pragma once
struct Item {
    int index;
    long base;
    std::string name;
    std::string sigName;
    int customScript;

    Item(int index) {
        this->index = index;
    }

    void reset() {
        base = 0;
    }

    void readMemory() {
        reset();
        base = mem::Read<long>(OFF_REGION + OFF_ENTITY_LIST + ((index + 1) << 5));
        if (base == 0) { reset(); return; }
        long sigNamePointer = mem::Read<long>(base + OFF_SIGNIFIER_NAME);
        if (sigNamePointer != 0) {
            sigName = mem::ReadString(sigNamePointer, 1024);
            if (!isItem()) { reset(); return; }
            customScript = mem::Read<int>(base + OFF_CUSTOM_SCRIPT);
        }

    }

    bool isValid() {
        return base != 0;
    }


    bool isItem() {
        return sigName == "prop_survival";
    }
};



