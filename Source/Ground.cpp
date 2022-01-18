/*
 *   Class definition for Ground class.
 *   Created by Jeff Colgan, January 8, 2022. 
 */

#include "Ground.h"

// Function definition for Ground default constructor.
Ground::Ground()
{
   // Set default position (x, y, z) coordinates.
   this->posX = 0.0;
   this->posY = 0.0;
   this->posZ = 0.0;

   // Set default scaling values along x, y, z axes.
   this->scaleX = 1.0;
   this->scaleY = 1.0;
   this->scaleZ = 1.0;

   // Set default rotation values about x, y, z axes.
   this->rotX = 0.0;
   this->rotY = 0.0;
   this->rotZ = 0.0;
}

// Function definition for Ground constructor.
Ground::Ground(float x, float y, float z, float dx, float dy, float dz, float rx, float ry, float rz)
{
   // Set specified position (x, y, z) coordinates.
   this->posX = x;
   this->posY = y;
   this->posZ = z;

   // Set specified scaling values along x, y, z axes.
   this->scaleX = dx;
   this->scaleY = dy;
   this->scaleZ = dz;

   // Set specified scaling values about x, y, z axes.
   this->rotX = rx;
   this->rotY = ry;
   this->rotZ = rz;
}

// Function definition for Ground Initialize function implementation.
int Ground::Initialize(const char* filename)
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

// Function definition for Ground Reverse function.
void Ground::Reverse(void* x, const int n)
{
	char* ch = (char*)x;
	for (int k = 0; k < n/2; k++)
	{
		char tmp = ch[k];
		ch[k] = ch[n - 1 - k];
		ch[n - 1 - k] = tmp;
	}
}

// Function definition for Ground Render function implementation.
void Ground::Render()
{
   // Draw ground polygons here.
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
   glBindTexture(GL_TEXTURE_2D, texture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);

   for (int i = -this->scaleX; i < this->scaleX; i++)
   {
      for (int j = -this->scaleZ; j < this->scaleZ - 1; j += 2)
      {
         float minX = i / this->scaleX;
         float maxX = (i + 1) / this->scaleX;
         float minZ = j / this->scaleZ;
         float maxZ = (j + 1) / this->scaleZ;
         float maxZ1 = (j + 2) / this->scaleZ;

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

// Function definition for Ground getPosX getter function.
float Ground::getPosX()
{
   return posX;
}

// Function definition for Ground getPosY getter function.
float Ground::getPosY()
{
   return posY;
}

// Function definition for Ground getPosZ getter function.
float Ground::getPosZ()
{
   return posZ;
}

// Function definition for Ground getScaleX getter function.
float Ground::getScaleX()
{
   return scaleX;
}

// Function definition for Ground getScaleY getter function.
float Ground::getScaleY()
{
   return scaleY;
}

// Function definition for Ground getScaleZ getter function.
float Ground::getScaleZ()
{
   return scaleZ;
}

// Function definition for Ground getRotX getter function.
float Ground::getRotX()
{
   return rotX;
}

// Function definition for Ground getRotY getter function.
float Ground::getRotY()
{
   return rotY;
}

// Function definition for Ground getRotZ getter function.
float Ground::getRotZ()
{
   return rotZ;
}