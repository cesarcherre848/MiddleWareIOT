#ifndef VALUESMAPS_H
#define VALUESMAPS_H

#include "QMap"
#include "Models/FFTConf.h"

const QMap<Window, double> mapWindowFactor = {
    {Window::Rectangular, 1.},
    {Window::Hanning, 1.5},
    {Window::FlatTop, 3.77}
};


const QMap<Window, double> mapWindowMFactor = {
    {Window::Rectangular, 1.},
    {Window::Hanning, 0.5},
    {Window::FlatTop, 0.21558}
};

const QMap<AmpFormat, double> mapAmpFormatFactor = {
    {AmpFormat::RMS, 0.707 },
    {AmpFormat::Pk, 1.},
    {AmpFormat::PkPk, 2.}
};

#endif // VALUESMAPS_H
