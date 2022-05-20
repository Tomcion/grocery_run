#include "Call.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[Error]: " << function << " - ";
        switch (error)
        {
            case GL_INVALID_ENUM:
                std::cout << "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:
                std::cout << "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:
                std::cout << "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:
                std::cout << "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:
                std::cout << "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:
                std::cout << "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                std::cout << "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout <<  "\nFile: " << file << ", Line: " << line << std::endl;
        return false;
    }
    return true;
}
