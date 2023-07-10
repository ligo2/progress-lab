// #include <GL/glut.h>      // 包含 GLUT 库的头文件
// #include <GL/glu.h>       // 包含 GLU 库的头文件
// #include <GL/gl.h>        // 包含 OpenGL 核心库的头文件

// !glfw用来协助opengl创建窗口，glad用来管理函数指针
// void init()
// {
//     glClearColor(0.0, 0.0, 0.0, 0.0);
//     glMatrixMode(GL_PROJECTION);
//     glOrtho(-5, 5, -5, 5, 5, 15);
//     glMatrixMode(GL_MODELVIEW);
//     gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
// }

// void display()
// {
//     glClear(GL_COLOR_BUFFER_BIT);
//     glColor3f(1.0, 0, 0);
//     glutWireTeapot(3);
//     glFlush();
// }

// int main(int argc, char *argv[])
// {
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
//     glutInitWindowPosition(0, 0);
//     glutInitWindowSize(300, 300);
//     glutCreateWindow("OpenGL 3D View");
//     init(); glutDisplayFunc(display);
//     glutMainLoop();
//     return 0;
// }







// #include <stdio.h>
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// int main() {
//     glfwInit();
//     int glfwMajor, glfwMinor, glfwRevision;
//     glfwGetVersion(&glfwMajor, &glfwMinor, &glfwRevision);
//     printf("GLFW version: %d.%d.%d\n", glfwMajor, glfwMinor, glfwRevision);
//     glfwTerminate();
//     return 0;
// }










// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <stdio.h>

// void errorCallback(int error, const char* description) {
//     fprintf(stderr, "Error: %s\n", description);
// }

// int main() {
//     // 初始化 GLFW
//     glfwSetErrorCallback(errorCallback);
//     if (!glfwInit()) {
//         fprintf(stderr, "Failed to initialize GLFW\n");
//         return -1;
//     }

//     // 创建窗口和上下文
//     GLFWwindow* window = glfwCreateWindow(800, 600, "GLAD Test", NULL, NULL);
//     if (!window) {
//         fprintf(stderr, "Failed to create GLFW window\n");
//         glfwTerminate();
//         return -1;
//     }

//     // 设置当前上下文为窗口上下文
//     glfwMakeContextCurrent(window);

//     // 初始化 GLAD
//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//         fprintf(stderr, "Failed to initialize GLAD\n");
//         glfwTerminate();
//         return -1;
//     }

//     // 打印 OpenGL 信息
//     printf("OpenGL version: %s\n", glGetString(GL_VERSION));
//     printf("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

//     // 渲染循环
//     while (!glfwWindowShouldClose(window)) {
//         // 清空屏幕为黑色
//         glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);

//         // 绘制代码

//         // 交换缓冲区并获取事件
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     // 终止 GLFW
//     glfwTerminate();
//     return 0;
// }










// #include <iostream>
// #include <glad/glad.h>  //函数地址设置，管理opengl的函数指针
// #include <GLFW/glfw3.h> //用于窗口创建

// //回调
// void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//     glViewport(0, 0, width, height);
// }

// void processInput(GLFWwindow* window) {
//     //检查用户是否按下了返回键(Esc)（如果没有按下，glfwGetKey将会返回GLFW_RELEASE，按下则为PRESS
//     //GLFW_KEY_ESCAPE：键盘Esc键的键码常量
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {//获取Esc建状态
//         glfwSetWindowShouldClose(window, true);
//     }
// }

// int main() {
//     glfwInit();//初始化失败会自动调用glfwTerminate
//     //告诉GLFW使用的oepngl版本3.3（主版本major，此版本minor）
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     // 使用核心模式
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     // 创建窗口对象
//     GLFWwindow* window = glfwCreateWindow(800, 600, "LEARNOPENGL", nullptr, nullptr);
//     if (window == nullptr) {
//         std::cerr << "failed to create GLFW windwo" << std::endl;
//         glfwTerminate();//终止
//         /*
//             此函数销毁所有剩余的窗口和游标，恢复任何修改的gamma坡道
//             并释放任何其他已分配的资源。
//         */
//         return -1;
//     }
//     glfwMakeContextCurrent(window);
//     //使指定窗口的上下文为调用线程的当前上下文

//     //调用oepngl时需要初始化GLAD
//     // glfwGetProcAddress:返回当前上下文的指定函数的地址
//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//         std::cerr << "Failed to initialize GLAD" << std::endl;
//         return -2;
//     }

//     glViewport(0, 0, 200, 200);//视口实际上就是在窗口对象中显示大小
//     // 函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）。
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//     //渲染循环
//     while (!glfwWindowShouldClose(window)) {
//         //设置清屏的颜色
//         glClearColor(0.5f, 0.3f, 0.3f, 1.0f);
//         /*
//             它接受一个缓冲位(Buffer Bit)来指定要清空的缓冲，
//             可能的缓冲位有GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT。
//         */
//         glClear(GL_COLOR_BUFFER_BIT);

//         processInput(window);
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     glfwTerminate();
//     return 0;
// }









// void test1() {
//     //创建和绑定顶点缓冲对象
//     unsigned int VBO;
//     glGenBuffers(1, &VBO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);

//     // 将顶点数据绑定到当前的顶点缓冲对象中：
//     GLfloat vertices[] = {
//     // 顶点坐标数据
//     };
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     // 绑定顶点缓冲对象
//     glBindBuffer(GL_ARRAY_BUFFER, VBO); 

//     // 指定顶点属性指针
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);
// // }


// // void test2() {
//     const char *vertexShaderSource = "#version 330 core\n"
//     "layout (location = 0) in vec3 aPos;\n"
//     "void main()\n"
//     "{\n"
//     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//     "}\0";
//     unsigned int vertexShader;
//     vertexShader = glCreateShader(GL_VERTEX_SHADER);
        //~ 把这个着色器源码附加到着色器对象上，然后编译它：
//     glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
//     glCompileShader(vertexShader);

//     int success;
//     char infoLog[512];//编译错误时可以存储错误信息
//     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//     if (!success) {
//         glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
//         std::cerr << "compile failed\n" << \
//             "error message: " << infoLog << std::endl;
//     }



//     //片段着色器
//     const char *fragmentShaderSource = "#version 330 core\n"
//     "out vec4 FragColor;\n"
//     "void main()\n"
//     "{\n"
//     "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//     "}\0";
//     unsigned int fragmentShader;
//     fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
//     glCompileShader(fragmentShader);

//     //将两个着色器对象链接到一个用来渲染的着色器程序(Shader Program)中。




//     unsigned int shaderProgram;
//     shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);

//     glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//     if (!success) {
//         glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
//         //....
//     }

//     glUseProgram(shaderProgram);//激活程序对象

//     //链接后，直接删除着色器对象
//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);

//     //使用glVertexAttribPointer函数告诉OpenGL该如何解析顶点数据（应用到逐个顶点属性上）
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);



//     unsigned int VAO;
//     glGenVertexArrays(1, &VAO);
//     glBindVertexArray(VAO);
//     // 2. 把顶点数组复制到缓冲中供OpenGL使用
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     // 3. 设置顶点属性指针
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);

//     // [...]

//     // ..:: 绘制代码（渲染循环中） :: ..
//     // 4. 绘制物体
//     glUseProgram(shaderProgram);
//     glBindVertexArray(VAO);
//     glDrawArrays(GL_TRIANGLES, 0, 3);
// }






#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // 创建窗口对象
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}