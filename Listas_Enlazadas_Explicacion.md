# 📚 Listas Enlazadas - Documentación del Proyecto TFI 2

## Índice
1. [¿Qué es una Lista Enlazada?](#qué-es-una-lista-enlazada)
2. [Estructura de un Nodo](#estructura-de-un-nodo)
3. [Implementación en el Proyecto](#implementación-en-el-proyecto)
4. [Operaciones Implementadas](#operaciones-implementadas)
5. [Diagrama Visual](#diagrama-visual)
6. [Uso en el Módulo de Matchmaking](#uso-en-el-módulo-de-matchmaking)

---

## ¿Qué es una Lista Enlazada?

Una **lista enlazada** es una estructura de datos dinámica compuesta por una secuencia de **nodos**. A diferencia de los arreglos (arrays), las listas enlazadas:

| Característica | Arreglo | Lista Enlazada |
|----------------|---------|----------------|
| Tamaño | Fijo (definido en compilación) | Dinámico (crece según necesidad) |
| Memoria | Contigua | Dispersa |
| Acceso | Directo por índice `arr[i]` | Secuencial (recorrer desde el inicio) |
| Inserción/Eliminación | Costoso (mover elementos) | Eficiente (cambiar punteros) |

### ¿Por qué usamos listas enlazadas en este proyecto?

En el módulo de **Matchmaking**, necesitamos:
- Cargar datos desde archivos binarios sin conocer previamente la cantidad de registros.
- Evitar límites fijos de memoria (como el límite de 100 usuarios).
- Realizar búsquedas y comparaciones eficientes en memoria.

---

## Estructura de un Nodo

Un **nodo** es la unidad básica de una lista enlazada. Contiene dos partes:

1. **Dato**: La información que queremos almacenar.
2. **Puntero al siguiente**: Una referencia al próximo nodo de la lista.

### Definición en el Proyecto

```c
// Nodo para almacenar empleados
struct nodoEmpleado {
    empleado dato;      // Información del empleado
    nodoEmpleado *sig;  // Puntero al siguiente nodo
};

// Nodo para almacenar puestos
struct nodoPuesto {
    puesto dato;        // Información del puesto
    nodoPuesto *sig;    // Puntero al siguiente nodo
};
```

### Explicación Campo por Campo

| Campo | Tipo | Descripción |
|-------|------|-------------|
| `dato` | `empleado` o `puesto` | Estructura que contiene toda la información del registro |
| `sig` | Puntero a nodo | Dirección de memoria del siguiente nodo. Si es `NULL`, indica el fin de la lista |

---

## Implementación en el Proyecto

### Variables Globales (Punteros de Cabecera)

```c
nodoEmpleado *listaEmpleados = NULL;  // Cabecera de la lista de empleados
nodoPuesto *listaPuestos = NULL;      // Cabecera de la lista de puestos
```

Estos punteros apuntan al **primer nodo** de cada lista. Si valen `NULL`, la lista está vacía.

---

## Operaciones Implementadas

### 1. Cargar Datos en la Lista (Inserción al Final)

La función `cargarEmpleadosEnLista()` lee registros de un archivo binario y los inserta en la lista:

```c
void cargarEmpleadosEnLista() {
    // 1. Liberar lista anterior (evita fugas de memoria)
    liberarListaEmpleados();

    // 2. Abrir archivo binario
    FILE *fp = fopen("empleados.dat", "rb");
    if (fp == NULL) {
        printf("Aviso: No se pudo abrir empleados.dat.\n");
        return;
    }

    empleado e;
    int contador = 0;
    nodoEmpleado *ultimo = NULL;  // Puntero auxiliar al último nodo

    // 3. Leer cada registro del archivo
    while (fread(&e, sizeof(empleado), 1, fp)) {
        // Solo cargar empleados activos (no dados de baja)
        if (e.activo) {
            // 4. Crear nuevo nodo con memoria dinámica
            nodoEmpleado *nuevo = new nodoEmpleado;
            
            if (nuevo == NULL) {
                printf("Error: Memoria insuficiente.\n");
                break;
            }

            // 5. Asignar datos al nodo
            nuevo->dato = e;
            nuevo->sig = NULL;  // Será el último nodo

            // 6. Insertar al final de la lista
            if (listaEmpleados == NULL) {
                // Lista vacía: el nuevo nodo es el primero
                listaEmpleados = nuevo;
            } else {
                // Lista no vacía: enlazar después del último
                ultimo->sig = nuevo;
            }
            ultimo = nuevo;  // Actualizar puntero al último
            contador++;
        }
    }

    fclose(fp);
    printf(">> %d empleado(s) cargado(s) en memoria.\n", contador);
}
```

#### Paso a Paso Visual

**Estado Inicial:** Lista vacía
```
listaEmpleados = NULL
```

**Después de insertar el primer empleado (DNI: 12345678):**
```
listaEmpleados → [12345678 | NULL]
```

**Después de insertar el segundo empleado (DNI: 87654321):**
```
listaEmpleados → [12345678 | •] → [87654321 | NULL]
```

**Después de insertar el tercer empleado (DNI: 11223344):**
```
listaEmpleados → [12345678 | •] → [87654321 | •] → [11223344 | NULL]
```

---

### 2. Mostrar la Lista (Recorrido)

La función `mostrarListaEmpleados()` recorre toda la lista desde el inicio hasta el final:

```c
void mostrarListaEmpleados() {
    // Verificar si la lista está vacía
    if (listaEmpleados == NULL) {
        printf("La lista de empleados esta vacia.\n");
        return;
    }

    printf("\n--- Empleados en Memoria ---\n");
    
    // Puntero auxiliar para recorrer (no modificar la cabecera)
    nodoEmpleado *p = listaEmpleados;
    int i = 1;

    // Recorrer mientras no lleguemos al final (NULL)
    while (p != NULL) {
        // Acceder a los datos del nodo actual
        printf("[%d] DNI: %d\n", i, p->dato.dni);
        printf("    Nombre: %s\n", p->dato.nombre);
        
        // Avanzar al siguiente nodo
        p = p->sig;
        i++;
    }

    printf("\n>> Total: %d empleado(s) en la lista.\n", i - 1);
}
```

#### ¿Por qué usamos un puntero auxiliar `p`?

Si usáramos directamente `listaEmpleados` para recorrer, al terminar perderíamos la referencia al inicio de la lista. El puntero `p` nos permite navegar sin modificar la cabecera.

---

### 3. Liberar Memoria (Eliminación de toda la lista)

La función `liberarListaEmpleados()` elimina todos los nodos y libera la memoria:

```c
void liberarListaEmpleados() {
    nodoEmpleado *actual = listaEmpleados;
    nodoEmpleado *siguiente;

    while (actual != NULL) {
        // 1. Guardar referencia al siguiente ANTES de eliminar
        siguiente = actual->sig;
        
        // 2. Liberar memoria del nodo actual
        delete actual;
        
        // 3. Avanzar al siguiente nodo
        actual = siguiente;
    }

    // 4. Marcar la lista como vacía
    listaEmpleados = NULL;
}
```

#### ¿Por qué guardamos `siguiente` antes de hacer `delete`?

Cuando ejecutamos `delete actual`, la memoria del nodo se libera y ya no podemos acceder a `actual->sig`. Por eso guardamos la referencia al siguiente nodo **antes** de eliminar.

---

## Diagrama Visual

### Estructura de la Lista Enlazada de Empleados

```
MEMORIA RAM
┌─────────────────────────────────────────────────────────────────┐
│                                                                 │
│  listaEmpleados                                                 │
│       │                                                         │
│       ▼                                                         │
│  ┌─────────────┐      ┌─────────────┐      ┌─────────────┐     │
│  │   NODO 1    │      │   NODO 2    │      │   NODO 3    │     │
│  ├─────────────┤      ├─────────────┤      ├─────────────┤     │
│  │ dato:       │      │ dato:       │      │ dato:       │     │
│  │  dni: 123   │      │  dni: 456   │      │  dni: 789   │     │
│  │  nombre:... │      │  nombre:... │      │  nombre:... │     │
│  │  edad: 25   │      │  edad: 30   │      │  edad: 28   │     │
│  ├─────────────┤      ├─────────────┤      ├─────────────┤     │
│  │ sig: ───────┼──────► sig: ───────┼──────► sig: NULL   │     │
│  └─────────────┘      └─────────────┘      └─────────────┘     │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

## Uso en el Módulo de Matchmaking

### Flujo de Trabajo

1. **Cargar datos**: Al ingresar al módulo de Matchmaking, se cargan empleados y puestos en sus respectivas listas enlazadas.

2. **Buscar candidatos**: Se recorre la lista de empleados comparando cada uno con los requisitos de un puesto específico.

3. **Liberar memoria**: Al salir del módulo, se liberan ambas listas.

### Función de Búsqueda de Candidatos

```c
void buscarCandidatosParaPuesto() {
    // Validar que las listas tengan datos
    if (listaPuestos == NULL || listaEmpleados == NULL) {
        printf("No hay datos cargados en memoria.\n");
        return;
    }

    int idBuscado;
    printf("Ingrese el ID del puesto: ");
    scanf("%d", &idBuscado);

    // 1. Buscar el puesto en la lista (recorrido de búsqueda)
    nodoPuesto *puestoActual = listaPuestos;
    puesto *puestoEncontrado = NULL;

    while (puestoActual != NULL) {
        if (puestoActual->dato.id == idBuscado) {
            puestoEncontrado = &(puestoActual->dato);
            break;  // Encontrado, salir del bucle
        }
        puestoActual = puestoActual->sig;  // Avanzar
    }

    if (puestoEncontrado == NULL) {
        printf("Puesto no encontrado.\n");
        return;
    }

    // 2. Recorrer empleados y verificar requisitos
    nodoEmpleado *empActual = listaEmpleados;
    int candidatosEncontrados = 0;

    while (empActual != NULL) {
        empleado *e = &(empActual->dato);

        // Verificar criterios de matchmaking
        bool cumpleEdad = (e->edad >= puestoEncontrado->edadMinima &&
                          e->edad <= puestoEncontrado->edadMaxima);
        bool cumpleEducacion = (e->nivelEducacion >= puestoEncontrado->nivelEducacionReq);
        bool cumpleExperiencia = (e->aniosExperiencia >= puestoEncontrado->aniosExperienciaReq);

        if (cumpleEdad && cumpleEducacion && cumpleExperiencia) {
            // Mostrar candidato válido
            printf("Candidato: %s (DNI: %d)\n", e->nombre, e->dni);
            candidatosEncontrados++;
        }

        empActual = empActual->sig;  // Avanzar al siguiente
    }

    printf("Total candidatos: %d\n", candidatosEncontrados);
}
```

---

## Conceptos Clave a Recordar

### 1. El operador `->` (flecha)
Se usa para acceder a los miembros de una estructura a través de un puntero:
```c
p->dato.dni    // Equivale a: (*p).dato.dni
p->sig         // Equivale a: (*p).sig
```

### 2. Asignación dinámica con `new`
```c
nodoEmpleado *nuevo = new nodoEmpleado;
```
- `new` reserva memoria en el **heap** (memoria dinámica).
- Retorna un puntero a la memoria reservada.
- La memoria persiste hasta que se libere con `delete`.

### 3. Liberación con `delete`
```c
delete actual;
```
- Libera la memoria que fue reservada con `new`.
- **Importante**: No usar el puntero después de `delete` (se vuelve inválido).

### 4. El valor `NULL`
- Indica que un puntero no apunta a ninguna dirección válida.
- Se usa para marcar el final de la lista (`sig = NULL`).
- Se usa para indicar lista vacía (`listaEmpleados = NULL`).

---

## Ventajas de esta Implementación

✅ **Sin límite fijo**: Podemos cargar tantos registros como memoria tengamos disponible.

✅ **Eficiencia en inserción**: Agregar al final es O(1) porque mantenemos un puntero `ultimo`.

✅ **Filtrado automático**: Solo cargamos registros activos, optimizando las búsquedas.

✅ **Liberación controlada**: La memoria se libera explícitamente al salir del módulo.

---

## Preguntas Frecuentes

### ¿Por qué no usar un arreglo dinámico?
Los arreglos requieren conocer el tamaño o redimensionar (realloc), lo cual puede ser costoso. Las listas permiten crecer nodo a nodo.

### ¿Qué pasa si no libero la memoria?
Se produce una **fuga de memoria** (memory leak). El programa consume más memoria cada vez que se carga la lista sin liberar la anterior.

### ¿Puedo acceder directamente al nodo N?
No de forma directa. Hay que recorrer desde el inicio. Para acceso directo, un arreglo sería más eficiente.

---

**Documento generado para el TFI 2 - AyED 2025 1K4**

*Autores: Burgos, Medina, Ruiz, Santucho*
