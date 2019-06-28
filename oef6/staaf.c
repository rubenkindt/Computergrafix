#include <GL/glut.h>
#include <math.h>


GLint winWidth = 800,winHeight = 800;  /* 800*800 pixels */
GLdouble xlens =5.0, ylens = 5.0, zlens = 5.0;
int xmax;
int ymax;
int hoek=90;
int verhouding=1;
float near=0.5;
float far=100.0;
GLfloat zwart[]     = {0.0,0.0,0.0,1.0};
GLfloat wit[]       = {1.0,1.0,1.0,1.0};
GLfloat lichtpos[]  = {4.0,4.0,4.0};
GLfloat lichtposTWEE[]  = {4.0,0.0,0.0};

float solid=1.0;
GLfloat BOLEEN[]={1.0, 0.0, 0.0, 1.0};
GLfloat bolTWEE[]={0.0, 1.0, 0.0, 0.5};
GLfloat bolTWEEtrans[]={0.0, 0.0, 0.0, 0.0};

int licht=1;
int lichttwee=0;
char projectie='p';
int alpa=0;


void init(void)
{
	glClearColor(1.0,1.0,1.0,1.0);  /* window color white */
	glEnable(GL_DEPTH_TEST);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, zwart);
	
	
	glLightfv(GL_LIGHT0,GL_SPECULAR,wit);	
	glLightfv(GL_LIGHT0,GL_DIFFUSE,zwart);	
	glLightfv(GL_LIGHT0,GL_AMBIENT,zwart);	
	
	glLightfv(GL_LIGHT1,GL_SPECULAR,zwart);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,wit);
	glLightfv(GL_LIGHT1,GL_AMBIENT,zwart);
	glBlendFunc(GL_ONE,GL_ONE_MINUS_DST_ALPHA);
				
}



void winReshapeFcn (GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	winWidth = newWidth;
	winHeight = newHeight;
	
	
	gluPerspective(hoek,verhouding,  near, far);
	


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
			   ylens = 5.0;
			   zlens = 5.0;	
			   break;	
		 case 't': solid=0.0;
		 	break;
		 case 'T': solid=1.0;
		 	break;
		 case 'l': glEnable(GL_LIGHT0);
		 	break;
		 case 'L': glDisable(GL_LIGHT0);
		 	break;
		 case 'k': glEnable(GL_LIGHT1);
		 	break;
		 case 'K': glDisable(GL_LIGHT1);
		 	break;  
		 case 'a': alpa=0;
		 	break;
		 case 'A': alpa=1;
		 	break;  
		 		
		 	 	
		
	}
	
	printf("oog %lf %lf %lf\n", xlens, ylens, zlens);
	glutPostRedisplay();
}


void displayFcn(void)
{	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glLightfv(GL_LIGHT0,GL_POSITION,lichtpos);	
	gluLookAt(xlens,ylens,zlens, 0.0,0.0,0.0, 0.0,1.0,0.0);
	glLightfv(GL_LIGHT1,GL_POSITION,lichtposTWEE);

	glBegin(GL_LINES);// assen
			glColor3f(1.0,0.0,0.0);
		glVertex3f(xmax,0.0,0.0);
		glVertex3f(.0,0.0,0.0);
			glColor3f(0.0,1.0,0.0);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(0.0,ymax,0.0);
			glColor3f(0.0,0.0,1.0);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(0.0,0.0,30.0);
	glEnd();
	glBegin(GL_POINTS);// puntjes waar de lichtbron staat
		glColor3f(1.0,0.0,0.0);
		glVertex3i(lichtpos[0],lichtpos[1],lichtpos[2]);
		glVertex3i(lichtposTWEE[0],lichtposTWEE[1],lichtposTWEE[2]);
		
	glEnd();
	glEnable(GL_LIGHTING);
	
	glDisable(GL_BLEND);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, BOLEEN);
	glMaterialfv(GL_FRONT, GL_SPECULAR, BOLEEN);
	glMaterialfv(GL_FRONT, GL_AMBIENT, BOLEEN);
	glutSolidSphere(1,10,10);
		
	if(alpa){
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
		
	}
	
	
	glMaterialfv(GL_FRONT, GL_DIFFUSE, bolTWEE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, bolTWEE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, bolTWEE);

	glPushMatrix();
	glTranslated(2.0,0.0,0.0);
	glScalef(1,1,1);
	if(solid){glutSolidSphere(1,10,10);}
	else{glutWireSphere(1,10,10);}
	glPopMatrix();		
			
	if(alpa){
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
	}
		
	
	glDisable(GL_LIGHTING);
	
	
	glFlush();
}




int main (int argc,char* argv[])
{	
	
	
	
	xmax=10;
	ymax=10;
	

	
	
	
	
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
