#include <stdio.h>     // - Just for some ASCII messages
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <GL/glut.h>   // - An interface and windows management library
#include "visuals.h"   // Header file for our OpenGL functions


using namespace std;

//Moving platform's variables
static float tx = 0.0, ty = 0.0, tz = 0.0;
static int prev_x, prev_y, prev_z;


static bool lost = false; //Ball got outside of the front plane
static int hits=0; //Brick hits by ball

static float camerapos=1;

static bool brick[48];  //True = brick hasn't been hit, False = brick has been hit

//Ball's variables
static float MoveX = 10.0f, MoveY = 20.0f, MoveZ = 40.0f;
static float vx = -31, vy = -31, vz = -40;
static double radius = 4;




void axes()  //For debugging purposes
{
  glColor3f(0.6, 0.6, 0.6);
  glPushMatrix();
    glTranslatef(0, 0, -1.0);
    glBegin(GL_LINES);
      glVertex2f(0.0,0.0);
      glVertex2f(100.0,0.0);
      glVertex2f(0.0,0.0);
      glVertex2f(0.0,100.0);
    glEnd();
  glPopMatrix();
}


void text(const char *str, float size)  //For displaying messages
{
    glPushMatrix();
        glTranslatef(-20, 51, -25);
        glScalef(size, size, size);
        glColor3f(0, 0, 0);
        for (unsigned int i = 0; i < strlen(str); i++)
        {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
        }
    glPopMatrix();

}


