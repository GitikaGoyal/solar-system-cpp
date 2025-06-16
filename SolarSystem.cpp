#include <GL/glut.h>
#include<iostream>
using namespace std;

const float M_PI = 3.1415926f;
const int NUM_SHOOTING_STARS = 100;
const int NUM_COMETS = 2000;
const int NUM_STARS = 100;
const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 600;
const int NUM_FLARES = 16;

float planetSpeeds[] = { 1.46f, 0.78f, 1.00f, 0.61f, 0.43f, 0.30f, 0.21f, 0.18f };
float angles[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
float distances[] = { 7.0f, 9.0f, 11.0f, 13.5f, 19.5f, 26.5f, 32.0f, 36.5f };
float rad[] = { 0.3f, 0.35f, 0.65f, 0.6f, 2.9f, 1.8f, 1.5f ,1.35f };

float viewAngleX = 0.0f;
float viewAngleY = 0.0f;
float viewDistance = 70.0f;

float moonAngle = 0.0f;
float moonDistance = 1.0f;

bool showAmbientLight = false;
bool showOrbitLines = false;

void drawSphere(GLfloat radius, GLfloat slices, GLfloat stacks, GLfloat* color) {
    glColor3fv(color);
    glutSolidSphere(radius, slices, stacks);
}

void drawOrbitLines() {
    if (showOrbitLines) {
        glDisable(GL_LIGHTING);
        glColor3f(0.8f, 0.8f, 1.0f);
        for (int i = 0; i < 8; ++i) {
            glBegin(GL_LINE_LOOP);
            for (int j = 0; j < 360; j += 5) {
                float x = cos(j * M_PI / 180) * distances[i];
                float y = sin(j * M_PI / 180) * distances[i];
                glVertex3f(x, y, 0.0f);
            }
            glEnd();
        }
        glEnable(GL_LIGHTING);
    }
}

void sunlight() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat lightColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
}

void drawShootingStar(float x, float y, float z) {
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(x, y, z);
    glVertex3f(x - 1.0f, y - 1.0f, z - 1.0f);
    glEnd();
}

void drawComet(float x, float y, float z, float size, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLES);
    glVertex3f(x, y, z);
    glVertex3f(x + size, y + size, z);
    glVertex3f(x - size, y - size, z);
    glEnd();
}

void drawMoon() {
    glPushMatrix();
    glRotatef(angles[2], 0.0f, 0.0f, 1.0f);
    glTranslatef(distances[2], 0.0f, 0.0f);
    glRotatef(moonAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(moonDistance, 0.0f, 0.0f);

    GLfloat moonAmbient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat moonDiffuse[] = { 0.9, 0.9, 0.9, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, moonAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, moonDiffuse);

    GLfloat moonColor[] = { 0.9f, 0.9f, 0.9f };
    drawSphere(0.2f, 30, 30, moonColor);
    glPopMatrix();
}

void drawSaturnRings() {
    glPushMatrix();
    glRotatef(angles[5], 0.0f, 0.0f, 1.0f);
    glTranslatef(distances[5], 0.0f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor4f(0.8f, 0.6f, 0.5f, 0.5f);
    glutSolidTorus(0.3f, 3.0f, 50, 50);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -viewDistance);
    glRotatef(viewAngleY, 1.0f, 0.0f, 0.0f);
    glRotatef(viewAngleX, 0.0f, 1.0f, 0.0f);

    glPushMatrix();
    GLfloat sunColor[] = { 25.2f, 25.9f, 0.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sunColor);
    glutSolidSphere(5.0f, 50, 50);
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < NUM_STARS; ++i) {
        float x = rand() % SCREEN_WIDTH - SCREEN_WIDTH / 2.0f;
        float y = rand() % SCREEN_HEIGHT - SCREEN_HEIGHT / 2.0f;
        float z = -(rand() % 100) - 1.0f;
        glVertex3f(x, y, z);
    }
    glEnd();
    glEnable(GL_LIGHTING);

    for (int i = 0; i < NUM_SHOOTING_STARS; ++i) {
        float x = rand() % SCREEN_WIDTH - SCREEN_WIDTH / 2.0f;
        float y = rand() % SCREEN_HEIGHT - SCREEN_HEIGHT / 2.0f;
        float z = -(rand() % 100) - 1.0f;
        drawShootingStar(x, y, z);
    }

    sunlight();
    drawOrbitLines();

    GLfloat planetColors[][3] = {
        {0.8f, 0.8f, 0.8f}, {0.9f, 0.8f, 0.5f}, {0.0f, 0.5f, 1.0f}, {1.0f, 0.5f, 0.0f},
        {0.7f, 0.6f, 0.5f}, {0.5f, 0.1f, 0.8f}, {0.5f, 0.7f, 1.0f}, {0.0f, 0.0f, 1.0f}
    };

    for (int i = 0; i < 8; ++i) {
        glPushMatrix();
        glRotatef(angles[i], 0.0f, 0.0f, 1.0f);
        glTranslatef(distances[i], 0.0f, 0.0f);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, planetColors[i]);
        drawSphere(rad[i], 50, 50, planetColors[i]);
        glPopMatrix();
        angles[i] += 0.05f * planetSpeeds[i];
        if (angles[i] > 360.0f) angles[i] -= 360.0f;
    }

    drawMoon();
    drawSaturnRings();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 100.0);
}

void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT: viewAngleX -= 5.0f; break;
    case GLUT_KEY_RIGHT: viewAngleX += 5.0f; break;
    case GLUT_KEY_UP: viewAngleY -= 5.0f; break;
    case GLUT_KEY_DOWN: viewAngleY += 5.0f; break;
    case GLUT_KEY_HOME: viewAngleX = 0.0f; viewAngleY = 0.0f; drawOrbitLines(); break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'i': viewDistance -= 1.0f; break;
    case 'o': viewDistance += 1.0f; break;
    case 'n':
        showAmbientLight = !showAmbientLight;
        if (!showAmbientLight) {
            GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
        }
        else {
            GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
        }
        break;
    case 'm':
        showOrbitLines = !showOrbitLines;
        break;
    }
    glutPostRedisplay();
}

void idle() {
    for (int i = 0; i < 8; ++i) {
        angles[i] += 0.05f * planetSpeeds[i];
        if (angles[i] > 360.0f) angles[i] -= 360.0f;
    }
    moonAngle += 0.05f;
    if (moonAngle > 360.0f) moonAngle -= 360.0f;
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        viewAngleX = 0.0f;
        viewAngleY = 90.0f;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1400, 600);
    glutInitWindowPosition(50, 100);
    glutCreateWindow("Solar System");
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}