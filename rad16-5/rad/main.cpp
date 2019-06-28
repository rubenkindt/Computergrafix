// Ruben Kindt
#include <windows.h>

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "..//../jpeg/InitJPG.h"    //textuur jpg
#define AANT 3

GLint winWidth = 900,winHeight = 950;
char projectie='p';
float oognear=0.5;
float oogfar=200.0;
GLdouble xoog = 2.0, yoog = 1.0, zoog = 9.0;

GLfloat WIT[]       =   {1.0,1.0,1.0,1.0};
GLfloat GROEN_EN_BLAUW[]= {0.0,1.0,1.0,1.0};
GLfloat grijs[]     =  {1.0,1.0,1.0,1.0};
int doorzichtig=0;
int assen=1;
int reuzenraderen=1;
int cabines=8;
int toonCtrlPunten=0;
int tooncomplex=0;
int uitbreiding=0;
int cilinderKuip=0;//0=bezier,1=cilinder

GLint draaien=0,hoek=0;
GLint draaisnelheid=1;
GLint wiebelen=0,wiebelhoek=0; GLfloat wiebelrichting=1.0;
GLint tijd =10;

int materiaalKuip=1;    //grijs
int materiaalStang=1;   //Chroom
int materiaalDak=1;     //Geel
int flatS=1;

int textuur=0;    //texcstuur werkt niet
int kleurenPalet=0;
GLuint texName[AANT];
char beeldnaam[AANT][80] = { "dak.jpg" , "kuip.jpg" , "vloer.jpg" } ;

const GLfloat ORANJE[]       = {1.0, 0.6, 0.0, 1.0};
const GLfloat PAARS[]        = {1.0, 0.6, 0.4, 1.0};
const GLfloat ROOS[]         = {1.0, 0.5, 0.7, 1.0};
const GLfloat BRIJN[]        = {0.5, 0.2, 0.0, 1.0};
      GLfloat LICHTBLAUW[]   = {0.0, 1.0, 1.0, 1.0};
const GLfloat ZWART[]        = {0.0, 0.0, 0.0, 1.0};
const GLfloat GEEL[]         = {1.0, 1.0, 0.0, 1.0};
const GLfloat ROOD[]         = {1.0, 0.0, 0.0, 1.0};
const GLfloat smogkleur[] = { 0.75, 0.25, 0.75, 1.0 };

const GLfloat KUIPGRIJSAMBI[]  = { 0.22, 0.22, 0.22, 1.0 };
const GLfloat KUIPGRIJSDIFF[]  = { 0.33, 0.33, 0.33, 1.0 };
const GLfloat KUIPGRIJSSPEC[]  = { 0.11, 0.11, 0.11, 1.0 };

const GLfloat KUIPWITAMBI[]  = { 0.66, 0.66, 0.66, 1.0 };
const GLfloat KUIPWITDIFF[]  = { 0.77, 0.77, 0.77, 1.0 };
const GLfloat KUIPWITSPEC[]  = { 0.55, 0.55, 0.55, 1.0 };

const GLfloat STANGCHROOMAMBI[]  = { 0.46, 0.58, 0.35, 1.0 };
const GLfloat STANGCHROOMDIFF[]  = { 0.23, 0.29, 0.17, 1.0 };
const GLfloat STANGCHROOMSPEC[]  = { 0.69, 0.87, 0.52, 1.0 };

const GLfloat STANGBRONSAMBI[]  = { 0.21, 0.13, 0.10, 1.0 };
const GLfloat STANGBRONSDIFF[]  = { 0.39, 0.27, 0.17, 1.0 };
const GLfloat STANGBRONSSPEC[]  = { 0.71, 0.43, 0.18, 1.0 };

const GLfloat DAKGEELAMBI[]  = { 0.65, 0.55, 0.15, 1.0 };
const GLfloat DAKGEELDIFF[]  = { 0.75, 0.45, 0.15, 1.0 };
const GLfloat DAKGEELSPEC[]  = { 0.85, 0.35, 0.15, 1.0 };

const GLfloat DAKLILAAMBI[]  = { 0.45, 0.15, 0.75, 1.0 };
const GLfloat DAKLILADIFF[]  = { 0.55, 0.15, 0.65, 1.0 };
const GLfloat DAKLILASPEC[]  = { 0.35, 0.15, 0.85, 1.0 };
GLfloat shini = 10.0;
const GLfloat LICHTPOS1[]  = { 0.0, 0.0, 0.0, 0.0 };
const GLfloat LICHTPOS2[]  = { 4.0, 3.0, 4.0, 0.0 };    //vooraan=loodrecht op reuzenrad, achterkant van het rad = donker
const GLfloat LICHTPOS3[]  = { 3.0, 0.0, 3.0, 0.0 };    // langs onder
GLfloat LICHTPOS4[]  	   = { 4.5, 0.0, 3.0, 0.0 }; //vooraan

