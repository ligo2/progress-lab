#shader Vertex

#version 330 core
layout (location = 0) in vec2 aPos;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 1, 1.0);
};

#shader Fragment

#version 330 core
out vec4 color;
uniform vec4 u_Color;
void main()
{
    color = u_Color;
};
