#include <iostream>
#include <SOIL/SOIL.h>
#include "cube.h"

using namespace std;

const float standartBackSide[]{
-1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
 1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
 1.0f,  1.0f, -1.0f,  0.0f, 0.0f,
 1.0f,  1.0f, -1.0f,  0.0f, 0.0f,
-1.0f,  1.0f, -1.0f,  0.0f, 0.0f,
-1.0f, -1.0f, -1.0f,  0.0f, 0.0f,};

const float standartFrontSide[]{
-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
 1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
 1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
 1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
-1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
-1.0f, -1.0f,  1.0f,  0.0f, 0.0f, };

const float standartLeftSide[]{
-1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
-1.0f,  1.0f, -1.0f,  0.0f, 0.0f,
-1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
-1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
-1.0f,  1.0f,  1.0f,  0.0f, 0.0f, };

const float standartRightSide[]{
 1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
 1.0f,  1.0f, -1.0f,  0.0f, 0.0f,
 1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
 1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
 1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
 1.0f,  1.0f,  1.0f,  0.0f, 0.0f, };

const float standartDownSide[]{
-1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
 1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
 1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
 1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
-1.0f, -1.0f, -1.0f,  0.0f, 0.0f, };

const float standartUpSide[]{
-1.0f,  1.0f, -1.0f,  0.0f, 0.0f,
 1.0f,  1.0f, -1.0f,  0.0f, 0.0f,
 1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
 1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
-1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
-1.0f,  1.0f, -1.0f,  0.0f, 0.0f, };


Texture::Texture() :
src(nullptr) { }

Texture::Texture(const string& txt) :
src(SOIL_load_image(txt.c_str(), &width, &height, 0, SOIL_LOAD_RGB)) { }

Texture::Texture(Texture&& tx) noexcept :
src(std::move(tx.src)),
width(tx.width),
height(tx.height) { }

unsigned char* Texture::GetSrc() const
{
    return src.get();
}

int Texture::GetTextureHeight() const
{
    return height;
}

int Texture::GetTextureWidth() const
{
    return width;
}

Texture& Texture::operator=(const Texture& tx) &
{
    src    = tx.src;
    width  = tx.width;
    height = tx.height;

    return *this;
}

Texture& Texture::operator=(Texture&& tx) & noexcept
{
    src    = move(tx.src);
    width  = tx.width;
    height = tx.height;

    return *this;
}

void Cube::MakeStandartSide()
{
    for (size_t i = 0; i < 6; ++i)
    {
        for (size_t j = 0; j < 30; ++j)
        {
            if (i == 0)
                vertices[0][j] = standartFrontSide[j];
            else if (i == 1)
                vertices[1][j] = standartBackSide[j];
            else if (i == 2)
                vertices[2][j] = standartLeftSide[j];
            else if (i == 3)
                vertices[3][j] = standartRightSide[j];
            else if (i == 4)
                vertices[4][j] = standartDownSide[j];
            else if (i == 5)
                vertices[5][j] = standartUpSide[j];
            if (j % 5 == 0)
            {
                vertices[i][j] *= GetWidth();
            }
            else if (j % 5 == 1)
            {
                vertices[i][j] *= GetHeight();
            }
            else if (j % 5 == 2)
            {
                vertices[i][j] *= GetLength();
            }
        }
    }
}

Cube::Cube():
positionX(0.0),
positionY(0.0),
positionZ(0.0),
width(1),
height(1),
length(1)
{
    MakeStandartSide();
}


Cube::Cube(float width, float length, float height,
           float x, float y, float z, std::array<Texture, 6>&& textures) :
positionX(x),
positionY(y),
positionZ(z),
width(width),
height(height),
length(length)
{
    MakeStandartSide();
    SetTexture(std::move(textures));
}

Cube::Cube(Cube&& cb) noexcept :
positionX(cb.positionX),
positionY(cb.positionY),
positionZ(cb.positionZ),
width(cb.width),
height(cb.height),
length(cb.length),
vertices(cb.vertices),
textures(std::move(cb.textures)) { }

float Cube::GetPositionX() const
{
    return positionX;
}

float Cube::GetPositionY() const
{
    return positionY;
}

float Cube::GetPositionZ() const
{
    return positionZ;
}

float Cube::GetHeight() const
{
    return height;
}

float Cube::GetWidth() const
{
    return width;
}

float Cube::GetLength() const
{
    return length;
}

unsigned char* Cube::GetTexture(size_t i) const
{
    if (i <= 5)
        return this->textures.at(i).GetSrc();
    else
        return nullptr;
}

int Cube::GetTextureHeight(size_t i) const
{
    try
    {
        return this->textures.at(i).GetTextureHeight();
    }
    catch (...)
    {
        cerr << "textures array out of range" << endl;
    }
    return 0;
}

int Cube::GetTextureWidth(size_t i) const
{
    try
    {
        return this->textures.at(i).GetTextureWidth();
    }
    catch (...)
    {
        cerr << "textures array out of range" << endl;
    }
    return 0;
}

std::array<float, 30> Cube::GetVertices(size_t i) const
{
    try
    {
        return this->vertices.at(i);
    }
    catch (...)
    {
        cerr << "vertices array out of range" << endl;
    }
    return vertices[0];
}

void Cube::SetTexture(std::array<Texture, 6>&& textures)
{
    Texture tmp;
    for (auto& texture : textures)
    {
        if (texture.GetSrc() != nullptr)
        {
            tmp = std::move(texture);
            break;
        }
    }

    for (std::size_t i = 0; i < 6; ++i)
    {
        if (textures[i].GetSrc() == nullptr)
            this->textures[i] = tmp;
        else
            this->textures[i] = std::move(textures[i]);

        this->vertices[i][3] = 0.0f;
        this->vertices[i][4] = 0.0f;

        this->vertices[i][8] = 1.0f;
        this->vertices[i][9] = 0.0f;

        this->vertices[i][13] = 1.0f;
        this->vertices[i][14] = 1.0f;

        this->vertices[i][18] = 1.0f;
        this->vertices[i][19] = 1.0f;

        this->vertices[i][23] = 0.0f;
        this->vertices[i][24] = 1.0f;

        this->vertices[i][28] = 0.0f;
        this->vertices[i][29] = 0.0f;
    }

}

Cube& Cube::operator=(Cube&& cb) & noexcept
{
    using std::move;
    positionX = cb.positionX;
    positionY = cb.positionY;
    positionZ = cb.positionZ;
    width     = cb.width;
    height    = cb.height;
    length    = cb.length;
    vertices  = cb.vertices;
    textures  = move(cb.textures);

    return *this;
}
