#!/bin/bash


libs_dir=$(pwd)/libs # Obtén el directorio actual
export LD_LIBRARY_PATH=$libs_dir:/usr/local/lib # Configura LD_LIBRARY_PATH
export QT_PLUGIN_PATH=$libs_dir


# Ejecuta tu aplicación
./App
