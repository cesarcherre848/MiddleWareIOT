#!/bin/bash

# Obtén el directorio actual
current_dir=$(pwd)/libs

# Configura LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$current_dir:$LD_LIBRARY_PATH

# Ejecuta tu aplicación
./App
