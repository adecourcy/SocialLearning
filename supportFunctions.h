typedef enum bool_tag {FALSE, TRUE} Boolean;
unsigned int randInt(int ceiling, int floor);
int wraparound(int x, int y);
double randomReal();
void numToBinary(int geneLength, unsigned int numericRepresenation, int* binaryRepresentation);
void getNext(char* buffer, int* index, FILE* fp);