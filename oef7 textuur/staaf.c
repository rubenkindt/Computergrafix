#include <GL/glut.h>
#include <math.h>
#include "../jpeg/InitJPG.h"
#define AANT 2

GLint winWidth = 800,winHeight = 800;  /* 800*800 pixels */
GLdouble xlens =5.0, ylens = 5.0, zlens = 5.0;
int xmax;
int ymax;
int xmin=0;
int ymin=0;

float near=0.5;
float far=100.0;
int bloem=0;
char projectie='p';
GLuint texName[AANT];
char beeldnaam[AANT][80] = { "Image.jpg" , "bloem.jpg" } ;
int textuur=0;
int cili =0;
int bo =0;//bol
int kege =0;
int muur=0;//muur

void init(void)
{
	glClearColor ( 0.7,0.7,0.7,0.0);  //grijs display window.
        glShadeModel( GL_FLAT);
    	glEnable( GL_DEPTH_TEST);
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1);
   	glGenTextures(AANT, texName);
   	int i=0;
 	tImageJPG *pImage;
	for(i=0;i< AANT;i++)
	{
	    pImage = LoadJPG(beeldnaam[i]);
	    fprintf(stderr, "prent %s : %d x %d\n", beeldnaam[i],
                                            pImage->sizeX, pImage->sizeY);
		glBindTexture (GL_TEXTURE_2D,texName[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pImage->sizeX, pImage->sizeY,
                        0, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
		printf("sizeX is %d en sizeY is %d\n",pImage->sizeX,pImage->sizeY);
	}
				
}



void winReshapeFcn (GLint newWidth, GLint newHeight)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch ( projectie )
	{
		case 'o':
				glOrtho(xmin, xmax,  ymin, ymax, near, far);
				break;
		case 'f':
				glFrustum(xmin, xmax,  ymin, ymax, near, far);
				break;
		default:
		case 'p':
				gluPerspective(60.0, 1.0,  near, far);
				break;
	}
	glViewport(0, 0, newWidth, newHeight);

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
		
		case 'b' : bo=!bo; break;
		case 'k' : kege=!kege; break;
		
		case 'B' : bloem=!bloem; break;
		case 'm' : muur=!muur; break;
		case 'c' : cili=!cili; break;
		case 't' : textuur=!textuur; break;
		case 'q' : exit(0); break;
		case 'r' : xlens = 5.0;
			   ylens = 5.0;
			   zlens = 5.0;	
			   break;	
			
	}
	
	printf("oog %lf %lf %lf\n", xlens, ylens, zlens);
	glutPostRedisplay();
}


void displayFcn(void)
{	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(xlens,ylens,zlens, 0,0,0, 0,1,0);
	
	glBegin(GL_LINES);// assen
			glColor3f(1.0,0.0,0.0);
		glVertex3f(5.0,0.0,0.0);
		glVertex3f(0.0,0.0,0.0);
			glColor3f(0.0,1.0,0.0);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(0.0,5.0,0.0);
			glColor3f(0.0,0.0,1.0);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(0.0,0.0,5.0);
	glEnd();
	
	GLUquadricObj *bol;
	GLUquadricObj *cilinder;
	GLUquadricObj *kegel;

	
	if(cili){
		cilinder = gluNewQuadric();
		glPushMatrix();//cilinde
			glTranslatef(1.0, 0.0,0.0);
			if(textuur){
			glEnable(GL_TEXTURE_2D);
			glBindTexture (GL_TEXTURE_2D,texName[bloem]);
			glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			gluQuadricTexture(cilinder,GL_TRUE);
			}
			gluQuadricDrawStyle(cilinder,GLU_FILL);
			gluCylinder(cilinder,0.5,0.5,2,8,8);
			if(textuur)
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();	
		gluDeleteQuadric(cilinder);
	}
	if(bo){
		bol = gluNewQuadric();
		glPushMatrix();//bol
			glTranslatef(0.0, 1.0,0.0);
			if(textuur){
			glEnable(GL_TEXTURE_2D);
			glBindTexture (GL_TEXTURE_2D,texName[bloem]);
			glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			gluQuadricTexture(bol,GL_TRUE);
			}
			gluQuadricDrawStyle(bol,GLU_FILL);
			gluSphere(bol,0.5,8,8);
			if(textuur)
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();	
		gluDeleteQuadric(bol);
	}
	if(kege){
		kegel = gluNewQuadric();
		glPushMatrix();//kegel
			glTranslatef(0.0, 0.0,2.5);
			if(textuur){
			glEnable(GL_TEXTURE_2D);
			glBindTexture (GL_TEXTURE_2D,texName[bloem]);
			glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			gluQuadricTexture(kegel,GL_TRUE);
			}
			gluQuadricDrawStyle(kegel,GLU_FILL);
			gluCylinder(kegel,0.0,0.5,2,8,8);
			if(textuur)
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();	
		gluDeleteQuadric(kegel);
	}
	if (muur){
		
		glPushMatrix();//muur
			glColor3f(0.0,0.0,1.0);
			if(textuur){
			glEnable(GL_TEXTURE_2D);
			glBindTexture (GL_TEXTURE_2D,texName[bloem]);
			glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
			}
			glBegin(GL_QUADS);
				glTexCoord2f(0.0,0.0);	glVertex3d(0.0,0.0,-1.0);
				glTexCoord2f(0.0,2.0);	glVertex3d(0.0,4.0,-1.0);
				glTexCoord2f(2.0,2.0);	glVertex3d(4.0,4.0,-1.0);
				glTexCoord2f(2.0,0.0);	glVertex3d(4.0,0.0,-1.0);
			glEnd();
			
			if(textuur)
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();	
		gluDeleteQuadric(kegel);
	}
	
	
	
	
	glFlush();
}



int main (int argc,char* argv[])
{	
	xmax=10;
	ymax=10;
	if ( argc > 1 )
		projectie = argv[1][0];
	else
		projectie = 'p';
		
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
