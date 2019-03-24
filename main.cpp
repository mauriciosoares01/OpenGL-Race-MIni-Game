/**************************

 **************************
*/

#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>


float pX=32,pY=17;		// initial player's position
float wX=27, wY=17;		// initial walls position	
float aX[3]={32, 32, 32}, aY[3]= {86, 86, 86};		//initial adversary position
float tWY = 0; 			// initial translation of wall
float tAY[3] = {0, 40, 80}; 			//initial translation of adversary
float step=0.5;	
float actualStep = 0.5;
bool state=0;			// players crash state
int counter = 0; 		// Counter to change speed

//Configure the window and the viewport
void Init(void){
	glClearColor(1,1,1,1.0f);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,100.0,0.0,100.0);
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

//Draw the player and the console
void Draw(void){
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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

void Anima(int value)
{
	
	tWY = tWY <= -20 ? -step : tWY-step;
	for(int i = 0; i< 3; i++){
		if(tAY[i] <= -85){
			int al = rand()%2;
			aX[i] = al?32:47;
			printf("al: %i\n", al);
			tAY[i] = 40-step;
		} else 
			tAY[i] = tAY[i]-step;
	}
		
	if(counter++> 50){
		counter = 0;
		actualStep += 0.2;
	}

	// Redesenha a casinha em outra posição
	glutPostRedisplay();
	glutTimerFunc(100,Anima, 1);
}
void KeyboardReleaseManagement(unsigned char key, int mouseX, int mouseY){
	printf("HEY JUDE\n");
	if(key == GLUT_KEY_UP) step = actualStep;
}
void KeyboardManagement(int key, int mouseX, int mouseY){
	
	if(state!=1){
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
				step = 10;
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
	glutKeyboardUpFunc(KeyboardReleaseManagement);
glutTimerFunc(150, Anima, 1);
	glutMainLoop();
}


