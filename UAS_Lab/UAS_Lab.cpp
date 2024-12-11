#include <glut.h>
#include <iostream>
#include <cmath>

// Quadric object for the cylinder
GLUquadric* quadric;

// Cylinder properties
float cylinderBaseRadius = 0.5f;
float cylinderTopRadius = 0.5f;
float cylinderHeight = 3.0f;
int cylinderSlices = 32;
int cylinderStacks = 32;

// Camera properties
float cameraX = 5.0f, cameraY = 0.0f, cameraZ = 5.0f; // Initial camera position
float lookAtX = 0.0f, lookAtY = 0.0f, lookAtZ = 0.0f; // Point the camera is looking at
float upX = 0.0f, upY = 1.0f, upZ = 0.0f;             // Camera's up vector
float cameraSpeed = 0.1f;                             // Speed of camera movement

// Function to draw the "legs" or "supports"
void kaki(float x1, float x2, float z1, float z2) {
    // Define local variables for vertical positions
    float ya1 = -0.4f; // Bottom front
    float ya2 = 0.1f;  // Top front
    float yb1 = 0.0f;  // Bottom back
    float yb2 = 0.5f;  // Top back

    glBegin(GL_QUADS);

    // Front side
    glColor3f(0.9, 0.9, 0.9);
    glVertex3f(x1, ya1, z1);
    glVertex3f(x2, ya1, z1);
    glVertex3f(x2, ya2, z1);
    glVertex3f(x1, ya2, z1);

    // Back side
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(x1, yb1, z2);
    glVertex3f(x2, yb1, z2);
    glVertex3f(x2, yb2, z2);
    glVertex3f(x1, yb2, z2);

    // Left side
    glColor3f(1.0, 0.8, 1.0);
    glVertex3f(x1, ya1, z1);
    glVertex3f(x1, yb1, z2);
    glVertex3f(x1, yb2, z2);
    glVertex3f(x1, ya2, z1);

    // Right side
    glColor3f(0.9, 1.0, 1.0);
    glVertex3f(x2, ya1, z1);
    glVertex3f(x2, yb1, z2);
    glVertex3f(x2, yb2, z2);
    glVertex3f(x2, ya2, z1);

    // Top side
    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(x1, yb2, z2);
    glVertex3f(x2, yb2, z2);
    glVertex3f(x2, ya2, z1);
    glVertex3f(x1, ya2, z1);

    // Bottom side
    glColor3f(0.5, 0.05, 0.5);
    glVertex3f(x1, yb1, z2);
    glVertex3f(x2, yb1, z2);
    glVertex3f(x2, ya1, z1);
    glVertex3f(x1, ya1, z1);

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set up the camera view
    gluLookAt(
        cameraX, cameraY, cameraZ,  // Eye position (camera position)
        lookAtX, lookAtY, lookAtZ, // Look-at point (where the camera looks)
        upX, upY, upZ              // Up direction
    );

    // Draw the cylinder
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Rotate around X-axis
    glColor3f(0.9f, 0.9f, 1.0f); // Set cylinder color
    gluCylinder(quadric, cylinderBaseRadius, cylinderTopRadius, cylinderHeight, cylinderSlices, cylinderStacks);
    glPopMatrix();

    // Draw the legs
    kaki(-0.05, 0.05, 1, 0.5);
    kaki(0.05, -0.05, -1, -0.5);
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // Rotate 90 degrees around Y-axis
    kaki(-0.05, 0.05, 1, 0.5);   // Leg 3 (rotated)
    kaki(0.05, -0.05, -1, -0.5);  // Leg 4 (rotated)
    glPopMatrix();

    // Set material properties
    GLfloat material_ambient[] = { 0.2f, 0.2f, 0.6f, 1.0f };
    GLfloat material_diffuse[] = { 0.6f, 0.6f, 0.8f, 1.0f };
    GLfloat material_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat material_shininess[] = { 50.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

    // Draw oval sphere on top of the cylinder
    glPushMatrix();
    glTranslatef(0.0f, 3.0f, 0.0f);  // Position above the cylinder
    glScalef(1.0f, 1.5f, 1.0f);      // Scale to make it oval (stretch in Y)
    gluSphere(quadric, 0.5f, 32, 32); // Sphere to be stretched
    glPopMatrix();

    glutSwapBuffers();
}

void init() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Set background color

    // Set up perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    // Lighting setup
    GLfloat light_position[] = { 5.0f, 5.0f, 5.0f, 1.0f };  // Position of the light
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };    // Ambient light
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };    // Diffuse light

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glEnable(GL_LIGHT0);   // Enable light source 0
    glEnable(GL_LIGHTING); // Enable lighting

    // Create a new quadric object for rendering shapes
    quadric = gluNewQuadric();
    if (!quadric) {
        std::cout << "Failed to create GLU quadric" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': // Move forward
        cameraZ -= cameraSpeed;
        break;
    case 's': // Move backward
        cameraZ += cameraSpeed;
        break;
    case 'a': // Move left
        cameraX -= cameraSpeed;
        break;
    case 'd': // Move right
        cameraX += cameraSpeed;
        break;
    case 'q': // Move up
        cameraY += cameraSpeed;
        break;
    case 'e': // Move down
        cameraY -= cameraSpeed;
        break;
    case 27: // Escape key to exit
        exit(0);
        break;
    }
    glutPostRedisplay(); // Redraw the scene with the updated camera position
}

void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:    // Tilt up
        lookAtY += cameraSpeed;
        break;
    case GLUT_KEY_DOWN:  // Tilt down
        lookAtY -= cameraSpeed;
        break;
    case GLUT_KEY_LEFT:  // Pan left
        lookAtX -= cameraSpeed;
        break;
    case GLUT_KEY_RIGHT: // Pan right
        lookAtX += cameraSpeed;
        break;
    }
    glutPostRedisplay(); // Redraw the scene with the updated look-at point
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Cylinder with Legs and Lighting");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    return 0;
}