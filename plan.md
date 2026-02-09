# 🚀 PROYECTO: Sistema de Gestión y Matchmaking Laboral (TFI AyED 2025)

## 🎯 1. OBJETIVO
Desarrollar una aplicación de consola en C++ para gestionar perfiles laborales y vacantes, permitiendo realizar un "match" automático basado en requisitos clave. El sistema debe diferenciar estrictamente entre la gestión de usuarios (seguridad) y la gestión de datos del negocio.

## 💾 2. ESTRATEGIA DE PERSISTENCIA (CRÍTICO)
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

## 🏗️ 3. ESTRUCTURAS DE DATOS

### A. Estructura de Usuario
```cpp
struct usuario {
    char user[11];      // Max 10 chars. Reglas de validación estrictas (PDF 1).
    char pass[33];      // Max 32 chars. Reglas de validación estrictas (PDF 1).
    char nombre[60];    // Nombre del operador.
};
```

### B. Estructura de Puesto (Vacante)
```cpp
struct puesto {
    int id;
    char nombreCargo[50];
    int edadMinima;             // Rango inferior (18-65)
    int edadMaxima;             // Rango superior (18-65)
    int nivelEducacionReq;      // 1:Primaria, 2:Secundaria, 3:Terciaria, 4:Grado, 5:Posgrado
    int aniosExperienciaReq;    // Mínimo de años (0-100)
    bool activo;                // Para baja lógica
};
```

### C. Estructura de Empleado (Candidato)
```cpp
struct empleado {
    int dni;
    char nombre[100];
    int edad;                   // Rango laboral (18-65)
    int nivelEducacion;         // 1:Primaria, 2:Secundaria, 3:Terciaria, 4:Grado, 5:Posgrado
    int aniosExperiencia;       // 0-100 años
    bool activo;                // Para baja lógica
};
```

## 🧩 4. LÓGICA DE MATCHMAKING
La función `generarMatch` comparará un Puesto contra la lista de Empleados. Es `true` si:
1. `empleado.nivelEducacion >= puesto.nivelEducacionReq`
2. `empleado.aniosExperiencia >= puesto.aniosExperienciaReq`
3. `empleado.edad` está dentro de `[puesto.edadMinima, puesto.edadMaxima]`

## 🛡️ 5. REGLAS DE SEGURIDAD (PDF 1)
* **Usuario:** 6-10 chars, empieza minúscula, min 2 mayúsculas, max 3 dígitos. Caracteres permitidos limitados.
* **Pass:** 6-32 chars, 1 mayus, 1 minus, 1 num. Sin puntuación. No más de 3 nums consecutivos. No letras consecutivas alfabéticamente.

## 🗺️ 6. HOJA DE RUTA (ROADMAP)

### Fase 1: ✅ Configuración y Autenticación (COMPLETADA)
*   [x] Definir `struct usuario`, `puesto`, `empleado`.
*   [x] Definir constantes de archivos.
*   [x] Función `cargarUsuariosMemoria()`: Lee `usuarios.dat` a un array en memoria.
*   [x] Función `guardarUsuariosArchivo()`: Escribe el array de memoria a `usuarios.dat` al salir.
*   [x] Implementar funciones de validación de credenciales (`validarUsuario`, `validarPass`).
*   [x] Implementar `registrarUsuario()` e `iniciarSesion()`.
*   [x] Implementar lectura segura de cadenas con `fgets` y limpieza de buffer.
*   [x] Implementar menú de login y menú principal post-autenticación.

### Fase 2: ✅ Módulo de Gestión de Puestos (COMPLETADA)
*   [x] Actualizar `menuGestionPuestos` para incluir las nuevas opciones.
*   [x] Implementar `crearArchivoPuestos()`: Crea el archivo `puestos.dat` (con confirmación si ya existe).
*   [x] Implementar `altaPuesto()` (Grabar):
    *   [x] Validación de existencia del archivo al inicio (modo `r+b`).
    *   [x] Validación de ID duplicado con `existeIdPuesto()`.
    *   [x] Validación de edades (rango 18-65) usando `esValidaEdad()`.
    *   [x] Validación de nivel de educación (1-5) usando `esValidoNivelEducacion()`.
    *   [x] Validación de años de experiencia (0-100) usando `esValidaExperiencia()`.
    *   [x] Uso de `fseek()` para posicionar al final y escribir.
    *   [x] Cierre correcto del archivo en todos los casos de salida.
