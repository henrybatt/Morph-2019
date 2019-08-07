#ifndef LINE_DATA_H
#define LINE_DATA_H

struct LineData {
    double angle;
    double size;
    bool onField;

    LineData(double a, double s, bool o) : angle(a), size(s), onField(o) {}
};

#endif