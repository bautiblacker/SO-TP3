# SO-TP3

1) Ejecutar en la terminal el comando './so_docker' teniendo Docker abierto.
2) Una vez en la terminal de docker, abrir una segunda terminal, cambiar el directorio actual al actual.
3) En la segunda terminal ejecutar 'docker exec -ti <número sesión docker> bash', donde el número de la sesión está presente en la terminal previamente abierta como 'root@<número>'.
4) Ahora en ambas sesiones ejecutamos 'cd' para pararnos en la carpeta con los archivos.
5) En una de las terminales compilar tanto el server como el cliente con:
    'gcc cerverza.c serverGame.c -o server2'
    'gcc client2.c -o client2'
6) En una de las terminales (cualquiera) ejecutamos el servidor primero con './server2', o el nombre que hayan elegido para compilar.
7) En la otra terminal ejecutamos el servidor con './server2'.
8) Ambos se empezarán a comunicar entre sí, hasta terminar el juego.
