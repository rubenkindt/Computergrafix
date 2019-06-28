#include <GL/glut.h>
#include <math.h>
#define AANTALPLAN 8

GLint winWidth = 800,winHeight = 800;  /* 800*800 pixels */
GLdouble xlens =5.0, ylens = 5.0, zlens = 5.0;
int xmax=10;
int ymax=10;
int kijkHoek=90;
int verhouding=1;
float near=0.5;
float far=100.0;
GLfloat zwart[]     = {0.0,0.0,0.0,1.0};
GLfloat wit[]       = {1.0,1.0,1.0,1.0};
GLfloat ROOD[]	={0.5, 0.0, 0.0, 0.0};
GLfloat emmissie[]	={1.0,1.0,0.0,1.0};
GLfloat blauw[]	={0.3,0.0,1.0,1.0};
GLfloat lichtpos[]={0.0,0.0,0.0};

float solid=1.0;
int l=0;
char projectie='p';
GLfloat hoek=0.0;
GLfloat initHoek=71.0;
GLfloat maxHoek=360.0;

GLfloat planeet[AANTALPLAN][3]={
{4.06,	3.06,	0.3},
{5.68,	5.0,	0.5},
{7.01,	7.01,	0.55},
{8.42,	9.2,	0.4},
{10.66,	10.0,	1.05},
{12.26,	11.26,	1.03},
{13.96,	14.46,	0.85},
{15.41,	16.4,	0.825}
};
GLfloat zon[3]={0.0,	0.0,	1.0};
void init(void)
{
	glClearColor(1.0,1.0,1.0,1.0);  /* window color white */
	glEnable(GL_DEPTH_TEST);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, zwart);
		
	
	glLightfv(GL_LIGHT0,GL_SPECULAR,zwart);	
	glLightfv(GL_LIGHT0,GL_DIFFUSE,wit);
	glLightfv(GL_LIGHT0,GL_EMISSION,wit);
	
	glLightfv(GL_LIGHT0,GL_AMBIENT,zwart);	
		
	glDisable(GL_LIGHT0);
	//glClearColor(0.0,0.0,0.0,1.0);
				
}



void winReshapeFcn (GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	winWidth = newWidth;
	winHeight = newHeight;
	
	
	gluPerspective(kijkHoek,verhouding,  near, far);
	


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
		case 'l' : l=!l;
		 case 't': solid=0.0;
		 	break;
		 case 'T': solid=1.0;
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
	glColor3f(0.0,0.0,0.0);

	glLightfv(GL_LIGHT0,GL_POSITION,lichtpos);
	glEnable(GL_LIGHT0);
	//zon
	GLUquadricObj *zonglu;
	zonglu=gluNewQuadric();

	
	
	if(l)
		glEnable(GL_LIGHTING);
		
	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emmissie);	
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, emmissie);	
		glTranslatef(cos((M_PI/180)*(hoek))*zon[0],0.0,sin((M_PI/180)*(hoek))*zon[1]);
		gluSphere(zonglu,zon[2],8,8);
		//gluCylinder(zonglu,0.0,1.0,3.0,8,8);
	glPopMatrix();
	gluDeleteQuadric(zonglu);

	GLUquadricObj *bol;
	bol=gluNewQuadric();

	for(int i=0; i<AANTALPLAN;i++){	
		glPushMatrix();
			
			
			glMaterialfv(GL_FRONT, GL_EMISSION, ROOD);		
			glTranslatef(cos((M_PI/180)*(hoek+initHoek*i))*planeet[i][0],0.0,sin((M_PI/180)*(hoek+initHoek*i))*planeet[i][1]);

			gluSphere(bol,planeet[i][2],8,8);
			if(i==4){
				GLUquadricObj *maan;
				maan=gluNewQuadric();
				glMaterialfv(GL_FRONT, GL_EMISSION, blauw);
				glPushMatrix();
					glTranslatef(1.0+cos((M_PI/180)*(hoek))*0.5,0.0,sin((M_PI/180)*(hoek))*0.5);
					glRotated(hoek,0.0,0.0,1.0);
					//gluQuadricDrawStyle(maan,GLU_LINE);
					//gluCylinder(maan,0.0,1.0,3.0,8,8);
					gluSphere(maan,0.4,8,8);
					glPopMatrix();
				gluDeleteQuadric(maan);	
				glMaterialfv(GL_FRONT, GL_EMISSION, zwart);
			}
			if(i==3){
				GLUquadricObj *ring;
				ring=gluNewQuadric();
				glMaterialfv(GL_FRONT, GL_EMISSION, blauw);
				glPushMatrix();
					//glTranslatef(cos((M_PI/180)*(hoek+initHoek*i))*planeet[i][0],0.0,sin((M_PI/180)*(hoek+initHoek*i))*planeet[i][1]);
					glRotated(90,1.0,0.0,0.0);
					//gluQuadricDrawStyle(maan,GLU_LINE);
					//gluCylinder(maan,1.0,0.0,3.0,8,8);
					gluDisk(ring,planeet[i][2]+0.1,planeet[i][2]+0.3,8,8);
				glPopMatrix();	
				glMaterialfv(GL_FRONT, GL_EMISSION, zwart);
				gluDeleteQuadric(ring);	
			}
			
		glPopMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, zwart);	
	}
	if(l)
		glDisable(GL_LIGHTING);
	
	gluDeleteQuadric(bol);		
	glutSwapBuffers();
	glDisable(GL_LIGHTING);
	glFlush();
}
void hoekfct(){
	//printf("hoek: %f \n",hoek);
	hoek+=1;
	if(hoek>=maxHoek)hoek=0.0;
	glutPostRedisplay();
}
int main (int argc,char* argv[])
{	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_DEPTH| GLUT_RGBA);
	glutInitWindowPosition(100,100);  //top left corner 
	glutInitWindowSize(winWidth,winHeight);
	glutCreateWindow("7.2de opengl prog");
	init();
	glutDisplayFunc(displayFcn);
	glutKeyboardFunc(toetsen);	
	glutReshapeFunc(winReshapeFcn);
	glutIdleFunc(hoekfct);
	glutMainLoop();
	return 0;
}
