woody_woodpacker es el primero de los proyectos de especializacion en cyberseg de 42, se trata de un software que toma como argumento un binario compilado de tipo ELF64 y retorna un nuevo binario el cual contiene un nuevo segmento que muestra el mensaje "....WOODY...." con codigo encriptado hasta el momento de se ejecucion y no modifica el comportamiento habitual del binario anterior.

especificaciones:

- nombre del programa: woody_woodpacker
- lenguaje C con version libre
- Makefile con reglas std
- funciones permitidas: open, close, lseek, read, write, malloc, free, mmap, munmap, mprotect, exit, perror, strerror, syscall, printf (y derivados) y fflush.
- formato estricto de ELF64 (arquitectura x86_64, dynamic...)
- ha de ser cifrado con algoritmo complejo y generado el nuevo binario con nombre woody
- no crash, segfault, bus...

uso:

make packer -> genera woody_woodpacker
make example -> genera un binario elf64 de ejemplo

./example => "hello world!"

./woody_woodpacker example =>  genera woody

./woody => "....WOODY...."
"hello world!"