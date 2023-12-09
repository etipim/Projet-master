cmake_minimum_required(VERSION 3.26)
project(CarteCombinatoire)

set(CMAKE_CXX_STANDARD 17)
# Ajoutez tous vos fichiers source ici
set(SOURCES
        carte.cpp
        affichage.cpp
        point.cpp
        winbgi.cpp
        triangulation.cpp
        triangulation.h
)

add_executable(CarteCombinatoire main.cpp ${SOURCES})
