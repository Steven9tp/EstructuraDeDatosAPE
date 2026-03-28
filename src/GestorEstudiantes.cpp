// ============================================================
//  UNIVERSIDAD TÉCNICA DE AMBATO — Estructura de Datos
//  Archivo : GestorEstudiantes.cpp
//  Rol     : Implementación de la clase GestorEstudiantes
// ============================================================

#include "GestorEstudiantes.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

// ════════════════════════════════════════════════════════════
//  CONSTRUCTOR
// ════════════════════════════════════════════════════════════
GestorEstudiantes::GestorEstudiantes() : cantidadEstudiantes(0) {}

// ════════════════════════════════════════════════════════════
//  HELPERS DE ENTRADA/SALIDA
// ════════════════════════════════════════════════════════════

// Leer una línea no vacía desde stdin
std::string GestorEstudiantes::leerLinea(const std::string& prompt) {
    std::string linea;
    do {
        std::cout << prompt;
        std::getline(std::cin, linea);
    } while (linea.empty());
    return linea;
}

// Leer un entero validado dentro del rango [min, max]
int GestorEstudiantes::leerEntero(const std::string& prompt, int min, int max) {
    int valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor && valor >= min && valor <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  [!] Valor fuera de rango. Ingrese un numero entre "
                  << min << " y " << max << ".\n";
    }
}

// Leer un float validado dentro del rango [min, max]
float GestorEstudiantes::leerFlotante(const std::string& prompt, float min, float max) {
    float valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor && valor >= min && valor <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  [!] Nota invalida. Ingrese un valor entre "
                  << min << " y " << max << ".\n";
    }
}

// Preguntar al usuario si desea repetir la misma acción
bool GestorEstudiantes::preguntarRepetir() {
    std::string resp;
    do {
        std::cout << "  ¿Desea realizar esta accion nuevamente? (s/n): ";
        std::getline(std::cin, resp);
    } while (resp != "s" && resp != "S" && resp != "n" && resp != "N");
    return (resp == "s" || resp == "S");
}

// Validar que día/mes/año conforman una fecha real
bool GestorEstudiantes::fechaValida(int d, int m, int a) const {
    if (m < 1 || m > 12 || d < 1 || a < 1900) return false;
    int diasMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if ((a % 4 == 0 && a % 100 != 0) || a % 400 == 0)
        diasMes[1] = 29;   // año bisiesto
    return d <= diasMes[m - 1];
}

// ════════════════════════════════════════════════════════════
//  PRESENTACIÓN INTERNA
// ════════════════════════════════════════════════════════════

// Mostrar tabla de estudiantes registrados con su autonumérico
void GestorEstudiantes::mostrarListadoEstudiantes() const {
    std::cout << "\n"
              << "  |---|--------------|----------------------|----------------------|\n"
              << "  | # |    Cédula    |       Nombres        |      Apellidos       |\n"
              << "  |---|--------------|----------------------|----------------------|\n";
    for (int i = 0; i < cantidadEstudiantes; ++i) {
        std::cout << "  | " << std::left << std::setw(1) << (i + 1) << " | "
                  << std::setw(12) << estudiantes[i].getCedula()    << " | "
                  << std::setw(20) << estudiantes[i].getNombres()   << " | "
                  << std::setw(20) << estudiantes[i].getApellidos() << " |\n";
    }
    std::cout << "  |---|--------------|-----------------------|----------------------|\n"
              << std::right;
}

// Mostrar listado de notas de un estudiante con su autonumérico
void GestorEstudiantes::mostrarListadoNotas(const Estudiante& est) const {
    std::cout << "\n  Calificaciones registradas ("
              << est.getCantidadNotas() << "/" << MAX_NOTAS << "):\n";
    if (est.getCantidadNotas() == 0) {
        std::cout << "  (Ninguna)\n";
        return;
    }
    for (int i = 0; i < est.getCantidadNotas(); ++i)
        std::cout << "    [" << (i + 1) << "] "
                  << std::fixed << std::setprecision(2)
                  << est.getNota(i) << "\n";
}

// ════════════════════════════════════════════════════════════
//  LECTURA DE DATOS DE ESTUDIANTE
// ════════════════════════════════════════════════════════════

