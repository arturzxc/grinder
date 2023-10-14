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

    FloatVector2D divide(const FloatVector2D& other) const {
        return FloatVector2D(x / other.x, y / other.y);
    }

    FloatVector2D divide(float scalar) const {
        return FloatVector2D(x / scalar, y / scalar);
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

    FloatVector2D multiply(float scalar) const {
        return FloatVector2D(x * scalar, y * scalar);
    }

    FloatVector2D normalized() const {
        FloatVector2D result;
        float length = std::sqrt(x * x + y * y);
        if (length != 0) {
            result.x = x / length;
            result.y = y / length;
        }
        return result;
    }

    FloatVector2D multipliedByScalar(float scalar) const {
        FloatVector2D result;
        result.x = x * scalar;
        result.y = y * scalar;
        return result;
    }

    FloatVector2D clamp() const {
        //pitch doesnt have a full rotation so just set it to max value if its more than that
        float clampedX = x;
        if (clampedX < -89) clampedX = -89;
        if (clampedX > 89) clampedX = 89;
        //yaw has a full rotation so we might want to move it to the oposite side from negative to positive or vice versa
        float clampedY = y;
        if (clampedY < -180) clampedY += 360;
        if (clampedY > 180) clampedY -= 360;
        //create the vector
        if (clampedX > 89 || clampedX < -89) throw std::invalid_argument("SHIT CLAMPING OF PITCH. CHECK YOUR CODE");
        if (clampedY > 180 || clampedY < -180) throw std::invalid_argument("SHIT CLAMPING OF YAW. CHECK YOUR CODE");
        return FloatVector2D(clampedX, clampedY);
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
