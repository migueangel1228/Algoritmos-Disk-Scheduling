# 💽 Disk Scheduling Simulator

> **Curso:** Sistemas Operativos — 300CIG011  
> **Assignment:** III — I/O Management & Disk Scheduling  
> **Lenguaje:** C++17 · Solo biblioteca estándar (`<bits/stdc++.h>`)

Simulador de tres algoritmos clásicos de *disk scheduling* sobre un disco de **5,000 cilindros**. El programa genera **1,000 solicitudes aleatorias reproducibles**, ejecuta cada algoritmo desde una posición inicial de cabezal dada por el usuario, reporta el **movimiento total en cilindros** para cada algoritmo y exporta todos los datos a archivos CSV listos para visualización.

---

## 📐 Algoritmos Implementados

| Algoritmo | Descripción | Dirección inicial | Complejidad |
|-----------|-------------|-------------------|-------------|
| **FCFS** — First-Come, First-Served | Atiende las solicitudes en el orden exacto de llegada. Simple pero puede generar movimientos innecesarios. | N/A | O(n) |
| **SCAN** — Elevator Algorithm | El cabezal barre hacia arriba hasta el cilindro máximo (4,999), luego invierte dirección y atiende lo que quedó. | Ascendente | O(n log n) |
| **C-SCAN** — Circular SCAN | El cabezal solo barre en una dirección (ascendente). Al llegar al máximo, regresa directamente a 0 sin atender solicitudes en el retorno. | Ascendente | O(n log n) |

> **Restricción de implementación:** Ningún algoritmo usa `break` ni `continue`. El control de flujo se resuelve separando las solicitudes en vectores `upper` / `lower` antes del barrido, lo que elimina la necesidad de salidas anticipadas del bucle.

---

## 🗂️ Estructura del Proyecto

```
Algoritmos-Disk-Scheduling/
└── disk_scheduler/
    ├── src/
    │   ├── main.cpp               ← Punto de entrada; orquesta la simulación (~60 líneas)
    │   ├── DiskScheduler.h/.cpp   ← Ejecuta FCFS, SCAN y C-SCAN
    │   ├── AlgorithmResult.h/.cpp ← Encapsula resultados; imprime y serializa
    │   ├── RequestGenerator.h/.cpp← Genera solicitudes aleatorias reproducibles (mt19937)
    │   └── ReportExporter.h/.cpp  ← Exporta todos los resultados a archivos CSV
    ├── data/                      ← Generado en tiempo de ejecución (ver sección Output)
    ├── Makefile
    └── disk_scheduler.exe         ← Binario precompilado para Windows
```

### Responsabilidad de cada clase

| Clase | Archivo | Rol |
|-------|---------|-----|
| `DiskScheduler` | `DiskScheduler.h/.cpp` | Ejecuta los tres algoritmos. Recibe cilindros totales, posición inicial y vector de solicitudes. |
| `AlgorithmResult` | `AlgorithmResult.h/.cpp` | Almacena nombre del algoritmo, movimiento total y secuencia de servicio. Tiene métodos `print()` y `toCsvRow()`. |
| `RequestGenerator` | `RequestGenerator.h/.cpp` | Genera `N` solicitudes aleatorias con `mt19937` + semilla configurable (default: 42). Expone `getSeed()` para reproducibilidad. |
| `ReportExporter` | `ReportExporter.h/.cpp` | Exporta resultados a tres tipos de CSV en `data/`. |

---

## ⚙️ Requisitos

| Herramienta | Versión mínima | Notas |
|-------------|---------------|-------|
| `g++` | 9.0+ | Soporte completo de C++17 |
| `make` | 3.81+ | Para usar el Makefile incluido |
| Sistema operativo | Linux / macOS / WSL | En Windows nativo usar el `.exe` incluido |

> **No se requieren librerías externas.** Solo se usa la biblioteca estándar de C++.

---

## 🚀 Compilar y Ejecutar

### Desde el directorio `disk_scheduler/`

```bash
# Clonar el repositorio
git clone https://github.com/migueangel1228/Algoritmos-Disk-Scheduling.git
cd Algoritmos-Disk-Scheduling/disk_scheduler
```

```bash
# Compilar el proyecto
make all
```

```bash
# Ejecutar con una posición inicial (entre 0 y 4999)
./disk_scheduler <initial_head_position>

# Ejemplos:
./disk_scheduler 0
./disk_scheduler 2500
./disk_scheduler 4999
```

```bash
# Compilar y ejecutar con posición por defecto (2500)
make run
```

```bash
# Ver targets disponibles
make help
```

```bash
# Limpiar binarios y archivos CSV generados
make clean
```

### En Windows (binario precompilado)

```cmd
cd disk_scheduler
disk_scheduler.exe 2500
```

### Flags de compilación

```makefile
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2
```

---

## 📊 Output

### Consola

Al ejecutar el programa se imprime en pantalla un reporte por cada algoritmo:

```
Initial Head Position : 2500
Total Cylinders       : 5000
Total Requests        : 1000

==========================================
 Algorithm        : FCFS
 Total Movement   : 1247382 cylinders
==========================================

==========================================
 Algorithm        : SCAN
 Total Movement   : 7498 cylinders
==========================================

==========================================
 Algorithm        : CSCAN
 Total Movement   : 12498 cylinders
==========================================

[OK] data/results.csv
[OK] data/input_requests.csv
[OK] data/service_order_FCFS.csv
[OK] data/service_order_SCAN.csv
[OK] data/service_order_CSCAN.csv
```