Estudiante GestorEstudiantes::leerDatosEstudiante() {
    std::string ced = leerLinea("  Cedula      : ");
    std::string nom = leerLinea("  Nombres     : ");
    std::string ape = leerLinea("  Apellidos   : ");

    int dia, mes, anio;
    while (true) {
        dia  = leerEntero("  Dia de nac. (1-31)  : ", 1, 31);
        mes  = leerEntero("  Mes de nac. (1-12)  : ", 1, 12);
        anio = leerEntero("  Año de nac.         : ", 1900, 2025);
        if (fechaValida(dia, mes, anio)) break;
        std::cout << "  [!] Fecha inválida para ese mes/año. Intente de nuevo.\n";
    }
    return Estudiante(ced, nom, ape, dia, mes, anio);
}

// ════════════════════════════════════════════════════════════
//  BÚSQUEDA
// Recorre linealmente el arreglo estático buscando la cédula.
// Retorna el índice encontrado o -1 si no existe.
// ════════════════════════════════════════════════════════════
int GestorEstudiantes::buscar(const std::string& cedula) const {
    for (int i = 0; i < cantidadEstudiantes; ++i)
        if (estudiantes[i].getCedula() == cedula)
            return i;
    return -1;
}

// ════════════════════════════════════════════════════════════
//  OPCIÓN 1 — MENÚ DE ESTUDIANTES
// ════════════════════════════════════════════════════════════

void GestorEstudiantes::menuEstudiantes() {
    int opcion;
    do {
        std::cout << "\n  --- Listado de estudiantes ---\n";
        if (cantidadEstudiantes == 0)
            std::cout << "  (Sin registros)\n";
        else
            mostrarListadoEstudiantes();

        std::cout << "\n  --- Submenu Estudiantes ---\n"
                  << "  1. Ingresar\n"
                  << "  2. Modificar\n"
                  << "  3. Eliminar\n"
                  << "  0. Volver\n";
        opcion = leerEntero("  Opcion: ", 0, 3);

        switch (opcion) {
            case 1: ingresarEstudiante();  break;
            case 2: modificarEstudiante(); break;
            case 3: eliminarEstudiante();  break;
            case 0: break;
        }
    } while (opcion != 0);
}

// ── Ingresar nuevo estudiante ─────────────────────────────────
// Inserta en la primera posición libre del arreglo estático.
// Complejidad de inserción: O(1).
void GestorEstudiantes::ingresarEstudiante() {
    bool seguir = true;
    while (seguir) {
        if (cantidadEstudiantes >= MAX_ESTUDIANTES) {
            std::cout << "  [!] Limite msximo de " << MAX_ESTUDIANTES
                      << " estudiantes alcanzado.\n";
            return;
        }
        std::cout << "\n  -- Nuevo estudiante --\n";
        Estudiante nuevo = leerDatosEstudiante();

        if (buscar(nuevo.getCedula()) != -1) {
            std::cout << "  [!] Ya existe un estudiante con esa cedula.\n";
        } else {
            // Insertar en la posición libre indicada por el contador
            estudiantes[cantidadEstudiantes] = nuevo;
            ++cantidadEstudiantes;
            std::cout << "  [✓] Registrado con ID #" << cantidadEstudiantes << ".\n";
        }
        seguir = preguntarRepetir();
    }
}

// ── Modificar estudiante existente ────────────────────────────
void GestorEstudiantes::modificarEstudiante() {
    if (cantidadEstudiantes == 0) {
        std::cout << "  [!] No hay estudiantes registrados.\n";
        return;
    }
    bool seguir = true;
    while (seguir) {
        mostrarListadoEstudiantes();
        int id  = leerEntero("  ID del estudiante a modificar: ", 1, cantidadEstudiantes);
        int idx = id - 1;

        std::cout << "\n  Datos actuales:\n";
        estudiantes[idx].mostrarDatos();
        std::cout << "\n  Nuevos datos:\n";

        Estudiante actualizado = leerDatosEstudiante();

        // Verificar que la nueva cédula no pertenezca a otro registro
        int posExistente = buscar(actualizado.getCedula());
        if (posExistente != -1 && posExistente != idx) {
            std::cout << "  [!] Otro estudiante ya tiene esa cedula.\n";
        } else {
            // Conservar las notas del registro original
            int    nNotas = estudiantes[idx].getCantidadNotas();
            float  notasTemp[MAX_NOTAS];
            for (int i = 0; i < nNotas; ++i)
                notasTemp[i] = estudiantes[idx].getNota(i);

            estudiantes[idx] = actualizado;   // reemplazar datos personales

            // Restaurar las notas en el nuevo objeto
            for (int i = 0; i < nNotas; ++i)
                estudiantes[idx].insertarNota(notasTemp[i]);

            std::cout << "  [✓] Estudiante #" << id << " modificado.\n";
        }
        seguir = preguntarRepetir();
    }
}