GLfloat lichthoek=45.0;
GLfloat expo=20.0;
const GLfloat direc[]={-1.0,0.0,0.0};//{0.0,-1.0,0.0};// ongeveer centrum rad
GLint tekenLampPunten=0;

GLint mist=0;
GLdouble clipvlak[4]={0.0,1.0,0.0,0.0};

GLfloat kuipCtrlPunten[6][4][3] =
{
   { {0.0, 0.1, 0.00}, {0.04, 0.1, 0.00}, {0.08, 0.1, 0.00}, {0.12, 0.1, 0.00}},
   { {0.0, 0.0, 0.04}, {0.04, 0.0, 0.04}, {0.08, 0.0, 0.04}, {0.12, 0.1, 0.04}},
   { {0.0, 0.0, 0.08}, {0.04, 0.0, 0.08}, {0.08, 0.0, 0.08}, {0.12, 0.1, 0.08}},
   { {0.0, 0.0, 0.12}, {0.04, 0.0, 0.12}, {0.08, 0.0, 0.12}, {0.12, 0.1, 0.12}},
   { {0.0, 0.0, 0.18}, {0.04, 0.0, 0.18}, {0.08, 0.0, 0.18}, {0.12, 0.1, 0.18}},
   { {0.0, 0.1, 0.20}, {0.04, 0.1, 0.20}, {0.08, 0.1, 0.20}, {0.12, 0.1, 0.20}}
};

GLUnurbsObj *theNurb;
GLfloat dakVreemdevorm[4][4][3];    //b-spline

void materiaalMenu(int id){
	switch(id){
	    case 1: break;
            case 11:	materiaalKuip=1;    break;
            case 12:	materiaalKuip=0;    break;
        case 2: break;
            case 21:	materiaalStang=1;   break;
            case 22:	materiaalStang=0;   break;
        case 3: break;
            case 31:	materiaalDak=1;     break;
            case 32:	materiaalDak=0;     break;
		case 4: exit(0);        			break;
		default: printf("default"); break;
	}
	glutPostRedisplay();
}
void init(void){
	glClearColor(0.9,0.9,0.9,0.0);  /* window color wit */
	glEnable(GL_DEPTH_TEST);

    GLint kuipMenu = glutCreateMenu(materiaalMenu);
            glutAddMenuEntry("grijs",11);
            glutAddMenuEntry("witachtig",12);
    GLint stangMenu = glutCreateMenu(materiaalMenu);
            glutAddMenuEntry("chroom",21);
            glutAddMenuEntry("brons",22);
    GLint dakMenu = glutCreateMenu(materiaalMenu);
            glutAddMenuEntry("geel",31);
            glutAddMenuEntry("lila",32);
	glutCreateMenu(materiaalMenu);
        glutAddSubMenu("kuip", kuipMenu);
        glutAddSubMenu("Stangen", stangMenu);
        glutAddSubMenu("Dak", dakMenu);
        glutAddMenuEntry("quit",4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ZWART);
    glLightfv(GL_LIGHT0,GL_POSITION,ZWART);
	glLightfv(GL_LIGHT0,GL_SPECULAR,ZWART);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,ZWART);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ZWART);

	glLightfv(GL_LIGHT1,GL_SPECULAR,ZWART);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,ZWART);
	glLightfv(GL_LIGHT1,GL_AMBIENT,ZWART);

    glLightfv(GL_LIGHT2,GL_SPECULAR,ZWART);
	glLightfv(GL_LIGHT2,GL_DIFFUSE,ZWART);
	glLightfv(GL_LIGHT2,GL_AMBIENT,ZWART);

    glLightfv(GL_LIGHT3,GL_SPECULAR,ZWART);
	glLightfv(GL_LIGHT3,GL_DIFFUSE,ZWART);
	glLightfv(GL_LIGHT3,GL_AMBIENT,ZWART);

    glLightfv(GL_LIGHT4,GL_SPECULAR,ZWART);
	glLightfv(GL_LIGHT4,GL_DIFFUSE,ZWART);
	glLightfv(GL_LIGHT4,GL_AMBIENT,ZWART);

	glBlendFunc(GL_ONE,GL_ONE_MINUS_DST_ALPHA);

    glDepthFunc(GL_LESS);

    glEnable(GL_NORMALIZE);//normaliseren van de vectoren

    theNurb = gluNewNurbsRenderer();
    gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);

