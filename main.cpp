/*******************************************
*
*	A mini race game using OpenGL
*
*	Authors: (on github) /mauriciosoares01
*						 /joaopedrofn
*						 /Talita1996
*
 *******************************************
*/

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <fstream>


float pX=32,pY=17;		// initial player's position
float wX=27, wY=17;		// initial walls position	
float aX[3]={32, 32, 47}, aY[3]= {86, 86, 86};		//initial adversary position
float tWY = 0; 			// initial translation of wall
float tAY[3] = {0, 40, 80}; 			//initial translation of adversary
float step=0.5;	
float actualStep = 0.5;
bool state=false;			// players crash state
int counter = 0; 		// Counter to change speed
int score = 0;			//initial score
int hiScore;
FILE *hiScoreFile; 	//FILE TO HIGH SCORE
int explosionCounter = 0;

//Configure the window and the viewport
void Init(void){
	hiScoreFile = fopen("hiscore", "r");
	fscanf(hiScoreFile, "%d", &hiScore);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glClearColor(1,1,1,1.0f);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,100.0,0.0,100.0);
}

//Text renderer
void print_text(const char *text, float x, float y){
	glRasterPos2f(x , y);
	for(int i = 0; i < strlen(text); i++){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
	}
}

void lightning() {
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0}; // "cor"
	GLfloat luzEspecular[4]={0.2, 0.2, 0.2, 0.2};// "brilho"
	GLfloat posicaoLuz[4]={40.0, 60.0, 50.0, 1};
	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 60;
	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz ); 
}

void DrawWalls() {
	// walls
	// glLineWidth(5);
	glPushMatrix();
	glTranslatef(0, tWY, 0);
	wY = 17;
	int i=0;
	for (i=0;i<=4;i++){
		glBegin(GL_POLYGON);
			glVertex3f(wX, wY, 0);
			glVertex3f(wX+4, wY, 0);
			glVertex3f(wX+4, wY+4, 0);
			glVertex3f(wX, wY+4, 0);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(wX+34, wY, 0);
			glVertex3f(wX+38, wY, 0);
			glVertex3f(wX+38, wY+4, 0);
			glVertex3f(wX+34, wY+4, 0);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(wX, wY+5, 0);
			glVertex3f(wX+4, wY+5, 0);
			glVertex3f(wX+4, wY+9, 0);
			glVertex3f(wX, wY+9, 0);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(wX+34, wY+5, 0);
			glVertex3f(wX+38, wY+5, 0);
			glVertex3f(wX+38, wY+9, 0);
			glVertex3f(wX+34, wY+9, 0);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(wX, wY+10, 0);
			glVertex3f(wX+4, wY+10, 0);
			glVertex3f(wX+4, wY+14, 0);
			glVertex3f(wX, wY+14, 0);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(wX+34, wY+10, 0);
			glVertex3f(wX+38, wY+10, 0);
			glVertex3f(wX+38, wY+14, 0);
			glVertex3f(wX+34, wY+14, 0);
		glEnd();
		// glBegin(GL_LINES);
		// 	glVertex3f(wX,wY, 0);
		// 	glVertex3f(wX,wY+3, 0);
		// 	glVertex3f(wX+32,wY,0);
		// 	glVertex3f(wX+32,wY+3,0);
		// glEnd();
		
		wY+=20;	
	}
	glPopMatrix();
}