// ── Eliminar estudiante y reorganizar el arreglo ──────────────
// Al eliminar un registro, todos los elementos que estaban a la
// derecha del índice eliminado se desplazan una posición hacia
// la izquierda.  Así el arreglo estático queda compacto sin
// huecos y el contador se decrementa.  Complejidad: O(n).
void GestorEstudiantes::eliminarEstudiante() {
    if (cantidadEstudiantes == 0) {
        std::cout << "  [!] No hay estudiantes para eliminar.\n";
        return;
    }
    bool seguir = true;
    while (seguir) {
        mostrarListadoEstudiantes();
        int id  = leerEntero("  ID del estudiante a eliminar: ", 1, cantidadEstudiantes);
        int idx = id - 1;

        std::cout << "  Eliminando: "
                  << estudiantes[idx].getNombres() << " "
                  << estudiantes[idx].getApellidos() << "\n";

        // Desplazar elementos posteriores hacia la izquierda
        for (int i = idx; i < cantidadEstudiantes - 1; ++i)
            estudiantes[i] = estudiantes[i + 1];

        // Reiniciar la última celda liberada con un objeto por defecto
        estudiantes[cantidadEstudiantes - 1] = Estudiante();
        --cantidadEstudiantes;

        std::cout << "  [✓] Eliminado. Quedan " << cantidadEstudiantes << " estudiante(s).\n";

        if (cantidadEstudiantes == 0) {
            std::cout << "  [i] No quedan mas registros.\n";
            break;
        }
        seguir = preguntarRepetir();
    }
}

// ════════════════════════════════════════════════════════════
//  OPCIÓN 2 — REGISTRO DE CALIFICACIONES
// ════════════════════════════════════════════════════════════

void GestorEstudiantes::menuCalificaciones() {
    bool intentarOtraCedula = true;

    while (intentarOtraCedula) {
        std::string cedula = leerLinea("\n  Cedula del estudiante: ");
        int idx = buscar(cedula);

        if (idx == -1) {
            std::cout << "  [!] No existe estudiante con cedula \"" << cedula << "\".\n";
            std::string resp;
            do {
                std::cout << "  ¿Intentar con otra cedula? (s/n): ";
                std::getline(std::cin, resp);
            } while (resp != "s" && resp != "S" && resp != "n" && resp != "N");
            intentarOtraCedula = (resp == "s" || resp == "S");
            continue;
        }

        intentarOtraCedula = false;
        Estudiante& est = estudiantes[idx];

        std::cout << "\n  Nombres   : " << est.getNombres()   << "\n"
                  << "  Apellidos : " << est.getApellidos() << "\n"
                  << "  Edad      : " << est.calcularEdad() << " anios\n";

        int opcion;
        do {
            mostrarListadoNotas(est);
            std::cout << "\n  -- Submenu Calificaciones --\n"
                      << "  1. Insertar nota\n"
                      << "  2. Modificar nota\n"
                      << "  3. Eliminar nota\n"
                      << "  0. Volver\n";
            opcion = leerEntero("  Opcion: ", 0, 3);

            switch (opcion) {
                case 1: insertarNota(est);  break;
                case 2: modificarNota(est); break;
                case 3: eliminarNota(est);  break;
                case 0: break;
            }
        } while (opcion != 0);
    }
}