/*
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1);
   	glGenTextures(AANT, texName);
 	tImageJPG *pImage;
	for(int i=0;i< AANT;i++)
	{
	    pImage = LoadJPG(beeldnaam[i]);
	    fprintf(stderr, "prent %s : %d x %d\n", beeldnaam[i],
                                            pImage->sizeX, pImage->sizeY);
		glBindTexture (GL_TEXTURE_2D,texName[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pImage->sizeX, pImage->sizeY,
                        0, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
		printf("sizeX is %d en sizeY is %d\n",pImage->sizeX,pImage->sizeY);
	}
    */

}

void ondersteuning(GLfloat x,GLfloat y,GLfloat z){
//------------------------------ondersteuning------------------------------
    GLUquadricObj *ondersteuning;
    ondersteuning = gluNewQuadric();
    if(materiaalStang){
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,STANGCHROOMAMBI);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,STANGCHROOMDIFF);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,STANGCHROOMSPEC);
    }else{
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,STANGBRONSAMBI);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,STANGBRONSDIFF);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,STANGBRONSSPEC);
    }
    glPushMatrix();
        glTranslatef(x, y, z);
        glRotated(90,1,0,0);
        glRotated(wiebelhoek,0,1,0);
        if (tooncomplex)
            gluQuadricDrawStyle(ondersteuning, GLU_LINE);
        else
            gluQuadricDrawStyle(ondersteuning, GLU_FILL);
        gluCylinder(ondersteuning, 0.01, 0.01, 0.39, 8, 8);
    glPopMatrix();
    gluDeleteQuadric(ondersteuning);
}
void dak(GLfloat x,GLfloat y,GLfloat z){
//------------------------------dak------------------------------
    GLfloat verkleiningsfactor=0.075;
    for(int i=0;i<4;i++){//dak genereren b-spline
        for(int j=0;j<4;j++){
            dakVreemdevorm[j][i][0]=i*verkleiningsfactor*(cos((30*j)*M_PI/180)); //X (i*cos(j*22.5))/10;
            dakVreemdevorm[j][i][1]=i*0.8*verkleiningsfactor;  //Y (i*1)/10;
            dakVreemdevorm[j][i][2]=i*verkleiningsfactor*(sin((30*j)*M_PI/180)); //Z (i*sin(j*22.5))/10;
        }
    }
    if(materiaalDak){
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT ,DAKGEELAMBI);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE ,DAKGEELDIFF);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,DAKGEELSPEC);
    }else{
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT ,DAKLILAAMBI);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE ,DAKLILADIFF);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,DAKLILASPEC);
    }
    if (tooncomplex){//toont b-spline
        GLfloat knots[8] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0};
        for(int i=0;i<4;i++){
            glPushMatrix();
                glTranslatef(x, y, z);
                glRotatef(180, 0.,0.,1.);
                glRotated(wiebelhoek,0,0,1);
                glRotatef(i*90, 0.,1.,0.);
                if(textuur){
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture (GL_TEXTURE_2D,texName[0]);   //dak.jpg
                    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
                    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
                }

                if(toonCtrlPunten){//tekent de dak punten
                    glDisable(GL_LIGHTING);
                    glPointSize(8.0);
                    glColor3f(1.0, 1.0, 0.0 );
                    glBegin(GL_POINTS);
                        for (int i=0;i<4;i++){//4=lengte of dakVreemdevorm
                            for (int j=0;j<4;j++){
                                glVertex3fv(dakVreemdevorm[i][j]);
                            }
                        }
                    glEnd();
                    glEnable(GL_LIGHTING);
                }
                if(uitbreiding){//toont de daklijnen
                    for (int j = 0; j < 4; j++) {
                        glBegin(GL_LINE_STRIP);
                        for (int i = 0; i < 4; i++){
                            glVertex3fv(dakVreemdevorm[j][i]);
                        }
                        glEnd();
                    }
                    for (int i=0; i<4; i++){
                        glBegin(GL_LINE_STRIP);
                        for (int j=0; j<4; j++){
                            glVertex3fv(dakVreemdevorm[j][i]);
                        }
                        glEnd();
                    }
                }else{//tekent de b-spline
                    gluBeginSurface(theNurb);
                    gluNurbsSurface(theNurb, 8, knots, 8, knots,  4 * 3, 3, &dakVreemdevorm[0][0][0],  4, 4, GL_MAP2_VERTEX_3);
                    gluEndSurface(theNurb);
                    if(textuur)
                        glDisable(GL_TEXTURE_2D);
                    }
            glPopMatrix();
            }
    }else{  // gluCylinder via quadric geeft een mooier beeld dan cone
        GLUquadricObj *dak;
        dak = gluNewQuadric();
        glPushMatrix();
            glTranslatef(x, y-0.04, z);
            glRotated(90,1,0,0);
            glRotated(wiebelhoek,0,1,0);
            if(textuur){
                glEnable(GL_TEXTURE_2D);
                glBindTexture (GL_TEXTURE_2D,texName[0]);   //0=dak.jpg
                glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
                gluQuadricTexture(dak,GL_TRUE);
			}
            gluQuadricDrawStyle(dak, GLU_FILL);
            gluCylinder(dak, 0.0, 0.2, 0.15, 15, 15);
            if(textuur)
                glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        gluDeleteQuadric(dak);
    }
}
void kuipValsgespeeld(GLfloat x,GLfloat y,GLfloat z){
//------------------------------kuip------------------------------
    if(cilinderKuip){//valsgespeeld via quadric een kuip
        GLUquadricObj *kuip;
        kuip = gluNewQuadric();
        glPushMatrix();
            glTranslatef(x+0.3*sin(wiebelhoek*M_PI/180), y-0.3*cos(wiebelhoek*M_PI/180), z);
            glRotated(90,1,0,0);
            glRotated(wiebelhoek,0,1,0);
            if(textuur){
                glEnable(GL_TEXTURE_2D);
                glBindTexture (GL_TEXTURE_2D,texName[1]);//1=kuip.jpg
                glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
                gluQuadricTexture(kuip,GL_TRUE);
            }
            if (tooncomplex)
                gluQuadricDrawStyle(kuip, GLU_LINE);
            else
                gluQuadricDrawStyle(kuip, GLU_FILL);
            gluCylinder(kuip, 0.2, 0.0, 0.1, 8, 8);
            if(textuur)
                glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        gluDeleteQuadric(kuip);
    }
}
void kuip(GLfloat x,GLfloat y,GLfloat z){
    //++++++++++++++++bezier++++++++++++++++++++++
        z-=0.1;//halve breedte van de kuip
        glPushMatrix();
            glTranslatef(x+0.4*sin(wiebelhoek*M_PI/180), y-0.4*cos(wiebelhoek*M_PI/180), z);
            glRotated(wiebelhoek,0,0,1);
            if(textuur){
                glEnable(GL_TEXTURE_2D);
                glBindTexture (GL_TEXTURE_2D,texName[1]);//1=kuip.jpg
                glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
                glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 3, 4, 0, 1, 12, 6, &kuipCtrlPunten[0][0][0]);
            }

            //	0,1,hoe groot is1punt,totale hoogte,0,1,hoever staan ze uit een,
            glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, &kuipCtrlPunten[0][0][0]);
            //TODO comments
            glEnable(GL_MAP2_VERTEX_3);
            glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
            for(int k=0;k<2;k++){
                if(tooncomplex){//toont de mesh lijnen
                    if(uitbreiding){//korte manier
                        glEvalMesh2(GL_LINE, 0, 20, 0, 20);
                    }else{//lange manier
                        for (int j = 0; j < 6; j++) {
                            glBegin(GL_LINE_STRIP);
                            for (int i = 0; i < 4; i++){
                                glVertex3fv(kuipCtrlPunten[j][i]);
                            }
                            glEnd();
                        }
                        for (int i=0; i<4; i++){
                            glBegin(GL_LINE_STRIP);
                            for (int j=0; j<6; j++){
                                glVertex3fv(kuipCtrlPunten[j][i]);
                            }
                            glEnd();
                        }
                    }
                }else{
                    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
                }
                if(toonCtrlPunten){//toon de punten
                    glDisable(GL_LIGHTING);
                    glPointSize(8.0);
                    glBegin(GL_POINTS);
                        for (int i=0;i<4;i++){  //4=breedte of kuipCtrlPunten
                            for(int j=0;j<6;j++){   ////6=lengte of kuipCtrlPunten
                                glVertex3fv(kuipCtrlPunten[j][i]);
                            }
                        }
                    glEnd();
                    glEnable(GL_LIGHTING);
                }
                glScaled(-1,1,1);//kuip 'spiegelen'
            }
            if(textuur)
                glDisable(GL_TEXTURE_2D);
            glDisable(GL_MAP2_VERTEX_3);

        glPopMatrix();
        glEnable(GL_LIGHTING);
}
void cabine(GLfloat x,GLfloat y,GLfloat z){
    z+=0.3;//midden van de dwarsbalk
    ondersteuning(x,y,z);
    dak(x,y,z);
    if(materiaalKuip){
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT ,KUIPGRIJSAMBI);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE ,KUIPGRIJSDIFF);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,KUIPGRIJSSPEC);
    }else{
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT ,KUIPWITAMBI);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE ,KUIPWITDIFF);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,KUIPWITSPEC);
    }
    if(cilinderKuip){//welke versie van de kuip tonen we
        kuipValsgespeeld(x,y,z);
    }else{
        kuip(x,y,z);
    }
}
void raam (GLint newWidth, GLint newHeight){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	winWidth = newWidth;
	winHeight = newHeight;

	GLdouble grens;
	switch ( projectie )
	{
		default:    break;
		case 'o':	glOrtho(-5,5,-5,5,oognear,oogfar);                break;
		case 'f':   grens = oognear*tan(M_PI*(45.0/2.0)/180.0);
				glFrustum(-grens, grens,  -grens, grens, oognear, oogfar);break;
		case 'p':	gluPerspective(45.0, (GLdouble)newWidth/ (GLdouble)newHeight, oognear, oogfar);	break;
        //afblijven het werkt eindelijk!
	}
	printf("herschaald \n " );
	glViewport (0,0,newWidth,newHeight);
}
void steunbalken(GLfloat offsetz){
    if(materiaalStang){
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,STANGCHROOMAMBI);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,STANGCHROOMDIFF);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,STANGCHROOMSPEC);
    }else{
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,STANGBRONSAMBI);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,STANGBRONSDIFF);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,STANGBRONSSPEC);
    }
    glPushMatrix();//schuine balken1A
        glTranslatef(3.0,0.0,offsetz+3.0);
        glRotated(25,0,0,1);
        glScalef(0.1,2.9,0.1);
        glutSolidCube(1);
    glPopMatrix();

     glPushMatrix();//schuine balken1B
        glTranslatef(2.0,0.0,offsetz+3.0);
        glRotated(25,0,0,-1);
        glScalef(0.1,2.9,0.1);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();//schuine balken2A
        glTranslatef(3.0,0.0,offsetz+2.0);
        glRotated(25,0,0,1);
        glScalef(0.1,2.9,0.1);
        glutSolidCube(1);
    glPopMatrix();

     glPushMatrix();//schuine balken2B
        glTranslatef(2.0,0.0,offsetz+2.0);
        glRotated(25,0,0,-1);
        glScalef(0.1,2.9,0.1);
        glutSolidCube(1);
    glPopMatrix();
}
void as(GLfloat offsetX){
    GLUquadricObj *rol;
    rol = gluNewQuadric();
    if(materiaalStang){
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,STANGCHROOMAMBI);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,STANGCHROOMDIFF);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,STANGCHROOMSPEC);
    }else{
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,STANGBRONSAMBI);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,STANGBRONSDIFF);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,STANGBRONSSPEC);
    }
    glPushMatrix();
        glTranslatef(2.5, 1.2, offsetX+1.9);
        glRotated(hoek,0,0,1);
        if(tooncomplex)
            gluQuadricDrawStyle(rol, GLU_LINE);
        else
            gluQuadricDrawStyle(rol, GLU_FILL);
        gluCylinder(rol, 0.1, 0.1, 1.2, 15, 15);
    glPopMatrix();
    gluDeleteQuadric(rol);
}
void torussen(GLfloat offsetX){// schijven waren lelijk, te plat
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT ,LICHTBLAUW);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE ,LICHTBLAUW);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,LICHTBLAUW);
    LICHTBLAUW[3]=1.0;

        for(int i=0;i<2;i++){
            glPushMatrix(); //torussen
            if ( doorzichtig ){
                LICHTBLAUW[3]=0.75;
                glEnable(GL_BLEND);
                glDepthMask(GL_FALSE);
                glBlendFunc (GL_SRC_ALPHA, GL_DST_ALPHA);//GL_ONE_MINUS_SRC_ALPHA);
            }
            glScalef(1.0, 1.0, 1.0);
            glTranslatef(2.5, 1.2, offsetX+2.2+i*0.6);
            glRotated(hoek, 0, 0, 1);
            if(tooncomplex)
                glutWireTorus(0.1, 1.6, 15, 15);
            else
                glutSolidTorus(0.1, 1.6, 15, 15);
            if(doorzichtig){
                glDepthMask(GL_TRUE);
                glDisable(GL_BLEND);
            }
            glPopMatrix();
        }
}
void spaken(GLfloat offsetX){
    if(materiaalStang){
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,STANGCHROOMAMBI);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,STANGCHROOMDIFF);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,STANGCHROOMSPEC);
    }else{
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT ,STANGBRONSAMBI);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE ,STANGBRONSDIFF);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,STANGBRONSSPEC);
    }
    GLUquadricObj *spaak;
    spaak = gluNewQuadric();
    for(float i=0.0;i<360.0;i+=(360.0/cabines)){
        for(int j=0;j<2;j++){
            glPushMatrix();//spaak 1
            glTranslatef(2.5, 1.2, offsetX+2.25+j*0.55);
            glRotatef(-90.0, 1.0, 0.0, 0.0);
            glRotatef(i, 0.0, 1.0, 0.0);
            glRotated(-hoek, 0, 1, 0);
            gluQuadricDrawStyle(spaak, GLU_FILL);
            if (tooncomplex)
                gluQuadricDrawStyle(spaak, GLU_LINE);
            else
                gluQuadricDrawStyle(spaak, GLU_FILL);
            gluCylinder(spaak, 0.05, 0.05, 1.6, 15, 15);
        glPopMatrix();
        }
    }
    gluDeleteQuadric(spaak);
}
void dwarsEnCabine(GLfloat offsetX){//dwarsbalk en cabines
    GLUquadricObj *dwars;
    dwars = gluNewQuadric();
    if(materiaalStang){
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,STANGCHROOMAMBI);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,STANGCHROOMDIFF);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,STANGCHROOMSPEC);
    }else{
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,STANGBRONSAMBI);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,STANGBRONSDIFF);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,STANGBRONSSPEC);
    }
    for(GLfloat i=-hoek;i<360.0-hoek;i+=(360.0/cabines)){
        glPushMatrix();
            glTranslatef(2.5+1.6*sin(i*M_PI/180), 1.2+1.6*cos(i*M_PI/180), offsetX+2.2);
            glRotatef(0.0, 1.0, 0.0, 0.0);
            if (tooncomplex)
                gluQuadricDrawStyle(dwars, GLU_LINE);
            else
                gluQuadricDrawStyle(dwars, GLU_FILL);
            gluCylinder(dwars, 0.05, 0.05, 0.6, 15, 15);
        glPopMatrix();
        cabine(2.5+1.6*sin(i*M_PI/180), 1.2+1.6*cos(i*M_PI/180), offsetX+2.2);
    }
    gluDeleteQuadric(dwars);
}
void lichten(){
    glLightfv(GL_LIGHT1, GL_AMBIENT, WIT);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, GROEN_EN_BLAUW);
    glLightfv(GL_LIGHT3, GL_SPECULAR, ROOD);
    glLightfv(GL_LIGHT4, GL_AMBIENT, GEEL);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, GEEL);
    glLightfv(GL_LIGHT4, GL_SPECULAR, GEEL);

    glLightfv(GL_LIGHT1,GL_POSITION,LICHTPOS1);
    glLightfv(GL_LIGHT2,GL_POSITION,LICHTPOS2);
    glLightfv(GL_LIGHT3,GL_POSITION,LICHTPOS3);
    glLightfv(GL_LIGHT4,GL_POSITION,LICHTPOS4);

    glLightf(GL_LIGHT4,GL_SPOT_CUTOFF, lichthoek);
	glLightf(GL_LIGHT4,GL_SPOT_EXPONENT, expo);
	glLightfv(GL_LIGHT4,GL_SPOT_DIRECTION, direc);

}
void anim(int delta){
	if ( wiebelen )
	{
		wiebelhoek += wiebelrichting * wiebelen * delta;
		if ( wiebelhoek > 15.0 )
			wiebelrichting=-1.0;
		else if ( wiebelhoek < -15.0 )
			wiebelrichting=1.0;
	}
	glutTimerFunc(tijd, anim, 1);
	glutPostRedisplay();
}
void animidle(void){
    if ( draaien ){
		hoek += draaisnelheid;
		if ( hoek > 360.0 )
			hoek -= 360.0;
		else if ( hoek < -360.0 )
			hoek += 360.0;
	}
	glutPostRedisplay();
}
void tekenAssenEnLampen(){
    if(assen){
        glBegin(GL_LINES);//  xyz assen
                glColor3f(1.0,0.0,0.0);
            glVertex3f(50,0.0,0.0);
            glVertex3f(.0,0.0,0.0);
                glColor3f(0.0,1.0,0.0);
            glVertex3f(0.0,0.0,0.0);
            glVertex3f(0.0,50,0.0);
                glColor3f(0.0,0.0,1.0);
            glVertex3f(0.0,0.0,0.0);
            glVertex3f(0.0,0.0,50);
        glEnd();
    }

    glColor3f(1.0,0.0,0.0);
    glPointSize(8.0);
    if (tekenLampPunten){
        glBegin(GL_POINTS);
            glVertex3fv(LICHTPOS1);
            glVertex3fv(LICHTPOS2);
            glVertex3fv(LICHTPOS3);
            glVertex3fv(LICHTPOS4);
        glEnd();
    }
    glColor3f(0.0,0.0,0.0);

}
void toets(unsigned char key, int x, int y)
{
    switch (key)
    {   case 'X' : xoog--; break;
		case 'x' : xoog++; break;
        case 'Y' : yoog--; break;
		case 'y' : yoog++; break;
		case 'Z' : zoog--; break;
		case 'z' : zoog++; break;

        case '0' : xoog = 2.0, yoog = 3.0, zoog = 4.0;  break;
        case '1' : xoog = 2.0, yoog = 1.0, zoog = 9.0;  break;
        case '2' : xoog = 2.0, yoog = 1.0, zoog = 7.0;  break;
        case '3' : xoog =-1.0, yoog = 2.0, zoog = 4.0;  break;
        case '4' : xoog = 3.0, yoog = 2.0, zoog = 6.0;  break;
        case '5' : xoog = 5.0, yoog = 6.0, zoog = 0.0;  break;
        case '6' : xoog = 6.0, yoog = 4.0, zoog = 5.0;  break;
        case '7' : xoog = 0.0, yoog = 3.0, zoog = 4.0;  break;
        case '8' : xoog = 3.0, yoog = 5.0, zoog = 12.0; break;
        case '9' : xoog = 6.0, yoog = 2.0, zoog = 3.0;  break;
        case 'r' : xoog = 5.0, yoog = 5.0, zoog = 5.0; shini=10; lichthoek=45.0; expo=20.0; LICHTPOS4[1]=0.0; reuzenraderen=1;              break;

        //lichten
        case 'a' : glEnable(GL_LIGHT1);     printf("wit licht ambi \n");            break;
        case 'A' : glDisable(GL_LIGHT1);    printf("wit licht uit\n");              break;
        case 'b' : glEnable(GL_LIGHT2);     printf("groen/blauw licht diff \n");    break;
        case 'B' : glDisable(GL_LIGHT2);    printf("groen/blauw licht uit\n");      break;
        case 'c' : glEnable(GL_LIGHT3);     printf("rood licht spec\n");            break;
        case 'C' : glDisable(GL_LIGHT3);    printf("rood licht uit\n");             break;
        case 'd' : glEnable(GL_LIGHT4);     printf("geel licht \n");                break;
        case 'D' : glDisable(GL_LIGHT4);    printf("geel licht uit\n probeer een exponent van 10 \n");  break;
        case 'h' : LICHTPOS4[1]+=0.25;      printf("zet eerst 'v' en 'w' juist!");	printf("lichtpositie: %f\n",LICHTPOS4[1]);  break;
        case 'H' : LICHTPOS4[1]-=0.25;      printf("zet eerst 'v' en 'w' juist!");	printf("lichtpositie: %f\n",LICHTPOS4[1]);  break;
        case 'v' : lichthoek -=5.0;     printf("lichthoek: %f\n",lichthoek);    printf("probeer eens rond 60\n");
                    if ( lichthoek  > 90.0 && lichthoek  < 180.0) lichthoek  = 90.0; break;
        case 'V' : lichthoek +=5.0;     printf("lichthoek: %f\n",lichthoek);    printf("probeer eens rond 60\n");
                    if ( lichthoek  > 90.0) lichthoek  = 180.0;                       break;
        case 'w' : expo+=5;     printf("exponent= %f\n",expo);printf("probeer eens rond 5\n");break;
        case 'W' : expo-=5;     printf("exponent= %f\n",expo);printf("probeer eens rond 5\n");break;
        case 'L' : tekenLampPunten=!tekenLampPunten;  printf("plaats van de Lampen: %d\n",tekenLampPunten);break;


        case 'e' : shini+=5.0;      printf("shininess: %f\n",shini);  break;
        case 'E' : shini-=5.0;      printf("shininess: %f\n",shini);  break;

        case 'f' : doorzichtig=!doorzichtig;    printf("doorzichtig %d \n",doorzichtig);    break;
        case 'j' : assen=!assen;                printf("assen %d \n",assen);                break;
        case 'n' : reuzenraderen++;             printf("aantal ruezenraderen %d \n",reuzenraderen);    break;
        case 'g' : draaien=!draaien;                    break;
        case 'G' : wiebelen=!wiebelen;                  break;
        case 's' : flatS=1;                     printf("flat\n");   break;
        case 'S' : flatS=0;                     printf("smooth\n"); break;


        case 'i' : cilinderKuip=!cilinderKuip;      printf("cilinder als kuip: %d\n",cilinderKuip);break;
        case 'l' : tooncomplex=!tooncomplex;        printf("tooncomplex %d\n",tooncomplex);break;
        case 'k' : toonCtrlPunten=!toonCtrlPunten;  printf("CtrlPunten %d\n",toonCtrlPunten);break;
        case 'K' : uitbreiding=!uitbreiding;        printf("daklijnen+gl_line bij kuip ipv for{} \n");break;
        case 'm' : mist=!mist;                      printf("mist %d\n",mist);break;
        case 'M' : mist++;                          printf("mist %d\n",mist);break;
        case 't' : textuur=!textuur;                printf("jpeglib.h werkte tegen, - _ -  \n");    break;
        case 'T' : kleurenPalet=kleurenPalet;       printf("kleurenplaet: %d \n",kleurenPalet); break;
        case 'q' : exit(0);             break;

    }
    printf("Oog x:%5.1f y:%5.1f z:%5.1f \n",xoog,yoog,zoog);
    glutPostRedisplay();
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(xoog,yoog,zoog, 3.0,2.0,3.0, 0.0,1.0,0.0);//waar staat het oog, waar kijkt het oog naar, wat is 'boven' ?
    tekenAssenEnLampen();

    glEnable(GL_LIGHTING);
    lichten();

    glMaterialf(GL_FRONT,GL_SHININESS,shini);
   	glShadeModel( flatS ? GL_FLAT : GL_SMOOTH );

   	if ( mist )	{
		glEnable(GL_FOG);
		if ( mist >= 3 )
			glFogi(GL_FOG_MODE, GL_EXP2);
		else if ( mist == 2 )
			glFogi(GL_FOG_MODE, GL_EXP);
		else
			glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogfv(GL_FOG_COLOR, smogkleur);
		glFogf(GL_FOG_DENSITY, 0.25);
		glFogf(GL_FOG_START, 0.0);      //afstand van oog
		glFogf(GL_FOG_END, 30.0);       //afstand van oog
	}
    for (int i=0;i>(-reuzenraderen);i--){
        steunbalken(4*i+0.0);   // elke ruezenrad liefst 4 uit ееn
        as(4*i+0.0);    // reuzenrad is3 breed, mooier met 5 tussen
        spaken(4*i+0.0);
        torussen(4*i+0.0);
        dwarsEnCabine(4*i+0.0);
    }

    glPushMatrix();//clipping plane
        glTranslatef(0.0,-1.0,0.0);
        glClipPlane(GL_CLIP_PLANE0,clipvlak);
        glEnable(GL_CLIP_PLANE0);
    glPopMatrix();

    if (textuur){
        glPushMatrix();//vloer
            glEnable(GL_TEXTURE_2D);
            glBindTexture (GL_TEXTURE_2D,texName[2]);//2=vloer.jpg
            glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);

            glBegin(GL_QUADS);
                glTexCoord2f(0.0,0.0);	glVertex3d(-20.0, -0.99, 20.0);
                glTexCoord2f(0.0,2.0);	glVertex3d( 20.0, -0.99, 20.0);
                glTexCoord2f(2.0,2.0);	glVertex3d( 20.0, -0.99,-50.0);
                glTexCoord2f(2.0,0.0);	glVertex3d(-20.0, -0.99,-50.0);
            glEnd();

            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
    if ( mist )
		glDisable(GL_FOG);

    glutSwapBuffers();
    glDisable(GL_LIGHTING);
    glFlush();
}
int main(int argc, char *argv[]){
    if(argc==2){
        projectie=argv[1][0];
    }
    if(argc==3){
        projectie=argv[1][0];
        cabines=atoi(argv[2]); // char to int
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE |GLUT_DEPTH| GLUT_RGBA);
    glutInitWindowSize(winWidth,winHeight);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Draaimolen Ruben Kindt");
    init();
    glutReshapeFunc(raam);
    glutDisplayFunc(display);
    glutKeyboardFunc(toets);
    glutIdleFunc(animidle);
    glutTimerFunc(tijd, anim, 1);
    glutMainLoop();
    return EXIT_SUCCESS;
}
