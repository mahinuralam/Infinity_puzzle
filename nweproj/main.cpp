#include<bits/stdc++.h>
#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <stdlib.h>
using namespace std;

//-----------------

typedef struct {
    double x;
    double y;
} Vector2;

typedef struct {
    Vector2 min;
    Vector2 max;
} AABB;


double x_position  = -10.0, x_position2  = -10.0, x_position3  = -10.0, x_position4  = -10.0, x_position_p1  = -10.0, x_position_p2  = -10.0;
int state = 1, state2 = 1, state3 = 1, state4 = 1, flag = 0, score = 0, point1 = 1, point2 = 0;
double SpeedBox1 = 0.25, SpeedBox2 = 0.35, SpeedBox3 = 0.40, SpeedBox4 = 0.40;
char level = 48, cnt = 0;
double xp=-1.5,yp=-8.5,xp2=1.5,yp2=-7.5,p=0,q=0;

struct Point {
    double xP, yP;
};

void init()
{
    glClearColor(0.0f,0.15f,0.3f,1.0f);
}


void drawText(const char *text, int lenght, int x, int y, char level)
{
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2d(x,y);
    for(int i=0;i<lenght;i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, (int)text[i]);
    }

//    cout<<(int)level<<endl;

    if(cnt>9&&cnt<20)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '1');
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, level);
    }
    else if(cnt>=20)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '2');
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, level);
    }
    else
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, level);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}

std::string String ( double Val ) {
	std::ostringstream Stream;
	Stream << Val;
	string s1 = "Your Score : ";
	string ss = Stream.str ( );
	string s3 = s1 + ss;
	return s3;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();


    if(flag == 1)
    {
        MessageBoxA ( NULL, String ( cnt*10 ).c_str ( ), "Game Over", 0 );
        exit(0);
    }

    if((int)level >= 58){
        level = 48;
    }

    string text = "Level - ";
    glColor3f(0.0f, 0.5f, 1.0f);//baby Blue
    drawText(text.data(), text.size(), 0, 590, level);


//Box_1
    glBegin(GL_POLYGON);
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    glVertex2d(x_position,1.0);
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    glVertex2d(x_position,-0.0);
    glColor3f(0.1f, 0.0f, 0.0f);//Brown
    glVertex2d(x_position+2.0,-0.0);
    glColor3f(0.1f, 0.0f, 0.0f);//Brown
    glVertex2d(x_position+2.0,1.0);
    glEnd();
//Box_2
    glBegin(GL_POLYGON);
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    glVertex2d(x_position2+4.0,4.0);
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    glVertex2d(x_position2+4.0,3.0);
    glColor3f(0.1f, 0.0f, 0.0f);//Brown
    glVertex2d(x_position2+6.0,3.0);
    glColor3f(0.1f, 0.0f, 0.0f);//Brown
    glVertex2d(x_position2+6.0,4.0);
    glEnd();

//Box_3
    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.0f, 0.0f);//Brown
    glVertex2d(x_position3+4.0,-2.0);
    glColor3f(0.1f, 0.0f, 0.0f);//Brown
    glVertex2d(x_position3+4.0,-3.0);
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    glVertex2d(x_position3+6.0,-3.0);
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    glVertex2d(x_position3+6.0,-2.0);
    glEnd();
//Box_4
    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.0f, 0.0f);//Brown
    glVertex2d(x_position4+4.0,7.0);
    glColor3f(0.1f, 0.0f, 0.0f);//Brown
    glVertex2d(x_position4+4.0,6.0);
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    glVertex2d(x_position4+6.0,6.0);
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    glVertex2d(x_position4+6.0,7.0);
    glEnd();

//PlayerBox
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 1.0f);//baby Blue
    glVertex2d(xp+q,yp2+p);
    glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
    glVertex2d(xp+q,yp+p);
    glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
    glVertex2d(xp2+q,yp+p);
    glColor3f(0.0f, 0.5f, 1.0f);//baby Blue
    glVertex2d(xp2+q,yp2+p);
    glEnd();

//point_box_1
    glBegin(GL_POLYGON);
    if(point1==1)
    {
        glColor3f(0.0f, 1.0f, 0.0f);//Green
    }
    else
    {
        glColor3f(0.0f, 0.0f, 0.0f);//Black
    }
    glVertex2d(x_position_p1+8.0,9.5);
    glVertex2d(x_position_p1+8.0,10.0);
    glVertex2d(x_position_p1+12.0,10.0);
    glVertex2d(x_position_p1+12.0,9.5);
    glEnd();

//point_box_2
    glBegin(GL_POLYGON);
    if(point2==1)
    {
        glColor3f(0.0f, 1.0f, 0.0f);//Green
    }
    else
    {
        glColor3f(0.0f, 0.0f, 0.0f);//Black
    }
    glVertex2d(x_position_p2+8.0,-9.5);
    glVertex2d(x_position_p2+8.0,-10.0);
    glVertex2d(x_position_p2+12.0,-10.0);
    glVertex2d(x_position_p2+12.0,-9.5);
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10,10,-10,10);
    glMatrixMode(GL_MODELVIEW);
}

//AABB 2D collision
bool TestAABBOverlap(AABB* a, AABB* b)
{
    float d1x = b->min.x - a->max.x;
    float d1y = b->min.y - a->max.y;
    float d2x = a->min.x - b->max.x;
    float d2y = a->min.y - b->max.y;

    if (d1x > 0.0f || d1y > 0.0f){
        return false;
    }

    if (d2x > 0.0f || d2y > 0.0f)
        return false;

    return true;
}

