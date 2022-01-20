/*
 *   Class definition for Ground class.
 *   Created by Jeff Colgan, January 8, 2022. 
 */

#include "Ground.h"

// Function definition for Ground default constructor.
Ground::Ground() : GameObject()
{

}

// Function definition for Ground constructor.
Ground::Ground(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
: GameObject(x, y, z, dx, dy, dz, rx, ry, rz)
{

}

// Function definition for Ground Initialize function implementation.
int Ground::Initialize(const char* filename)
{
   this->texture = GameObject::Initialize(filename);

   if (this->texture == 0)
      return 0;
   else
      return this->texture;
}

// Function definition for Ground Render function implementation.
void Ground::Render()
{
   // Set material properties.
   float white[] = { 1.0, 1.0, 1.0, 1.0 };
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);

   glPushMatrix();
   glColor3f(1.0, 1.0, 1.0);

   // Set object translation, scaling and rotation.
   glTranslated(this->getPosX(), this->getPosY(), this->getPosZ());
   glRotated(this->getRotX(), 1, 0, 0);
   glRotated(this->getRotY(), 0, 1, 0);
   glRotated(this->getRotZ(), 0, 0, 1);
   glScaled(this->getScaleX(), this->getScaleY(), this->getScaleZ());

   // Enable and bind textures.
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, texture);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);

   // Tessalate ground squares.
   for (int i = -this->getScaleX(); i < this->getScaleX(); i++)
   {
      for (int j = -this->getScaleZ(); j < this->getScaleZ() - 1; j += 2)
      {
         // Compute minimum and maximum x, z values.
         float minX = i / this->getScaleX();
         float maxX = (i + 1) / this->getScaleX();
         float minZ = j / this->getScaleZ();
         float maxZ = (j + 1) / this->getScaleZ();
         float maxZ1 = (j + 2) / this->getScaleZ();

         // Draw two ground tiles per iteration of inner loop.
         glNormal3f(0.0, 1.0, 0.0);
         glBegin(GL_QUADS);
         glTexCoord2f(0.0, 0.0);
         glVertex3f(maxX, 1.0, maxZ);
         glTexCoord2f(0.0, 1.0);
         glVertex3f(maxX, 1.0, minZ);
         glTexCoord2f(1.0, 1.0);
         glVertex3f(minX, 1.0, minZ);
         glTexCoord2f(1.0, 0.0);
         glVertex3f(minX, 1.0, maxZ);
         glEnd();

         glNormal3f(0.0, 1.0, 0.0);
         glBegin(GL_QUADS);
         glTexCoord2f(0.0, 0.0);
         glVertex3f(maxX, 1.0, maxZ1);
         glTexCoord2f(0.0, 1.0);
         glVertex3f(maxX, 1.0, maxZ);
         glTexCoord2f(1.0, 1.0);
         glVertex3f(minX, 1.0, maxZ);
         glTexCoord2f(1.0, 0.0);
         glVertex3f(minX, 1.0, maxZ1);
         glEnd();
	  }
   }

   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
}

// Function definition for Ground resolveCollision function implementation.
void Ground::resolveCollision(Camera* camera)
{
   // Implement collision resolution here.
}