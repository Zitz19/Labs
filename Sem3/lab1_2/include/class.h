#pragma once

namespace mns {
    const double PI = 3.14159265358979324;
}

class Line {
  private:
    double a;
  public:
    explicit Line(double a = 1); // defence from implicit conversion
    double f(const double x);
    double r(const double alpha);
    double R_zp();
    double S1();
    double V1();
    double S2();
    void Setter(const double new_a);
};
