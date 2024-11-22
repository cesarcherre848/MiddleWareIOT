#ifndef UCCONF_H
#define UCCONF_H
#include <QString>
#include <QList>


enum class Window {
    Rectangular,
    Hanning,
    FlatTop,
    Hamming,
};


enum class TypeFilter{
    HighPass,
    LowPass
};


enum class MathOperation{
    None,
    Integral,
    DoubleIntegral,
    Derivation,
    DoubleDerivation
};

/*
struct flowOperation{


    QString inputUnit;
    QString outputUnit;
    double aCoeff;
    double bCoeff;
    MathOperation mathOp;


    flowOperation(QString _inputUnit, QString _outputUnit, double _aCoeff, double _bCoeff, MathOperation _mathOp){
        inputUnit = _inputUnit;
        outputUnit = _outputUnit;
        aCoeff = _aCoeff;
        bCoeff = _bCoeff;
        mathOp = _mathOp;
    }

};
*/


struct UCConf{
    double HP_fc = 0.;
    double HP_bt = 0.;
    double LP_fc = 0.;
    double LP_bt = 0.;
    QString outputUnit;
};


struct flowOperation {
    QString inputUnit;
    QString outputUnit;
    double aCoeff;
    double bCoeff;
    MathOperation mathOp;

    // Constructor personalizado
    flowOperation(const QString& iU, const QString& oU, double aC, double bC, const MathOperation& mO) : inputUnit(iU), outputUnit(oU), aCoeff(aC), bCoeff(bC), mathOp(mO) {
        // Puedes agregar más lógica aquí si es necesario
    }
};

#endif // UCCONF_H
