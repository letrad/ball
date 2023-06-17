#include <GL/glut.h>
#include <cmath>

// Variables to store the current viewing angles
float angleX = 0.0f;
float angleY = 0.0f;

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 16.0 / 9.0, 1.0, 10.0); // Aspect ratio set to 16:9
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(4.0 * sin(angleX), 4.0 * sin(angleY), 4.0 * cos(angleX), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Draw a sphere
    const float radius = 1; // 1 captures whole screen

    const int slices = 50;
    const int stacks = 50;

    for (int stack = 0; stack < stacks; ++stack)
    {
        float phi1 = static_cast<float>(stack) / stacks * M_PI;
        float phi2 = static_cast<float>(stack + 1) / stacks * M_PI;

        for (int slice = 0; slice < slices; ++slice)
        {
            float theta1 = static_cast<float>(slice) / slices * 2 * M_PI;
            float theta2 = static_cast<float>(slice + 1) / slices * 2 * M_PI;

            glBegin(GL_QUADS);

            // Vertex 1
            glColor3f(1.0f, 0.0f, 0.0f); // Red
            glVertex3f(radius * sin(phi1) * cos(theta1), radius * cos(phi1), radius * sin(phi1) * sin(theta1));

            // Vertex 2
            glColor3f(1.0f, 1.0f, 0.0f); // Yellow
            glVertex3f(radius * sin(phi1) * cos(theta2), radius * cos(phi1), radius * sin(phi1) * sin(theta2));

            // Vertex 3
            glColor3f(0.0f, 1.0f, 0.0f); // Green
            glVertex3f(radius * sin(phi2) * cos(theta2), radius * cos(phi2), radius * sin(phi2) * sin(theta2));

            // Vertex 4
            glColor3f(0.0f, 0.0f, 1.0f); // Blue
            glVertex3f(radius * sin(phi2) * cos(theta1), radius * cos(phi2), radius * sin(phi2) * sin(theta1));

            glEnd();
        }
    }

    glFlush();
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void keyboard(int key, int x, int y)
{
    const float rotationSpeed = 0.05f;

    switch (key)
    {
        case GLUT_KEY_LEFT:
            angleX -= rotationSpeed;
            break;
        case GLUT_KEY_RIGHT:
            angleX += rotationSpeed;
            break;
        case GLUT_KEY_UP:
            angleY -= rotationSpeed;
            break;
        case GLUT_KEY_DOWN:
            angleY += rotationSpeed;
            break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 450); // Set window size with 16:9 aspect ratio
    glutCreateWindow("Simple 3D Engine");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard); // Register keyboard event handler for special keys

    glutMainLoop();

    return 0;
}
