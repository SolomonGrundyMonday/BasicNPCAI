/*
 *   Player class definition.
 *   Created by Jeff Colgan, January 13, 2022.  
 */

#include "Player.h"

// Function definition for Player class default constructor.
Player::Player()
{
   // Set default translation.
   this->posX = 0.0;
   this->posY = 0.0;
   this->posZ = 0.0;

   // Set default scaling.
   this->scaleX = 1.0;
   this->scaleY = 1.0;
   this->scaleZ = 1.0;

   // Set default rotation.
   this->rotX = 1.0;
   this->rotY = 1.0;
   this->rotZ = 1.0;
}

// Function definition for Player class constructor.
Player::Player(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
{
   // Set the specified translation.
   this->posX = x;
   this->posY = y;
   this->posZ = z;

   // Set the specified scaling.
   this->scaleX = dx;
   this->scaleY = dy;
   this->scaleZ = dz;

   // Set the specified rotation.
   this->rotX = rx;
   this->rotY = ry;
   this->rotZ = rz;
}

// Function definition for Player class Initialize function implementation.
int Player::Initialize(const char* filename)
{
	// Load texture from input filename here.
	unsigned int text;
	unsigned short magic;
	unsigned int x, y, size;
	unsigned short planes, bits;
	unsigned char* image;
	unsigned int off;
	unsigned int k;
	unsigned int max;
	FILE* input;

	input = fopen(filename, "rb");

	if (!input)
	{
		printf("Failed to open texture file!\n");
		return 1;
	}

	if (fread(&magic, 2, 1, input) != 1)
	{
		printf("Failed to read texture file!\n");
		return 1;
	}

	if (magic != 0x4D42 && magic != 0x424D)
	{
		printf("Wrong magic value!\n");
		return 1;
	}

	if (fseek(input, 8, SEEK_CUR) || fread(&off, 4, 1, input) != 1 ||
		fseek(input, 4, SEEK_CUR) || fread(&x, 4, 1, input) != 1 || fread(&y, 4, 1, input) != 1 ||
		fread(&planes, 2, 1, input) != 1 || fread(&bits, 2, 1, input) != 1 || fread(&k, 4, 1, input) != 1)
	{
		printf("Failed to read texture dimensions!\n");
		return 1;
	}

	if (magic == 0x424D)
	{
		Reverse(&off, 4);
		Reverse(&x, 4);
		Reverse(&y, 4);
		Reverse(&planes, 2);
		Reverse(&bits, 2);
		Reverse(&k, 4);
	}

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, (int*)&max);
	if (x < 1 || x > max)
	{
		printf("Incorrect x-dimension!\n");
		return 1;
	}
	if (y < 1 || y > max)
	{
		printf("Incorrect y-dimension!\n");
		return 1;
	}
	if (planes != 1)
	{
		printf("Incorrect number of planes per pixel!\n");
		return 1;
	}
	if (bits != 24)
	{
		printf("Incorrect number of bits per pixel!\n");
		return 1;
	}
	if (k != 0)
	{
		printf("Incorrect counter value!\n");
		return 1;
	}

#ifndef GL_VERSION_2_0
	for (k = 1; k < x; k *= 2);
	if (k != x)
	{
		printf("Image x-dimension not a power of 2!\n");
		return 1;
	}
	for (k = 1; k < y; k *= 2);
	if (k != y)
	{
		printf("Image y-dimension not a power of 2!\n");
		return 1;
	}
#endif

	size = 3 * x * y;
	image = (unsigned char*)malloc(size);
	if (!image)
	{
		printf("Failed to allocate memory for image!\n");
		return 1;
	}

	if (fseek(input, off, SEEK_SET) || fread(image, size, 1, input) != 1)
	{
		printf("Failed to read image!\n");
		return 1;
	}
	fclose(input);

	for (k = 0; k < size; k += 3)
	{
		unsigned char temp = image[k];
		image[k] = image[k + 2];
		image[k + 2] = temp;
	}

	glGenTextures(1, &text);
	glBindTexture(GL_TEXTURE_2D, text);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	if (glGetError())
	{
		printf("OpenGL error in generating texture!\n");
		return 1;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	free(image);
	this->texture = text;

	return 0;
}

// Function definition for Player class Reverse helper function.
void Player::Reverse(void* x, const int n)
{
   char* ch = (char*)x;
   for (int k = 0; k < n / 2; k++)
   {
      char tmp = ch[k];
      ch[k] = ch[n - 1 - k];
      ch[n - 1 - k] = tmp;
   }
}

// Function definition for Player class Render function implementation.
void Player::Render()
{
   float white[] = { 1.0, 1.0, 1.0, 1.0 };

   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);

   glPushMatrix();
   glColor3f(1.0, 1.0, 1.0);

   glTranslated(this->posX, this->posY, this->posZ);
   glRotated(this->rotX, 1, 0, 0);
   glRotated(this->rotY, 0, 1, 0);
   glRotated(this->rotZ, 0, 0, 1);
   glScaled(this->scaleX, this->scaleY, this->scaleZ);

   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, this->texture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

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

// Function definition for Player class setPosition function.
void Player::setPosition(float x, float y, float z)
{
   // Set object translation coordinates.
   this->posX = x;
   this->posY = y;
   this->posZ = z;
}

// Function definition for Player class setScale function.
void Player::setScale(float x, float y, float z)
{
   // Set object scaling values.
   this->scaleX = x;
   this->scaleY = y;
   this->scaleZ = z;
}

// Function definition for Player class setRotation function.
void Player::setRotation(float x, float y, float z)
{
   // Set object's rotation about each axis.
   this->rotX = x;
   this->rotY = y;
   this->rotZ = z;
}

// Function definition for Player class getPosX function.
float Player::getPosX()
{
   return this->posX;
}

// Function definition for Player class getPosY function.
float Player::getPosY()
{
   return this->posY;
}

// Function definition for Player class getPosZ function.
float Player::getPosZ()
{
   return this->posZ;
}

// Function definition for Player class getScaleX function.
float Player::getScaleX()
{
   return this->scaleX;
}

// Function definition for Player class getScaleY function.
float Player::getScaleY()
{
   return this->scaleY;
}

// Function definition for Player class getScaleZ function.
float Player::getScaleZ()
{
   return this->scaleZ;
}

// Function definition for Player class getRotX function.
float Player::getRotX()
{
   return this->rotX;
}

// Function definition for Player class getRotY function.
float Player::getRotY()
{
   return this->rotY;
}

// Function definition for Player class getRotZ function.
float Player::getRotZ()
{
   return this->rotZ;
}