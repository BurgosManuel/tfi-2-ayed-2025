#include <stdio.h> // Libreria estandar para usar printf() y scanf().
#include <string.h> // Libreria para utilizar strcmp(), strlen(), etc.
#include <ctype.h>  // Libreria para utilizar isupper, islower, isdigit


// ========= ENTIDADES ==========
struct usuario {
    char user[11];
    char pass[33];
    char nombre[60];
};

struct puesto {
    int id;
    char nombreCargo[50];
    int edadMinima;
    int edadMaxima;
    int nivelEducacionReq; // 1: Primaria, 2: Secundaria, 3: Terciaria, 4: Grado, 5: Posgrado
    int aniosExperienciaReq;
    bool activo;
};

struct empleado {
    int dni;
    char nombre[100];
    int edad;
    int nivelEducacion; // 1: Primaria, 2: Secundaria, 3: Terciaria, 4: Grado, 5: Posgrado
    int aniosExperiencia;
    bool activo;
};

// ========== VARIABLES GLOBALES ==========

// Opciones de menu login
const char *opcionesLogin[] = {
    "Salir",
    "Iniciar Sesion",
    "Registrar Nuevo Usuario"
};
const int numOpcionesLogin = sizeof(opcionesLogin) / sizeof(opcionesLogin[0]); // Total bytes / bytes de 1 elemento = cantidad de elementos

// Opciones de menu principal
const char *opcionesPrincipal[] = {
    "Cerrar Sesion",
    "Gestion de Puestos",
    "Gestion de Empleados",
    "Matchmaking"
};
const int numOpcionesPrincipal = sizeof(opcionesPrincipal) / sizeof(opcionesPrincipal[0]); // Total bytes / bytes de 1 elemento = cantidad de elementos

// Opciones de menu gestion de puestos
const char *opcionesGestionPuestos[] = {
    "Volver",
    "Crear archivo de Puestos",
    "Grabar un Puesto (Alta)",
    "Baja Logica de Puesto",
    "Baja Fisica de Puesto",
    "Modificar un Puesto",
    "Listar Puestos",
    "Consultar un Puesto"
};
const int numOpcionesGestionPuestos = sizeof(opcionesGestionPuestos) / sizeof(opcionesGestionPuestos[0]);

// Opciones de menu gestion de empleados
const char *opcionesGestionEmpleados[] = {
    "Volver",
    "Crear archivo de Empleados",
    "Grabar un Empleado (Alta)",
    "Baja Logica de Empleado",
    "Baja Fisica de Empleado",
    "Modificar un Empleado",
    "Listar Empleados",
    "Consultar un Empleado"
};
const int numOpcionesGestionEmpleados = sizeof(opcionesGestionEmpleados) / sizeof(opcionesGestionEmpleados[0]);

// Opciones de menu matchmaking
const char *opcionesMatchmaking[] = {
    "Volver",
    "Buscar candidatos para un puesto",
    "Buscar puestos para un candidato"
};
const int numOpcionesMatchmaking = sizeof(opcionesMatchmaking) / sizeof(opcionesMatchmaking[0]);

// Estado de sesión
bool sesionActiva = false;

// Usuarios
int cantidadUsuarios = 0;
usuario usuariosEnMemoria[100]; // Limitamos hasta 100 usuarios.

// ========== PROTOTIPO DE FUNCIONES ==========

// Menús
void menuLogin();
void menuPrincipal();
void menuGestionPuestos();
void menuGestionEmpleados();
void menuMatchmaking();

// Gestión de Puestos
void crearArchivoPuestos();
void altaPuesto();
void bajaLogicaPuesto();
void bajaFisicaPuesto();
void modificarPuesto();
void listarPuestos();
void consultarPuesto();

// Gestión de Empleados
void crearArchivoEmpleados();
void altaEmpleado();
void bajaLogicaEmpleado();
void bajaFisicaEmpleado();
void modificarEmpleado();
void listarEmpleados();
void consultarEmpleado();

void crearArchivo(const char *nombreArchivo);

// Matchmaking
void buscarCandidatosParaPuesto();
void buscarPuestosParaCandidato();

// Gestión de Usuarios
void cargarUsuariosEnMemoria();
void guardarUsuariosEnArchivo();
void registrarUsuario();
void iniciarSesion();

