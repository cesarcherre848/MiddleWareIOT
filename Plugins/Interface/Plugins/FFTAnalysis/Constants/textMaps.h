#ifndef TEXTMAPS_H
#define TEXTMAPS_H

#include "QMap"
#include "QHash"
#include "Models/FFTConf.h"
#include "Models/Units.h"

const QMap<Scale, QString> mapScale = {
    {Scale::Linear, "Linear"},
    {Scale::Power, "Power"},
    //{Scale::ESD, "ESD"},
    //{Scale::PSD, "PSD"}
};


const QMap<QString, Scale> invMapScale = {
    {"Linear", Scale::Linear},
    {"Power", Scale::Power},
    //{"ESD", Scale::ESD},
    //{"PSD", Scale::PSD}
};


const QMap<Window, QString> mapWindow = {
    {Window::Rectangular, "Rectangular"},
    {Window::Hanning, "Hanning"},
    {Window::FlatTop, "Flat Top"}
};


const QMap<QString, Window> invMapWindow = {
    {"Rectangular", Window::Rectangular},
    {"Hanning", Window::Hanning},
    {"Flat Top", Window::FlatTop}
};


const QMap<Average, QString> mapAverage = {
    {Average::Linear, "Linear"},
    {Average::PeakHold, "Peak Hold"}
};

const QMap<QString, Average> invMapAverage = {
    {"Linear", Average::Linear},
    {"Peak Hold", Average::PeakHold}
};

const QMap<AmpFormat, QString> mapAmpFormat = {
    {AmpFormat::RMS, "RMS"},
    {AmpFormat::Pk, "Pk"},
    {AmpFormat::PkPk, "Pk-Pk"}
};

const QMap<QString, AmpFormat> invMapAmpFormat = {
    {"RMS", AmpFormat::RMS},
    {"Pk", AmpFormat::Pk},
    {"Pk-Pk", AmpFormat::PkPk}
};


const QMap<UnitFreq, QString> mapUnitFreq = {
    {UnitFreq::Hz, "Hz"},
    {UnitFreq::CPM, "CPM"}
};

const QMap<QString, UnitFreq> invMapUnitFreq = {
    {"Hz", UnitFreq::Hz},
    {"CPM", UnitFreq::CPM}
};



const QMap<Function, QString> mapFunction = {
    {Function::FFT, "FFT"},
    {Function::ESD, "ESD"},
    {Function::PSD, "PSD"},
    {Function::AutoSpectrum, "AutoSpectrum"},
    {Function::CrossSpectrum, "CrossSpectrum"},
    {Function::Transmissibility, "Transmissibility"},
    {Function::Coherence, "Coherence"},
    {Function::ODSFRF, "ODSFRF"}
};


const QMap<QString, Function> invMapFunction = {
    {"FFT", Function::FFT},
    {"ESD", Function::ESD},
    {"PSD", Function::PSD},
    {"AutoSpectrum", Function::AutoSpectrum},
    {"CrossSpectrum", Function::CrossSpectrum},
    {"Transmissibility", Function::Transmissibility},
    {"Coherence", Function::Coherence},
    {"ODSFRF", Function::ODSFRF}
};


const QMap<OutputType, QString> mapOutputType = {

    {OutputType::Magnitude, "Magnitude"},
    {OutputType::Phase, "Phase"},
    {OutputType::Bode, "Bode"},
    {OutputType::Real, "Real"},
    {OutputType::Imag, "Imag"},
    {OutputType::Complex, "Complex"},

};


const QMap<QString, OutputType> invMapOutputType = {

    {"Magnitude", OutputType::Magnitude},
    {"Phase", OutputType::Phase},
    {"Bode", OutputType::Bode},
    {"Real", OutputType::Real},
    {"Imag", OutputType::Imag},
    {"Complex", OutputType::Complex},

};


const QMap<MathOperation, QString> mapMathOperation = {
    {MathOperation::None, ""},
    {MathOperation::Integral, "Integral"},
    {MathOperation::DoubleIntegral, "DoubleIntegral"},
    {MathOperation::Derivation, "Derivation"},
    {MathOperation::DoubleDerivation, "DoubleDerivation"},
};

const QMap<Unit, QString> mapUnit = {
    {Unit::g, "g"},
    {Unit::m_s2, "m/s2"},
    {Unit::mm_s, "mm/s"},
    {Unit::in_s, "in/s"},
    {Unit::um, "um"},
    {Unit::mils, "mils"}
};


const QMap<QString, Unit> invMapUnit = {
    {"g", Unit::g},
    {"m/s2", Unit::m_s2},
    {"mm/s", Unit::mm_s},
    {"in/s", Unit::in_s},
    {"um", Unit::um},
    {"mils", Unit::mils}
};

#endif // TEXTMAPS_H
