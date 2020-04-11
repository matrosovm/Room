#ifndef OPENGL_CUBE_H
#define OPENGL_CUBE_H

#include <array>
#include <list>
#include <memory>

class Texture
{
public:
    Texture();
    explicit Texture(const std::string& txt);

    Texture(Texture&& tx) noexcept ;
    Texture(const Texture&) = delete;

    unsigned char* GetSrc() const;
    int            GetTextureWidth() const;
    int            GetTextureHeight() const;

    Texture& operator=(const Texture& tx) &;
    Texture& operator=(Texture&& tx) & noexcept;

private:
    int width;
    int height;

    std::shared_ptr<unsigned char> src;
};

class Cube
{
public:
    Cube();
    Cube(float width, float length, float height, float x, float y, float z, std::array<Texture, 6>&& textures);

    Cube(Cube&& cb) noexcept ;
    Cube(const Cube&) = delete;

    float GetPositionX() const;
    float GetPositionY() const;
    float GetPositionZ() const;
    float GetWidth() const;
    float GetHeight() const;
    float GetLength() const;
    int   GetTextureWidth(size_t i) const;
    int   GetTextureHeight(size_t i) const;

    unsigned char*        GetTexture(size_t i) const;
    std::array<float, 30> GetVertices(size_t i) const;

    Cube& operator=(Cube&& cb) & noexcept ;
    Cube& operator=(const Cube&) & = delete;

private:
    float positionX;
    float positionY;
    float positionZ;
    float width;
    float length;
    float height;

    std::array<std::array<float, 30>, 6> vertices;
    std::array<Texture, 6>               textures;

    void MakeStandartSide();
    void SetTexture(std::array<Texture, 6>&& textures);
};

#endif //OPENGL_CUBE_H
