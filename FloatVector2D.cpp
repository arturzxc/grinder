#pragma once
struct FloatVector2D {
    float x, y;

    FloatVector2D() : x(0), y(0) {}

    FloatVector2D(float x_val, float y_val) : x(x_val), y(y_val) {}

    FloatVector2D subtract(const FloatVector2D& other) const {
        return FloatVector2D(x - other.x, y - other.y);
    }

    FloatVector2D add(const FloatVector2D& other) const {
        return FloatVector2D(x + other.x, y + other.y);
    }

    float dotProduct(const FloatVector2D& other) const {
        return x * other.x + y * other.y;
    }

    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    float distance(const FloatVector2D& other) const {
        FloatVector2D diff = subtract(other);
        return diff.magnitude();
    }

    FloatVector2D clamp() const {
        float clampedX = x;
        if (clampedX < -90) clampedX = 89;
        if (clampedX > 90) clampedX = -89;

        float clampedY = y;
        if (clampedY < -180) clampedY = 179;
        if (clampedY > 180) clampedY = -179;

        return FloatVector2D(clampedX, clampedY);

        // float clampedX = std::max(-89.0f, std::min(x, 89.0f));
        // float clampedY = std::max(-180.0f, std::min(y, 180.0f));
        // return FloatVector2D(clampedX, clampedY);
    }

    bool isZeroVector() {
        return x == 0 && y == 0;
    }

    std::string toString() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }

    void print() {
        std::cout << toString() << "\n";
    }

    bool operator==(const FloatVector2D& other) const {
        float epsilon = 1e-5;
        return (std::abs(x - other.x) < epsilon)
            && (std::abs(y - other.y) < epsilon);
    }

    bool operator!=(const FloatVector2D& other) const {
        return !(*this == other);
    }
};