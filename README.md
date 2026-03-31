# APE 2: Gestión de colección de datos utilizando vectores

**Universidad Técnica de Ambato (UTA)** **Facultad:** Ingeniería en Sistemas, Electrónica e Industrial  
**Carrera:** Software  
**Asignatura:** Estructura de Datos  
**Ciclo Académico:** Enero 2026 - Julio 2026

Este repositorio contiene el código fuente de una aplicación de consola en C++ orientada a la gestión académica de estudiantes matriculados en un curso. El objetivo principal es calcular la media de valores estructurados aplicando estrictamente los principios de la Programación Orientada a Objetos (POO) y el uso de vectores (arreglos estáticos).

## Restricciones Técnicas
Para cumplir con los objetivos pedagógicos de la práctica:
- **Arreglos Estáticos:** Está estrictamente prohibido el uso de colecciones dinámicas (como `std::vector` o listas enlazadas). Se utilizan arreglos de dimensión conocida a priori.
- **Límites Fijos:** El sistema gestiona un cupo máximo de **20 estudiantes** y un máximo de **7 calificaciones** por cada uno.
- **Manejo de Memoria:** La eliminación de registros (estudiantes o notas) se maneja algorítmicamente mediante el desplazamiento de elementos hacia la izquierda para evitar la fragmentación lógica del arreglo.

## Características y Menú Principal
La aplicación despliega el siguiente menú interactivo:
1. **Estudiantes:** Submenú para ingresar, modificar y eliminar datos personales (cédula, nombres, apellidos y fecha de nacimiento).
2. **Registro de calificaciones:** Búsqueda por cédula para insertar, modificar o eliminar hasta 7 notas.
3. **Promedio individual:** Calcula y muestra el promedio de notas de un estudiante específico.
4. **Promedio del curso:** Determina el promedio general agrupando a todos los estudiantes con calificaciones registradas.

## Requisitos del Sistema
- **Compilador:** GCC (MinGW-w64) compatible con C++11 o superior.
- **Entorno de Desarrollo:** Visual Studio Code con la extensión C/C++

## Instrucciones de Compilación y Ejecución (VS Code)
1. Clona este repositorio en tu máquina local:
   ```bash
   git clone [https://github.com/Steven9tp/EstructuraDeDatosAPE.git](https://github.com/Steven9tp/EstructuraDeDatosAPE.git)
