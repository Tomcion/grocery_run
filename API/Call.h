#ifndef CALL_H
#define CALL_H

#include <iostream>
#include <GL/glew.h>

#define Call(x) GLClearError();\
    x;\
    if(!GLLogCall(#x, __FILE__, __LINE__)) exit(1);


void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

#endif /* CALL_H */
