#include <stdio.h>
#include <iostream>
#include <GL/glut.h>

using namespace std; 

//g++ main.cpp -o lookAtThis -lglut -lGL; ./lookAtThis

void displayMe(void)
{
    cout << "9" << endl;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.5, 0.5, 0.0);
        glVertex3f(0.0, 0.5, 0.0);
    glEnd();
    glFlush();
}

float red=1,green=1,blue=1;

void init (void)
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,200.0,0.0,200.0);
}


void process_SHIFT_ALT_CTRL(unsigned char key, int x, int y) 
{
    // Press ALT or  SHIFT or  CTRL in combination with other keys.
    printf("key_code =%d  \n",key);

    int mod = glutGetModifiers();

    if (mod != 0) //ALT=4  SHIFT=1  CTRL=2
    {      
          switch(mod)
          {
             case 1 :  printf("SHIFT key %d\n",mod);  break;
             case 2 :  printf("CTRL  key %d\n",mod);  break;
             case 4 :  printf("ALT   key %d\n",mod);  break;
             mod=0;
          }
    }
}


void process_Normal_Keys(int key, int x, int y) 
{
     switch (key) 
    {    
       case 27 :      break;
       case 100 : printf("GLUT_KEY_LEFT %d\n",key);   break;
       case 102: printf("GLUT_KEY_RIGHT %d\n",key);  ;  break;
       case 101   : printf("GLUT_KEY_UP %d\n",key);  ;  break;
       case 103 : printf("GLUT_KEY_DOWN %d\n",key);  ;  break;
    }

}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    displayMe();
    glFlush();
}

int main(int argc, char** argv)
{
    cout << "1" << endl; //del
    glutInit(&argc, argv);
    cout << "2" << endl; //del
    glutInitDisplayMode(GLUT_SINGLE);
    cout << "3" << endl; //del
    glutInitWindowSize(300, 300);
    cout << "4" << endl; //del
    glutInitWindowPosition(100, 100);
    cout << "5" << endl; //del
    glutCreateWindow("Hello world from Badprog.com :D");
    cout << "6" << endl; //del
    glutDisplayFunc(display);
    cout << "7" << endl; //del
    init();
    cout << "8" << endl; //del
    glutSpecialFunc( process_Normal_Keys );
    cout << "9" << endl; //del
    glutKeyboardFunc( process_SHIFT_ALT_CTRL );
    cout << "10" << endl; //del
    glutMainLoop();
    cout << "11" << endl; //del
    return 0;
}