*   [x] Implementar `bajaLogicaPuesto()`: Busca por ID y establece `activo = false`.
*   [x] Implementar `bajaFisicaPuesto()`: Elimina permanentemente usando archivo auxiliar.
*   [x] Implementar `modificarPuesto()`: Busca un puesto por ID y permite editar sus campos con validaciones.
*   [x] Implementar `listarPuestos()`: Lee y muestra todos los registros activos de `puestos.dat`.
*   [x] Implementar `consultarPuesto()`: Pide un ID y muestra la información detallada.

### Fase 3: ✅ Módulo de Gestión de Empleados (COMPLETADA)
*   [x] Actualizar `menuGestionEmpleados` para incluir las nuevas opciones.
*   [x] Implementar `crearArchivoEmpleados()`: Crea el archivo `empleados.dat` (con confirmación si ya existe).
*   [x] Implementar `altaEmpleado()` (Grabar):
    *   [x] Validación de existencia del archivo al inicio (modo `r+b`).
    *   [x] Validación de DNI duplicado con `existeDniEmpleado()`.
    *   [x] Validación de edad (rango 18-65) usando `esValidaEdad()`.
    *   [x] Validación de nivel de educación (1-5) usando `esValidoNivelEducacion()`.
    *   [x] Validación de años de experiencia (0-100) usando `esValidaExperiencia()`.
    *   [x] Uso de `fseek()` para posicionar al final y escribir.
    *   [x] Cierre correcto del archivo en todos los casos de salida.
*   [x] Implementar `bajaLogicaEmpleado()`: Busca por DNI y establece `activo = false`.
*   [x] Implementar `bajaFisicaEmpleado()`: Elimina permanentemente usando archivo auxiliar.
*   [x] Implementar `modificarEmpleado()`: Busca un empleado por DNI y permite editar sus campos con validaciones.
*   [x] Implementar `listarEmpleados()`: Lee y muestra todos los registros activos de `empleados.dat`.
*   [x] Implementar `consultarEmpleado()`: Pide un DNI y muestra la información detallada.

### Fase 4: ✅ Módulo de Matchmaking con Estructuras Dinámicas (COMPLETADA)

Al ingresar a este módulo, el sistema carga automáticamente los datos de `empleados.dat` y `puestos.dat` en **listas enlazadas** en memoria, mostrando el mensaje "Cargando datos en memoria...". Todas las operaciones de matchmaking se realizan sobre estas estructuras dinámicas.

*   [x] Crear el submenú `menuMatchmaking` con las opciones.

*   [x] Implementar estructuras de nodos para listas enlazadas:
    *   Definir `struct nodoEmpleado` con un puntero `siguiente`.
    *   Definir `struct nodoPuesto` con un puntero `siguiente`.
    *   Basarse en el archivo `Lista1.cpp` como referencia de implementación.

*   [x] Implementar `cargarEmpleadosEnLista()`:
    *   Mostrar mensaje "Cargando empleados en memoria...".
    *   Liberar cualquier lista previamente cargada para evitar fugas de memoria.
    *   Abrir `empleados.dat` y leerlo secuencialmente.
    *   Por cada registro de empleado activo, crear un nuevo nodo y añadirlo a la lista.
    *   Informar al usuario cuántos empleados se cargaron.

*   [x] Implementar `cargarPuestosEnLista()`:
    *   Mostrar mensaje "Cargando puestos en memoria...".
    *   Liberar cualquier lista previamente cargada.
    *   Abrir `puestos.dat` y leerlo secuencialmente.
    *   Por cada registro de puesto activo, crear un nuevo nodo y añadirlo a la lista.
    *   Informar al usuario cuántos puestos se cargaron.

*   [x] Implementar `buscarCandidatosParaPuesto()`:
    *   Solicitar al usuario el ID del puesto.
    *   Buscar el puesto en la lista enlazada de puestos en memoria.
    *   Si no se encuentra, informar al usuario.
    *   Recorrer la lista de empleados y comparar atributos (`edad`, `nivelEducacion`, `aniosExperiencia`) con los requisitos del puesto.
    *   Si el empleado cumple con todos los criterios, mostrar sus datos (DNI, Nombre, etc.) como candidato válido.

