#ifndef LINEDATA_H
#define LINEDATA_H

struct LineData {
    double angle;
    double size;
    bool onField;

    LineData() {}
    LineData(double a, double s, bool o) : angle(a), size(s), onField(o) {}

};

extern LineData lineInfo;


#endif