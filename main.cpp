/**************************
 *
 * MAZE GAME
 * Checkout on github: https://github.com/mauriciosoares01/Open_GL-Maze-Game
 * Author: Maurício Silva Soares
 * Using OpenGL
 * Goal:
 *	Move trough the maze until the end, without touch the walls
 * Controls:
 *	Directional keys for movement
 *	Left mouse buttom for color change
 *
 **************************
*/

#include <stdlib.h>
#include <gl/glut.h>
#include <iostream>


float pX=44,pY=17;	// initial player's position

//Configure the window and the viewport
void Init(void){
	glClearColor(1,1,1,1.0f);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,100.0,0.0,100.0);
}

//Draw the player and the console
void Draw(void){
	glClear(GL_COLOR_BUFFER_BIT);
	
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
		glVertex3f(60, 0, 0);
		glVertex3f(61, 0, 0);
		glVertex3f(61, 100, 0);
		glVertex3f(60, 100, 0);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(25, 0, 0);
		glVertex3f(26, 0, 0);
		glVertex3f(26, 100, 0);
		glVertex3f(25, 100, 0);
	glEnd();

// player

	glBegin(GL_POLYGON);
		glVertex3f(pX, pY, 0);
		glVertex3f(pX+4, pY, 0);
		glVertex3f(pX+4, pY+4, 0);
		glVertex3f(pX, pY+4, 0);
	glEnd();
	
	glBegin(GL_POLYGON);
		glVertex3f(pX+4.3, pY, 0);
		glVertex3f(pX+8.3, pY, 0);
		glVertex3f(pX+8.3, pY+4, 0);
		glVertex3f(pX+4.3, pY+4, 0);
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

	
	glFlush();
}

int main(void){
	
	//Game window
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(650,650);
    glutInitWindowPosition(100,50);
	glutCreateWindow("Mini Race Game");
	Init();
	glutDisplayFunc(Draw);

	glutMainLoop();
}


