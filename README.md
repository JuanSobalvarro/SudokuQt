# SUDOKU
Powered by Qt5.15

![image](https://github.com/JuanSobalvarro/SudokuQt/assets/114633789/4fc15f39-1877-4041-a723-ba9cde11ad7d)

## Uso
Al momento de querer iniciar una partida se le debe dar click al boton de Generate Sudoku.

Luego con el mouse selecciona la celda a la que quieres agregar un numero, y pulsando las teclas pon el numero que quieras.

Si el numero no es el correcto saldra como rojo, si es correcto saldra verde.

El sudoku finaliza cuando se pinta de azul el ultimo numero y sale el mensaje abajo del boton de generate sudoku.

Por ahora la dificulta se setea manualmente al momento de compilar.

### Codigo

Se utilizo como base de clase el QMainWindow para generar la ventana, QGridLayout para la generacion de cuadriculas y QPushButton junto a setStyleSheet para el estilo de los botones.

En sudoku.cpp esta tanto la logica como el design de la UI.

El sudoku es generado comprobando que en cada casilla puede ser agregado un numero aleatorio o no. Asi una por una barriendo el grid, por lo que solo es posible generar sudokus validos.

### Compilacion
Si queres modificar y compilar el codigo utiliza la version Qt5.15.2 MSVC2019_64bit, con ese esta desarrollado y compilado el proyecto. Si quieren utilizar mi codigo no hay ningun problema :p
