#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

typedef float point[3];

class Dormer {
  point bottomCenter;
  float height, width, depth, roofHeight;

public:
  Dormer(float x, float y, float z);
  void draw(GLenum mode);
};

Dormer::Dormer(float x, float y, float z) {
  bottomCenter[0] = x;
  bottomCenter[1] = y;
  bottomCenter[2] = z;
  height = 1.75;
  roofHeight = 1.0;
  width = 1.75;
  depth = 4;
}

void Dormer::draw(GLenum mode) {
  glPushAttrib(GL_CURRENT_BIT);
  glPushAttrib(GL_POLYGON_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, mode);

  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1.0, 1.0);

  if (mode == GL_LINE) {
    glColor3f(0.0, 0.0, 0.0);
  } else {
    glColor3f(brickColor[0], brickColor[1], brickColor[2]);
  }

  glBegin(GL_QUADS);
    // front face
    glVertex3f(bottomCenter[0] - (width / 2), bottomCenter[1], bottomCenter[2]);
    glVertex3f(bottomCenter[0] + (width / 2), bottomCenter[1], bottomCenter[2]);
    glVertex3f(bottomCenter[0] + (width / 2), bottomCenter[1] + height, bottomCenter[2]);
    glVertex3f(bottomCenter[0] - (width / 2), bottomCenter[1] + height, bottomCenter[2]);

    // right side face
    glVertex3f(bottomCenter[0] + (width / 2), bottomCenter[1], bottomCenter[2]);
    glVertex3f(bottomCenter[0] + (width / 2), bottomCenter[1], bottomCenter[2] - depth);
    glVertex3f(bottomCenter[0] + (width / 2), bottomCenter[1] + height, bottomCenter[2] - depth);
    glVertex3f(bottomCenter[0] + (width / 2), bottomCenter[1] + height, bottomCenter[2]);

    // left side face
    glVertex3f(bottomCenter[0] - (width / 2), bottomCenter[1], bottomCenter[2]);
    glVertex3f(bottomCenter[0] - (width / 2), bottomCenter[1], bottomCenter[2] - depth);
    glVertex3f(bottomCenter[0] - (width / 2), bottomCenter[1] + height, bottomCenter[2] - depth);
    glVertex3f(bottomCenter[0] - (width / 2), bottomCenter[1] + height, bottomCenter[2]);
  glEnd();

  glDisable(GL_POLYGON_OFFSET_FILL);

  glBegin(GL_TRIANGLES);
    glVertex3f(bottomCenter[0] - (width / 2), bottomCenter[1] + height, bottomCenter[2]);
    glVertex3f(bottomCenter[0] + (width / 2), bottomCenter[1] + height, bottomCenter[2]);
    glVertex3f(bottomCenter[0], bottomCenter[1] + height + roofHeight, bottomCenter[2]);
  glEnd();

  if (mode == GL_FILL) {
    glColor3f(roofColor[0], roofColor[1], roofColor[2]);
  }

  glBegin(GL_QUADS);
    // roof right side
    glVertex3f(bottomCenter[0] + (width / 2), bottomCenter[1] + height, bottomCenter[2]);
    glVertex3f(bottomCenter[0] + (width / 2), bottomCenter[1] + height, bottomCenter[2] - depth);
    glVertex3f(bottomCenter[0], bottomCenter[1] + height + roofHeight, bottomCenter[2] - depth);
    glVertex3f(bottomCenter[0], bottomCenter[1] + height + roofHeight, bottomCenter[2]);

    // roof left side
    glVertex3f(bottomCenter[0] - (width / 2), bottomCenter[1] + height, bottomCenter[2]);
    glVertex3f(bottomCenter[0] - (width / 2), bottomCenter[1] + height, bottomCenter[2] - depth);
    glVertex3f(bottomCenter[0], bottomCenter[1] + height + roofHeight, bottomCenter[2] - depth);
    glVertex3f(bottomCenter[0], bottomCenter[1] + height + roofHeight, bottomCenter[2]);

    // window pane
    if (mode == GL_LINE) {
      glColor3f(0.0, 0.0, 0.0);
    } else {
      glColor3f(windowColor[0], windowColor[1], windowColor[2]);
    }
    glVertex3f(bottomCenter[0] - (width / 2) + 0.45, bottomCenter[1] + 0.40, bottomCenter[2]);
    glVertex3f(bottomCenter[0] + (width / 2) - 0.45, bottomCenter[1] + 0.40, bottomCenter[2]);
    glVertex3f(bottomCenter[0] + (width / 2) - 0.45, bottomCenter[1] + height - 0.40, bottomCenter[2]);
    if (mode == GL_FILL) {
      glColor3f(windowCornerColor[0], windowCornerColor[1], windowCornerColor[2]);
    }
    glVertex3f(bottomCenter[0] - (width / 2) + 0.45, bottomCenter[1] + height - 0.40, bottomCenter[2]);

  glEnd();
  glPopAttrib();
  glPopAttrib();
}