*   [x] Implementar `liberarListaEmpleados()` y `liberarListaPuestos()`:
    *   Funciones auxiliares para liberar la memoria de las listas al salir del módulo o al recargar.

## 📋 7. ASIGNACIÓN DE TAREAS

### TIAGO:
- `crearArchivoPuestos()` y `crearArchivoEmpleados()` ✅
- `altaPuesto()` y `altaEmpleado()` ✅

### SOPHIA:
- `bajaLogicaPuesto()` y `bajaLogicaEmpleado()` ✅
- `bajaFisicaPuesto()` y `bajaFisicaEmpleado()` ✅

### AMBAR:
- `modificarPuesto()` y `modificarEmpleado()` ✅
- `listarPuestos()` y `listarEmpleados()` ✅
- `consultarPuesto()` y `consultarEmpleado()` ✅

## 💡 8. RECOMENDACIONES PARA EL EQUIPO DE DESARROLLO

### A. Metodología de Trabajo y Colaboración

1.  **🗺️ Seguir el Plan:** 
    Este documento (`plan.md`) es nuestra guía. Antes de empezar una nueva función, revisa la fase correspondiente para asegurarte de que cumples con la estrategia definida (ej. acceso a disco vs. memoria).

2.  **🪜 Desarrollo Incremental:** 
    No intentes implementar todo un módulo de una vez. Sigue los pasos:
    *   Crea la estructura del menú.
    *   Implementa la función de "Alta".
    *   Implementa la función de "Listar" para poder verificar que el alta funciona.
    *   Continúa con "Modificar" y "Baja".

3.  **🗣️ Comunicación:** 
    Si encuentras un problema o piensas en una mejora que se desvía del plan, coméntalo con el equipo antes de implementarlo.

### B. Uso Eficaz de Asistentes de IA (Copilot)

La IA es una herramienta de apoyo, no un reemplazo del programador. Úsala para acelerar, no para delegar el pensamiento.

1.  **🤖 Ideal para Tareas Repetitivas (Boilerplate):**
    
    *   **Qué pedir:** "Genera la estructura del `menuGestionEmpleados` con un `switch` para las opciones de ABM", o "Crea una función `listarPuestos` que lea el archivo `puestos.dat` y muestre los registros activos".
    
    *   **Por qué:** La IA es excelente generando código que sigue un patrón claro y repetitivo, ahorrándote tiempo de escritura.

2.  **📚 Excelente para Explicar y Documentar:**
    
    *   **Qué pedir:** "Explícame esta línea: `puntero[strcspn(puntero, "\n")] = 0;` como si fuera un profesor", o "Agrega un comentario que explique de forma sencilla para qué sirve la función `validarPass`".
    
    *   **Por qué:** Ayuda a comprender código complejo (especialmente de C/C++) y a mantener una buena documentación interna.

3.  **✨ Útil para Refactorizar y Optimizar:**
    
    *   **Qué pedir:** "Tengo esta función que usa `scanf`, ¿puedes reescribirla usando `fgets` para que sea más segura contra desbordamientos de búfer?", o "Esta función es muy larga, ¿puedes separarla en funciones más pequeñas?".
    
    *   **Por qué:** La IA puede sugerir mejoras de seguridad, legibilidad y eficiencia que quizás no veas a simple vista.

4.  **⚠️ ¡CUIDADO! Cuándo NO confiar ciegamente en la IA:**
    
    *   **Lógica de Negocio Crítica:** No pidas "Haz el sistema de matchmaking". La IA no conoce las reglas específicas de las consignas. Debes guiarla paso a paso: "Compara la edad del empleado con la edad mínima y máxima del puesto".
    
    *   **Decisiones de Arquitectura:** La decisión de qué datos van a memoria y cuáles a disco es nuestra. La IA puede implementar cualquiera de las dos, pero no sabe cuál es la correcta según los requisitos del proyecto.
    
    *   **Verificación Siempre:** **NUNCA** aceptes código de la IA sin entender qué hace. Siempre revísalo, comprueba que se alinea con el plan y, lo más importante, **pruébalo** para asegurarte de que funciona como esperas.