void DrawAdversaries() {
	for(int i = 0; i< 3; i++){
		glPushMatrix();
			glTranslatef(0, tAY[i], 0);
			glBegin(GL_POLYGON);
				glVertex3f(aX[i], aY[i], 0);
				glVertex3f(aX[i]+4, aY[i], 0);
				glVertex3f(aX[i]+4, aY[i]+4, 0);
				glVertex3f(aX[i], aY[i]+4, 0);
			glEnd();
			
			glBegin(GL_POLYGON);
				glVertex3f(aX[i]+8.6, aY[i], 0);
				glVertex3f(aX[i]+12.6, aY[i], 0);
				glVertex3f(aX[i]+12.6, aY[i]+4, 0);
				glVertex3f(aX[i]+8.6, aY[i]+4, 0);
			glEnd();
			
			glBegin(GL_POLYGON);
				glVertex3f(aX[i]+4.3, aY[i]+4.3, 0);
				glVertex3f(aX[i]+8.3, aY[i]+4.3, 0);
				glVertex3f(aX[i]+8.3, aY[i]+8.3, 0);
				glVertex3f(aX[i]+4.3, aY[i]+8.3, 0);
			glEnd();

			glBegin(GL_POLYGON);
				glVertex3f(aX[i], aY[i]+8.6, 0);
				glVertex3f(aX[i]+4, aY[i]+8.6, 0);
				glVertex3f(aX[i]+4, aY[i]+12.6, 0);
				glVertex3f(aX[i], aY[i]+12.6, 0);
			glEnd();
			
			glBegin(GL_POLYGON);
				glVertex3f(aX[i]+4.3, aY[i]+8.6, 0);
				glVertex3f(aX[i]+8.3, aY[i]+8.6, 0);
				glVertex3f(aX[i]+8.3, aY[i]+12.6, 0);
				glVertex3f(aX[i]+4.3, aY[i]+12.6, 0);
			glEnd();
			
			glBegin(GL_POLYGON);
				glVertex3f(aX[i]+8.6, aY[i]+8.6, 0);
				glVertex3f(aX[i]+12.6, aY[i]+8.6, 0);
				glVertex3f(aX[i]+12.6, aY[i]+12.6, 0);
				glVertex3f(aX[i]+8.6, aY[i]+12.6, 0);
			glEnd();
			
			glBegin(GL_POLYGON);
				glVertex3f(aX[i]+4.3, aY[i]+12.9, 0);
				glVertex3f(aX[i]+8.3, aY[i]+12.9, 0);
				glVertex3f(aX[i]+8.3, aY[i]+16.9, 0);
				glVertex3f(aX[i]+4.3, aY[i]+16.9, 0);
			glEnd();
		glPopMatrix();
	}
}

