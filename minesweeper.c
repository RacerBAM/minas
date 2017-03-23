/* minesweeper.c */

#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

struct casilla {
     char etiqueta;
     char tipo;
     int nMinas;
};

typedef struct casilla tipoCasilla;

tipoCasilla **crearMatrix(int filas, int columnas) {
  tipoCasilla **mat = (tipoCasilla **) malloc(filas*sizeof(tipoCasilla *));
  for (int i=0; i < filas; i++) {
    mat[i] = (tipoCasilla *) malloc(columnas*sizeof(tipoCasilla *));
  }
  return mat;
}

void print_matrix(int rows, int cols, tipoCasilla **mat, int difficulty) {

  if (difficulty == 3) 
  	printf("   1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 \n");
  if (difficulty == 2)
  	printf("   1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16\n");
  if (difficulty == 1)
  	printf("   1  2  3  4  5  6  7  8  \n");

  for (int i = 0; i < rows; i++) {
  	if ((i+1) < 10)
  		printf("%d ", i+1); // deja un espacio si el numero de marcador es de 1 digito
  	else
  		printf("%d",  i+1); // no deja espacio si el numero de marcador tiene 2 digitos

    for (int j = 0; j < cols; j++) {
      if (mat[i][j].etiqueta == 'D')
      	printf("|%d|", mat[i][j].nMinas);   /* Imprime nMinas de cada casilla */
      else
      	printf("|%c|", mat[i][j].etiqueta); /* Imprime que es Cubierto o Bandera si lo es */
    }

    // printf("|%c%d|", mat[i][j].tipo, mat[i][j].nMinas);  /* para imprimir tipo y nMinas */
    if (difficulty == 1)
    	printf("\n--------------------------\n"); // bordes inferiores
    if (difficulty == 2)
    	printf("\n--------------------------------------------------\n");
    if (difficulty == 3)
    	printf("\n--------------------------------------------------------------------------------------------\n");
  }
}

void colocarMinas(int filas, int columnas, tipoCasilla **matrix, int NumeroMinas) {
	int posFil, posCol, n;
	srand(time(NULL));
	n = 0;
	while (n < NumeroMinas) {
		posFil = rand() % filas;
		posCol = rand() % columnas;
		matrix[posFil][posCol].tipo = 'M';
		n++;
	}
}

int procedimiento(tipoCasilla **matriz, int r, int c, int di) {

 // retorna 0 si toca una Mina y retorna 1 si toca un cuadro sin minas
 // si toca un cuadro sin minas, chequea las casillas adyacentes por minas
 // el numero de minas adyacentes sera el entero "b"

 int i = r, j = c, b = 0, k, x, y;
 char C;
	
 if (di == 1) {
	 x = 8;
	 y = 8;
}

 if (di == 2) {
	 x = 16;
	 y = 16;
 }
	
 if (di == 3) {
	 x = 16;
	 y = 30;
 }

 if (matriz[i][j].tipo == 'M') {
   k = 0;
   return k;
 }

 else {

   if ((i-1 > 0) && (j-1 > 0) && matriz[i-1][j-1].tipo == 'M')
   	b++;  
   if ((i-1 > 0) && matriz[i-1][j].tipo == 'M')
    b++;  
   if ((i-1 > 0) && (j+1 < y) && matriz[i-1][j+1].tipo == 'M')
    b++;  
   if ((j-1 > 0) && matriz[i][j-1].tipo == 'M')
    b++;  
   if ((j+1 < y) && matriz[i][j+1].tipo == 'M')
    b++;  
   if ((j-1 > 0) && (i+1 < x) && matriz[i+1][j-1].tipo == 'M')
    b++;  
   if (matriz[i+1][j].tipo == 'M')
    b++;  
   if ((j+1 < y) && (i+1 < x) && matriz[i+1][j+1].tipo == 'M')
    b++;  
  
   //C = (char)(((int)'0')+b); // convierte int a char;

   matriz[i][j].nMinas = b;
   matriz[i][j].etiqueta = 'D';
 }
 return 1;  
}

void inicializarMatriz(tipoCasilla **matriz, int rs, int cs) {
    for(int i=0; i<rs; i++) {
	    for(int j=0; j<cs; j++) {
    	  matriz[i][j].etiqueta = 'C';
    	}
	}
}

void bandera(tipoCasilla **matx, int s, int d) {
	int x = s, y = d;
	matx[x][y].etiqueta = 'B';
}

int victoria(tipoCasilla **matrx, int difficult) {

	int r, c, vic, minas;
	vic = 0;

	if (difficult == 1) {
		minas = 10;
		r = 8;
		c = 8;
	}
	if (difficult == 2) {
		minas = 40;
		r = 16;
		c = 16;
	}
	if (difficult == 3) {
		minas = 99;
		r = 16;
		c = 30;
	}

	for (int i; i < r; i++) {
		for (int j; j < c; j++) {
			if (matrx[i][j].tipo == 'M' && matrx[i][j].etiqueta == 'B') {
				vic++;
			}
		}
	}

	if (vic == minas) {
		return 1;
	}
	return 0;
}

