// this file can save screenshot

#include <string>

using namespace std;



bool saveScreenshot (string filename, unsigned int w, unsigned int h)
{
    //This prevents the images getting padded when the width multiplied by 3 is not a multiple of 4
    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    int nSize = w*h*3;
    // First let's create our buffer, 3 channels per Pixel
    char* dataBuffer = (char*)malloc(nSize*sizeof(char));

    if (!dataBuffer) return false;

    // Let's fetch them from the backbuffer. We request the pixels in GL_BGR format
    glReadPixels((GLint)0, (GLint)0, (GLint)w, (GLint)h, GL_BGR, GL_UNSIGNED_BYTE, dataBuffer);

    //Now the file creation
    FILE *filePtr = fopen(filename.c_str(), "wb");
    if (!filePtr) return false;

    unsigned char TGAheader[12] = {0,0,2,0,0,0,0,0,0,0,0,0};

    //unsigned char header[6] = { w%256,w/256, h%256,h/256, 24,0};
    unsigned char header[6] = { (unsigned char)(w%256),(unsigned char)(w/256), (unsigned char)(h%256),(unsigned char)(h/256), 24,0};
    // We write the headers
    fwrite(TGAheader, sizeof(unsigned char), 12, filePtr);
    fwrite(header,    sizeof(unsigned char),  6, filePtr);
    // And finally our image data
    fwrite(dataBuffer,	sizeof(GLubyte),	nSize,	filePtr);
    fclose(filePtr);

    free(dataBuffer);

    return true;
}