void DrawExplosion(int level){
	switch (level)
	{
		case 3:
			glBegin(GL_POLYGON);
				glVertex3f(pX+5, pY, 0);
				glVertex3f(pX+9, pY, 0);
				glVertex3f(pX+9, pY+4, 0);
				glVertex3f(pX+5, pY+4, 0);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3f(pX+10, pY, 0);
				glVertex3f(pX+14, pY, 0);
				glVertex3f(pX+14, pY+4, 0);
				glVertex3f(pX+10, pY+4, 0);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3f(pX+5, pY+15, 0);
				glVertex3f(pX+9, pY+15, 0);
				glVertex3f(pX+9, pY+19, 0);
				glVertex3f(pX+5, pY+19, 0);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3f(pX+10, pY+15, 0);
				glVertex3f(pX+14, pY+15, 0);
				glVertex3f(pX+14, pY+19, 0);
				glVertex3f(pX+10, pY+19, 0);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3f(pX, pY+5, 0);
				glVertex3f(pX+4, pY+5, 0);
				glVertex3f(pX+4, pY+9, 0);
				glVertex3f(pX, pY+9, 0);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3f(pX, pY+10, 0);
				glVertex3f(pX+4, pY+10, 0);
				glVertex3f(pX+4, pY+14, 0);
				glVertex3f(pX, pY+14, 0);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3f(pX+15, pY+5, 0);
				glVertex3f(pX+19, pY+5, 0);
				glVertex3f(pX+19, pY+9, 0);
				glVertex3f(pX+15, pY+9, 0);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3f(pX+15, pY+10, 0);
				glVertex3f(pX+19, pY+10, 0);
				glVertex3f(pX+19, pY+14, 0);
				glVertex3f(pX+15, pY+14, 0);
			glEnd();
			break;
		case 2:
			glBegin(GL_POLYGON);
				glVertex3f(pX, pY, 0);
				glVertex3f(pX+4, pY, 0);
				glVertex3f(pX+4, pY+4, 0);
				glVertex3f(pX, pY+4, 0);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3f(pX+15, pY, 0);
				glVertex3f(pX+19, pY, 0);
				glVertex3f(pX+19, pY+4, 0);
				glVertex3f(pX+15, pY+4, 0);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3f(pX+15, pY+15, 0);
				glVertex3f(pX+19, pY+15, 0);
				glVertex3f(pX+19, pY+19, 0);
				glVertex3f(pX+15, pY+19, 0);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3f(pX, pY+15, 0);
				glVertex3f(pX+4, pY+15, 0);
				glVertex3f(pX+4, pY+19, 0);
				glVertex3f(pX, pY+19, 0);
			glEnd();
		case 1:
			glBegin(GL_POLYGON);
				glVertex3f(pX+5, pY+5, 0);
				glVertex3f(pX+9, pY+5, 0);
				glVertex3f(pX+9, pY+9, 0);
				glVertex3f(pX+5, pY+9, 0);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3f(pX+10, pY+5, 0);
				glVertex3f(pX+14, pY+5, 0);
				glVertex3f(pX+14, pY+9, 0);
				glVertex3f(pX+10, pY+9, 0);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3f(pX+5, pY+10, 0);
				glVertex3f(pX+9, pY+10, 0);
				glVertex3f(pX+9, pY+14, 0);
				glVertex3f(pX+5, pY+14, 0);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3f(pX+10, pY+10, 0);
				glVertex3f(pX+14, pY+10, 0);
				glVertex3f(pX+14, pY+14, 0);
				glVertex3f(pX+10, pY+14, 0);
			glEnd();
			break;
	
		default:
			break;
	}
}

void DrawPlayer() {
	glBegin(GL_POLYGON);
		glVertex3f(pX, pY, 0);
		glVertex3f(pX+4, pY, 0);
		glVertex3f(pX+4, pY+4, 0);
		glVertex3f(pX, pY+4, 0);
	glEnd();
	
	glBegin(GL_POLYGON);
		glVertex3f(pX+8.6, pY, 0);
		glVertex3f(pX+12.6, pY, 0);
		glVertex3f(pX+12.6, pY+4, 0);
		glVertex3f(pX+8.6, pY+4, 0);
	glEnd();
	
	glBegin(GL_POLYGON);
		glVertex3f(pX+4.3, pY+4.3, 0);
		glVertex3f(pX+8.3, pY+4.3, 0);
		glVertex3f(pX+8.3, pY+8.3, 0);
		glVertex3f(pX+4.3, pY+8.3, 0);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(pX, pY+8.6, 0);
		glVertex3f(pX+4, pY+8.6, 0);
		glVertex3f(pX+4, pY+12.6, 0);
		glVertex3f(pX, pY+12.6, 0);
	glEnd();
	
	glBegin(GL_POLYGON);
		glVertex3f(pX+4.3, pY+8.6, 0);
		glVertex3f(pX+8.3, pY+8.6, 0);
		glVertex3f(pX+8.3, pY+12.6, 0);
		glVertex3f(pX+4.3, pY+12.6, 0);
	glEnd();
	
	glBegin(GL_POLYGON);
		glVertex3f(pX+8.6, pY+8.6, 0);
		glVertex3f(pX+12.6, pY+8.6, 0);
		glVertex3f(pX+12.6, pY+12.6, 0);
		glVertex3f(pX+8.6, pY+12.6, 0);
	glEnd();
	
	glBegin(GL_POLYGON);
		glVertex3f(pX+4.3, pY+12.9, 0);
		glVertex3f(pX+8.3, pY+12.9, 0);
		glVertex3f(pX+8.3, pY+16.9, 0);
		glVertex3f(pX+4.3, pY+16.9, 0);
	glEnd();
}

