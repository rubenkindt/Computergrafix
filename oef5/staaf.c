#include <GL/glut.h>
#include <math.h>
#include "staaf.h"


GLint winWidth = 800,winHeight = 800;  /* 800*800 pixels */
GLdouble xlens = 5.0, ylens = 4.0, zlens = 75.0;
int start;
int end;
int aantal;
int ymax=0;
int xmax=0;
int ymin;
int xmin;
float near=0.5;
float far=100.0;

int weektotalen[WLEN];
int weekKleuren[WLEN];
int knop;
Gebruik stru[AANTA];
GLdouble left=0.0;
GLdouble right;
GLdouble bot=0.0;
GLdouble top;
char projectie='o';
int solid=0;

void init(void)
{
	for(int i=0;i<WLEN;i++){// teggen idereen zeggen, er is rechts op je geklikt 
		weekKleuren[i]=0; //rechterMuisknop == normaal
	}
	glClearColor(1.0,1.0,1.0,1.0);  /* window color white */
	glEnable(GL_DEPTH_TEST);
				
}



void winReshapeFcn (GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	winWidth = newWidth;
	winHeight = newHeight;
	
	switch ( projectie )
	{
		default:
		case 'o':	glOrtho(xmin,xmax*1.1,ymin,ymax*1.1,near,far);
				break;
		case 'f':	glFrustum(xmin, xmax,  ymin, ymax, 3*near, far);
				break;
		
		case 'p':	gluPerspective(xmax, ymax,  near, far);
				break;
	}


	printf("herschaald \n " );
	glViewport (0,0,newWidth,newHeight);
}
void toetsen( unsigned char key, int x, int y)
{
	switch ( key )
	{	case 'y' : ylens++; break;
		case 'z' : zlens++; break;
		case 'x' : xlens++; break;
		
		case 'Y' : ylens--; break;
		case 'Z' : zlens--; break;
		case 'X' : xlens--; break;
		case 'q' : exit(0); break;
		case 'r' : xlens = 5.0;
			   ylens = 4.0;
			   zlens = 75.0;	
			   break;	
		 case 's': solid=!solid;
		 	break;
		 case 'f': projectie='f';
		 	break;
		 case 'p': projectie='p';
		 	break;
		 case 'o': projectie='o';
		 	break;	 	   	
		
	}
	printf("oog %lf %lf %lf\n", xlens, ylens, zlens);
	glutPostRedisplay();
}


void displayFcn(void)
{	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(xlens,ylens,zlens, 0.0,0.0,0.0, 0.0,1.0,0.0);
	
	
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);// assen
			glColor3f(1.0,0.0,0.0);
		glVertex3f(xmax*1.2,0.0,0.0);
		glVertex3f(.0,0.0,0.0);
			glColor3f(0.0,1.0,0.0);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(0.0,ymax*1.8,0.0);
			glColor3f(0.0,0.0,1.0);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(0.0,0.0,30.0);
	glEnd();
	int vorigeWeek =weektotalen[0+start];
	
	
	
	for(int i=0;i<xmax;i++){
		glColor3f(0.0,1.0,0.0);
		glPushMatrix();
		glColor3f(0.0, 1.0, 0.0);
		glTranslatef((i*1.0)+0.5,weektotalen[i+start]/2.0,0.0);
		glScalef(0.8,weektotalen[i+start], 1);
		if(solid){glutSolidCube(1);}
		else{glutWireCube(1);}
		glPopMatrix();		
			
	}
		
	glFlush();
}




int main (int argc,char* argv[])
{	
		
	aantal=lees(&start,&end,stru);
	for(int i=0;i<WLEN;i++){
		weektotalen[i]=0;
		for (int j=0;j<aantal;j++){
			weektotalen[i]+=stru[j].uren[i];
		}
		if (ymax<weektotalen[i] ){ymax=weektotalen[i];}
		//printf("%d  \n",weektotalen[i]);
	}	
	xmax=end-start+1;//aantal weken
	xmin=-1.0;
	ymin=-10.0;
	//xmax=1;
	//ymax=1;
	
	xmax=end-start+1;
	printf("xmax: %d  \n",xmax);
	printf("ymax: %d  \n",ymax);
	printf("xmin: %d  \n",xmin);
	printf("ymin: %d  \n",ymin);
	
	
	
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE |GLUT_DEPTH| GLUT_RGBA);
	glutInitWindowPosition(100,100);  //top left corner 
	glutInitWindowSize(winWidth,winHeight);
	glutCreateWindow("5de opengl prog");
	init();
	glutDisplayFunc(displayFcn);
	glutKeyboardFunc(toetsen);	
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
	return 0;
}