void Render()
{
    //CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clean up the color of the window and the depth buffer
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    
    if (camerapos==2)
    {
        gluLookAt(-80.0, 20.0, 134.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //The camera from afar
    }
    else if (camerapos==3)
    {
        gluLookAt(15.0, 120.0, 45.0, 15.0, 0.0, 0.0, 0.0, 0.0, -1.0);  //The camera from above (for debugging purposes)
    }
    else
    {
        gluLookAt(17.0, 20.0, 133.0, 17.0, 0.0, 0.0, 0.0, 1.0, 0.0); //The camera from behind (default)
    }
    
    
    
    if (lost==true)  //Ball got outside of the front panel of the game's enclosed space
    {
        text("You Lost!", 0.11f);
    }
    
    
    
    if (hits==48)  //The ball hit all 48 bricks
    {
        vx=0;
        vy=0;
        vz=0;
        text("You Won!!!", 0.11f);
    }
    
    
    
    //cout << "hits: " << hits << endl;
    //axes();
    
    
    
    glPushMatrix();   //The ball
        glTranslatef(MoveX, MoveY, MoveZ);
        glColor3f(0.0, 0.0, 0.1);
        glutSolidSphere(radius, 30, 20);
    glPopMatrix();
    
    
    
    //First layer of bricks (z=0)
    if (brick[0]==true)
    {
        glPushMatrix();  //Brick #1
            glTranslatef(0, 0, 0);
            glColor3f(0.5, 0.1, 0.2); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[1]==true)
    {
        glPushMatrix();  //Brick #2
            glTranslatef(15, 0, 0);
            glColor3f(0.6, 0.1, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[2]==true)
    {
        glPushMatrix();  //Brick #3
            glTranslatef(30, 0, 0);
            glColor3f(0.1, 0.5, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[3]==true)
    {
        glPushMatrix();  //Brick #4
            glTranslatef(45, 0, 0);
            glColor3f(0.4, 0.3, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[4]==true)
    {
        glPushMatrix();  //Brick #5
            glTranslatef(0, -15, 0);
            glColor3f(0.5, 0.1, 0.2); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[5]==true)
    {
        glPushMatrix();  //Brick #6
            glTranslatef(15, -15, 0);
            glColor3f(0.1, 0.1, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[6]==true)
    {
        glPushMatrix();  //Brick #7
            glTranslatef(30, -15, 0);
            glColor3f(0.1, 0.5, 0.1); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[7]==true)
    {
        glPushMatrix();  //Brick #8
            glTranslatef(45, -15, 0);
            glColor3f(0.5, 0.5, 0.1); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[8]==true)
    {
        glPushMatrix();  //Brick #9
            glTranslatef(0, 15, 0);
            glColor3f(0.6, 0.1, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[9]==true)
    {
        glPushMatrix();  //Brick #10
            glTranslatef(15, 15, 0);
            glColor3f(0.1, 0.5, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[10]==true)
    {
        glPushMatrix();  //Brick #11
            glTranslatef(30, 15, 0);
            glColor3f(0.4, 0.3, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[11]==true)
    {
        glPushMatrix();  //Brick #12
            glTranslatef(45, 15, 0);
            glColor3f(0.6, 0.5, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[12]==true)
    {
        glPushMatrix();  //Brick #13
            glTranslatef(0, -30, 0);
            glColor3f(0.5, 0.1, 0.2); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[13]==true)
    {
        glPushMatrix();  //Brick #14
            glTranslatef(15, -30, 0);
            glColor3f(0.1, 0.1, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[14]==true)
    {
        glPushMatrix();  //Brick #15
            glTranslatef(30, -30, 0);
            glColor3f(0.1, 0.5, 0.1); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[15]==true)
    {
        glPushMatrix();  //Brick #16
            glTranslatef(45, -30, 0);
            glColor3f(0.5, 0.5, 0.1); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    
    //Second layer of bricks (z=-15)
    if (brick[16]==true)
    {
        glPushMatrix();  //Brick #17
            glTranslatef(0, 0, -15);
            glColor3f(0.5, 0.1, 0.2); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[17]==true)
    {
        glPushMatrix();  //Brick #18
            glTranslatef(15, 0, -15);
            glColor3f(0.1, 0.1, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[18]==true)
    {
        glPushMatrix();  //Brick #19
            glTranslatef(30, 0, -15);
            glColor3f(0.1, 0.5, 0.1); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[19]==true)
    {
        glPushMatrix();  //Brick #20
            glTranslatef(45, 0, -15);
            glColor3f(0.5, 0.5, 0.1); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[20]==true)
    {
        glPushMatrix();  //Brick #21
            glTranslatef(0, -15, -15);
            glColor3f(0.6, 0.1, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[21]==true)
    {
        glPushMatrix();  //Brick #22
            glTranslatef(15, -15, -15);
            glColor3f(0.1, 0.5, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[22]==true)
    {
        glPushMatrix();  //Brick #23
            glTranslatef(30, -15, -15);
            glColor3f(0.4, 0.3, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[23]==true)
    {
        glPushMatrix();  //Brick #24
            glTranslatef(45, -15, -15);
            glColor3f(0.6, 0.5, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[24]==true)
    {
        glPushMatrix();  //Brick #25
            glTranslatef(0, 15, -15);
            glColor3f(0.5, 0.1, 0.2); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[25]==true)
    {
        glPushMatrix();  //Brick #26
            glTranslatef(15, 15, -15);
            glColor3f(0.1, 0.1, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[26]==true)
    {
        glPushMatrix();  //Brick #27
            glTranslatef(30, 15, -15);
            glColor3f(0.1, 0.5, 0.1); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[27]==true)
    {
        glPushMatrix();  //Brick #28
            glTranslatef(45, 15, -15);
            glColor3f(0.5, 0.5, 0.1); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[28]==true)
    {
        glPushMatrix();  //Brick #29
            glTranslatef(0, -30, -15);
            glColor3f(0.6, 0.1, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[29]==true)
    {
        glPushMatrix();  //Brick #30
            glTranslatef(15, -30, -15);
            glColor3f(0.1, 0.5, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[30]==true)
    {
        glPushMatrix();  //Brick #31
            glTranslatef(30, -30, -15);
            glColor3f(0.4, 0.3, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[31]==true)
    {
        glPushMatrix();  //Brick #32
            glTranslatef(45, -30, -15);
            glColor3f(0.6, 0.5, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    //Third layer of bricks (z=-30)
    if (brick[24]==true)
    {
        glPushMatrix();  //Brick #25
            glTranslatef(0, 0, -30);
            glColor3f(0.6, 0.1, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[25]==true)
    {
        glPushMatrix();  //Brick #26
            glTranslatef(15, 0, -30);
            glColor3f(0.1, 0.5, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[26]==true)
    {
        glPushMatrix();  //Brick #27
            glTranslatef(30, 0, -30);
            glColor3f(0.4, 0.3, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[27]==true)
    {
        glPushMatrix();  //Brick #28
            glTranslatef(45, 0, -30);
            glColor3f(0.6, 0.5, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[28]==true)
    {
        glPushMatrix();  //Brick #29
            glTranslatef(0, -15, -30);
            glColor3f(0.5, 0.1, 0.2); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[29]==true)
    {
        glPushMatrix();  //Brick #30
            glTranslatef(15, -15, -30);
            glColor3f(0.1, 0.1, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[30]==true)
    {
        glPushMatrix();  //Brick #31
            glTranslatef(30, -15, -30);
            glColor3f(0.1, 0.5, 0.1); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[31]==true)
    {
        glPushMatrix();  //Brick #32
            glTranslatef(45, -15, -30);
            glColor3f(0.5, 0.5, 0.1); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[32]==true)
    {
        glPushMatrix();  //Brick #33
            glTranslatef(0, 15, -30);
            glColor3f(0.6, 0.1, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[33]==true)
    {
        glPushMatrix();  //Brick #34
            glTranslatef(15, 15, -30);
            glColor3f(0.1, 0.5, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[34]==true)
    {
        glPushMatrix();  //Brick #35
            glTranslatef(30, 15, -30);
            glColor3f(0.4, 0.3, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[35]==true)
    {
        glPushMatrix();  //Brick #36
            glTranslatef(45, 15, -30);
            glColor3f(0.6, 0.5, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[44]==true)
    {
        glPushMatrix();  //Brick #45
            glTranslatef(0, -30, -30);
            glColor3f(0.5, 0.1, 0.2); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[45]==true)
    {
        glPushMatrix();  //Brick #46
            glTranslatef(15, -30, -30);
            glColor3f(0.6, 0.1, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[46]==true)
    {
        glPushMatrix();  //Brick #47
            glTranslatef(30, -30, -30);
            glColor3f(0.1, 0.5, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    if (brick[47]==true)
    {
        glPushMatrix();  //Brick #48
            glTranslatef(45, -30, -30);
            glColor3f(0.4, 0.3, 0.6); // Set drawing color
            BuildBrick();
        glPopMatrix();
    }
    
    
    
    glPushMatrix();  //The moving platform
        glTranslatef(10, 0, 54.5);
        glTranslatef(tx, ty, 0);
        
        glColor4f(0.5, 0.5, 0.5, 0.8); // Set drawing color and transparency (so that you can see the ball and the bricks from behind the platform)
        glBegin(GL_TRIANGLES);
        //Front
            glVertex3f(-20, 0, 0);
            glVertex3f(-20, 20, 0);
            glVertex3f(0, 20, 0);
            glVertex3f(0, 20, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(-20, 0, 0);
        //Left
            glVertex3f(-20, 0, -3);
            glVertex3f(-20, 20, -3);
            glVertex3f(-20, 20, 0);
            glVertex3f(-20, 20, 0);
            glVertex3f(-20, 0, 0);
            glVertex3f(-20, 0, -3);
        //Right
            glVertex3f(0, 20, 0);
            glVertex3f(0, 20, -3);
            glVertex3f(0, 0, -3);
            glVertex3f(0, 0, -3);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 20, 0);
        //Back
            glVertex3f(-20, 0, -3);
            glVertex3f(-20, 20, -3);
            glVertex3f(0, 20, -3);
            glVertex3f(0, 20, -3);
            glVertex3f(0, 0, -3);
            glVertex3f(-20, 0, -3);
        //Top
            glVertex3f(-20, 20, 0);
            glVertex3f(-20, 20, -3);
            glVertex3f(0, 20, -3);
            glVertex3f(0, 20, -3);
            glVertex3f(0, 20, 0);
            glVertex3f(-20, 20, 0);
        //Bottom
            glVertex3f(-20, 0, 0);
            glVertex3f(-20, 0, -3);
            glVertex3f(0, 0, -3);
            glVertex3f(0, 0, -3);
            glVertex3f(0, 0, 0);
            glVertex3f(-20, 0, 0);
        glEnd();
    glPopMatrix();
    
    
    
    //The game's enclosed space
    glPushMatrix();
        glColor4f(0.6, 0.1, 0.4, 0.5);
        glBegin(GL_TRIANGLES);
            //Front panel
            glVertex3f(-25, -35, 55);
            glVertex3f(-25, 35, 55);
            glVertex3f(60, 35, 55);
            glVertex3f(60, 35, 55);
            glVertex3f(60, -35, 55);
            glVertex3f(-25, -35, 55);
            //Right panel
            glVertex3f(60, -35, 55);
            glVertex3f(60, 35, 55);
            glVertex3f(60, 35, -35);
            glVertex3f(60, 35, -35);
            glVertex3f(60, -35, -35);
            glVertex3f(60, -35, 55);
            //Left panel
            glVertex3f(-25, 35, 55);
            glVertex3f(-25, -35, 55);
            glVertex3f(-25, -35, -35);
            glVertex3f(-25, -35, -35);
            glVertex3f(-25, 35, -35);
            glVertex3f(-25, 35, 55);
            //Back panel
            glVertex3f(-25, -35, -35);
            glVertex3f(-25, 35, -35);
            glVertex3f(60, 35, -35);
            glVertex3f(60, 35, -35);
            glVertex3f(60, -35, -35);
            glVertex3f(-25, -35, -35);
            //Bottom panel
            glVertex3f(-25, -35, 55);
            glVertex3f(-25, -35, -35);
            glVertex3f(60, -35, -35);
            glVertex3f(60, -35, -35);
            glVertex3f(60, -35, 55);
            glVertex3f(-25, -35, 55);
            //Top panel
            glVertex3f(-25, 35, 55);
            glVertex3f(-25, 35, -35);
            glVertex3f(60, 35, -35);
            glVertex3f(60, 35, -35);
            glVertex3f(60, 35, 55);
            glVertex3f(-25, 35, 55);
        glEnd();
    glPopMatrix();

    glutSwapBuffers(); // All drawing commands applied to the
                       // hidden buffer, so now, bring forward
                       // the hidden buffer and hide the visible one
}


void BuildBrick()  //Builds each brick
{
    glBegin(GL_TRIANGLES);
        //Front
            glVertex3f(-10, 0, 0);
            glVertex3f(-10, 10, 0);
            glVertex3f(0, 10, 0);
            glVertex3f(0, 10, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(-10, 0, 0);
        //Left
            glVertex3f(-10, 10, -3);
            glVertex3f(-10, 10, 0);
            glVertex3f(-10, 0, 0);
            glVertex3f(-10, 0, 0);
            glVertex3f(-10, 0, -3);
            glVertex3f(-10, 10, -3);
        //Right
            glVertex3f(0, 10, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, -3);
            glVertex3f(0, 10, 0);
            glVertex3f(0, 10, -3);
            glVertex3f(0, 0, -3);
        //Back
            glVertex3f(-10, 0, -3);
            glVertex3f(-10, 10, -3);
            glVertex3f(0, 10, -3);
            glVertex3f(0, 10, -3);
            glVertex3f(0, 0, -3);
            glVertex3f(-10, 0, -3);
        //Top
            glVertex3f(-10, 10, 0);
            glVertex3f(-10, 10, -3);
            glVertex3f(0, 10, -3);
            glVertex3f(0, 10, -3);
            glVertex3f(0, 10, 0);
            glVertex3f(-10, 10, 0);
        //Bottom
            glVertex3f(-10, 0, 0);
            glVertex3f(-10, 0, -3);
            glVertex3f(0, 0, -3);
            glVertex3f(0, 0, -3);
            glVertex3f(0, 0, 0);
            glVertex3f(-10, 0, 0);
        glEnd();
}



void Resize(int w, int h)
{
    //Define the visible area of the window (in pixels)
    if (h == 0)
    {
        h = 1;
    }
    
    glViewport(0, 0, w, h);

    
    // Setup viewing volume
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, (float) w / (float) h, 1.0, 1000.0);
    
}


void Idle()
{
    
    float g = 10;
    float dt = 0.01;
    
    //Collision with the walls
    if (MoveX+radius>=60 || MoveX-radius<=-25)  //Left and right plane
    {
        vx=-vx;
        
    }
    else if (MoveY+radius>=35 ||MoveY-radius<=-35)  //Top and bottom plane
    {
        vy=-vy;
        
    }
    else if (MoveZ-radius<=-35)  //Back plane
    {
        vz=-vz;
        
    }
    else if (MoveZ+radius>=70)  //Front plane
    {
        vx=0;
        vy=0;
        vz=0;
        lost=true;
    }
    
    
    
    //Collision with the moving platform
    if (abs(tx-MoveX)<20/2+radius && abs(ty-MoveY)<20/2+radius && abs((51.5)-MoveZ)<3/2+radius)
    {
        vz=-vz;
    }
    
    
    
    //Collision with the bricks
    if (abs(-5-MoveX)<10/2+radius && abs(5-MoveY)<10/2+radius && abs(0-MoveZ)<3/2+radius && brick[0]==true) //Collision with brick #1
    {
        brick[0]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(5-MoveX)<10/2+radius && abs(5-MoveY)<10/2+radius && abs(0-MoveZ)<3/2+radius && brick[1]==true) //Collision with brick #2
    {
        brick[1]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(20-MoveX)<10/2+radius && abs(5-MoveY)<10/2+radius && abs(0-MoveZ)<3/2+radius && brick[2]==true) //Collision with brick #3
    {
        brick[2]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(35-MoveX)<10/2+radius && abs(5-MoveY)<10/2+radius && abs(0-MoveZ)<3/2+radius && brick[3]==true) //Collision with brick #4
    {
        brick[3]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(-5-MoveX)<10/2+radius && abs(-10-MoveY)<10/2+radius && abs(0-MoveZ)<3/2+radius && brick[4]==true) //Collision with brick #5
    {
        brick[4]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(5-MoveX)<10/2+radius && abs(-10-MoveY)<10/2+radius && abs(0-MoveZ)<3/2+radius && brick[5]==true) //Collision with brick #6
    {
        brick[5]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(20-MoveX)<10/2+radius && abs(-10-MoveY)<10/2+radius && abs(0-MoveZ)<3/2+radius && brick[6]==true) //Collision with brick #7
    {
        brick[6]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(35-MoveX)<10/2+radius && abs(-10-MoveY)<10/2+radius && abs(0-MoveZ)<3/2+radius && brick[7]==true) //Collision with brick #8
    {
        brick[7]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(-5-MoveX)<10/2+radius && abs(20-MoveY)<10/2+radius && abs(0-MoveZ)<3/2+radius && brick[8]==true) //Collision with brick #9
    {
        brick[8]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(5-MoveX)<10/2+radius && abs(20-MoveY)<10/2+radius && abs(0-MoveZ)<3/2+radius && brick[9]==true) //Collision with brick #10
    {
        brick[9]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(20-MoveX)<10/2+radius && abs(20-MoveY)<10/2+radius && abs(0-MoveZ)<3/2+radius && brick[10]==true) //Collision with brick #11
    {
        brick[10]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(35-MoveX)<10/2+radius && abs(20-MoveY)<10/2+radius && abs(0-MoveZ)<3/2+radius && brick[11]==true) //Collision with brick #12
    {
        brick[11]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(-5-MoveX)<10/2+radius && abs(-25-MoveY)<10/2+radius && abs(0-MoveZ)<3/2+radius && brick[12]==true) //Collision with brick #13
    {
        brick[12]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(5-MoveX)<10/2+radius && abs(-25-MoveY)<10/2+radius && abs(0-MoveZ)<3/2+radius && brick[13]==true) //Collision with brick #14
    {
        brick[13]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(20-MoveX)<10/2+radius && abs(-25-MoveY)<10/2+radius && abs(0-MoveZ)<3/2+radius && brick[14]==true) //Collision with brick #15
    {
        brick[14]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(35-MoveX)<10/2+radius && abs(-25-MoveY)<10/2+radius && abs(0-MoveZ)<3/2+radius && brick[15]==true) //Collision with brick #16
    {
        brick[15]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(-5-MoveX)<10/2+radius && abs(5-MoveY)<10/2+radius && abs(-18-MoveZ)<3/2+radius && brick[16]==true) //Collision with brick #17
    {
        brick[16]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(5-MoveX)<10/2+radius && abs(5-MoveY)<10/2+radius && abs(-18-MoveZ)<3/2+radius && brick[17]==true) //Collision with brick #18
    {
        brick[17]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(20-MoveX)<10/2+radius && abs(5-MoveY)<10/2+radius && abs(-18-MoveZ)<3/2+radius && brick[18]==true) //Collision with brick #19
    {
        brick[18]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(35-MoveX)<10/2+radius && abs(5-MoveY)<10/2+radius && abs(-18-MoveZ)<3/2+radius && brick[19]==true) //Collision with brick #20
    {
        brick[19]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(-5-MoveX)<10/2+radius && abs(-10-MoveY)<10/2+radius && abs(-18-MoveZ)<3/2+radius && brick[20]==true) //Collision with brick #21
    {
        brick[20]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(5-MoveX)<10/2+radius && abs(-10-MoveY)<10/2+radius && abs(-18-MoveZ)<3/2+radius && brick[21]==true) //Collision with brick #22
    {
        brick[21]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(20-MoveX)<10/2+radius && abs(-10-MoveY)<10/2+radius && abs(-18-MoveZ)<3/2+radius && brick[22]==true) //Collision with brick #23
    {
        brick[22]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(35-MoveX)<10/2+radius && abs(-10-MoveY)<10/2+radius && abs(-18-MoveZ)<3/2+radius && brick[23]==true) //Collision with brick #24
    {
        brick[23]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(-5-MoveX)<10/2+radius && abs(20-MoveY)<10/2+radius && abs(-18-MoveZ)<3/2+radius && brick[24]==true) //Collision with brick #25
    {
        brick[24]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(5-MoveX)<10/2+radius && abs(20-MoveY)<10/2+radius && abs(-18-MoveZ)<3/2+radius && brick[25]==true) //Collision with brick #26
    {
        brick[25]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(20-MoveX)<10/2+radius && abs(20-MoveY)<10/2+radius && abs(-18-MoveZ)<3/2+radius && brick[26]==true) //Collision with brick #27
    {
        brick[26]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(35-MoveX)<10/2+radius && abs(20-MoveY)<10/2+radius && abs(-18-MoveZ)<3/2+radius && brick[27]==true) //Collision with brick #28
    {
        brick[27]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(-5-MoveX)<10/2+radius && abs(-25-MoveY)<10/2+radius && abs(-18-MoveZ)<3/2+radius && brick[28]==true) //Collision with brick #29
    {
        brick[28]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(5-MoveX)<10/2+radius && abs(-25-MoveY)<10/2+radius && abs(-18-MoveZ)<3/2+radius && brick[29]==true) //Collision with brick #30
    {
        brick[29]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(20-MoveX)<10/2+radius && abs(-25-MoveY)<10/2+radius && abs(-18-MoveZ)<3/2+radius && brick[30]==true) //Collision with brick #31
    {
        brick[30]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(35-MoveX)<10/2+radius && abs(-25-MoveY)<10/2+radius && abs(-18-MoveZ)<3/2+radius && brick[31]==true) //Collision with brick #32
    {
        brick[31]=false;
        hits++;
        vz=-vz;
    }
    if (abs(-5-MoveX)<10/2+radius && abs(5-MoveY)<10/2+radius && abs(-36-MoveZ)<3/2+radius && brick[32]==true) //Collision with brick #33
    {
        brick[32]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(5-MoveX)<10/2+radius && abs(5-MoveY)<10/2+radius && abs(-36-MoveZ)<3/2+radius && brick[33]==true) //Collision with brick #34
    {
        brick[33]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(20-MoveX)<10/2+radius && abs(5-MoveY)<10/2+radius && abs(-36-MoveZ)<3/2+radius && brick[34]==true) //Collision with brick #35
    {
        brick[34]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(35-MoveX)<10/2+radius && abs(5-MoveY)<10/2+radius && abs(-36-MoveZ)<3/2+radius && brick[35]==true) //Collision with brick #36
    {
        brick[35]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(-5-MoveX)<10/2+radius && abs(-10-MoveY)<10/2+radius && abs(-36-MoveZ)<3/2+radius && brick[36]==true) //Collision with brick #37
    {
        brick[36]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(5-MoveX)<10/2+radius && abs(-10-MoveY)<10/2+radius && abs(-36-MoveZ)<3/2+radius && brick[37]==true) //Collision with brick #38
    {
        brick[37]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(20-MoveX)<10/2+radius && abs(-10-MoveY)<10/2+radius && abs(-36-MoveZ)<3/2+radius && brick[38]==true) //Collision with brick #39
    {
        brick[38]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(35-MoveX)<10/2+radius && abs(-10-MoveY)<10/2+radius && abs(-36-MoveZ)<3/2+radius && brick[39]==true) //Collision with brick #40
    {
        brick[39]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(-5-MoveX)<10/2+radius && abs(20-MoveY)<10/2+radius && abs(-36-MoveZ)<3/2+radius && brick[40]==true) //Collision with brick #41
    {
        brick[40]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(5-MoveX)<10/2+radius && abs(20-MoveY)<10/2+radius && abs(-36-MoveZ)<3/2+radius && brick[41]==true) //Collision with brick #42
    {
        brick[41]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(20-MoveX)<10/2+radius && abs(20-MoveY)<10/2+radius && abs(-36-MoveZ)<3/2+radius && brick[42]==true) //Collision with brick #43
    {
        brick[42]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(35-MoveX)<10/2+radius && abs(20-MoveY)<10/2+radius && abs(-36-MoveZ)<3/2+radius && brick[43]==true) //Collision with brick #44
    {
        brick[43]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(-5-MoveX)<10/2+radius && abs(-25-MoveY)<10/2+radius && abs(-36-MoveZ)<3/2+radius && brick[44]==true) //Collision with brick #45
    {
        brick[44]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(5-MoveX)<10/2+radius && abs(-25-MoveY)<10/2+radius && abs(-36-MoveZ)<3/2+radius && brick[45]==true) //Collision with brick #46
    {
        brick[45]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(20-MoveX)<10/2+radius && abs(-25-MoveY)<10/2+radius && abs(-36-MoveZ)<3/2+radius && brick[46]==true) //Collision with brick #47
    {
        brick[46]=false;
        hits++;
        vz=-vz;
    }
    else if (abs(35-MoveX)<10/2+radius && abs(-25-MoveY)<10/2+radius && abs(-36-MoveZ)<3/2+radius && brick[47]==true) //Collision with brick #48
    {
        brick[47]=false;
        hits++;
        vz=-vz;
    }
    
    
    
    
    MoveX=MoveX + dt*vx;
    MoveY=MoveY + dt*vy;
    MoveZ=MoveZ + dt*vz;
    
    
    glutPostRedisplay();
}


void Setup()
{
    
    //Parameter handling
    glShadeModel(GL_SMOOTH);

    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); //Renders a fragment if its z value is less or equal of the stored value
    glClearDepth(1);

    //Polygon rendering mode
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    //Set up light source
    GLfloat light_position[] = {0.0, 30.0, 50.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    GLfloat ambientLight[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat diffuseLight[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat specularLight[] = {1.0, 1.0, 1.0, 1.0};


    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    

    
    /*
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    GLfloat specref[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT,GL_SPECULAR,specref);
    glMateriali(GL_FRONT,GL_SHININESS,32);
    */
    
    
    for (int i=0 ; i<48 ; i++)  //Setting up all the bricks to appear in the scene
    {
        brick[i]=true;
    }
    
    
    

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //Cutting the triangles that we can't see
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    



    //BLENDING
    glEnable(GL_BLEND);
    //  incoming      stored //
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    //Background color
    glClearColor(0.0f, 0.8f, 0.7f, 1.0f);

}


void Keyboard(unsigned char key, int x, int y)
{
    switch (key)  //For moving the platform (wasd) or quitting the game (q)
    {
        case 'q': exit(0);
            break;
        case 'a': if (prev_x<=-13){ tx -= 0; } else{ tx -= 1.9f; }
            break;
        case 'd': if(prev_x>=49){tx += 0;} else{ tx += 1.9f; }
            break;
        case 'w': if(prev_y>=14){ ty += 0; } else{ ty += 1.9f; }
            break;
        case 's': if(prev_y<=-34){ ty -= 0; } else{ ty -= 1.9f; }
            break;
        default: break;
    }
    
    
    switch (key)  //Hold 'e' for automatic platform movement (follows x and y coordinates of the ball)
    {
        case 'e': if (MoveX<=-13 || MoveX>=49){ tx -= 0; } else{ tx = MoveX; }
                  if (MoveY<=-34 || MoveY>=14){ ty -= 0; } else{ ty = MoveY; }
            break;
        default: break;
    }
    
    
    
    prev_x=tx;
    prev_y=ty;
    
    
    
    
    switch(key)  //For switching the camera view (from behind, from afar or from the top)
    {
        case '1': camerapos=1;
            break;
        case '2': camerapos=2;
            break;
        case '3': camerapos=3;
            break;
        default: break;
    }

    glutPostRedisplay();
}

/*
void Mouse(int button, int state, int x, int y)
{
    
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
    {
        prev_x = x;
        prev_y = y;
        
    }
    
    
}


void MouseMotion(int x, int y)
{
    //cout << x << " " << y << " " << endl;
    
    
    
    tx += (x - prev_x);
    ty += (prev_y - y);
    
    
    prev_x = x;
    prev_y = y;
    
    
    glutPostRedisplay();
}
*/
