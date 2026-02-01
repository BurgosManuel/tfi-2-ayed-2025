```markdown
# PROYECTO: Sistema de Gestión y Matchmaking Laboral (TFI AyED 2025)

## 1. OBJETIVO
Desarrollar una aplicación de consola en C++ para gestionar perfiles laborales y vacantes, permitiendo realizar un "match" automático basado en requisitos clave. El sistema debe diferenciar estrictamente entre la gestión de usuarios (seguridad) y la gestión de datos del negocio.

## 2. ESTRATEGIA DE PERSISTENCIA (CRÍTICO)
Según el documento de consignas, el manejo de archivos tiene dos comportamientos distintos que deben respetarse:

### A. Para Usuarios (`usuarios.dat`) - "Carga Inicial"
- **Inicio del Programa:** Se lee el archivo completo y se carga en un **Vector/Array en Memoria** antes de mostrar el login.
- **Validación:** El login verifica credenciales contra la memoria (RAM), no contra el disco.
- **Cierre:** Al salir del programa, se vuelca el contenido de la memoria al archivo para persistir cambios (altas de usuarios).

### B. Para Datos del Negocio (`empleados.dat`, `puestos.dat`) - "Acceso Directo y Dinámico"
- **Operaciones ABM:** Altas, Bajas y Modificaciones se realizan impactando directamente o secuencialmente en los archivos.
- **Estructuras Dinámicas (Punto 40 del PDF):**
  - **No** se cargan al inicio.
  - Se debe incluir una opción de menú específica: "Crear estructura dinámica".
  - Solo al seleccionar esa opción, se lee el archivo y se genera una **Lista Enlazada** en memoria para reportes o el proceso de Matchmaking.

## 3. ESTRUCTURAS DE DATOS

### A. Estructura de Usuario
```cpp
struct Usuario {
    char user[11];      // Max 10 chars. Reglas de validación estrictas (PDF 1).
    char pass[33];      // Max 32 chars. Reglas de validación estrictas (PDF 1).
    char nombre[60];    // Nombre del operador.
};

```

### B. Estructura de Puesto (Vacante)

Simplificado para factores de comparación numérica.

```cpp
struct Puesto {
    int id;
    char nombreCargo[50];
    int nivelEducacionReq;      // 1:Primario ... 5:Posgrado
    int aniosExperienciaReq;    // Mínimo de años
    int edadMinima;             // Rango inferior
    int edadMaxima;             // Rango superior
    bool activo;                // Para baja lógica
};

```

### C. Estructura de Empleado (Candidato)

Campos espejo a Puesto.

```cpp
struct Empleado {
    int dni;
    char nombre[60];
    char apellido[60];
    int nivelEducacion;
    int aniosExperiencia;
    int edad;
    bool activo;
};

```

## 4. LÓGICA DE MATCHMAKING

La función `generarMatch` comparará un Puesto contra la lista de Empleados. Es `true` si:

1. `empleado.nivelEducacion >= puesto.nivelEducacionReq`
2. `empleado.aniosExperiencia >= puesto.aniosExperienciaReq`
3. `empleado.edad` está dentro de `[puesto.edadMinima, puesto.edadMaxima]`

## 5. REGLAS DE SEGURIDAD (PDF 1)

* **Usuario:** 6-10 chars, empieza minúscula, min 2 mayúsculas, max 3 dígitos. Caracteres permitidos limitados.
* **Pass:** 6-32 chars, 1 mayus, 1 minus, 1 num. Sin puntuación. No más de 3 nums consecutivos. No letras consecutivas alfabéticamente.

## 6. HOJA DE RUTA (ROADMAP)

### Fase 1: Configuración

* [ ] Definir `struct Usuario`, `Puesto`, `Empleado`.
* [ ] Definir constantes de archivos.

### Fase 2: Autenticación (Estrategia RAM)

* [ ] Función `cargarUsuariosMemoria()`: Lee .dat -> Array Global.
* [ ] Función `guardarUsuariosArchivo()`: Array Global -> .dat.
* [ ] Implementar validaciones lógicas (`validarUsuario`, `validarPass`).

### Fase 3: Gestión de Archivos (Estrategia Directa)

* [ ] **Puestos/Empleados:** Implementar Alta (fseek/fwrite), Baja Lógica y Listado.
* [ ] Implementar lectura segura de strings.

### Fase 4: Estructuras Dinámicas y Match (Estrategia a Demanda)

* [ ] Opción de Menú: "Cargar Lista".
* [ ] Función `archivoALista()`: Lee Empleados.dat y crea nodos en memoria dinámica.
* [ ] Función `match()`: Recorre la lista en memoria comparando con un Puesto seleccionado.

### Fase 5: Interfaz

* [ ] Loop principal.
* [ ] Menú con las opciones exactas solicitadas en el PDF (pág. 2).