//Draw  the console
void Draw(void){
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	lightning();
	glColor3f(0.5,0.7,0.6);

// background
	glBegin(GL_POLYGON);
		glVertex3f(20, 0, 0);
		glVertex3f(80, 0, 0);
		glVertex3f(80, 100, 0);
		glVertex3f(20, 100, 0);
	glEnd();

// division lines
	glColor3f(0.15,0.15,0.15);
	
	glBegin(GL_POLYGON);
		glVertex3f(66, 0, 0);
		glVertex3f(67, 0, 0);
		glVertex3f(67, 100, 0);
		glVertex3f(66, 100, 0);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(25, 0, 0);
		glVertex3f(26, 0, 0);
		glVertex3f(26, 100, 0);
		glVertex3f(25, 100, 0);
	glEnd();
	
	DrawWalls();
	DrawAdversaries();
// player
	if(!state)
		DrawPlayer();
	else
		DrawExplosion((explosionCounter%3)+1);
	
//	borders
	glColor3f(0.8,0.15,0.15);
	
	glBegin(GL_POLYGON);
		glVertex3f(5, 0, 0);
		glVertex3f(95, 0, 0);
		glVertex3f(95, 17, 0);
		glVertex3f(5, 17, 0);
	glEnd();
	
	glBegin(GL_POLYGON);
		glVertex3f(5, 83, 0);
		glVertex3f(95, 83, 0);
		glVertex3f(95, 100, 0);
		glVertex3f(5, 100, 0);
	glEnd();
	
	glBegin(GL_POLYGON);
		glVertex3f(5, 10, 0);
		glVertex3f(20, 10, 0);
		glVertex3f(20, 90, 0);
		glVertex3f(5, 90, 0);
	glEnd();
	
	glBegin(GL_POLYGON);
		glVertex3f(80, 10, 0);
		glVertex3f(95, 10, 0);
		glVertex3f(95, 90, 0);
		glVertex3f(80, 90, 0);
	glEnd();
	
// shadows and details
	glColor3f(0.8,0.4,0.4);
	
	glBegin(GL_POLYGON);
		glVertex3f(80, 17, 0);
		glVertex3f(85, 14, 0);
		glVertex3f(85, 86, 0);
		glVertex3f(80, 83, 0);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(15, 14, 0);
		glVertex3f(85, 14, 0);
		glVertex3f(82, 17, 0);
		glVertex3f(20, 17, 0);
	glEnd();
	
	glBegin(GL_POLYGON);
		glVertex3f(5, 0, 0);
		glVertex3f(7, 0, 0);
		glVertex3f(7, 100, 0);
		glVertex3f(5, 100, 0);
	glEnd();	

	glColor3f(0.8,0.0,0.0);
	
	glBegin(GL_POLYGON);
		glVertex3f(15, 14, 0);
		glVertex3f(20, 17, 0);
		glVertex3f(20, 83, 0);
		glVertex3f(15, 86, 0);
	glEnd();
	
	glBegin(GL_POLYGON);
		glVertex3f(15, 86, 0);
		glVertex3f(20, 83, 0);
		glVertex3f(80, 83, 0);
		glVertex3f(85, 86, 0);
	glEnd();
	
	glBegin(GL_POLYGON);
		glVertex3f(93, 0, 0);
		glVertex3f(95, 0, 0);
		glVertex3f(95, 100, 0);
		glVertex3f(93, 100, 0);
	glEnd();
	
	glColor3f(1,1,0.3);
	glLineWidth(4);
	
	glBegin(GL_LINES);
		glVertex2f(87, 12);
		glVertex2f(87, 88);
		glVertex2f(87.2, 88);
		glVertex2f(12.8, 88);
		glVertex2f(13, 88);
		glVertex2f(13, 12);
		glVertex2f(12.8, 12);
		glVertex2f(87.2, 12);
	glEnd();
	

	//TEXTS
	glColor3f(0.15,0.15,0.15);
	print_text("HI-SCORE: ", 67.5, 78);
	char hiScoreStr[10];
	snprintf(hiScoreStr, sizeof(hiScoreStr), "%d", hiScore);
	print_text(hiScoreStr, 67.5, 76);
	print_text("SCORE: ", 67.5, 70);
	char scoreStr[10];
	snprintf(scoreStr, sizeof(scoreStr), "%d", score);
	print_text(scoreStr, 67.5, 68);

	print_text("SPEED: ", 67.5, 60);
	char speed[10];
	snprintf(speed, sizeof(speed), "%.1lf", (actualStep*10)/5);
	print_text(speed, 67.5, 58);
	

	
	glFlush();
}

