Prepare the input files `piso1.in`, `piso2.in`, and `piso3.in`, which contain the representation of the board.

The program will read the initial state of the board from these files.

Use the following keys to move the character:

- **S**: Up
- **B**: Down
- **I**: Left
- **D**: Right
- **F**: Exit the game

The game will display the current state of the board after each move.

## Main Functions

- `leer(char* nombreArchivo, char ** destino)`: Reads the input file and loads the data into the board.

- `borrarEspacios(char ** imagen, char ** nuevaImagen)`: Removes spaces in the board to obtain a more compact version.

- `mostrarPantalla(char ** imagen)`: Prints the board to the console.

- `asignarNumero(char opcion)`: Assigns a number to the movement options.

- `pedirMov(int posX, int posY)`: Prompts the user for a movement and validates the option.

- `moverPersonaje(int posX, int posY, char ** piso)`: Moves the character on the board.

## Character Representations in the Input File

I: This character represents the player. It indicates the current position of the player on the game board.

O: This character represents the exit of the level. It signifies a point that the player can reach to complete the level or puzzle.

X: This character denotes blockages on the board. It indicates spaces that the player cannot pass through or move into.

_: This character represents empty spaces on the board where the player can move. These positions are accessible and can be used strategically to navigate the game.