// Validaciones
bool validarUsuario(char user[]);
bool validarPass(char pass[]);


// ========= IMPLEMENTACIÓN PRINCIPAL ==========
int main() {
    printf("========== SISTEMA DE GESTION Y MATCHMAKING LABORAL ==========\n");
    cargarUsuariosEnMemoria();
    menuLogin(); // El programa comienza en el menú de login
    guardarUsuariosEnArchivo(); // Guardar cambios al salir
    return 0;
}

// ========== IMPLEMENTACIÓN DE MENÚS ==========

void menuLogin() {
    int opcion;

    do {
        printf("\n========== BIENVENIDO ==========\n");
        for (int i = 1; i < numOpcionesLogin; i++) {
            printf("[%d]. %s\n", i, opcionesLogin[i]);
        }
        printf("[0]. %s\n", opcionesLogin[0]);
        printf("=================================\n");
        printf("> Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                iniciarSesion();
                if (sesionActiva) {
                    menuPrincipal();
                }
                break;
            case 2:
                registrarUsuario();
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 0 && !sesionActiva);
}

void menuPrincipal() {
    int opcion;

    do {
        printf("\n========== MENU PRINCIPAL ==========\n");
        for (int i = 1; i < numOpcionesPrincipal; i++) {
            printf("[%d]. %s\n", i, opcionesPrincipal[i]);
        }
        printf("[0]. %s\n", opcionesPrincipal[0]);
        printf("=====================================\n");
        printf("> Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                menuGestionPuestos();
                break;
            case 2:
                menuGestionEmpleados();
                break;
            case 3:
                menuMatchmaking();
                break;
            case 0:
                sesionActiva = false;
                printf("Sesion cerrada correctamente.\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 0);
}

void menuGestionPuestos() {
    int opcion;
    do {
        printf("\n--- Gestion de Puestos ---\n");
        for (int i = 1; i < numOpcionesGestionPuestos; i++) {
            printf("[%d]. %s\n", i, opcionesGestionPuestos[i]);
        }
        printf("[0]. %s\n", opcionesGestionPuestos[0]);
        printf("===========================\n");
        printf("> Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                crearArchivoPuestos();
                break;
            case 2:
                altaPuesto();
                break;
            case 3:
                bajaLogicaPuesto();
                break;
            case 4:
                bajaFisicaPuesto();
                break;
            case 5:
                modificarPuesto();
                break;
            case 6:
                listarPuestos();
                break;
            case 7:
                consultarPuesto();
                break;
            case 0:
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 0);
}

void menuGestionEmpleados() {
    int opcion;
    do {
        printf("\n--- Gestion de Empleados ---\n");
        for (int i = 1; i < numOpcionesGestionEmpleados; i++) {
            printf("[%d]. %s\n", i, opcionesGestionEmpleados[i]);
        }
        printf("[0]. %s\n", opcionesGestionEmpleados[0]);
        printf("=============================\n");
        printf("> Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                crearArchivoEmpleados();
                break;
            case 2:
                altaEmpleado();
                break;
            case 3:
                bajaLogicaEmpleado();
                break;
            case 4:
                bajaFisicaEmpleado();
                break;
            case 5:
                modificarEmpleado();
                break;
            case 6:
                listarEmpleados();
                break;
            case 7:
                consultarEmpleado();
                break;
            case 0:
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 0);
}

void menuMatchmaking() {
    int opcion;
    do {
        printf("\n--- Matchmaking ---\n");
        for (int i = 1; i < numOpcionesMatchmaking; i++) {
            printf("[%d]. %s\n", i, opcionesMatchmaking[i]);
        }
        printf("[0]. %s\n", opcionesMatchmaking[0]);
        printf("=====================\n");
        printf("> Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                buscarCandidatosParaPuesto();
                break;
            case 2:
                buscarPuestosParaCandidato();
                break;
            case 0:
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 0);
}
// Función para crear archivos
void crearArchivo(const char *nombreArchivo) {
    FILE *archivo;
    char confirmacion;

    printf("\n--- Crear Archivo: %s ---\n", nombreArchivo);

    // 1. Verificación: ¿Ya existe?
    archivo = fopen(nombreArchivo, "rb");
    if (archivo != NULL) {
        fclose(archivo);
        printf("ATENCION: El archivo '%s' ya existe.\n", nombreArchivo);
        printf("Si continua, se SOBRESCRIBIRA (se borraran los datos viejos).\n");
        printf("Desea continuar? (s/n): ");
        scanf(" %c", &confirmacion);

        if (confirmacion != 's' && confirmacion != 'S') {
            printf("Operacion cancelada.\n");
            return;
        }
    }

    // 2. Creación: Modo "wb" (escritura binaria)
    archivo = fopen(nombreArchivo, "wb");

    if (archivo == NULL) {
        printf("Error: No se pudo crear el archivo '%s'.\n", nombreArchivo);
    } else {
        printf("Archivo '%s' creado exitosamente.\n", nombreArchivo);
        fclose(archivo);
    }
}

// ========= IMPLEMENTACIÓN DE GESTIÓN DE PUESTOS ==========

void crearArchivoPuestos() {
    crearArchivo("puestos.dat");
}

// 2. Función auxiliar para verificar ID duplicado
bool existeIdPuesto(int id) {
    FILE *archivo = fopen("puestos.dat", "rb");
    puesto p;

    // Si no existe el archivo, no hay duplicados
    if (archivo == NULL) return false;

    while (fread(&p, sizeof(struct puesto), 1, archivo)) {
        if (p.id == id) {
            fclose(archivo);
            return true;
        }
    }

    fclose(archivo);
    return false;
}

void altaPuesto() {
    puesto nuevoPuesto;
    FILE *archivo;

    printf("\n--- Grabar Nuevo Puesto (Alta) ---\n");

    // --- Validación de existencia del archivo ---
    // Usamos r+b para verificar existencia y luego escribir sin reabrir
    archivo = fopen("puestos.dat", "r+b");
    if (archivo == NULL) {
        printf("Error: El archivo 'puestos.dat' no existe. Debe crearlo primero.\n");
        return;
    }

    // --- Validación de ID ---
    printf("Ingrese ID del puesto (numero entero): ");
    scanf("%d", &nuevoPuesto.id);

    if (existeIdPuesto(nuevoPuesto.id)) {
        printf("Error: El ID %d ya existe en el sistema.\n", nuevoPuesto.id);
        fclose(archivo); // Cerramos el archivo antes de salir
        return;
    }

    // --- Carga de String (Nombre) ---
    printf("Ingrese nombre del cargo: ");
    while(getchar() != '\n'); // Limpia el buffer del teclado
    fgets(nuevoPuesto.nombreCargo, sizeof(nuevoPuesto.nombreCargo), stdin);
    // Elimina el salto de línea al final
    nuevoPuesto.nombreCargo[strcspn(nuevoPuesto.nombreCargo, "\n")] = 0;

    // --- Validaciones de Lógica (Edades) ---
    do {
        printf("Ingrese Edad Minima requerida (18-65): ");
        scanf("%d", &nuevoPuesto.edadMinima);
        printf("Ingrese Edad Maxima requerida (18-65): ");
        scanf("%d", &nuevoPuesto.edadMaxima);

        // Validar rango de edad laboral (18 a 65, antes de jubilación)
        if (nuevoPuesto.edadMinima < 18 || nuevoPuesto.edadMinima > 65) {
            printf("Error: La edad minima debe estar entre 18 y 65.\n");
        } else if (nuevoPuesto.edadMaxima < 18 || nuevoPuesto.edadMaxima > 65) {
            printf("Error: La edad maxima debe estar entre 18 y 65.\n");
        } else if (nuevoPuesto.edadMinima > nuevoPuesto.edadMaxima) {
            printf("Error: La edad minima no puede ser mayor a la maxima.\n");
        }
    } while (nuevoPuesto.edadMinima < 18 || nuevoPuesto.edadMinima > 65 ||
             nuevoPuesto.edadMaxima < 18 || nuevoPuesto.edadMaxima > 65 ||
             nuevoPuesto.edadMinima > nuevoPuesto.edadMaxima);

    // --- Validación de Nivel de Educación (1-5) ---
    do {
        printf("Nivel de Educacion (1-Primaria, 2-Secundaria, 3-Terciaria, 4-Grado, 5-Posgrado): ");
        scanf("%d", &nuevoPuesto.nivelEducacionReq);
        if (nuevoPuesto.nivelEducacionReq < 1 || nuevoPuesto.nivelEducacionReq > 5) {
            printf("Error: El nivel de educacion debe estar entre 1 y 5.\n");
        }
    } while (nuevoPuesto.nivelEducacionReq < 1 || nuevoPuesto.nivelEducacionReq > 5);

    // --- Validación de Años de Experiencia (0-100) ---
    do {
        printf("Anios de Experiencia requeridos (0-100): ");
        scanf("%d", &nuevoPuesto.aniosExperienciaReq);
        if (nuevoPuesto.aniosExperienciaReq < 0 || nuevoPuesto.aniosExperienciaReq > 100) {
            printf("Error: Los anios de experiencia deben estar entre 0 y 100.\n");
        }
    } while (nuevoPuesto.aniosExperienciaReq < 0 || nuevoPuesto.aniosExperienciaReq > 100);

    // --- Estado Inicial ---
    nuevoPuesto.activo = true;

    // --- Guardado en Disco ---
    // Movemos el puntero al final del archivo para añadir el nuevo registro
    fseek(archivo, 0, SEEK_END);
    fwrite(&nuevoPuesto, sizeof(struct puesto), 1, archivo);
    fclose(archivo);

    printf("\n>> Puesto '%s' (ID: %d) registrado exitosamente.\n", nuevoPuesto.nombreCargo, nuevoPuesto.id);
}

void bajaLogicaPuesto() {
    FILE *fp = fopen("puestos.dat", "rb+");
    if (fp == NULL) {
        printf("Error al abrir el archivo de puestos.\n");
        return;
    }

    int id;
    puesto p;
    bool encontrado = false;

    printf("Ingrese el ID del puesto a dar de baja logica: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(puesto), 1, fp)) {
        if (p.id == id && p.activo) {
            p.activo = false;
            fseek(fp, -sizeof(puesto), SEEK_CUR);
            fwrite(&p, sizeof(puesto), 1, fp);
            encontrado = true;
            break;
        }
    }

    fclose(fp);

    if (encontrado)
        printf("Puesto dado de baja logica correctamente.\n");
    else
        printf("Puesto no encontrado o ya estaba inactivo.\n");
}

void bajaFisicaPuesto() {
    FILE *fp = fopen("puestos.dat", "rb");
    FILE *aux = fopen("aux.dat", "wb");

    if (fp == NULL || aux == NULL) {
        printf("Error al abrir archivos.\n");
        return;
    }

    int id;
    puesto p;
    bool eliminado = false;

    printf("Ingrese el ID del puesto a eliminar fisicamente: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(puesto), 1, fp)) {
        if (p.id != id) {
            fwrite(&p, sizeof(puesto), 1, aux);
        } else {
            eliminado = true;
        }
    }

    fclose(fp);
    fclose(aux);

    remove("puestos.dat");
    rename("aux.dat", "puestos.dat");

    if (eliminado)
        printf("Puesto eliminado fisicamente.\n");
    else
        printf("Puesto no encontrado.\n");
}

void modificarPuesto() {
    printf("\n--- Modificar Puesto (en construccion) ---\n");
}

void listarPuestos() {
    printf("\n--- Listar Puestos (en construccion) ---\n");
}

void consultarPuesto() {
    printf("\n--- Consultar Puesto (en construccion) ---\n");
}

// ========= IMPLEMENTACIÓN DE GESTIÓN DE EMPLEADOS ==========

void crearArchivoEmpleados() {
    crearArchivo("empleados.dat");
}

// 2. Función auxiliar para validar DNI duplicado
bool existeDniEmpleado(int dni) {
    FILE *archivo = fopen("empleados.dat", "rb");
    empleado e;

    // Si no existe el archivo, no hay duplicados
    if (archivo == NULL) return false;

    while (fread(&e, sizeof(struct empleado), 1, archivo)) {
        if (e.dni == dni) {
            fclose(archivo);
            return true;
        }
    }

    fclose(archivo);
    return false;
}

void altaEmpleado() {
    empleado nuevoEmp;
    FILE *archivo;

    printf("\n--- Grabar Nuevo Empleado (Alta) ---\n");

    // --- Validación de existencia del archivo ---
    // Usamos r+b para verificar existencia y luego escribir sin reabrir
    archivo = fopen("empleados.dat", "r+b");
    if (archivo == NULL) {
        printf("Error: El archivo 'empleados.dat' no existe. Debe crearlo primero.\n");
        return;
    }

    // --- Validación de DNI ---
    printf("Ingrese DNI (sin puntos): ");
    scanf("%d", &nuevoEmp.dni);

    if (existeDniEmpleado(nuevoEmp.dni)) {
        printf("Error: El DNI %d ya esta registrado en el sistema.\n", nuevoEmp.dni);
        fclose(archivo); // Cerramos el archivo antes de salir
        return;
    }

    // --- Carga de Nombre ---
    printf("Ingrese Nombre y Apellido: ");
    while(getchar() != '\n'); // Limpia el buffer del teclado (el Enter del dni)
    fgets(nuevoEmp.nombre, sizeof(nuevoEmp.nombre), stdin);
    // Elimina el salto de línea al final
    nuevoEmp.nombre[strcspn(nuevoEmp.nombre, "\n")] = 0;

    // --- Validación de Edad (rango laboral 18-65) ---
    do {
        printf("Ingrese Edad (18-65): ");
        scanf("%d", &nuevoEmp.edad);
        if (nuevoEmp.edad < 18 || nuevoEmp.edad > 65) {
            printf("Error: La edad debe estar entre 18 y 65 (edad laboral).\n");
        }
    } while (nuevoEmp.edad < 18 || nuevoEmp.edad > 65);

    // --- Validación de Nivel de Educación (1-5) ---
    do {
        printf("Nivel de Educacion (1-Primaria, 2-Secundaria, 3-Terciaria, 4-Grado, 5-Posgrado): ");
        scanf("%d", &nuevoEmp.nivelEducacion);
        if (nuevoEmp.nivelEducacion < 1 || nuevoEmp.nivelEducacion > 5) {
            printf("Error: El nivel de educacion debe estar entre 1 y 5.\n");
        }
    } while (nuevoEmp.nivelEducacion < 1 || nuevoEmp.nivelEducacion > 5);

    // --- Validación de Años de Experiencia (0-100) ---
    do {
        printf("Anios de Experiencia (0-100): ");
        scanf("%d", &nuevoEmp.aniosExperiencia);
        if (nuevoEmp.aniosExperiencia < 0 || nuevoEmp.aniosExperiencia > 100) {
            printf("Error: Los anios de experiencia deben estar entre 0 y 100.\n");
        }
    } while (nuevoEmp.aniosExperiencia < 0 || nuevoEmp.aniosExperiencia > 100);

    // --- Estado Inicial ---
    nuevoEmp.activo = true;

    // --- Guardado en Disco ---
    // Movemos el puntero al final del archivo para añadir el nuevo registro
    fseek(archivo, 0, SEEK_END);
    fwrite(&nuevoEmp, sizeof(struct empleado), 1, archivo);
    fclose(archivo);

    printf("\n>> Empleado '%s' (DNI: %d) registrado exitosamente.\n", nuevoEmp.nombre, nuevoEmp.dni);
}

void bajaLogicaEmpleado() {
    FILE *fp = fopen("empleados.dat", "rb+");
    if (fp == NULL) {
        printf("Error al abrir el archivo de empleados.\n");
        return;
    }

    int dni;
    empleado e;
    bool encontrado = false;

    printf("Ingrese el DNI del empleado a dar de baja logica: ");
    scanf("%d", &dni);

    while (fread(&e, sizeof(empleado), 1, fp)) {
        if (e.dni == dni && e.activo) {
            e.activo = false;
            fseek(fp, -sizeof(empleado), SEEK_CUR);
            fwrite(&e, sizeof(empleado), 1, fp);
            encontrado = true;
            break;
        }
    }

    fclose(fp);

    if (encontrado)
        printf("Empleado dado de baja logica correctamente.\n");
    else
        printf("Empleado no encontrado o ya estaba inactivo.\n");
}

void bajaFisicaEmpleado() {
    FILE *fp = fopen("empleados.dat", "rb");
    FILE *aux = fopen("aux.dat", "wb");

    if (fp == NULL || aux == NULL) {
        printf("Error al abrir archivos.\n");
        return;
    }

    int dni;
    empleado e;
    bool eliminado = false;

    printf("Ingrese el DNI del empleado a eliminar fisicamente: ");
    scanf("%d", &dni);

    while (fread(&e, sizeof(empleado), 1, fp)) {
        if (e.dni != dni) {
            fwrite(&e, sizeof(empleado), 1, aux);
        } else {
            eliminado = true;
        }
    }

    fclose(fp);
    fclose(aux);

    remove("empleados.dat");
    rename("aux.dat", "empleados.dat");

    if (eliminado)
        printf("Empleado eliminado fisicamente.\n");
    else
        printf("Empleado no encontrado.\n");
}


void modificarEmpleado() {
    printf("\n--- Modificar Empleado (en construccion) ---\n");
}

void listarEmpleados() {
    printf("\n--- Listar Empleados (en construccion) ---\n");
}

void consultarEmpleado() {
    printf("\n--- Consultar Empleado (en construccion) ---\n");
}

// ========= IMPLEMENTACIÓN DE MATCHMAKING ==========

void buscarCandidatosParaPuesto() {
    printf("\n--- Buscar Candidatos para Puesto (en construccion) ---\n");
}

void buscarPuestosParaCandidato() {
    printf("\n--- Buscar Puestos para Candidato (en construccion) ---\n");
}

// ========= IMPLEMENTACIÓN DE GESTIÓN DE USUARIOS ==========

void registrarUsuario() {
    if (cantidadUsuarios >= 100) {
        printf("Error: Se ha alcanzado el limite maximo de usuarios.\n");
        return;
    }

    usuario nuevoUsuario;
    printf("\n--- Registrar Nuevo Usuario ---\n");

    do {
        printf("Ingrese nombre de usuario (6-10 chars, 1ra minus, min 2 mayus, max 3 dig): ");
        scanf("%s", nuevoUsuario.user);
        if (!validarUsuario(nuevoUsuario.user)) {
            printf("Error: El nombre de usuario no cumple con las reglas.\n");
        }
    } while (!validarUsuario(nuevoUsuario.user));

    do {
        printf("Ingrese contrasena (6-32 chars, 1 mayus, 1 minus, 1 num, sin simbolos ni secuencias): ");
        scanf("%s", nuevoUsuario.pass);
        if (!validarPass(nuevoUsuario.pass)) {
            printf("Error: La contrasena no cumple con las reglas de seguridad.\n");
        }
    } while (!validarPass(nuevoUsuario.pass));

    printf("Ingrese su nombre completo: ");
    while(getchar() != '\n') {} // Limpiamos el buffer de manera segura
    fgets(nuevoUsuario.nombre, sizeof(nuevoUsuario.nombre), stdin);

    // Reemplaza el '\n' con '\0' para terminar la cadena sin el salto de línea y no guardar datos extras.
    nuevoUsuario.nombre[strcspn(nuevoUsuario.nombre, "\n")] = 0;

    usuariosEnMemoria[cantidadUsuarios] = nuevoUsuario;
    cantidadUsuarios++;

    printf("\nUsuario '%s' registrado correctamente en memoria.\n", nuevoUsuario.user);
}

void iniciarSesion() {
    char user[11];
    char pass[33];
    bool encontrado = false;

    printf("\n--- Iniciar Sesion ---\n");
    printf("Usuario: ");
    scanf("%s", user);
    printf("Contrasena: ");
    scanf("%s", pass);

    for (int i = 0; i < cantidadUsuarios; i++) {
        if (strcmp(user, usuariosEnMemoria[i].user) == 0 && strcmp(pass, usuariosEnMemoria[i].pass) == 0) {
            printf("\nBienvenido, %s! Sesion iniciada correctamente.\n", usuariosEnMemoria[i].nombre);
            sesionActiva = true;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        printf("\nError: Usuario o contrasena incorrectos.\n");
        sesionActiva = false;
    }
}

void cargarUsuariosEnMemoria() {
    FILE *archivo = fopen("usuarios.dat", "rb");
    if (archivo == NULL) {
        printf("Archivo 'usuarios.dat' no encontrado. Se creara uno nuevo al registrar usuarios.\n");
        return;
    }

    cantidadUsuarios = 0;
    // No usamos feof() para evitar desbordes en la lectura.
    while(fread(&usuariosEnMemoria[cantidadUsuarios], sizeof(usuario), 1, archivo) == 1) {
        cantidadUsuarios++;
        if (cantidadUsuarios >= 100) break;
    }
    fclose(archivo);
    printf("Se cargaron %d usuarios en memoria.\n", cantidadUsuarios);
}

void guardarUsuariosEnArchivo() {
    FILE *archivo = fopen("usuarios.dat", "wb");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo para guardar los usuarios.\n");
        return;
    }

    fwrite(usuariosEnMemoria, sizeof(usuario), cantidadUsuarios, archivo);
    fclose(archivo);
    printf("Se guardaron %d usuarios en 'usuarios.dat'.\n", cantidadUsuarios);
}

// ========== IMPLEMENTACIÓN DE VALIDACIONES ==========

bool esCaracterPermitido(char c) {
    char permitidos[] = "+-/*?!";
    // strchr busca el caracter 'c' en la cadena 'permitidos'.
    // Si lo encuentra, devuelve un puntero (no NULL), y la expresión es verdadera.
    // Si no lo encuentra, devuelve NULL, y la expresión es falsa.
    return NULL != strchr(permitidos, c);
}

bool validarUsuario(char user[]) {
    // Cantidad mínima de 6 caracteres y máxima de 10.
    int len = strlen(user);
    if (len < 6 || len > 10) return false;

    // b. Comenzar con una letra minúscula.
    if (!islower(user[0])) return false;

    int mayusculas = 0;
    int digitos = 0;
    for (int i = 0; i < len; i++) {
        // c. Tener al menos 2 letras mayúsculas.
        if (isupper(user[i])) mayusculas++;
        // d. Tener como máximo 3 dígitos.
        if (isdigit(user[i])) digitos++;
        // Podrán ser letras, números y/o símbolos del conjunto {+,-,/,*,?,!}
        if (!isupper(user[i]) && !islower(user[i]) && !isdigit(user[i]) && !esCaracterPermitido(user[i])) {
            return false;
        }
    }

    // c. Tener al menos 2 letras mayúsculas.
    if (mayusculas < 2) return false;
    // d. Tener como máximo 3 dígitos.
    if (digitos > 3) return false;

    return true;
}

bool validarPass(char pass[]) {
    // c. Deberá tener entre 6 y 32 caracteres.
    int len = strlen(pass);
    if (len < 6 || len > 32) return false;

    bool tieneMayuscula = false;
    bool tieneMinuscula = false;
    bool tieneNumero = false;

    for (int i = 0; i < len; i++) {
        // a. Deberá contener al menos una letra mayúscula, una letra minúscula y un número.
        if (isupper(pass[i])) tieneMayuscula = true;
        if (islower(pass[i])) tieneMinuscula = true;
        if (isdigit(pass[i])) tieneNumero = true;

        // b. No podrá contener ningún carácter de puntuación, ni acentos, ni espacios. Sólo caracteres alfanuméricos.
        if (!isalnum(pass[i])) return false;

        // d. No debe tener más de 3 caracteres numéricos consecutivos en secuencia ascendente.
        if (i > 1 && isdigit(pass[i]) && isdigit(pass[i-1]) && isdigit(pass[i-2])) {
             if (pass[i] == pass[i-1] + 1 && pass[i-1] == pass[i-2] + 1) return false;
        }

        // e. No debe tener 2 caracteres consecutivos que refieran a letras alfabéticamente consecutivas (ascendentemente).
        //    Este criterio es válido tanto para letras mayúsculas, minúsculas o combinación de ambas.
        if (i > 0 && isalpha(pass[i]) && isalpha(pass[i-1])) {
            if (tolower(pass[i]) == tolower(pass[i-1]) + 1) {
                return false;
            }
        }
    }

    // a. Deberá contener al menos una letra mayúscula, una letra minúscula y un número.
    return tieneMayuscula && tieneMinuscula && tieneNumero;
}
