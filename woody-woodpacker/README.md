En este ejercicio tengo que crear un Packer (software de compresion y encriptado) para poder generar ejecutables .exe/.dll/.ocx ocultos para un antivirus, o al menos hasta el momento de su ejecucion.

Las indicaciones son:

- nombre: woody_woodpacker

- lenguaje C con version libre

- Makefile con reglas std

- funciones permitidas: open, close, lseek, read, write, malloc, free, mmap, munmap, mprotect, exit, perror, strerror, syscall, printf (y derivados) y fflush.

- el packer recibe ejecutable ELF de 64  bits

- ha de ser cifrado con algoritmo complejo y generado el nuevo binario con nombre woody

- este en tiempo de su ejecucion se descifra y muestra [....WOODY....]

- no crash, segfault, bus...