# Sistema de Gestión y Matchmaking Laboral

Este documento describe la funcionalidad y el flujo de trabajo de la aplicación de consola "Sistema de Gestión y Matchmaking Laboral", desarrollada en C++.

## Descripción General

El sistema permite la gestión de usuarios, puestos de trabajo y empleados. Ofrece funcionalidades para registrar usuarios, iniciar sesión y, una vez autenticado, acceder a módulos para la administración de puestos, empleados y un sistema de "matchmaking" para encontrar coincidencias laborales.

Los datos de los usuarios se persisten en un archivo binario llamado `usuarios.dat`.

## Flujo del Programa

1.  **Inicio (`main`)**:
    *   Al ejecutar el programa, se invoca a `cargarUsuariosEnMemoria()` para leer los datos de los usuarios desde `usuarios.dat` y cargarlos en un arreglo en memoria.
    *   A continuación, se muestra el `menuPrincipal()`, que es el punto de entrada para todas las operaciones del sistema.
    *   Cuando el usuario elige la opción de salir del menú principal, el programa llama a `guardarUsuariosEnArchivo()` para escribir el estado actual de los usuarios (incluyendo los nuevos registros) de vuelta al archivo `usuarios.dat`.

2.  **Menú Principal (`menuPrincipal`)**:
    *   Presenta las opciones disponibles al usuario.
    *   Inicialmente, solo se pueden seleccionar "Iniciar Sesión", "Registrar Nuevo Usuario" o "Salir".
    *   Las opciones "Gestión de Puestos", "Gestión de Empleados" y "Matchmaking" solo se vuelven visibles y accesibles después de que un usuario haya iniciado sesión correctamente (la variable global `sesionActiva` se establece en `true`).

## Funcionalidades Principales

### Gestión de Usuarios

Este módulo se encarga del registro y la autenticación de los usuarios del sistema.

*   **`registrarUsuario()`**:
    1.  Solicita al usuario un nombre de usuario y una contraseña.
    2.  Valida las entradas utilizando `validarUsuario()` y `validarPass()` respectivamente. Si la validación falla, solicita los datos nuevamente hasta que sean correctos.
    3.  Pide el nombre completo del usuario.
    4.  Almacena el nuevo usuario en el arreglo `usuariosEnMemoria`.
    5.  Incrementa el contador `cantidadUsuarios`.

*   **`iniciarSesion()`**:
    1.  Solicita al usuario sus credenciales (usuario y contraseña).
    2.  Recorre el arreglo `usuariosEnMemoria` buscando una coincidencia exacta.
    3.  Si se encuentra una coincidencia, muestra un mensaje de bienvenida, establece `sesionActiva` en `true` y finaliza la búsqueda.
    4.  Si no se encuentra ninguna coincidencia después de revisar todos los usuarios, muestra un mensaje de error.

### Persistencia de Datos

*   **`cargarUsuariosEnMemoria()`**:
    *   Se ejecuta al inicio del programa.
    *   Abre el archivo `usuarios.dat` en modo de lectura binaria (`rb`).
    *   Lee los registros de `usuario` uno por uno y los carga en el arreglo `usuariosEnMemoria`, actualizando `cantidadUsuarios`.
    *   Si el archivo no existe, informa al usuario y continúa (se creará uno nuevo al guardar).

*   **`guardarUsuariosEnArchivo()`**:
    *   Se ejecuta justo antes de que el programa termine.
    *   Abre `usuarios.dat` en modo de escritura binaria (`wb`), sobrescribiendo cualquier contenido anterior.
    *   Escribe todo el contenido del arreglo `usuariosEnMemoria` en el archivo.

### Funciones de Validación

Estas funciones aseguran que los datos ingresados por el usuario cumplan con las reglas de negocio definidas.

*   **`validarUsuario(char user[])`**:
    *   Verifica que el nombre de usuario tenga entre 6 y 10 caracteres.
    *   Asegura que el primer carácter sea una letra minúscula.
    *   Comprueba que contenga al menos 2 letras mayúsculas.
    *   Valida que no tenga más de 3 dígitos.
    *   Confirma que todos los caracteres sean alfanuméricos o pertenezcan a un conjunto específico de símbolos permitidos (`+-/*?!`).

*   **`validarPass(char pass[])`**:
    *   Verifica que la contraseña tenga entre 6 y 32 caracteres.
    *   Asegura que contenga al menos una letra mayúscula, una minúscula y un número.
    *   Valida que todos los caracteres sean alfanuméricos (sin símbolos, espacios o acentos).
    *   Impide secuencias numéricas ascendentes de 3 dígitos (ej. "123").
    *   Impide secuencias alfabéticas ascendentes de 2 caracteres (ej. "ab", "Gh").

### Módulos en Construcción

Las siguientes funciones de menú han sido definidas pero su lógica interna aún no ha sido implementada:

*   `menuGestionPuestos()`
*   `menuGestionEmpleados()`
*   `menuMatchmaking()`
