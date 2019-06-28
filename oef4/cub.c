#include <GL/glut.h>
#include <math.h>
#include "staaf.h"
/*
Gevraagd, naar analogie met de cursus, teken in 3D een kubus met elk zijvlak
een ander kleurtje en afhankelijk van het argument dat je aan je programma
meegeeft (p,o,f) gebruik je gluPerspective,glOrtho of glFrustum.
Mogelijke uitbreiding: laat de gebruiker via toetsen de coordinaten 
van de 'camerapositie' inzoemen (x,y,z) of uitzoemen (X,Y,Z). Zorg er ook voor
dat bij het herschalen van uw venster uw kubus geen balk wordt.

*/
GLint winWidth = 800,winHeight = 800;  /* 800*800 pixels */
GLdouble xlens = 5.0, ylens = 5.0, zlens = 5.0;
float xmax;
float ymax;
float xmin;
float ymin;
float near;
float far;
int projectie='p';

void init(void)
{

	glClearColor(1.0,1.0,1.0,1.0);  /* window color white */
	glEnable(GL_DEPTH_TEST);
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
		case 'q' : exit(0);
		
	}
	printf("oog %lf %lf %lf\n", xlens, ylens, zlens);
	glutPostRedisplay();
}


void winReshapeFcn (GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	//winWidth = newWidth;
	//winHeight = newHeight;
	
	
	switch ( projectie )
	{
		case 'o':	glOrtho(xmin ,xmax,ymin,ymax,near,far);
				break;
		case 'f':	glFrustum(xmin, xmax,  ymin, ymax, 3*near, far);
				break;
		default:
		case 'p':	gluPerspective(60.0, 1.0,  near, far);
				break;
	}
	printf("herschaald \n" );
	glViewport (0,0,newWidth,newHeight);
}
void displayFcn(void)
{	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);    /* clear display window */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(xlens,ylens,zlens, 0.0,0.0,0.0, 0.0,1.0,0.0);
		
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);	//assen
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(5.0,0.0,0.0);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(0.0,5.0,0.0);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(0.0,0.0,5.0);
	glEnd();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);
		glVertex3f(0.0, 0.0, 0.0);//onder
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(1.0, 0.0, 1.0);
		glVertex3f(1.0, 0.0, 0.0);
	glEnd();
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_QUADS);
		glVertex3f(0.0, 1.0, 0.0);//boven
		glVertex3f(0.0, 1.0, 1.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(1.0, 1.0, 0.0);
	glEnd();
	glColor3f(1.0,1.0,0.5);
	glBegin(GL_QUADS);
		glVertex3f(0.0, 0.0, 0.0);//links
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 1.0, 1.0);
		glVertex3f(0.0, 0.0, 1.0);
	glEnd();
	glColor3f(0.0,1.0,1.0);
	glBegin(GL_QUADS);
		glVertex3f(1.0, 0.0, 0.0);//rechts
		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(1.0, 0.0, 1.0);
	glEnd();
	glColor3f(1.0,0.0,0.5);	
	glBegin(GL_QUADS);
		glVertex3f(0.0, 0.0, 1.0);//dicht
		glVertex3f(1.0, 0.0, 1.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(0.0, 1.0, 1.0);
	glEnd();
	glColor3f(0.0,1.0,0.5);
	glBegin(GL_QUADS);
		glVertex3f(0.0, 0.0, 0.0);//ver
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
	glEnd();
	
	
	
	glFlush();
}
int main (int argc,char* argv[])
{	
	if ( argc > 1 )
		{projectie = argv[1][0];}
	else
	projectie = 'p';

	xmin=-1.0;
	ymin=-1.0;
	ymax=1.0;
	xmax=1.0;
	
	near=0.5;
	far=35.0;
	
	/*
	printf("xmax: %f  \n",xmax);
	printf("ymax: %f  \n",ymax);
	printf("xmin: %f  \n",xmin);
	printf("ymin: %f  \n",ymin);
	*/
		
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE |GLUT_DEPTH| GLUT_RGBA);
	glutInitWindowPosition(100,100);  //top left corner 
	glutInitWindowSize(winWidth,winHeight);
	glutCreateWindow("tweede opengl prog");
	init();
	glutKeyboardFunc(toetsen);
	glutDisplayFunc(displayFcn);	
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
	return 0;
}
