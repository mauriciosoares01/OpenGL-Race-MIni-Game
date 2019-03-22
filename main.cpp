/**************************

 **************************
*/

#include <stdlib.h>
#include <gl/glut.h>
#include <iostream>


float pX=44,pY=17;	// initial player's position
float step=0.5;
bool state=0;		// players crash state

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
	
//	glBegin(GL_POLYGON);
//		glVertex3f(pX+4.3, pY, 0);
//		glVertex3f(pX+8.3, pY, 0);
//		glVertex3f(pX+8.3, pY+4, 0);
//		glVertex3f(pX+4.3, pY+4, 0);
//	glEnd();
	
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
	
	
	glFlush();
}

void KeyboardManagement(int key, int mouseX, int mouseY){
	
	float x=pX,y=pY;
	
	if(state!=1){
		// add or subtract the step for wich directional key pressed
		switch(key){
			case GLUT_KEY_RIGHT:
				x += step;
				break;
			case GLUT_KEY_LEFT:
				x -= step;
				break;
			case GLUT_KEY_DOWN:

				break;
			case GLUT_KEY_UP:
				
				break;
			default:
				break;	
		}
	}
	
	pX = x;
	pY = y;
	glutPostRedisplay();
	
}

int main(void){
	
	//Game window
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(650,650);
    glutInitWindowPosition(100,50);
	glutCreateWindow("Mini Race Game");
	Init();
	glutDisplayFunc(Draw);
	glutSpecialFunc(KeyboardManagement);

	glutMainLoop();
}


