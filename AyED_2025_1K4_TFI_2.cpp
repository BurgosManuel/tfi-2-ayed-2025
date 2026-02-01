#include <stdio.h> // Libreria estandar para usar printf() y scanf().
#include <stdlib.h> // Libreria para hacer uso de la funcion rand().
#include <time.h> // Libreria utilizada para medir el tiempo de ejecucion de los algoritmos de ordenamiento.

// Estructuras de Datos (basadas en plan.md)
struct Usuario {
    char user[11];
    char pass[33];
    char nombre[60];
};

struct Puesto {
    int id;
    char nombreCargo[50];
    int nivelEducacionReq;
    int aniosExperienciaReq;
    int edadMinima;
    int edadMaxima;
    bool activo;
};

struct Empleado {
    int dni;
    char nombre[60];
    char apellido[60];
    int nivelEducacion;
    int aniosExperiencia;
    int edad;
    bool activo;
};

// Prototipos de Funciones
void menuPrincipal();
void menuGestionPuestos();
void menuGestionEmpleados();
void menuMatchmaking();
void iniciarSesion();
void registrarUsuario();

main()
{
    printf("========== SISTEMA DE GESTION Y MATCHMAKING LABORAL ==========\n");
    menuPrincipal();
}

void menuPrincipal() {
    int opcion;
    do {
        printf("\n========== MENU PRINCIPAL ==========\n");
        printf("[1]. Iniciar Sesion\n");
        printf("[2]. Registrar Nuevo Usuario\n");
        printf("[3]. Gestion de Puestos (Requiere Sesion)\n");
        printf("[4]. Gestion de Empleados (Requiere Sesion)\n");
        printf("[5]. Matchmaking (Requiere Sesion)\n");
        printf("[0]. Salir\n");
        printf("==================================\n");
        printf("> Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                iniciarSesion();
                break;
            case 2:
                registrarUsuario();
                break;
            case 3:
                // A futuro, verificar si hay sesion activa
                menuGestionPuestos();
                break;
            case 4:
                // A futuro, verificar si hay sesion activa
                menuGestionEmpleados();
                break;
            case 5:
                 // A futuro, verificar si hay sesion activa
                menuMatchmaking();
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 0);
}

void iniciarSesion() {
    printf("\n--- Iniciar Sesion (en construccion) ---\n");
    // Logica de inicio de sesion aqui
}

void registrarUsuario() {
    printf("\n--- Registrar Usuario (en construccion) ---\n");
    // Logica de registro de usuario aqui
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