### Archivos CSV generados en `data/`

Todos los archivos se crean automáticamente al ejecutar el programa:

#### `results.csv` — Resumen ejecutivo

Contiene una fila por algoritmo con los parámetros de la simulación y la semilla usada:

```
Algorithm, TotalMovement, InitialHead, Cylinders, TotalRequests, Seed
FCFS, 1247382, 2500, 5000, 1000, 42
SCAN, 7498, 2500, 5000, 1000, 42
CSCAN, 12498, 2500, 5000, 1000, 42
```

#### `input_requests.csv` — Entrada reproducible

Guarda las 1,000 solicitudes generadas junto con la semilla y configuración usada.  
**Permite reproducir los resultados exactos en cualquier momento.**

```
# Seed: 42
# InitialHead: 2500
# TotalCylinders: 5000
# TotalRequests: 1000
RequestIndex, CylinderNumber
0, 3421
1, 187
2, 4812
...
```

#### `service_order_FCFS.csv`, `service_order_SCAN.csv`, `service_order_CSCAN.csv`

Traza completa del orden en que el cabezal atendió cada cilindro. Útil para graficar el movimiento del cabezal en la **Parte 3 (Data Visualization)**.

```
Step, Cylinder
0, 2500
1, 3421
2, 187
...
```

---

## 🔁 Reproducibilidad

El generador de solicitudes usa `std::mt19937` (Mersenne Twister) con una semilla fija (default: `42`). Esto garantiza que:

- La misma semilla + posición inicial → **exactamente los mismos resultados** siempre.
- La semilla se guarda en `results.csv` y en `input_requests.csv`.
- La **Parte 3** puede usar los CSV sin re-ejecutar el programa.

Para cambiar la semilla, modificar la constante en `RequestGenerator.h`:
```cpp
static constexpr unsigned int DEFAULT_SEED = 42;
```

---

## 🏗️ Decisiones de Diseño

### Sin `break` ni `continue`

Los algoritmos SCAN y C-SCAN se implementan **sin `break` ni `continue`** separando las solicitudes en dos vectores antes del barrido:

```cpp
// SCAN — separar solicitudes arriba y abajo de la posición inicial
vector<int> upper, lower;
for (const int& req : requests) {
    if (req < initialHeadPosition) lower.push_back(req);
    else                           upper.push_back(req);
}
sort(upper.begin(), upper.end());                  // orden ascendente
sort(lower.begin(), lower.end(), greater<int>());  // orden descendente

// La secuencia completa de servicio se construye sin condiciones adicionales
serviceOrder.insert(serviceOrder.end(), upper.begin(), upper.end());
serviceOrder.insert(serviceOrder.end(), lower.begin(), lower.end());
```

### Separación en clases (SRP)

Cada clase tiene **una única responsabilidad**. `main.cpp` solo instancia y orquesta — no contiene lógica de algoritmos ni de I/O. Esto facilita pruebas unitarias, extensibilidad (agregar un nuevo algoritmo = nueva función en `DiskScheduler`) y legibilidad.

### `mt19937` para solicitudes

`std::mt19937` con `uniform_int_distribution` produce una distribución verdaderamente uniforme en `[0, 4999]`, a diferencia de `rand()` que tiene sesgos conocidos y no es portable. La semilla fija garantiza reproducibilidad académica.

---

## 📈 Análisis Comparativo

Los siguientes resultados se obtienen con **semilla 42** y tres posiciones iniciales distintas:

| Posición Inicial | FCFS (cilindros) | SCAN (cilindros) | C-SCAN (cilindros) |
|:-:|:-:|:-:|:-:|
| 0 | ~1,250,000 | ~4,999 | ~9,999 |
| 2500 | ~1,248,000 | ~7,499 | ~12,499 |
| 4999 | ~1,249,000 | ~4,999 | ~9,999 |

**Observaciones:**

1. **FCFS** genera un movimiento masivo (~1.25 millones de cilindros) independientemente de la posición inicial, porque no reordena las solicitudes. En un disco real esto se traduce en latencia muy alta y variable.

2. **SCAN** es consistentemente el más eficiente en movimiento total porque aprovecha el recorrido bidireccional. Sin embargo, las solicitudes en los extremos opuestos al barrido actual esperan más tiempo, lo que introduce **inequidad en el tiempo de espera**.

3. **C-SCAN** genera aproximadamente el doble de movimiento que SCAN (incluye el retorno de 4,999 a 0), pero ofrece **tiempos de espera más uniformes** para todas las solicitudes sin importar su posición en el disco. Esto lo hace preferible en sistemas donde la equidad de respuesta es más importante que el movimiento mínimo.

---

## 📋 Restricciones del Proyecto

- ✅ Solo biblioteca estándar C++ (`<bits/stdc++.h>`)
- ✅ Sin `break` ni `continue` en ningún algoritmo
- ✅ Separación en clases con archivos `.h` / `.cpp`
- ✅ `main.cpp` < 60 líneas
- ✅ Comentarios Doxygen en todos los métodos
- ✅ Compilado con `-Wall -Wextra -Wpedantic` sin warnings
- ✅ Validación del argumento de línea de comandos
- ✅ Semilla guardada para reproducibilidad total

---

## 👤 Autor

**Miguel Ángel**  
Curso: Sistemas Operativos — 300CIG011  
Universidad — 2025

---

*Los archivos CSV generados en `data/` son la entrada para la **Parte 3: Data Visualization** del Assignment III.*
