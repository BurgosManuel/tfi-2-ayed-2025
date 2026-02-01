# PROYECTO: Sistema de Gestión y Matchmaking Laboral (TFI AyED 2025)

## 1. OBJETIVO
Desarrollar una aplicación de consola en C++ para gestionar perfiles laborales y vacantes, permitiendo realizar un "match" automático basado en requisitos clave (educación, experiencia y edad).

## 2. ESTRUCTURAS DE DATOS (DEFINITIVAS)

### A. Estructura de Usuario (Simplificada)
Datos del operador del sistema.
```cpp
struct Usuario {
    char user[11];      // Usuario (Max 10 + \0) - Debe validar reglas estrictas
    char pass[33];      // Contraseña (Max 32 + \0) - Debe validar reglas estrictas
    char nombre[60];    // Nombre completo del operador
};

```

### B. Estructura de Puesto (Vacante)

Basado en la "Planilla de Puesto" (PDF 2), simplificado a factores numéricos de comparación.

```cpp
struct Puesto {
    int id;
    char nombreCargo[50];       // Título del puesto
    int nivelEducacionReq;      // 1:Primario, 2:Secundario, 3:Terciario, 4:Univ, 5:Posgrado
    int aniosExperienciaReq;    // Cantidad mínima de años requeridos
    int edadMinima;             // Rango de edad (Límite inferior)
    int edadMaxima;             // Rango de edad (Límite superior)
    bool activo;                // Para baja lógica
};

```

### C. Estructura de Empleado (Candidato)

Campos espejo a Puesto para facilitar la comparación directa.

```cpp
struct Empleado {
    int dni;
    char nombre[60];
    char apellido[60];
    int nivelEducacion;         // Se compara con nivelEducacionReq
    int aniosExperiencia;       // Se compara con aniosExperienciaReq
    int edad;                   // Se compara con el rango edadMinima-edadMaxima
    bool activo;                // Para baja lógica
};

```

## 3. LÓGICA DE MATCHMAKING

La función `generarMatch(Puesto p, Empleado e)` debe retornar `true` solo si se cumplen las 3 condiciones:

1. **Educación:** `e.nivelEducacion >= p.nivelEducacionReq`
2. **Experiencia:** `e.aniosExperiencia >= p.aniosExperienciaReq`
3. **Edad:** `e.edad >= p.edadMinima` Y `e.edad <= p.edadMaxima`

## 4. REGLAS DE VALIDACIÓN DE SEGURIDAD (Obligatorias por PDF 1)

Aunque el struct Usuario es simple, las reglas de validación son estrictas:

### Validación de Usuario

* Longitud: 6 a 10 caracteres.
* Comienza con minúscula.
* Al menos 2 mayúsculas.
* Máximo 3 dígitos.
* Caracteres permitidos: Letras, números y `+ - / * ? i !`.

### Validación de Contraseña

* Longitud: 6 a 32 caracteres.
* Al menos: 1 mayúscula, 1 minúscula, 1 número.
* Sin puntuación ni espacios (solo alfanuméricos).
* Sin más de 3 números consecutivos (ej: `1234` prohibido).
* Sin letras consecutivas alfabéticamente (ej: `ab` prohibido).

## 5. HOJA DE RUTA (ROADMAP)

### Fase 1: Configuración

* [ ] Definir `struct Usuario`, `struct Puesto`, `struct Empleado`.
* [ ] Definir constantes de archivos: "usuarios.dat", "puestos.dat", "empleados.dat".

### Fase 2: Autenticación

* [ ] Implementar `bool validarUsuario(char* u)`.
* [ ] Implementar `bool validarPass(char* p)`.
* [ ] Crear `registrarUsuario()` y `iniciarSesion()`.

### Fase 3: Gestión de Archivos (ABM)

* [ ] **Puestos:** Alta, Baja Lógica, Listado.
* [ ] **Empleados:** Alta, Baja Lógica, Listado.
* [ ] Implementar función auxiliar `void cargarCadena(char* destino, int tam)` para manejar `fgets` y limpieza de buffer de forma segura.

### Fase 4: Matchmaking

* [ ] Implementar menú "Reportes".
* [ ] Lógica: Seleccionar un Puesto -> Leer archivo Empleados -> Filtrar con lógica de Match -> Mostrar candidatos aptos.

### Fase 5: Interfaz

* [ ] Loop principal con Menú (`do-while`).
* [ ] Estética de consola (separadores, títulos claros).