#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H


#include <string>

// Tamaño máximo del arreglo estático de notas por estudiante
static const int MAX_NOTAS = 7;

class Estudiante {
private:
    // ── Datos personales ─────────────────────────────────────
    std::string cedula;
    std::string nombres;
    std::string apellidos;

    // Fecha de nacimiento almacenada como tres enteros
    int diaNacimiento;
    int mesNacimiento;
    int anioNacimiento;

    // ── Arreglo estático de calificaciones ───────────────────
    // Tamaño fijo MAX_NOTAS; 'cantidadNotas' indica cuántas
    // posiciones reales están ocupadas en el arreglo.
    float notas[MAX_NOTAS];
    int   cantidadNotas;

public:
    // ── Constructores ─────────────────────────────────────────
    Estudiante();
    Estudiante(const std::string& cedula,
               const std::string& nombres,
               const std::string& apellidos,
               int dia, int mes, int anio);

    // ── Getters ───────────────────────────────────────────────
    std::string getCedula()        const;
    std::string getNombres()       const;
    std::string getApellidos()     const;
    int         getDia()           const;
    int         getMes()           const;
    int         getAnio()          const;
    int         getCantidadNotas() const;
    float       getNota(int idx)   const;   // acceso por índice 0-based

    // ── Setters ───────────────────────────────────────────────
    void setCedula   (const std::string& cedula);
    void setNombres  (const std::string& nombres);
    void setApellidos(const std::string& apellidos);
    void setFecha    (int dia, int mes, int anio);

    // ── Lógica de calificaciones ──────────────────────────────
    bool   insertarNota  (float nota);              // false si arreglo lleno
    bool   modificarNota (int idx, float nueva);    // false si idx fuera de rango
    bool   eliminarNota  (int idx);                 // desplaza elementos hacia la izq.

    // ── Cálculos ──────────────────────────────────────────────
    int    calcularEdad    () const;   // a partir de la fecha actual del sistema
    double calcularPromedio() const;   // retorna -1.0 si no hay notas

    // ── Presentación ─────────────────────────────────────────
    void mostrarDatos() const;         // imprime atributos en consola
};

#endif // ESTUDIANTE_H
