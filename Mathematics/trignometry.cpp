#include <cmath>          // For standard math functions like sin, cos, tan, etc.
#include <limits>         // For std::numeric_limits to handle invalid inputs

class trignometry {
public:
    // Mathematical constant PI with high precision
    static constexpr double PI = 3.14159265358979323846;

    // **Trigonometric Ratio Functions (Using Side Lengths)**
    // These compute ratios directly from the sides of a right triangle.

    /** Computes sine as opposite/hypotenuse */
    static double sine(double opposite, double hypotenuse) {
        if (hypotenuse == 0) {
            return std::numeric_limits<double>::quiet_NaN(); // Division by zero
        }
        return opposite / hypotenuse;
    }

    /** Computes cosine as adjacent/hypotenuse */
    static double cosine(double adjacent, double hypotenuse) {
        if (hypotenuse == 0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return adjacent / hypotenuse;
    }

    /** Computes tangent as opposite/adjacent */
    static double tangent(double opposite, double adjacent) {
        if (adjacent == 0) {
            return std::numeric_limits<double>::quiet_NaN(); // Undefined
        }
        return opposite / adjacent;
    }

    /** Computes cosecant as hypotenuse/opposite */
    static double cosecant(double hypotenuse, double opposite) {
        if (opposite == 0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return hypotenuse / opposite;
    }

    /** Computes secant as hypotenuse/adjacent */
    static double secant(double hypotenuse, double adjacent) {
        if (adjacent == 0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return hypotenuse / adjacent;
    }

    /** Computes cotangent as adjacent/opposite */
    static double cotangent(double adjacent, double opposite) {
        if (opposite == 0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return adjacent / opposite;
    }

    // **Angle Computation Functions (Using Side Lengths)**
    // These return the angle in radians based on two sides.

    /** Computes angle using arcsin from opposite and hypotenuse */
    static double angleFromOppositeAndHypotenuse(double opposite, double hypotenuse) {
        if (hypotenuse == 0 || std::abs(opposite) > std::abs(hypotenuse)) {
            return std::numeric_limits<double>::quiet_NaN(); // Invalid input
        }
        return std::asin(opposite / hypotenuse);
    }

    /** Computes angle using arccos from adjacent and hypotenuse */
    static double angleFromAdjacentAndHypotenuse(double adjacent, double hypotenuse) {
        if (hypotenuse == 0 || std::abs(adjacent) > std::abs(hypotenuse)) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return std::acos(adjacent / hypotenuse);
    }

    /** Computes angle using arctan from opposite and adjacent */
    static double angleFromOppositeAndAdjacent(double opposite, double adjacent) {
        return std::atan2(opposite, adjacent); // Handles quadrants correctly
    }

    // **Standard Trigonometric Functions (Using Angles in Radians)**
    // Wrappers for standard C++ math functions.

    static double sin(double angleRadians) {
        return std::sin(angleRadians);
    }

    static double cos(double angleRadians) {
        return std::cos(angleRadians);
    }

    static double tan(double angleRadians) {
        return std::tan(angleRadians);
    }

    static double csc(double angleRadians) {
        double sinVal = std::sin(angleRadians);
        if (sinVal == 0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return 1.0 / sinVal;
    }

    static double sec(double angleRadians) {
        double cosVal = std::cos(angleRadians);
        if (cosVal == 0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return 1.0 / cosVal;
    }

    static double cot(double angleRadians) {
        double tanVal = std::tan(angleRadians);
        if (tanVal == 0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return 1.0 / tanVal;
    }

    // **Trigonometric Functions (Using Angles in Degrees)**
    // Convenience functions converting degrees to radians internally.

    static double sinDegrees(double angleDegrees) {
        double angleRadians = angleDegrees * PI / 180.0;
        return std::sin(angleRadians);
    }

    static double cosDegrees(double angleDegrees) {
        double angleRadians = angleDegrees * PI / 180.0;
        return std::cos(angleRadians);
    }

    static double tanDegrees(double angleDegrees) {
        double angleRadians = angleDegrees * PI / 180.0;
        return std::tan(angleRadians);
    }

    static double cscDegrees(double angleDegrees) {
        double angleRadians = angleDegrees * PI / 180.0;
        return csc(angleRadians);
    }

    static double secDegrees(double angleDegrees) {
        double angleRadians = angleDegrees * PI / 180.0;
        return sec(angleRadians);
    }

    static double cotDegrees(double angleDegrees) {
        double angleRadians = angleDegrees * PI / 180.0;
        return cot(angleRadians);
    }

    // **Inverse Trigonometric Functions (Returning Degrees)**
    // These return angles in degrees for user convenience.

    static double asinDegrees(double sineValue) {
        if (sineValue < -1.0 || sineValue > 1.0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        double angleRadians = std::asin(sineValue);
        return angleRadians * 180.0 / PI;
    }

    static double acosDegrees(double cosineValue) {
        if (cosineValue < -1.0 || cosineValue > 1.0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        double angleRadians = std::acos(cosineValue);
        return angleRadians * 180.0 / PI;
    }

    static double atan2Degrees(double y, double x) {
        double angleRadians = std::atan2(y, x);
        return angleRadians * 180.0 / PI;
    }

    // **Utility Functions**
    // Angle unit conversions.

    static double degreesToRadians(double degrees) {
        return degrees * PI / 180.0;
    }

    static double radiansToDegrees(double radians) {
        return radians * 180.0 / PI;
    }
};
