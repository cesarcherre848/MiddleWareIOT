#ifndef UNITSCONVERT_H
#define UNITSCONVERT_H
#include "Models/FFTConf.h"
#include "Models/Units.h"

inline MathOperation getMathOperation(PhysicalQty inputQty, PhysicalQty outputQty){
    MathOperation operation = MathOperation::None;

    if(inputQty == PhysicalQty::acceleration && outputQty == PhysicalQty::velocity){
        return MathOperation::Integral;
    }
    else if(inputQty == PhysicalQty::velocity && outputQty == PhysicalQty::displacement){
        return MathOperation::Integral;
    }
    else if(inputQty == PhysicalQty::acceleration && outputQty == PhysicalQty::displacement){
        return MathOperation::DoubleIntegral;
    }
    else if(inputQty == PhysicalQty::velocity && outputQty == PhysicalQty::acceleration){
        return MathOperation::Derivation;
    }
    else if(inputQty == PhysicalQty::displacement && outputQty == PhysicalQty::velocity){
        return MathOperation::Derivation;
    }
    else if(inputQty == PhysicalQty::displacement && outputQty == PhysicalQty::acceleration){
        return MathOperation::DoubleDerivation;
    }

    return operation;
}


inline UnitOperation getUnitOperation(Unit input, Unit output){
    UnitOperation unitOperation;
    unitOperation.a = 1.;
    unitOperation.b = 0.;

    double &a = unitOperation.a;
    double &b = unitOperation.b;

    if(input == Unit::g && output == Unit::m_s2){
        a = 9.81;
        return unitOperation;
    }

    else if(input == Unit::g && output == Unit::mm_s){
        a = 9806.65;
        return unitOperation;
    }

    return unitOperation;
}


#endif // UNITSCONVERT_H
