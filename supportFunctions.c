#include "includes.h"

unsigned int randInt(int ceiling, int floor)
{
	if (ceiling < 0 || floor < 0) {
		return -1;
	}
	
	if (floor > ceiling) {
		int temp = floor;
		floor = ceiling;
		ceiling = temp;
	}
	
	ceiling -= floor;

	unsigned int unsignedMax = (unsigned int) RAND_MAX;
	
	if (ceiling > unsignedMax) {
		return -1;
	}
	
	int divisor = unsignedMax / (ceiling + 1);
	int temp;
	
	do {
		temp = rand() / divisor;
	} while (temp > ceiling);
	
	return (temp + floor);
}




int wraparound(int x, int y)
{
    int r = x;
    if (x < 0)
        r = y + x;
    else if (x >= y)
        r = x - y;
    return r;
}




double randomReal()
{
	unsigned int numerator = rand();
	return ((double) numerator) / ((double) RAND_MAX);
}




void numToBinary(int geneLength, unsigned int numericRepresenation,
                 int* binaryRepresentation)
{
	for (int i = (geneLength - 1); i > -1; i--) {
		binaryRepresentation[i] = (numericRepresenation % 2);
		numericRepresenation /= 2;
	}
}




// This function gets the next whitespace-separated token
void getNext(char* buffer, int* index, FILE* fp)
{
  int i;
  for (i = 0; i < 255; i++) {
    buffer[i] = fgetc(fp);
    if (buffer[i] == '\n' ||
        buffer[i] == ' ') {
      buffer[i] = '\0';
      break;
    } else if (buffer[i] == EOF) {
      break;
    }
  }
  
  if (i == 254) {
    printf("Output file name is too long. Must be under 255 characters\n");
    exit(0);
  }
  
  *index = i;
}
