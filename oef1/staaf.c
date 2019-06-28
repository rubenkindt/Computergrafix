#include <GL/glut.h>
#include <math.h>
#include "staaf.h"


GLint winWidth = 800,winHeight = 800;  /* 800*800 pixels */
int start;
int end;
int aantal;
int max=0;
int xrand;
int yrand;
int xmax;
int weektotalen[WLEN];
int weekKleuren[WLEN];
int knop;
Gebruik stru[AANTA];
GLdouble left=0.0;
GLdouble right;
GLdouble bot=0.0;
GLdouble top;
int toplijn=0;//geen boolean in opengl
int yWaarden=0;//geen boolean


void lijnMenu(int id){
	switch(id){
		case 0: 
			toplijn=1;
			break;
		case 1: 
			toplijn=0;
			break;
		case 2: 
			yWaarden=1;
			break;
		case 3: 
			yWaarden=0;
			break;
		case 4: 
			exit(0); 
			break;
		
	}
	glutPostRedisplay();			

}

void init(void)
{
	for(int i=0;i<WLEN;i++){// teggen idereen zeggen, er is rechts op je geklikt 
		weekKleuren[i]=0; //rechterMuisknop == normaal
	}
	glClearColor(1.0,1.0,1.0,1.0);  /* window color white */
	GLint menuu=glutCreateMenu(lijnMenu);
		glutAddMenuEntry("topLijnWeergeven",0);
		glutAddMenuEntry("topLijnVerbergen",1);
		glutAddMenuEntry("y waarden tonen",2);
		glutAddMenuEntry("y waarden verbergen",3);
		glutAddMenuEntry("quit",4);
		glutAttachMenu(GLUT_MIDDLE_BUTTON);
				
}



void winReshapeFcn (GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	winWidth = newWidth;
	winHeight = newHeight;
	
	gluOrtho2D(-xrand ,xmax+xrand,-yrand,max+yrand);// met 10% buffer
	printf("herschaald" );
	glViewport (0,0,newWidth,newHeight);
}



void displayFcn(void)
{	glClear(GL_COLOR_BUFFER_BIT);    /* clear display window */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
		glVertex2i(0,0);
		glVertex2d(xmax,0);//X-as
		glVertex2d(0,0);
		glVertex2d(0,max);//Y-as
		
	glEnd();
	int vorigeWeek =weektotalen[0+start];
	for(int i=0;i<xmax;i++){
		if(weekKleuren[i]==1){	//links
			int hoogte=0;
			int vorigeHoogte=0;
			for(int j=0;j<aantal;j++){
				if (stru[j].uren[i+start] != 0 )
				{
				hoogte+=stru[j].uren[i+start]; //onze gegevens
				glColor3f(1.0-((float)j/aantal),1.0,(float)j/aantal);
				glRectf(i,vorigeHoogte,i+0.5,hoogte);
				vorigeHoogte=hoogte;
				}
			}
		}else if(weekKleuren[i]==0){	//rechts
			glColor3f(0.0,1.0,0.0);
			//printf("%d\n",weektotalen[i+start]);		
			glRectf(i,0,i+0.5,weektotalen[i+start]);	
		}
		if (toplijn==1 && i>0){
			glColor3f(1.0,0.0,0.0);
			glBegin(GL_LINES);
				glVertex2f(0.25+i-1.0,vorigeWeek);//vorige week
				glVertex2f(0.25+i,weektotalen[i+start]);// deze week
				vorigeWeek=weektotalen[i+start];
			glEnd();
		}
		if (yWaarden==1){
			glColor3f(0.0,0.0,1.0);
			char woord[8]="";
			sprintf(woord,"%d",weektotalen[i+start]);
			glRasterPos2i(i,weektotalen[i+start]);
			int j=0;
			while(woord[j] !=0){
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15,woord[j]);
				j++;
			}
			
		}
	}
	
	glFlush();
}


int vindBalk(int px){
	int balkje=0;
	balkje=px*(xrand*2.0 + xmax)/(float)(winWidth);//
	balkje=balkje-xrand;//xradn offset
	printf("ik zie balkje : %d \n",balkje);
	return balkje;
}
void muis(int button,int pressed, int x, int y){
	if (pressed==GLUT_DOWN){
		switch(button){
			case GLUT_LEFT_BUTTON: //weizig kleur
				knop=0;
				//printf("x: %d  \n",x);
				break;
			case GLUT_RIGHT_BUTTON: 
				knop=1;//reset kleur
				break;
		}
		int balkje=vindBalk(x);
		if (balkje>=0 && balkje<=xmax){
			weekKleuren[balkje]=knop;	// in deze array gaat 0of1
			// komen om aan te duiden of er links/rechts geklikt is geweest
		}
		
	}
	glutPostRedisplay();// zegt tegen sys dat het opnieuw moet tekenen

}
int main (int argc,char* argv[])
{	
	for(int ii=0;ii<WLEN;ii++){
		weekKleuren[ii]=0.0;
	}
	
	aantal=lees(&start,&end,stru);
	for(int i=0;i<WLEN;i++){
		weektotalen[i]=0;
		for (int j=0;j<aantal;j++){
			weektotalen[i]+=stru[j].uren[i];
		}
		if (max<weektotalen[i] ){max=weektotalen[i];}
		//printf("%d  \n",weektotalen[i]);
	}	
	xmax=end-start+1;//aantal weken
	xrand=xmax*0.1;
	yrand=max*0.1;
	printf("xmax: %d  \n",xmax);
	printf("(y)max: %d  \n",max);
	printf("xrand: %d  \n",xrand);
	printf("yrand: %d  \n",yrand);
	
	
	
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);  //top left corner 
	glutInitWindowSize(winWidth,winHeight);
	glutCreateWindow("Eerste opengl prog");
	init();
	glutDisplayFunc(displayFcn);	
	glutReshapeFunc(winReshapeFcn);
	glutMouseFunc(muis);
	glutMainLoop();
	return 0;
}
