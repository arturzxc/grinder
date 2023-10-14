#pragma once
struct GlowMode {
    std::byte bodyStyle, borderStyle, borderWidth, transparency;

    GlowMode() {}

    GlowMode(int bodyStyle_val, int borderStyle_val, int borderWidth_val, int transparency_val) :
        bodyStyle(static_cast<std::byte>(bodyStyle_val)),
        borderStyle(static_cast<std::byte>(borderStyle_val)),
        borderWidth(static_cast<std::byte>(borderWidth_val)),
        transparency(static_cast<std::byte>(transparency_val)) {}


    GlowMode(std::byte bodyStyle_val, std::byte borderStyle_val, std::byte borderWidth_val, std::byte transparency_val) :
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

    bool operator==(const GlowMode& other) const {
        return bodyStyle == other.bodyStyle
            && borderStyle == other.borderStyle
            && borderWidth == other.borderWidth
            && transparency == other.transparency;
    }

    bool operator!=(const GlowMode& other) const {
        return !(*this == other);
    }
};
