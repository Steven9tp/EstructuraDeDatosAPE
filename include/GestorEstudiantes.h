#ifndef GESTOR_ESTUDIANTES_H
#define GESTOR_GESTOR_ESTUDIANTES_H

#include "Estudiante.h"

// Capacidad máxima del arreglo estático de estudiantes
static const int MAX_ESTUDIANTES = 20;

class GestorEstudiantes {
private:
    // ── Almacenamiento principal (arreglo estático crudo) ─────
    Estudiante estudiantes[MAX_ESTUDIANTES];
    int        cantidadEstudiantes;   // cuántas posiciones están ocupadas

    // ── Helpers de entrada/salida ─────────────────────────────
    std::string leerLinea   (const std::string& prompt);
    int         leerEntero  (const std::string& prompt, int min, int max);
    float       leerFlotante(const std::string& prompt, float min, float max);
    bool        preguntarRepetir();
    bool        fechaValida (int dia, int mes, int anio) const;

    // ── Presentación interna ──────────────────────────────────
    void mostrarListadoEstudiantes() const;
    void mostrarListadoNotas      (const Estudiante& est) const;

    // ── Lectura de datos desde consola ────────────────────────
    Estudiante leerDatosEstudiante();

    // ── Operaciones CRUD sobre notas ──────────────────────────
    void insertarNota (Estudiante& est);
    void modificarNota(Estudiante& est);
    void eliminarNota (Estudiante& est);

public:
    // ── Constructor ───────────────────────────────────────────
    GestorEstudiantes();

    // ── Búsqueda por cédula ───────────────────────────────────
    // Retorna el índice en el arreglo estático, o -1 si no existe
    int buscar(const std::string& cedula) const;

    // ── Opciones del menú principal ───────────────────────────
    void menuEstudiantes   ();   // Opción 1
    void menuCalificaciones();   // Opción 2
    void promedioEstudiante();   // Opción 3
    void promedioCurso     () const; // Opción 4

    // ── CRUD de estudiantes (llamadas desde menuEstudiantes) ──
    void ingresarEstudiante ();
    void modificarEstudiante();
    void eliminarEstudiante ();
};

#endif // GESTOR_ESTUDIANTES_H
