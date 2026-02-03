
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
struct Usuario {
    char user[11];      // Max 10 chars. Reglas de validación estrictas (PDF 1).
    char pass[33];      // Max 32 chars. Reglas de validación estrictas (PDF 1).
    char nombre[60];    // Nombre del operador.
};
```

### B. Estructura de Puesto (Vacante)
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
*   [x] Definir `struct Usuario`, `Puesto`, `Empleado`.
*   [x] Definir constantes de archivos.
*   [x] Función `cargarUsuariosMemoria()`: Lee `usuarios.dat` a un array en memoria.
*   [x] Función `guardarUsuariosArchivo()`: Escribe el array de memoria a `usuarios.dat` al salir.
*   [x] Implementar funciones de validación de credenciales (`validarUsuario`, `validarPass`).
*   [x] Implementar `registrarUsuario()` e `iniciarSesion()`.
*   [x] Implementar lectura segura de cadenas con `fgets` y limpieza de buffer.
*   [x] Implementar menú de login y menú principal post-autenticación.

### Fase 2: ⏳ Módulo de Gestión de Puestos (EN PROGRESO)
*   [ ] Actualizar `menuGestionPuestos` para incluir las nuevas opciones.
*   [ ] Implementar `crearArchivoPuestos()`: Crea el archivo `puestos.dat` si no existe.
*   [ ] Implementar `altaPuesto()` (Grabar): Pide datos, valida y añade un nuevo puesto al archivo.
*   [ ] Implementar `bajaLogicaPuesto()`: Busca un puesto por ID y establece su campo `activo` a `false`.
*   [ ] Implementar `bajaFisicaPuesto()`: Elimina permanentemente un registro del archivo (requiere crear un archivo temporal).
*   [ ] Implementar `modificarPuesto()`: Busca un puesto por ID y permite editar sus campos.
*   [ ] Implementar `listarPuestos()`: Lee y muestra todos los registros de `puestos.dat`.
*   [ ] Implementar `consultarPuesto()`: Pide un ID y muestra la información detallada de ese puesto.

### Fase 3: 👨‍💼 Módulo de Gestión de Empleados
*   [ ] Actualizar `menuGestionEmpleados` para incluir las nuevas opciones.
*   [ ] Implementar `crearArchivoEmpleados()`: Crea el archivo `empleados.dat` si no existe.
*   [ ] Implementar `altaEmpleado()` (Grabar): Pide datos, valida y añade un nuevo empleado al archivo.
*   [ ] Implementar `bajaLogicaEmpleado()`: Busca un empleado por DNI y establece su campo `activo` a `false`.
*   [ ] Implementar `bajaFisicaEmpleado()`: Elimina permanentemente un registro del archivo (requiere crear un archivo temporal).
*   [ ] Implementar `modificarEmpleado()`: Busca un empleado por DNI y permite editar sus campos.
*   [ ] Implementar `listarEmpleados()`: Lee y muestra todos los registros de `empleados.dat`.
*   [ ] Implementar `consultarEmpleado()`: Pide un DNI y muestra la información detallada de ese empleado.

### Fase 4: 🤝 Módulo de Matchmaking
*   [ ] Crear el submenú `menuMatchmaking` con las opciones: "Buscar candidatos para un puesto" y "Buscar puestos para un candidato".

*   [ ] Implementar `buscarCandidatosParaPuesto()`:
    *   Solicitar al usuario el ID del puesto.
    *   Buscar y leer el registro del puesto en `puestos.dat`. Si no se encuentra o está inactivo, informar al usuario.
    *   Abrir `empleados.dat` y recorrerlo secuencialmente desde el principio.
    *   Para cada empleado con `activo == true`, comparar sus atributos (`edad`, `nivelEducacion`, `aniosExperiencia`) con los requisitos del puesto.
    *   Si el empleado cumple con todos los criterios, mostrar sus datos (DNI, Nombre, etc.) en pantalla como un candidato válido.

*   [ ] Implementar `buscarPuestosParaCandidato()`:
    *   Solicitar al usuario el DNI del empleado.
    *   Buscar y leer el registro del empleado en `empleados.dat`. Si no se encuentra o está inactivo, informar al usuario.
    *   Abrir `puestos.dat` y recorrerlo secuencialmente.
    *   Para cada puesto con `activo == true`, comparar sus requisitos con los atributos del empleado.
    *   Si el empleado es apto para el puesto, mostrar los datos del puesto (ID, Nombre del Cargo, etc.) en pantalla.

### Fase 5: 📊 Reportes y Estructuras Dinámicas
*   [ ] Crear un submenú `menuReportes` o añadir una opción en el menú principal para "Cargar Datos en Memoria".

*   [ ] Implementar la función `cargarEmpleadosEnLista()`:
    *   Al ser invocada, debe liberar cualquier lista previamente cargada para evitar fugas de memoria.
    *   Abrir `empleados.dat` y leerlo secuencialmente.
    *   Por cada registro de empleado activo, crear un nuevo nodo en una **lista enlazada simple** (`struct nodoEmpleado`).
    *   Almacenar los datos del empleado en el nodo y añadirlo al final de la lista.
    *   Informar al usuario cuántos empleados se cargaron en la estructura dinámica.

*   [ ] Implementar la función `reporteAvanzadoEmpleados()`:
    *   Verificar si la lista enlazada de empleados existe en memoria. Si no, pedir al usuario que la cargue primero.
    *   Recorrer la lista enlazada y mostrar los datos de los empleados, por ejemplo, ordenados por DNI o experiencia.
    *   (Opcional) Implementar un reporte que muestre estadísticas, como el promedio de edad o el nivel educativo más común.

## 💡 7. RECOMENDACIONES PARA EL EQUIPO DE DESARROLLO

### A. Metodología de Trabajo y Colaboración
1.  **🗺️ Seguir el Plan:** Este documento (`plan.md`) es nuestra guía. Antes de empezar una nueva función, revisa la fase correspondiente para asegurarte de que cumples con la estrategia definida (ej. acceso a disco vs. memoria).

2.  **🪜 Desarrollo Incremental:** No intentes implementar todo un módulo de una vez. Sigue los pasos:
    *   Crea la estructura del menú.
    *   Implementa la función de "Alta".
    *   Implementa la función de "Listar" para poder verificar que el alta funciona.
    *   Continúa con "Modificar" y "Baja".

3.  **🗣️ Comunicación:** Si encuentras un problema o piensas en una mejora que se desvía del plan, coméntalo con el equipo antes de implementarlo.

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