// verifies the collision	checkCollision(playerPosX,enemyVectorX,enemyVectorY)
void checkCollision(){
	
	int i=0;
	for (i=0;i<3;i++){
		if(((aY[i]+tAY[i]) <= pY+17) && (aX[i]==pX)){
			state = true;
			break;
		}
	}

}

void Anima(int value){
	if(!state){
		tWY = tWY <= -20 ? -step : tWY-step;
		for(int i = 0; i< 3; i++){
			if(tAY[i] <= -85){
				int al = rand()%2;
				aX[i] = al?32:47;
				tAY[i] = 40-step;
			} else 
				tAY[i] = tAY[i]-step;
		}
			
		if(counter++> 50){
			counter = 0;
			actualStep += 0.2;
		}
		score += 2*step;
		checkCollision();
	} else {
		if(explosionCounter++ >= 15){
			explosionCounter = 0;
			state = false;
			score =0;
			hiScoreFile = fopen("hiscore", "r");
			fscanf(hiScoreFile, "%d", &hiScore);
			tWY = 0;
			tAY[0] =0;
			tAY[1] = 40;
			tAY[2] = 80;
			counter =0;
			actualStep = 0.5;
			explosionCounter = 0;
			
		}
		if(score > hiScore){
			hiScoreFile = fopen("hiscore", "w");
			fprintf(hiScoreFile, "%d", score);
		}
	}
	// Redesenha a casinha em outra posição
	glutPostRedisplay();
	glutTimerFunc(100,Anima, 1);
}



void KeyboardReleaseManagement(unsigned char key, int mouseX, int mouseY){
	if(key == ' ') step = actualStep;
}
void KeyboardSpaceManagement(unsigned char key, int mouseX, int mouseY){
	switch(key){
			case ' ':
				step = 10;
				break;
			case 'a':
				pX = 32;
				break;
			case 27:
				exit(0);
				break;
			case 'd':
				pX = 47;
				break;
			default:
				break;	
		}
}



void KeyboardManagement(int key, int mouseX, int mouseY){
	
	if(state!=true){
		// change player side when a directional is key pressed
		switch(key){
			case GLUT_KEY_RIGHT:
				pX = 47;
				break;
			case GLUT_KEY_LEFT:
				pX = 32;
				break;
			case GLUT_KEY_DOWN:

				break;
			case GLUT_KEY_UP:
				
				break;
			default:
				break;	
		}
	}

	glutPostRedisplay();
	
}

int main(int argc, char **argv){
	
	//Game window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(650,650);
    glutInitWindowPosition(100,50);
	glutCreateWindow("Mini Race Game");
	Init();
	glutDisplayFunc(Draw);
	glutSpecialFunc(KeyboardManagement);
	glutKeyboardFunc(KeyboardSpaceManagement);
	glutKeyboardUpFunc(KeyboardReleaseManagement);
	glutTimerFunc(150, Anima, 1);

	glutMainLoop();
}


