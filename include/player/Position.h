#ifndef POSITION_H
#define POSITION_H

#include <cmath>
#include <iostream>
#include <string>
#include <sstream>

/**
 * @brief Represents a coordinate in 2D/3D space for game entities.
 * Kept lightweight and modular to avoid coupling with Environment modules.
 */
struct Position {
    float x;
    float y;
    float z;

    Position(float x = 0.0f, float y = 0.0f, float z = 0.0f)
        : x(x), y(y), z(z) {}

    bool operator==(const Position& other) const {
        const float epsilon = 1e-4f;
        return std::fabs(x - other.x) < epsilon &&
               std::fabs(y - other.y) < epsilon &&
               std::fabs(z - other.z) < epsilon;
    }

    bool operator!=(const Position& other) const {
        return !(*this == other);
    }

    float distanceTo(const Position& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        float dz = z - other.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << "(" << x << ", " << y << ", " << z << ")";
        return oss.str();
    }

    friend std::ostream& operator<<(std::ostream& os, const Position& pos) {
        os << pos.toString();
        return os;
    }
};

#endif // POSITION_H