// ── Insertar nota en el arreglo estático del estudiante ───────
void GestorEstudiantes::insertarNota(Estudiante& est) {
    bool seguir = true;
    while (seguir) {
        if (est.getCantidadNotas() >= MAX_NOTAS) {
            std::cout << "  [!] Se han ingresado todas las calificaciones posibles ("
                      << MAX_NOTAS << "). Proceso terminado.\n";
            return;
        }
        float nota = leerFlotante("  Nueva nota (0.0 - 10.0): ", 0.0f, 10.0f);
        est.insertarNota(nota);
        std::cout << "  [✓] Nota registrada.\n";

        if (est.getCantidadNotas() >= MAX_NOTAS) {
            std::cout << "  [i] Se alcanzo el limite de " << MAX_NOTAS << " notas.\n";
            return;
        }
        seguir = preguntarRepetir();
    }
}

// ── Modificar una nota existente ──────────────────────────────
void GestorEstudiantes::modificarNota(Estudiante& est) {
    if (est.getCantidadNotas() == 0) {
        std::cout << "  [!] No hay notas para modificar.\n";
        return;
    }
    bool seguir = true;
    while (seguir) {
        mostrarListadoNotas(est);
        int num = leerEntero("  Numero de nota a modificar: ", 1, est.getCantidadNotas());
        float nueva = leerFlotante("  Nueva nota (0.0 – 10.0): ", 0.0f, 10.0f);
        est.modificarNota(num - 1, nueva);
        std::cout << "  [✓] Nota #" << num << " actualizada.\n";
        seguir = preguntarRepetir();
    }
}

// ── Eliminar nota y reorganizar el arreglo interno ────────────
// La eliminación se delega a Estudiante::eliminarNota(), que
// realiza el desplazamiento hacia la izquierda internamente.
void GestorEstudiantes::eliminarNota(Estudiante& est) {
    if (est.getCantidadNotas() == 0) {
        std::cout << "  [!] No hay notas para eliminar.\n";
        return;
    }
    bool seguir = true;
    while (seguir) {
        mostrarListadoNotas(est);
        int num = leerEntero("  Numero de nota a eliminar: ", 1, est.getCantidadNotas());
        est.eliminarNota(num - 1);
        std::cout << "  [✓] Nota #" << num << " eliminada.\n";
        if (est.getCantidadNotas() == 0) {
            std::cout << "  [i] No quedan mas notas.\n";
            break;
        }
        seguir = preguntarRepetir();
    }
}

// ════════════════════════════════════════════════════════════
//  OPCIÓN 3 — PROMEDIO INDIVIDUAL
// ════════════════════════════════════════════════════════════

void GestorEstudiantes::promedioEstudiante() {
    std::string cedula = leerLinea("\n  Cedula del estudiante: ");
    int idx = buscar(cedula);

    if (idx == -1) {
        std::cout << "  [!] No se encontro. un estudiante con cedula \""
                  << cedula << "\".\n";
        return;
    }

    Estudiante& est = estudiantes[idx];
    std::cout << "\n  Nombres   : " << est.getNombres()   << "\n"
              << "  Apellidos : " << est.getApellidos() << "\n"
              << "  Edad      : " << est.calcularEdad() << " anios\n";

    double promedio = est.calcularPromedio();
    if (promedio < 0)
        std::cout << "  Promedio  : Sin calificaciones registradas.\n";
    else
        std::cout << "  Promedio  : " << std::fixed << std::setprecision(2)
                  << promedio << "\n";
}

// ════════════════════════════════════════════════════════════
//  OPCIÓN 4 — PROMEDIO GENERAL DEL CURSO
// Recorre linealmente el arreglo estático de estudiantes y
// acumula los promedios individuales de quienes tienen notas.
// ════════════════════════════════════════════════════════════

void GestorEstudiantes::promedioCurso() const {
    double sumaPromedios    = 0.0;
    int    estudiantesConNotas = 0;

    for (int i = 0; i < cantidadEstudiantes; ++i) {
        double prom = estudiantes[i].calcularPromedio();
        if (prom >= 0.0) {   // -1.0 indica que no tiene notas
            sumaPromedios += prom;
            ++estudiantesConNotas;
        }
    }

    std::cout << "\n";
    if (estudiantesConNotas == 0)
        std::cout << "  No se han registrado calificaciones de estudiantes.\n";
    else
        std::cout << "  Promedio general del curso: "
                  << std::fixed << std::setprecision(2)
                  << (sumaPromedios / estudiantesConNotas) << "\n";
}
