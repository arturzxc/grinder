#pragma once
struct Item {
    int index;
    long base;
    std::string name;
    std::string sigName;
    bool isProp;
    int customScript;

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
        long sigNamePointer = mem::ReadLong(base + off::SIGNIFIER_NAME);
        if (sigNamePointer != 0) {
            sigName = mem::ReadString(sigNamePointer);
            if (isItem()) {
                customScript = mem::ReadInt(base + 0x1668);
            }
        }

    }

    bool isValid() {
        return base != 0;
    }


    bool isItem() {
        return sigName == "prop_survival";
    }
};



