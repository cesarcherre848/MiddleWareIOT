# Usa la imagen base de Ubuntu 22.04
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

RUN apt-get update && apt-get install -y tzdata \
    && ln -fs /usr/share/zoneinfo/Etc/UTC /etc/localtime \
    && echo "Etc/UTC" > /etc/timezone \
    && dpkg-reconfigure -f noninteractive tzdata


# Actualiza los paquetes e instala las dependencias necesarias
RUN apt-get update && apt-get install -y \
    libglib2.0-0 \
    libglib2.0-dev \
    postgresql-client \
    libfftw3-dev \
    libfftw3-doc \
    && rm -rf /var/lib/apt/lists/*  # Limpia los archivos de listas de apt para reducir el tamaño de la imagen



# Establece el directorio de trabajo dentro del contenedor
WORKDIR /App

# Copia todo el contenido del directorio MiddleWareIOT en el host al contenedor
COPY App /App

# Da permisos de ejecución al script App.sh y al archivo App
RUN chmod +x /App/App.sh /App/App

# Define el comando para mantener el contenedor activo
CMD ["tail", "-f", "/dev/null"]
