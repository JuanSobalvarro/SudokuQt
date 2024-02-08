# SUDOKU
Powered by Qt5.15

## Uso
Al momento de querer iniciar una partida se le debe dar click al boton de Generate Sudoku.

Luego con el mouse selecciona la celda a la que quieres agregar un numero, y pulsando las teclas pon el numero que quieras.

Si el numero no es el correcto saldra como rojo, si es correcto saldra verde.

El sudoku finaliza cuando se pinta de azul el ultimo numero y sale el mensaje abajo del boton de generate sudoku.

Por ahora la dificulta se setea manualmente al momento de compilar.

### Codigo

Se utilizo como base de clase el QMainWindow para generar la ventana, QGridLayout para la generacion de cuadriculas y QPushButton junto a setStyleSheet para el estilo de los botones.
