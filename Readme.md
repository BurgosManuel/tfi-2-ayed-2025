# Sistema de Gestión y Matchmaking Laboral

Este documento describe la funcionalidad y el flujo de trabajo de la aplicación de consola "Sistema de Gestión y Matchmaking Laboral", desarrollada en C++.

## Descripción General

El sistema permite la gestión de usuarios, puestos de trabajo y empleados. Ofrece funcionalidades para registrar usuarios, iniciar sesión y, una vez autenticado, acceder a módulos para la administración de puestos, empleados y un sistema de "matchmaking" para encontrar coincidencias laborales.

Los datos se persisten en archivos binarios:
- `usuarios.dat` - Datos de usuarios del sistema
- `puestos.dat` - Datos de puestos/vacantes
- `empleados.dat` - Datos de empleados/candidatos

## Flujo del Programa

1.  **Inicio (`main`)**:
    *   Al ejecutar el programa, se invoca a `cargarUsuariosEnMemoria()` para leer los datos de los usuarios desde `usuarios.dat` y cargarlos en un arreglo en memoria.
    *   A continuación, se muestra el `menuLogin()`, que es el punto de entrada para la autenticación.
    *   Cuando el usuario elige la opción de salir, el programa llama a `guardarUsuariosEnArchivo()` para escribir el estado actual de los usuarios de vuelta al archivo `usuarios.dat`.

2.  **Menú de Login (`menuLogin`)**:
    *   Es el primer menú que ve el usuario al iniciar el programa.
    *   Presenta las opciones: "Iniciar Sesión", "Registrar Nuevo Usuario" y "Salir".
    *   Solo después de un inicio de sesión exitoso (`sesionActiva = true`) se permite el acceso al `menuPrincipal()`.

3.  **Menú Principal (`menuPrincipal`)**:
    *   Solo accesible después de autenticarse correctamente.
    *   Presenta las opciones: "Gestión de Puestos", "Gestión de Empleados", "Matchmaking" y "Cerrar Sesión".
    *   Al cerrar sesión, el usuario regresa al `menuLogin()`.

4.  **Submenús de Gestión (`menuGestionPuestos` y `menuGestionEmpleados`)**:
    *   Cada uno de estos menús ofrece un conjunto completo de herramientas para la administración de sus respectivos datos.
    *   Las opciones incluyen:
        *   **Crear archivo**: Inicializa el archivo de datos correspondiente (con confirmación si ya existe).
        *   **Grabar (Alta)**: Añade un nuevo registro al archivo con validaciones completas.
        *   **Baja Lógica**: Marca un registro como inactivo sin eliminarlo del archivo.
        *   **Baja Física**: Elimina permanentemente un registro del archivo usando archivo auxiliar.
        *   **Modificar**: Permite editar los campos de un registro existente con validaciones.
        *   **Listar**: Muestra todos los registros activos del archivo.
        *   **Consultar**: Busca y muestra un registro específico por su ID o DNI.

## Funcionalidades Implementadas

### Gestión de Usuarios

*   **`registrarUsuario()`**:
    1.  Solicita al usuario un nombre de usuario y una contraseña.
    2.  Valida las entradas utilizando `validarUsuario()` y `validarPass()` respectivamente.
    3.  Pide el nombre completo del usuario.
    4.  Almacena el nuevo usuario en el arreglo `usuariosEnMemoria`.

*   **`iniciarSesion()`**:
    1.  Solicita credenciales (usuario y contraseña).
    2.  Recorre el arreglo `usuariosEnMemoria` buscando una coincidencia exacta.
    3.  Si encuentra coincidencia, establece `sesionActiva` en `true`.

### Gestión de Puestos

*   **`crearArchivoPuestos()`**: 
    - Crea el archivo `puestos.dat` en modo binario.
    - Si el archivo ya existe, solicita confirmación antes de sobrescribirlo.

*   **`altaPuesto()`**:
    - Abre el archivo con modo `r+b` (lectura/escritura) para verificar existencia.
    - Valida que el ID no esté duplicado usando `existeIdPuesto()`.
    - Valida edades (rango 18-65, mínima <= máxima) usando `esValidaEdad()`.
    - Valida nivel de educación (1-5) usando `esValidoNivelEducacion()`.
    - Valida años de experiencia (0-100) usando `esValidaExperiencia()`.
    - Usa `fseek()` para posicionar al final y escribir el registro.
    - Cierra el archivo correctamente en todos los casos de salida.

*   **`bajaLogicaPuesto()`**:
    - Busca el puesto por ID en el archivo.
    - Si está activo, cambia `activo` a `false` y reescribe el registro.

*   **`bajaFisicaPuesto()`**:
    - Crea un archivo auxiliar `aux.dat`.
    - Copia todos los registros excepto el que se desea eliminar.
    - Elimina el archivo original y renombra el auxiliar.

*   **`modificarPuesto()`**:
    - Busca el puesto por ID en el archivo.
    - Permite modificar: nombre del cargo, edades, nivel educativo y experiencia.
    - Aplica las mismas validaciones que en alta usando funciones reutilizables.
    - Reescribe el registro en su posición original usando `fseek()`.

