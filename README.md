# MiniDB

MiniDB es un sistema ligero de gestión de bases de datos desarrollado en **C**, diseñado para almacenar, manipular y recuperar registros de manera eficiente utilizando archivos binarios. Además, ofrece una API interactiva basada en sockets para permitir la integración con aplicaciones externas.

---

## Características

- Gestión de registros básicos:
  - Inserción, eliminación, modificación y visualización de datos.
- Almacenamiento de datos en archivos binarios.
- Interfaz cliente-servidor para comunicación mediante sockets.
- Ligero, rápido y escrito completamente en **C**.
- Fácil integración con otros lenguajes, como Python, mediante una API simple.

---

## Requisitos

### Para compilar y ejecutar MiniDB:
- **Compilador GCC** o compatible.
- Sistema operativo Linux/Unix (o equivalente con soporte para sockets).

---

## Instalación

### 1. Clonar el repositorio
```bash
git clone https://github.com/MelchorRuiz/MiniDB
cd MiniDB
```

### 2. Compilar el proyecto
```bash
gcc -o MiniDB main.c model.c view.c controller.c
```

### 3. Ejecutar el servidor
```bash
./MiniDB
```

---

## Uso

### Desde la línea de comandos
Cuando inicies MiniDB, aparecerá un menú interactivo para gestionar los registros:
```plaintext
Menú de opciones:
1. Insertar registro
2. Mostrar todos los registros
3. Modificar registro
4. Eliminar registro
5. Salir
Seleccione una opción:
```

### Desde Python u otro cliente
MiniDB incluye un servidor que escucha solicitudes API en el puerto **8080**. Puedes enviar comandos como `INSERT`, `DISPLAY`, etc., desde cualquier cliente que utilice sockets.

Ejemplo de cliente en Python:
```python
import socket

def send_request(request):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('127.0.0.1', 8080))
    client_socket.sendall(request.encode())
    response = client_socket.recv(1024).decode()
    print("Respuesta:", response)
    client_socket.close()

send_request("INSERT")
send_request("DISPLAY")
```

---

## Estructura del Proyecto

```plaintext
MiniDB/
├── main.c           # Punto de entrada principal
├── model.c/.h       # Lógica para gestionar la base de datos
├── view.c/.h        # Interfaz para mostrar menús y mensajes
├── controller.c/.h  # Coordinación entre vista y modelo
├── README.md        # Documentación del proyecto
└── .gitignore       # Archivos y directorios a ignorar por Git
```
