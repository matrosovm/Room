#ifndef OPENGL_PARSER_H
#define OPENGL_PARSER_H

#include <string>
#include "cube.h"

void FunctionParser(Cube& room, std::list<Cube>& cubes, std::stringstream& stream, std::string& textLine);
void ConfigParser(Cube& room, std::list<Cube>& cubes, const char* config);

#endif //OPENGL_PARSER_H
