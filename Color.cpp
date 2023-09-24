#pragma once
struct Color {
    float red;
    float green;
    float blue;

    bool operator==(const Color& other) const {
        return (red == other.red) && (green == other.green) && (blue == other.blue);
    }

    bool operator!=(const Color& other) const {
        return !(*this == other);
    }
};

Color shieldsToColor(int shields) {
    if (shields <= 0)
        return { 0,1,0 }; //green
    else if (shields <= 50)
        return { 1,1,1 }; //gray
    else if (shields <= 75)
        return { 1,1,2 }; //blue
    else if (shields <= 100)
        return { 1,0,2 }; //purple
    else
        return { 1,0,0 }; //red   
}