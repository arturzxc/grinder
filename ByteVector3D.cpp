#pragma once
struct ByteVector3D {
    std::byte x, y, z;

    ByteVector3D() {}

    ByteVector3D(std::byte x_val, std::byte y_val, std::byte z_val) : x(x_val), y(y_val), z(z_val) {}

    bool isZeroVector() const {
        return x == std::byte(0) && y == std::byte(0) && z == std::byte(0);
    }

    void print() const {
        std::cout
            << "X:" << static_cast<int>(x)
            << " Y:" << static_cast<int>(y)
            << " Z:" << static_cast<int>(z)
            << "\n";
    }

    bool operator==(const ByteVector3D& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const ByteVector3D& other) const {
        return !(*this == other);
    }
};
