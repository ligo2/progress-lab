#shader Vertex

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexture;

out vec3 ourColor;   //输出给片段着色器
out vec2 texCoord;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ourColor = aColor;
    texCoord = aTexture;
};

#shader Fragment
#version 330 core
out vec4 color;
in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D Texture;
uniform sampler2D Face;
void main()
{
    color = texture(Texture, texCoord) * texture(Face, texCoord);
};
