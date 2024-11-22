#ifndef FFTCONF_H
#define FFTCONF_H
#include "../DataManagerLib/Models/Signals.h"

enum class Scale {
    Linear,
    Power
};

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

enum class Average {
    Linear,
    PeakHold
};

enum class AmpFormat{
    RMS,
    Pk,
    PkPk,
};

enum class UnitFreq{
    Hz,
    CPM
};


enum class Function{
    FFT,
    ESD,
    PSD,
    AutoSpectrum,
    CrossSpectrum,
    Transmissibility,
    Coherence,
    ODSFRF,
};

enum class MathOperation{
    None,
    Integral,
    DoubleIntegral,
    Derivation,
    DoubleDerivation
};

enum class OutputType{
    Real,
    Imag,
    Magnitude,
    Phase,
    Complex,
    Bode,
};

struct FFTConf{
    int blockSize;
    int numAvg;
    Average avg;
    Scale scale;
    AmpFormat ampFormat;
    Window window = Window::Rectangular;
    UnitFreq unitFreq = UnitFreq::Hz;
    Function function;
    OutputType outputType = OutputType::Magnitude;
    bool isDCFilter = false;
    double fcDCFilter = 0.;
    PhysicalQty outputQty;
    QString outputUnit;
    MathOperation mathOperation = MathOperation::None;
};

#endif // FFTCONF_H
