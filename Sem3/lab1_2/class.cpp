#include "include/class.h"
#include <cmath>
#include <limits>

Line::Line(double a): a(a) {}

double Line::f(const double x) {
    if (std::abs(x) > std::abs(this->a))
        return std::numeric_limits<double>::quiet_NaN(); // returns "Not a Number" value
    return x * std::sqrt((this->a + x) / (this->a - x));
}

double Line::r(const double alpha) {
    if (std::abs(alpha) == 90.0)
        return std::numeric_limits<double>::infinity(); // returns infinite value
    double alpha_rad = alpha / 180.0 * mns::PI;
    return std::abs(((-1) * this->a * cos(2 * alpha_rad)) / cos(alpha_rad));
}

double Line::R_zp() {
    return this->a / cos(mns::PI / 4.0);}

double Line::S1() {return pow(this->a, 2.0) * (2.0 - mns::PI / 2.0);}

double Line::V1() {return pow(this->a, 3.0) * mns::PI * (2.0 * log(2.0) - 4.0 / 3.0);}

double Line::S2() {return pow(this->a, 2.0) * (2.0 + mns::PI / 2.0);}

void Line::Setter(const double new_a) { this->a = new_a;}