int main() {

	int dificultad, x, y, prueba, prueba2;

	printf("\nBienvenido a 'Minesweeper' en C. \n \n");
	printf("Reglas del Juego: \n");
	printf("1. Cada casilla aparece cubierta.\n   Las puedes descubrir entrando la posicion que quieres desubrir en x,y.\n");
	printf("2. Cuando descubres la casilla, pasa de ser C (cubierto)\n   a un numero que representa las minas adyacentes.\n");
	printf("3. Si quieres colocar una bandera,\n   entre las posiciones 0 y 0 para x,y.\n   Despues, entre las posiciones x,y que quieres marcar.\n");
	printf("4. Cuando descubres una casilla con una mina, pierdes.\n\n");
	printf("Las dificultades disponibles son Nivel 1, Nivel 2 y Nivel 3. \n");
	printf("Nivel 1 genera 10 minas en una matriz de 8x8. \n");
	printf("Nivel 2 genera 40 minas en una matriz de 16x16. \n");
	printf("Nivel 3 genera 99 minas en una matriz de 16x30. \n");
	printf("\nElige entre dificultad de Nivel 1, Nivel 2 o Nivel 3 (Escriba 1, 2 o 3): ");
	scanf("%d \n", &dificultad);

	if (dificultad == 1) {
		tipoCasilla **red = crearMatrix(8, 8);   // Red de 08x08, 10 minas
		inicializarMatriz(red, 8, 8);
		colocarMinas(8, 8, red, 10);
		print_matrix(8, 8, red, 1);
		printf("Entre la posicion que desea descubrir: ");
		scanf("%d%d \n", &x, &y);
		prueba = procedimiento(red, x+1, y+1);
		if (x == 0 && y == 0)
			bandera(red, x, y);
		while (prueba == 1) {
			printf("Bien hecho, sigues en el juego.\n");
			print_matrix(8, 8, red, 1);
			printf("Entre la posicion que desea descubrir: ");
			scanf("%d%d \n", &x, &y);
			prueba2 = procedimiento(red, x+1, y+1);
			if (x == 0 && y == 0)
				bandera(red, x, y);
			if (victoria(red, 1) == 1) {
				printf("Felicitaciones! Ganaste el juego!");
				prueba = 2;
			}
			if (prueba2 == 0) {
				prueba = 0;
			}
		}
		if (prueba == 0) {
			printf("Descubriste una mina. Game Over. \n");
		}
		if (prueba == 2)
			return 0;
	}

	if (dificultad == 2) {
		tipoCasilla **red = crearMatrix(16, 16); // Red de 16x16, 40 minas
		inicializarMatriz(red, 16, 16);
		colocarMinas(16, 16, red, 40);
		print_matrix(16, 16, red, 2);
		scanf("%d%d \n", &x, &y);
		prueba = procedimiento(red, x+1, y+1);
		if (x == 0 && y == 0)
			bandera(red, x, y);
		while (prueba == 1) {
			printf("Bien hecho, sigues en el juego.\n");
			print_matrix(16, 16, red, 2);
			printf("Entre la posicion que desea descubrir: ");
			scanf("%d%d \n", &x, &y);
			prueba2 = procedimiento(red, x+1, y+1);
			if (x == 0 && y == 0)
				bandera(red, x, y);
			if (victoria(red, 2) == 1) {
				printf("Felicitaciones! Ganaste el juego!");
				prueba = 2;
			}
			if (prueba2 == 0) {
				prueba = 0;
			}
		}
		if (prueba == 0) {
			printf("Descubriste una mina. Game Over. \n");
		}
		if (prueba == 2)
			return 0;
	}

	if (dificultad == 3) {
		tipoCasilla **red = crearMatrix(16, 30); // Red de 16x30, 99 minas
		inicializarMatriz(red, 16, 30);
		colocarMinas(16, 30, red, 99);
		print_matrix(16, 30, red, 3);
		scanf("%d%d \n", &x, &y);
		prueba = procedimiento(red, x+1, y+1);
		if (x == 0 && y == 0)
			bandera(red, x, y);
		while (prueba == 1) {
			printf("Bien hecho, sigues en el juego.\n");
			print_matrix(16, 30, red, 3);
			printf("Entre la posicion que desea descubrir: ");
			scanf("%d%d \n", &x, &y);
			prueba2 = procedimiento(red, x+1, y+1);
			if (x == 0 && y == 0)
				bandera(red, x, y);
			if (victoria(red, 3) == 1) {
				printf("Felicitaciones! Ganaste el juego!");
				prueba = 2;
			}
			if (prueba2 == 0) {
				prueba = 0;
			}
		}
		if (prueba == 0) {
			printf("Descubriste una mina. Game Over. \n");
		}
		if (prueba == 2)
			return 0;
	}
	return 0;
	// se podria resumir las condicionales de dificultad
}