//Collision check for Box
void collision_check_box (double plr_x1, double plr_y1, double plr_x2, double plr_y2,
                     double box_x1, double box_y1, double box_x2, double box_y2)
{
    Vector2 a1_p2 = { plr_x1,plr_y1 }, b1_p2 = { plr_x2,plr_y2 };
    Vector2 a2_p2 = { box_x1,box_y1 }, b2_p2 = { box_x2,box_y2 };

    AABB aa_1 = {a1_p2,b1_p2};
    AABB bb_1 = {a2_p2,b2_p2};

    if (TestAABBOverlap(&aa_1, &bb_1)) {
//        printf("Collision with box\n");
        flag = 1;
    }
}

//Collision check for point Box 1
void collision_check_point1 (double plr_x1, double plr_y1, double plr_x2, double plr_y2,
                     double box_x1, double box_y1, double box_x2, double box_y2)
{
    Vector2 a1_p2 = { plr_x1,plr_y1 }, b1_p2 = { plr_x2,plr_y2 };
    Vector2 a2_p2 = { box_x1,box_y1 }, b2_p2 = { box_x2,box_y2 };

    AABB aa_1 = {a1_p2,b1_p2};
    AABB bb_1 = {a2_p2,b2_p2};

    if (TestAABBOverlap(&aa_1, &bb_1)) {
//        printf("Collision with point 1\n");
        if(point1==1)
        {
            point2=1;
            point1=0;
            level++;
            cnt++;
            SpeedBox1+=0.05;
            SpeedBox2+=0.05;
            SpeedBox3+=0.05;
            SpeedBox4+=0.05;
        }
    }

}
//Collision check for point Box 2
void collision_check_point2 (double plr_x1, double plr_y1, double plr_x2, double plr_y2,
                     double box_x1, double box_y1, double box_x2, double box_y2)
{
    Vector2 a1_p2 = { plr_x1,plr_y1 }, b1_p2 = { plr_x2,plr_y2 };
    Vector2 a2_p2 = { box_x1,box_y1 }, b2_p2 = { box_x2,box_y2 };

    AABB aa_1 = {a1_p2,b1_p2};
    AABB bb_1 = {a2_p2,b2_p2};

    if (TestAABBOverlap(&aa_1, &bb_1)) {
//        printf("Collision with point 2\n");
        if(point2==1)
        {
            point2=0;
            point1=1;
            level++;
            cnt++;
            SpeedBox1+=0.05;
            SpeedBox2+=0.05;
            SpeedBox3+=0.05;
            SpeedBox4+=0.05;
        }
    }

}


void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/60,timer,0);

//Box 4 move
    switch(state4)
    {
    case 1:
        if(x_position4<4)
        {
            x_position4 += SpeedBox4;
        }
        else
        {
            state4 = -1;
        }
        break;
    case -1:
        if(x_position4>-14)
        {
            x_position4 -= SpeedBox4;
        }
        else
        {
            state4 = 1;
        }
        break;
    }


//Box 3 move
    switch(state3)
    {
    case 1:
        if(x_position3<4)
        {
            x_position3 += SpeedBox3;
        }
        else
        {
            state3 = -1;
        }
        break;
    case -1:
        if(x_position3>-14)
        {
            x_position3 -= SpeedBox3;
        }
        else
        {
            state3 = 1;
        }
        break;
    }

//Box 1 move
    switch(state)
    {
    case 1:
        if(x_position<8)
        {
            x_position += SpeedBox1;
        }
        else
        {
            state = -1;
        }
        break;
    case -1:
        if(x_position>-10)
        {
            x_position -= SpeedBox1;
        }
        else
        {
            state = 1;
        }
        break;
    }

//Box 2 move
    switch(state2)
    {
    case 1:
        if(x_position2<4)
        {
            x_position2 += SpeedBox2;
        }
        else
        {
            state2 = -1;
        }
        break;
    case -1:
        if(x_position2>-14)
        {
            x_position2 -= SpeedBox2;
        }
        else
        {
            state2 = 1;
        }
        break;
    }

//point Box 2 collitoin
    collision_check_point1(xp+q, yp+p, xp2+q, yp2+p,x_position_p2+7.5, 10.0, x_position_p2+11.5, 9.5);
//point Box 1 collitoin
    collision_check_point2(xp+q, yp+p, xp2+q, yp2+p, x_position_p1+8.0, -10.0, x_position_p1+12.0, -9.5);
//for block 1 collitoin
    collision_check_box(xp+q, yp+p, xp2+q, yp2+p,x_position, -0.0, x_position+2.0, 1.0);
//for block 2 collitoin
    collision_check_box(xp+q, yp+p, xp2+q, yp2+p, x_position2+4.0, 3.0, x_position2+6.0, 4.0);
//for block 3 collitoin
    collision_check_box(xp+q, yp+p, xp2+q, yp2+p, x_position3+4.0, -3.0, x_position3+6.0, -2.0);
//for block 4  collitoin
    collision_check_box(xp+q, yp+p, xp2+q, yp2+p, x_position4+4.0, 6.0, x_position4+6.0, 7.0);

}


void Specialkey(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        p += 1;
        break;
    case GLUT_KEY_DOWN:
        p -= 1;
        break;
    case GLUT_KEY_LEFT:
        q -= 1;
        break;
    case GLUT_KEY_RIGHT:
        q += 1;
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char*argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowSize(500,900);
    glutInitWindowPosition(200,100);

    glutCreateWindow("Opengl_Game");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(Specialkey);

    glutTimerFunc(0,timer,0);
    init();

    glutMainLoop();
}
