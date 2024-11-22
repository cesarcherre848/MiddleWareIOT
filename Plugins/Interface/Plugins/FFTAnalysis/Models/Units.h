#ifndef UNITS_H
#define UNITS_H


enum Unit{
    g,
    m_s2,
    mm_s,
    in_s,
    um,
    mils
};


struct UnitOperation{
    double a;
    double b;
};

#endif // UNITS_H
