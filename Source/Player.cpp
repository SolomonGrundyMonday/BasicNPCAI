/*
 *   Player class definition.
 *   Created by Jeff Colgan, January 13, 2022.  
 */

#include "Player.h"

// Function definition for Player class default constructor.
Player::Player() : GameObject()
{

}

// Function definition for Player class constructor.
Player::Player(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
: GameObject(x, y, z, dx, dy, dz, rx, ry, rz)
{

}

// Function definition for Player class Initialize function implementation.
int Player::Initialize(const char* filename)
{
	this->texture = GameObject::Initialize(filename);

    if (this->texture == 0)
       return 0;
    else
       return this->texture;
}

// Function definition for Player class Render function implementation.
void Player::Render()
{
   // Set material properties.
   float white[] = { 1.0, 1.0, 1.0, 1.0 };
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);

   glPushMatrix();
   glColor3f(1.0, 1.0, 1.0);

   // Set object's translation, scaling and rotation.
   glTranslated(this->getPosX(), this->getPosY(), this->getPosZ());
   glRotated(this->getRotX(), 1, 0, 0);
   glRotated(this->getRotY(), 0, 1, 0);
   glRotated(this->getRotZ(), 0, 0, 1);
   glScaled(this->getScaleX(), this->getScaleY(), this->getScaleZ());

   // Enable and bind textures.
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, this->texture);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

   // Draw the player as an incomplete circle (placeholder).
   glBegin(GL_TRIANGLE_FAN);
   glNormal3f(0.0, 0.0, 0.0);
   glTexCoord2f(0.5, 0.5);
   glVertex3f(0.0, 0.0, 0.0);

   for (int i = 0; i < 330; i++)
   {
      float x = Cos(i);
      float z = Sin(i);

      glTexCoord2f(0.5 * x + 0.5, 0.5 * z + 0.5);
      glVertex3f(x, 0.0, z);
   }
   glEnd();

   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

// Function definition for Player class resolveCollision function implementation.
void Player::resolveCollision(Camera* camera)
{
   // Do nothing.
}