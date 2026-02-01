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
    int nivelEducacionReq;
    int aniosExperienciaReq;
    bool activo;
};

struct empleado {
    int dni;
    char nombre[100];
    int edad;
    int nivelEducacion;
    int aniosExperiencia;
    bool activo;
};

// ========== PROTOTIPO DE FUNCIONES ==========

// Menús
void menuLogin();
void menuPrincipal();
void menuGestionPuestos();
void menuGestionEmpleados();
void menuMatchmaking();

// Gestión de Usuarios
void cargarUsuariosEnMemoria();
void guardarUsuariosEnArchivo();
void registrarUsuario();
void iniciarSesion();

// Validaciones
bool validarUsuario(char user[]);
bool validarPass(char pass[]);

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

// Estado de sesión
bool sesionActiva = false;

// Usuarios
int cantidadUsuarios = 0;
usuario usuariosEnMemoria[100]; // Soporta hasta 100 usuarios


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
    printf("\n--- Gestion de Puestos (en construccion) ---\n");
    // Logica para ABM de puestos
}

void menuGestionEmpleados() {
    printf("\n--- Gestion de Empleados (en construccion) ---\n");
    // Logica para ABM de empleados
}

void menuMatchmaking() {
    printf("\n--- Matchmaking (en construccion) ---\n");
    // Logica para generar coincidencias
}

// ========= IMPLEMENTACIÓN DE GESTIÓN DE USUARIOS ==========

void registrarUsuario() {
    if (cantidadUsuarios >= 100) {
        printf("Error: Se ha alcanzado el limite maximo de usuarios.\n");
        return;
    }

    usuario nuevoUsuario; // Se actualiza el tipo de la variable
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
    while(getchar() != '\n');
    fgets(nuevoUsuario.nombre, sizeof(nuevoUsuario.nombre), stdin);
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
    // Se actualiza el tipo en sizeof()
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

    // Se actualiza el tipo en sizeof()
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
    int len = strlen(user);
    if (len < 6 || len > 10) return false;
    if (!islower(user[0])) return false;

    int mayusculas = 0;
    int digitos = 0;
    for (int i = 0; i < len; i++) {
        if (isupper(user[i])) mayusculas++;
        if (isdigit(user[i])) digitos++;
        if (!isupper(user[i]) && !islower(user[i]) && !isdigit(user[i]) && !esCaracterPermitido(user[i])) {
            return false; // Caracter no permitido
        }
    }

    if (mayusculas < 2) return false;
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

        // d. No debe tener más de 3 caracteres numéricos consecutivos.
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
