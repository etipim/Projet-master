cmake_minimum_required(VERSION 3.26)
project(AlgoConvexe)

set(CMAKE_CXX_STANDARD 17)
# Ajoutez tous vos fichiers source ici
set(SOURCES
        polygone.cpp
        affichage.cpp
        point.cpp
        enveloppe.cpp
        winbgi.cpp
)

add_executable(AlgoConvexe main.cpp ${SOURCES})
