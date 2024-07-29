#pragma once
struct Highlight {
    std::byte bodyStyle;
    std::byte borderStyle;
    std::byte borderWidth;
    std::byte transparency;
    float red;
    float green;
    float blue;

    Highlight() {}

    Highlight(int bodyStyle_val, int borderStyle_val, int borderWidth_val, int transparency_val) :
        bodyStyle(static_cast<std::byte>(bodyStyle_val)),
        borderStyle(static_cast<std::byte>(borderStyle_val)),
        borderWidth(static_cast<std::byte>(borderWidth_val)),
        transparency(static_cast<std::byte>(transparency_val)) {}


    Highlight(std::byte bodyStyle_val, std::byte borderStyle_val, std::byte borderWidth_val, std::byte transparency_val) :
        bodyStyle(bodyStyle_val),
        borderStyle(borderStyle_val),
        borderWidth(borderWidth_val),
        transparency(transparency_val) {}

    bool isZeroVector() const {
        return bodyStyle == std::byte(0)
            && borderStyle == std::byte(0)
            && borderWidth == std::byte(0)
            && borderWidth == std::byte(0);
    }

    void print() const {
        std::cout
            << "bodyStyle:" << static_cast<int>(bodyStyle)
            << " borderStyle:" << static_cast<int>(borderStyle)
            << " borderWidth:" << static_cast<int>(borderWidth)
            << " transparency:" << static_cast<int>(transparency)
            << "\n";
    }

    std::string toString() const {
        return "bodyStyle:" + std::to_string(static_cast<int>(bodyStyle)) +
            " borderStyle:" + std::to_string(static_cast<int>(borderStyle)) +
            " borderWidth:" + std::to_string(static_cast<int>(borderWidth)) +
            " transparency:" + std::to_string(static_cast<int>(transparency)) +
            " red:" + std::to_string(red) +
            " green:" + std::to_string(green) +
            " blue:" + std::to_string(blue);
    }

    bool operator==(const Highlight& other) const {
        return bodyStyle == other.bodyStyle
            && borderStyle == other.borderStyle
            && borderWidth == other.borderWidth
            && transparency == other.transparency;
    }

    bool operator!=(const Highlight& other) const {
        return !(*this == other);
    }
};
