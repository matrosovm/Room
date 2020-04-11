#include <iostream>
#include <sstream>
#include <fstream>
#include "parser.h"

using namespace std;

void FunctionParser(Cube& room, std::list<Cube>& cubes, stringstream& stream, string& line)
{
    string url[6];

    float width  = 1.0f;
    float height = 1.0f;
    float length = 1.0f;
    float x      = 0.0f;
    float y      = 0.0f;
    float z      = 0.0f;

    bool  mainCubeKey = true;

    if (line == "{")
        mainCubeKey = false;

    while (getline(stream, line) && line != "}")
    {
        if (line.length() >= 2 && line.substr(0, 1) == "//")
            continue;

        stringstream streamline(line);

        while (streamline >> line)
        {
            if (line == "texture:front")
                streamline >> url[0];
            else if (line == "texture:back")
                streamline >> url[1];
            else if (line == "texture:left")
                streamline >> url[2];
            else if (line == "texture:right")
                streamline >> url[3];
            else if (line == "texture:down")
                streamline >> url[4];
            else if (line == "texture:up")
                streamline >> url[5];
            else if (line == "size:")
                streamline >> width >> length >> height;
            else if (line == "position:")
                streamline >> x >> y >> z;
        }
    }

    std::array<Texture, 6> textures;

    for (size_t i = 0; i < 6; ++i)
        textures[i] = Texture(url[i]);

    Cube cube(width, length, height, x, y, z, std::move(textures));

    if (mainCubeKey)
        room = std::move(cube);
    else
        cubes.push_back(std::move(cube));
}

void ConfigParser(Cube& room, std::list<Cube>& cubes, const char* config)
{
    ifstream file(config);

    if (!file.is_open())
        cerr << "can't open file" << endl;

    string line;

    file.exceptions(ifstream::failbit);
    try
    {
        stringstream stream;
        stream << file.rdbuf();

        file.close();

        while (getline(stream, line))
        {
            stringstream streamLine(line);
            streamLine >> line;

            if (line.length() >= 2 && line.substr(0, 2) == "//")
                continue;
            else if (line == "{" || line == "{main")
                FunctionParser(room, cubes, stream, line);
            else if (line != "\0")
                cerr << "syntax error in config file: " << line << endl;
        }
    }
    catch(ifstream::failure& e)
    {
        cerr << "can't read config file" << endl;
        file.close();
    }

}
