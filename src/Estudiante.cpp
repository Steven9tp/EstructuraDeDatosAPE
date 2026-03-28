

#include "Estudiante.h"
#include <iostream>
#include <iomanip>
#include <ctime>

// ── Constructor por defecto ───────────────────────────────────
Estudiante::Estudiante()
    : cedula(""), nombres(""), apellidos(""),
      diaNacimiento(1), mesNacimiento(1), anioNacimiento(2000),
      cantidadNotas(0)
{
    // Inicializar el arreglo estático en 0.0 para evitar basura
    for (int i = 0; i < MAX_NOTAS; ++i)
        notas[i] = 0.0f;
}

// ── Constructor parametrizado ─────────────────────────────────
Estudiante::Estudiante(const std::string& cedula,
                       const std::string& nombres,
                       const std::string& apellidos,
                       int dia, int mes, int anio)
    : cedula(cedula), nombres(nombres), apellidos(apellidos),
      diaNacimiento(dia), mesNacimiento(mes), anioNacimiento(anio),
      cantidadNotas(0)
{
    for (int i = 0; i < MAX_NOTAS; ++i)
        notas[i] = 0.0f;
}

// ── Getters ───────────────────────────────────────────────────
std::string Estudiante::getCedula()        const { return cedula; }
std::string Estudiante::getNombres()       const { return nombres; }
std::string Estudiante::getApellidos()     const { return apellidos; }
int         Estudiante::getDia()           const { return diaNacimiento; }
int         Estudiante::getMes()           const { return mesNacimiento; }
int         Estudiante::getAnio()          const { return anioNacimiento; }
int         Estudiante::getCantidadNotas() const { return cantidadNotas; }

// Retorna la nota en la posición idx (0-based); -1 si índice inválido
float Estudiante::getNota(int idx) const {
    if (idx >= 0 && idx < cantidadNotas)
        return notas[idx];
    return -1.0f;
}

// ── Setters ───────────────────────────────────────────────────
void Estudiante::setCedula   (const std::string& v) { cedula    = v; }
void Estudiante::setNombres  (const std::string& v) { nombres   = v; }
void Estudiante::setApellidos(const std::string& v) { apellidos = v; }
void Estudiante::setFecha(int d, int m, int a) {
    diaNacimiento  = d;
    mesNacimiento  = m;
    anioNacimiento = a;
}

// ── Insertar nota al final del arreglo estático ───────────────
// La inserción es O(1): simplemente se coloca en notas[cantidadNotas]
// y se incrementa el contador.  Retorna false si ya se llenó el arreglo.
bool Estudiante::insertarNota(float nota) {
    if (cantidadNotas >= MAX_NOTAS)
        return false;                       // arreglo lleno, no cabe más
    notas[cantidadNotas] = nota;
    ++cantidadNotas;
    return true;
}

// ── Modificar una nota existente (índice 0-based) ────────────
bool Estudiante::modificarNota(int idx, float nueva) {
    if (idx < 0 || idx >= cantidadNotas)
        return false;
    notas[idx] = nueva;
    return true;
}

// ── Eliminar una nota y reorganizar el arreglo ────────────────
// Para no dejar "huecos" en el arreglo estático, todos los
// elementos posteriores a 'idx' se desplazan una posición hacia
// la izquierda.  La última posición se pone a 0 y se decrementa
// el contador.  Complejidad: O(n) en el peor caso.
bool Estudiante::eliminarNota(int idx) {
    if (idx < 0 || idx >= cantidadNotas)
        return false;

    // Desplazamiento hacia la izquierda para cerrar el hueco
    for (int i = idx; i < cantidadNotas - 1; ++i)
        notas[i] = notas[i + 1];

    notas[cantidadNotas - 1] = 0.0f;   // limpiar la última celda liberada
    --cantidadNotas;
    return true;
}

// ── Calcular edad a partir de la fecha actual del sistema ─────
int Estudiante::calcularEdad() const {
    std::time_t tiempoActual = std::time(nullptr);
    std::tm*    hoy          = std::localtime(&tiempoActual);

    int anioHoy = hoy->tm_year + 1900;
    int mesHoy  = hoy->tm_mon  + 1;
    int diaHoy  = hoy->tm_mday;

    int edad = anioHoy - anioNacimiento;

    // Ajuste si todavía no llegó el cumpleaños este año
    if (mesHoy < mesNacimiento ||
       (mesHoy == mesNacimiento && diaHoy < diaNacimiento))
        --edad;

    return edad;
}

// ── Calcular promedio de las notas registradas ────────────────
// Recorre el arreglo estático hasta 'cantidadNotas'.
// Retorna -1.0 si no hay ninguna nota registrada.
double Estudiante::calcularPromedio() const {
    if (cantidadNotas == 0)
        return -1.0;

    double suma = 0.0;
    for (int i = 0; i < cantidadNotas; ++i)
        suma += notas[i];

    return suma / cantidadNotas;
}

// ── Mostrar datos en consola ──────────────────────────────────
void Estudiante::mostrarDatos() const {
    std::cout << "  Cedula    : " << cedula    << "\n"
              << "  Nombres   : " << nombres   << "\n"
              << "  Apellidos : " << apellidos << "\n"
              << "  Fecha nac.: "
              << std::setw(2) << std::setfill('0') << diaNacimiento << "/"
              << std::setw(2) << std::setfill('0') << mesNacimiento << "/"
              << anioNacimiento << "\n"
              << "  Edad      : " << calcularEdad() << " anios\n";
    std::cout << std::setfill(' ');   // restaurar relleno por defecto
}
