#include <stdio.h>
#include "affichage.h"


int remplirLab(int Labyrinthe[TAILLE_X][TAILLE_Y], int depart[2], int arrivee[2]){
	
	
    FILE *lab = NULL;
 
    lab = fopen("laby1.txt", "r");
	
	fscanf(lab, "%d", &depart[0]);
	fscanf(lab, "%d", &depart[1]);
	fscanf(lab, "%d", &arrivee[0]);
	fscanf(lab, "%d", &arrivee[1]);
	
	
	
	// stocker les valeurs dans le tableau
	for(int j = 0 ; j < TAILLE_Y ; j++ ){
	
		for(int i = 0 ; i < TAILLE_X ; i++){
		
		 	fscanf(lab, "%d", &Labyrinthe[i][j]);
		 }
	}
	
	fclose(lab);
	return 0;
}

void afficheLab(int Labyrinthe[TAILLE_X][TAILLE_Y], int depart[2], int arrivee[2]){

	
 
	for(int j = 0 ; j < TAILLE_Y ; j++ ){
	
		for(int i = 0 ; i < TAILLE_X ; i++){
			
			if(Labyrinthe[i][j] == -1) printf("X"); 
			if(Labyrinthe[i][j] == 0) printf(" "); 
			if((i == depart[0]) && (j == depart[1]) || ((i == arrivee[0]) && (j == arrivee[1])) ) {printf ("🟢 ");}
			if (Labyrinthe[i][j] > 1) printf("A "); 
		}
		 printf("\n");
	}
}


int deplacement(int Labyrinthe[TAILLE_X][TAILLE_Y], int coord[2], int direction){

	
	// coord est un tableau contenant les corrdonnées x et y de la case actuelle
	
			if ( (direction == 0)){ //direction Nord

					return Labyrinthe[coord[0]][coord[1]-1];
					//Labyrinthe[coord[0]][coord[1]]=Labyrinthe[coord[0]][coord[1]]+1;
			}
			
			if(direction == 2){ //direction Sud
					return Labyrinthe[coord[0]][coord[1]+1];
					//Labyrinthe[coord[0]][coord[1]]=Labyrinthe[coord[0]][coord[1]]+1;
			}
			if (direction == 1){ //direction Est
					return Labyrinthe[coord[0]+1][coord[1]];
					//Labyrinthe[coord[0]][coord[1]]=Labyrinthe[coord[0]][coord[1]]+1;
			}
			if (direction == 3) { //direction Ouest
					return Labyrinthe[coord[0]-1][coord[1]];
					//Labyrinthe[coord[0]][coord[1]]=Labyrinthe[coord[0]][coord[1]]+1;
			}

}

/* L'algorithme renverra un nombre au hasard + boucle infinie */

int avance(int Labyrinthe[TAILLE_X][TAILLE_Y], int depart[2], int arrivee[2],int direction, int chemin[TAILLE_X][TAILLE_Y]){

	Labyrinthe[depart[0]][depart[1]] = 1;
	Labyrinthe[arrivee[0]][arrivee[1]] = 1; 
	int coord[2];
	direction = 0 ;
	int distance = 2;
	coord[1] = depart[1];
	coord[0] = depart[0];
	int val= deplacement(Labyrinthe, coord, direction);
	int lesbonschemins[400];
	int nb = 0;
	printf(" val is  : %d \n ",val);

				for(int j = depart[1] ; j < TAILLE_Y ; j++ ){
					for(int i = depart[0]; i < TAILLE_X ; i++ ){
							while(val >= 0 ){
							distance++;
							Labyrinthe[coord[1]][coord[0]] = distance;
							if ( (direction == 0)) coord[1] =  coord[1]-1;
							if(direction == 2) coord[1] = coord[1]+1;
							if (direction == 1) coord[0] = coord[0] + 1;
							if (direction == 3) coord[0] = coord[0] - 1;
							val = deplacement(Labyrinthe, coord, direction);
								if((coord[0] == arrivee[0]) && (coord[1] == arrivee[1])){
									printf("%d\n", distance);
									nb++;
									lesbonschemins[nb]=distance;
								}
							}
							if(val < 0) {
								direction++;
								val = deplacement(Labyrinthe, coord, direction);
								//printf(" yess : %d \n ",val);
								if(direction == 4) direction = 0;
							}
							
						coord[1] = j;
						coord[0] = i;	
					}	
				}
			return distance;
}	
							
/*int remonte(int Labyrinthe[TAILLE_X][TAILLE_Y], int depart[2], int arrivee[2]){


	int distance[4];

	int direction = 0;
	int min = avance(Labyrinthe, arrivee, depart,directionLabyrinthe);
	int i = 0; 

	for(direction = 0 ; direction <= 4 ; direction++ ) { 

	distance[i] = avance(Labyrinthe, arrivee, depart,direction,Labyrinthe);
		i++;
			
	}
	for(int j = 0; j < 4 ; j++){
	
		if(min >= distance[j]) min = distance[j];
	}
	
	printf("Le chemin le plus court est %d\n", min);
	return min;
}

void nettoyage(int Labyrinthe[TAILLE_X][TAILLE_Y], int depart[2], int arrivee[2], int chemin[TAILLE_X][TAILLE_Y]){

	for(int j = 0 ; j < TAILLE_Y ; j++ ){

		for(int i = 0 ; i < TAILLE_X ; i++ ){
		
			if(chemin[i][j] >= 1) Labyrinthe[i][j] == 4; //voir affiche tab 
			
		}
	}
			
}*/
			

void main(){

	int Labyrinthe[TAILLE_X][TAILLE_Y]; //déclaration d'un tableau de taille X*Y
	int chemin[TAILLE_X][TAILLE_Y];
	int depart[2];
	int arrivee[2]; 
	int direction = 0;
	int coord[2];
	remplirLab(Labyrinthe,depart,arrivee); //remplit tab remplit mon tableau avec les bonnes coord
	
	//printf("les positions de départs sont : %d %d\n", depart[0], depart[1]);
	
	afficheLab(Labyrinthe,depart,arrivee); //récupère le tableau rmpli et l'affiche
	avance(Labyrinthe,depart,arrivee,direction,chemin); //trouve un chemin du départ vers l'arrivée
	afficheLab(Labyrinthe,depart,arrivee); //récupère le tableau rmpli et l'affiche
	//remonte(Labyrinthe, arrivee, depart);
	//nettoyage(Labyrinthe,depart,arrivee,chemin);//nettoie le labyrinthe, c’est-`a-dire marque les cases du labyrinthe n’appartenant pas au chemin trac ́ee et non bloqu ́ees par un obstacle comme libre
	
	
	
}
 	
					
		
