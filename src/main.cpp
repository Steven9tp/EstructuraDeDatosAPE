// ============================================================
//  UNIVERSIDAD TÉCNICA DE AMBATO — Estructura de Datos
//  Archivo : main.cpp
//  Rol     : Punto de entrada — menú principal de la aplicación
// ============================================================
// El main únicamente construye el GestorEstudiantes y delega
// cada opción del menú al método correspondiente.  Toda la
// lógica de negocio vive en GestorEstudiantes; toda la lógica
// de datos vive en Estudiante.
// ============================================================

#include <iostream>
#include <limits>
#include "GestorEstudiantes.h"

int main() {
    GestorEstudiantes gestor;
    int opcion;

    do {
        std::cout << "\n"
                  << "  |-----------------------------------|\n"
                  << "  |          GESTOR DE ESTUDIANTES    |\n"
                  << "  |-----------------------------------|\n"
                  << "  |  1  Estudiantes.                  |\n"
                  << "  |  2  Registro de calificaciones.   |\n"
                  << "  |  3  Promedio de un estudiante.    |\n"
                  << "  |  4  Promedio del curso.           |\n"
                  << "  |  0  Salir.                        |\n"
                  << "  |-----------------------------------|\n"
                  << "  Teclee su opcion (1-4): ";

        while (!(std::cin >> opcion) || opcion < 0 || opcion > 4) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "  [!] Opcion invalida. Teclee su opcion (0-4): ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
            case 1: gestor.menuEstudiantes();    break;
            case 2: gestor.menuCalificaciones(); break;
            case 3: gestor.promedioEstudiante(); break;
            case 4: gestor.promedioCurso();      break;
            case 0: std::cout << "  Hasta luego.\n"; break;
        }

    } while (opcion != 0);

    return 0;
}
