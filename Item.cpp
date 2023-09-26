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
        base = mem::ReadLong(off::REGION + off::ENTITY_LIST + ((index + 1) << 5));
        if (base == 0) { reset(); return; }
        long sigNamePointer = mem::ReadLong(base + off::SIGNIFIER_NAME);
        if (sigNamePointer != 0) {
            sigName = mem::ReadString(sigNamePointer);
            if (!isItem()) { reset(); return; }
            customScript = mem::ReadInt(base + 0x1578);
        }

    }

    bool isValid() {
        return base != 0;
    }


    bool isItem() {
        return sigName == "prop_survival";
    }
};