*   **`listarPuestos()`**:
    - Lee secuencialmente todos los registros del archivo.
    - Muestra solo los puestos con `activo == true`.
    - Informa si no hay puestos activos registrados.

*   **`consultarPuesto()`**:
    - Solicita un ID al usuario.
    - Busca el puesto en el archivo y muestra su información detallada.
    - Informa si el puesto no existe o está inactivo.

### Gestión de Empleados

*   **`crearArchivoEmpleados()`**: 
    - Crea el archivo `empleados.dat` en modo binario.
    - Si el archivo ya existe, solicita confirmación antes de sobrescribirlo.

*   **`altaEmpleado()`**:
    - Abre el archivo con modo `r+b` para verificar existencia.
    - Valida que el DNI no esté duplicado usando `existeDniEmpleado()`.
    - Valida edad (rango 18-65) usando `esValidaEdad()`.
    - Valida nivel de educación (1-5) usando `esValidoNivelEducacion()`.
    - Valida años de experiencia (0-100) usando `esValidaExperiencia()`.
    - Usa `fseek()` para posicionar al final y escribir el registro.
    - Cierra el archivo correctamente en todos los casos de salida.

*   **`bajaLogicaEmpleado()`**:
    - Busca el empleado por DNI en el archivo.
    - Si está activo, cambia `activo` a `false` y reescribe el registro.

*   **`bajaFisicaEmpleado()`**:
    - Crea un archivo auxiliar `aux.dat`.
    - Copia todos los registros excepto el que se desea eliminar.
    - Elimina el archivo original y renombra el auxiliar.

*   **`modificarEmpleado()`**:
    - Busca el empleado por DNI en el archivo.
    - Permite modificar: nombre, edad, nivel educativo y experiencia.
    - Aplica las mismas validaciones que en alta usando funciones reutilizables.
    - Reescribe el registro en su posición original usando `fseek()`.

*   **`listarEmpleados()`**:
    - Lee secuencialmente todos los registros del archivo.
    - Muestra solo los empleados con `activo == true`.
    - Informa si no hay empleados activos registrados.

*   **`consultarEmpleado()`**:
    - Solicita un DNI al usuario.
    - Busca el empleado en el archivo y muestra su información detallada.
    - Informa si el empleado no existe o está inactivo.

### Persistencia de Datos

*   **`cargarUsuariosEnMemoria()`**:
    - Se ejecuta al inicio del programa.
    - Lee los registros de `usuario` y los carga en `usuariosEnMemoria`.

*   **`guardarUsuariosEnArchivo()`**:
    - Se ejecuta al cerrar el programa.
    - Escribe todo el contenido del arreglo al archivo.

### Funciones de Validación

*   **`validarUsuario(char user[])`**:
    - 6-10 caracteres.
    - Primer carácter: letra minúscula.
    - Al menos 2 letras mayúsculas.
    - Máximo 3 dígitos.
    - Solo caracteres alfanuméricos o símbolos permitidos (`+-/*?!`).

*   **`validarPass(char pass[])`**:
    - 6-32 caracteres.
    - Al menos una mayúscula, una minúscula y un número.
    - Solo caracteres alfanuméricos.
    - Sin secuencias numéricas ascendentes de 3 dígitos (ej. "123").
    - Sin secuencias alfabéticas ascendentes de 2 caracteres (ej. "ab").

### Funciones Auxiliares

*   **`crearArchivo(const char *nombreArchivo)`**: Función genérica para crear archivos binarios con confirmación de sobrescritura.
*   **`existeIdPuesto(int id)`**: Verifica si un ID de puesto ya existe en el archivo.
*   **`existeDniEmpleado(int dni)`**: Verifica si un DNI de empleado ya existe en el archivo.
*   **`esCaracterPermitido(char c)`**: Verifica si un carácter pertenece al conjunto de símbolos permitidos.
*   **`esValidaEdad(int edad)`**: Valida que la edad esté en el rango laboral (18-65).
*   **`esValidaExperiencia(int anios)`**: Valida que los años de experiencia estén en rango válido (0-100).
*   **`esValidoNivelEducacion(int nivel)`**: Valida que el nivel de educación esté entre 1 y 5.

## Módulos en Construcción

Las siguientes funciones están definidas pero pendientes de implementación:


### Matchmaking:
- `buscarCandidatosParaPuesto()` - Encontrar empleados aptos para un puesto
- `buscarPuestosParaCandidato()` - Encontrar puestos aptos para un empleado

## Validaciones de Datos

| Campo | Rango Válido | Descripción |
|-------|-------------|-------------|
| Edad (empleado/puesto) | 18-65 | Rango de edad laboral |
| Nivel de Educación | 1-5 | 1:Primaria, 2:Secundaria, 3:Terciaria, 4:Grado, 5:Posgrado |
| Años de Experiencia | 0-100 | Años de experiencia laboral |
| ID Puesto | Único | No puede repetirse |
| DNI Empleado | Único | No puede repetirse |
