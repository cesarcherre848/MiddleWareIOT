#ifndef A2DSCONF_H
#define A2DSCONF_H
#include <QList>
#include <QVector>

enum class Operation{
    //RMS,
    //Peak,
    //Peak_Peak,
    //Kurtosis,
    //Crest_Factor,
    //Skewness
    Max,
    //Module
};

struct Function {
    QString searchAxis;
    QVector<double> range;
    Operation operation;
    QString alias;

};

enum class TypeBlock{
    Time,
    Samples,
};

struct A2DSConf {
   QList<Function> functions;
   //TypeBlock typeBlock;
   //double valueBlock;
   //double ov;
};



#endif // A2DSCONF_H
