/*
 * volumes.c  : enkele volumes
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

GLdouble xlens = 5.0, ylens = 1.0, zlens = 5.0;
GLdouble near = 1.0, far = 20.0;
GLdouble xmin = -6.5, xmax = 6.5, ymin = -2.2, ymax = 4.0;
GLfloat hoek = 90.0;
GLfloat ttx = 0.0, tty = 1.0, ttz =-1.0, tsx = 1.0, tsy = 1.0, tsz = 1.0;
GLfloat ctx =  0.0, cty = 0.5, ctz = 0.0, csx = 1.0, csy = 1.0, csz = 1.0;
GLfloat ktx = -0.5, kty = 0.5, ktz = 2.2, ksx = 0.8, ksy = 1.0, ksz = 0.9;
int kubus = 1, cylinder = 1, torus = 1;
int draad = 1;
int draaien = 0;
GLubyte projectie = 'p';

void myinit(void)
{
	glClearColor(0.8, 0.8, 0.8, 0.0);
	glEnable(GL_DEPTH_TEST);
}

void animidle(void)
{
	if ( draaien )
		hoek += draaien * 1.0;
	glutSwapBuffers();
	glutPostRedisplay();
}

void toetsen( unsigned char key, int x, int y)
{
	switch ( key )
	{
		case 't' : ttx++; tty++; ttz++;  hoek -= 1.0;
                           tsx *= 2.1; tsy *= 2.05; tsz *= 0.65;   break;
		case 'T' : ttx--; tty--; ttz--;  hoek += 1.0;
                           tsx /= 2.1; tsy /= 2.05; tsz /= 0.65;   break;
		case 'c' : ctx--; cty++; ctz++;  hoek += 1.0;
                           csx *= 0.8; csy *= 1.8; csz *= 1.5;   break;
		case 'C' : ctx++; cty--; ctz--;  hoek -= 1.0;
                           csx /= 0.8; csy /= 1.8; csz /= 1.5;   break;
		case 'k' : ktx++; kty--; ktz++;  hoek += 1.0;
                           ksx *= 1.9; ksy *= 0.7; ksz *= 1.45;   break;
		case 'K' : ktx--; kty++; ktz--;  hoek -= 1.0;
                           ksx /= 1.9; ksy /= 0.7; ksz /= 1.45;   break;
		case 'x' : xlens++;            break;
		case 'X' : xlens--;            break;
		case 'y' : ylens++;            break;
		case 'Y' : ylens--;            break;
		case 'z' : zlens++;            break;
		case 'Z' : zlens--;            break;
		case 'r' : xlens = ylens = zlens = 3.0;          break;
		case 'R' : hoek=0.0;    break;
		case 'g' : draaien = !draaien;  break;
		case 'G' : draaien = -draaien;  break;
		case '1' : kubus = !kubus;         break;
		case '2' : torus = !torus;         break;
		case '3' : cylinder = !cylinder;   break;
		case 'w' : draad = !draad;         break;
		case 'q' : exit(0);                break;
	}
	printf("oog %lf %lf %lf\n", xlens, ylens, zlens);
	glutPostRedisplay();
}


void torkubcyl(void)
{
	GLfloat smxz[16] = { 1.0,0.0,0.0,0.0, 1.0,1.0,1.0,0.0, 
			             0.0,0.0,1.0,0.0, 0.0,0.0,0.0,1.0 };
	GLdouble xyvlak[4] = { 1.0, 1.0, 0.0, 0.25 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClipPlane(GL_CLIP_PLANE0, xyvlak);
	gluLookAt(xlens,ylens,zlens, 0.0,0.0,0.0, 0.0,1.0,0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(2.0);
	glLineStipple(1, 0xCCCC);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(5.0,0.0,0.0);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(0.0,5.0,0.0);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(0.0,0.0,5.0);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	if ( projectie == 'o' )
	{
		glColor3f(0.7, 0.7, 0.7);
		glBegin(GL_QUADS);
			glVertex3f(-1.25, 1.0, 0.0);
			glVertex3f(-1.25, 1.0, -1.0);
			glVertex3f(1.0, -1.25, -1.0);
			glVertex3f(1.0, -1.25, 0.0);
		glEnd();
	}
	glLineWidth(2.5);
	if ( torus )
	{
		glPushMatrix();
		glEnable(GL_CLIP_PLANE0);
		glColor3f(0.0, 0.0, 1.0);
		glScalef(tsx, tsy, tsz);
		glTranslatef(ttx, tty, ttz);
		glRotatef(hoek, 0.0, 0.0, 1.0);
		if ( draad )
			glutWireTorus(0.5, 1.8, 8, 12);
		else
			glutSolidTorus(0.5, 1.8, 8, 12);
		glDisable(GL_CLIP_PLANE0);
		glPopMatrix();
	}
	if ( kubus )
	{
		smxz[4] = (float)1.0/tan(M_PI*80.0/180.0);
		smxz[6] = (float)1.0/tan(M_PI*70.0/180.0);
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glColor3f(0.0, 1.0, 0.0);
		glTranslatef(ktx, kty, ktz);
		glRotatef(hoek, 0.0, 1.0, 0.0);
		glPushMatrix();
		glMultMatrixf(smxz);
		glScalef(ksx, ksy, ksz);
		if ( draad )
			glutWireCube(1.0);
		else
			glutSolidCube(1.0);
		glPopMatrix();
		if ( cylinder )
		{
			GLUquadricObj *rol;
			rol = gluNewQuadric();
			glPushMatrix();
			glColor3f(1.0, 1.0, 0.0);
			glTranslatef(ctx, cty, ctz);
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			if ( draad )
		    	gluQuadricDrawStyle(rol, GLU_LINE);
			else
		    	gluQuadricDrawStyle(rol, GLU_SILHOUETTE);
			gluCylinder(rol, 0.4, 0.4, 1.9, 8, 4);
			glPopMatrix();
			gluDeleteQuadric(rol);
		}
		glPopAttrib();
		glBegin(GL_POINTS); glVertex3f(0.0,0.0,0.0);   glEnd();
		glPopMatrix();
	}
	glFlush();
}

void herschaal(GLint n_w, GLint n_h) 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch ( projectie )
	{
		case 'o':
				glOrtho(xmin, xmax,  ymin, ymax, near, far);
				break;
		case 'f':
				glFrustum(xmin, xmax,  ymin, ymax, 2*near, 8*far);
				break;
		default:
		case 'p':
				gluPerspective(60.0, 1.0,  near, far);
				break;
	}
	glViewport(0, 0, n_w, n_h);
}
int main( int argc, char * argv[])
{
	fprintf(stderr, "Gebruik: volumes p<o/f>\n");
	fprintf(stderr, "1(kubus) 2(torus) 3(cylinder) \n");
	fprintf(stderr, "w(ire) g(raaien) r(eset) tcodi(bewegen)  xyz\n");
	if ( argc > 1 )
	{
	     projectie = argv[1][0];
	}
	else
	     projectie = 'p';      /* default symmetrisch perspectief  */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Volumes");
	glutKeyboardFunc(toetsen);
	glutReshapeFunc(herschaal);
	myinit();
	glutIdleFunc(animidle);
	glutDisplayFunc(torkubcyl);
	glutMainLoop();
	return 0;
}
