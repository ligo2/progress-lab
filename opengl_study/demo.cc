// #include <GL/glut.h>      // 包含 GLUT 库的头文件
// #include <GL/glu.h>       // 包含 GLU 库的头文件
// #include <GL/gl.h>        // 包含 OpenGL 核心库的头文件

//! opengl本质上是提供的API，是一种规范，没有说明具体的代码，而具体的代码提供由显卡厂商提供，
//! 所以opengl不是库，或引擎
//! glfw用来协助opengl创建窗口，glad用来管理函数指针
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









//& 创建窗口，包含Esc键退出窗口
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



//     const char *vertexShaderSource = "#version 330 core\n"
//     "layout (location = 0) in vec3 aPos;\n"
//     "void main()\n"
//     "{\n"
//     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//     "}\0";
//     //& 顶点着色器
//     unsigned int vertexShader;
//     vertexShader = glCreateShader(GL_VERTEX_SHADER);

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



//     //& 片段着色器
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
//     glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//     if (!success)
//     {
//         glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//     }

//     //& 将两个着色器对象链接到一个用来渲染的着色器程序(Shader Program)中。
//     //& 将顶点着色器和片段着色器与着色器程序关联起来，从而创建一个完整的渲染管线。
//     unsigned int shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);

    // glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    // if (!success) {
    //     glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    //     //....
    // }

//     glUseProgram(shaderProgram);//激活程序对象

//     //链接后，直接删除着色器对象
//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);

//     //使用glVertexAttribPointer函数告诉OpenGL该如何解析顶点数据（应用到逐个顶点属性上）
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


//     float vertices[] = {
//         -0.5f, -0.5f, 0.0f, // left  
//          0.5f, -0.5f, 0.0f, // right 
//          0.0f,  0.5f, 0.0f  // top   
//     }; 

//     unsigned int VAO, VBO;
//     glGenVertexArrays(1, &VAO);
//     //& 先绑定顶点数组对象，再绑定顶点缓冲对象，最后设置顶点属性
//     glGenBuffers(1, &VBO);
//     glBindVertexArray(VAO);
//     // 2. 把顶点数组复制到缓冲中供OpenGL使用
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     // glBufferData把用户定义的数据复制到当前绑定缓冲的函数
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     // 3. 设置顶点属性指针（告诉opengl该如何对数据布局）
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);

//     //& 可选，只有修改或配置其他VAO和VBO时才需要解绑
//     glBindBuffer(GL_ARRAY_BUFFER, 0); 
//     glBindVertexArray(0); 
//     // [...]

//     while (!glfwWindowShouldClose(window)) {
//         processInput(window);
//         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);
//         // 4. 绘制物体
//         glUseProgram(shaderProgram);
//         glBindVertexArray(VAO);
//         glDrawArrays(GL_TRIANGLES, 0, 3);

//         //& glfwSwapBuffers 函数的主要作用是交换前缓冲区和后缓冲区的内容，以实现图像的显示和更新。
// 		   //& 在双缓冲环境下，绘制操作通常先绘制到后缓冲区，然后使用 glfwSwapBuffers 将后缓冲区的内容交换到前缓冲区，从而显示出来。
//         glfwSwapBuffers(window);
//         //& 检查并处理窗口事件，以保证应用程序能够及时响应用户的输入，并在执行渲染之前更新应用程序的状态。
//         glfwPollEvents();
//     }

//     glDeleteVertexArrays(1, &VAO);
//     glDeleteBuffers(1, &VBO);
//     glDeleteProgram(shaderProgram);

//     glfwTerminate();
//     return 0;
// }




#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <exception>

//从文件读取GLSL
#include <fstream>

struct ShaderSources {
    std::string vertexrSources;
    std::string fragmentSources;
};
ShaderSources ParseShader(const std::string& filePath) {
    std::ifstream ifs(filePath);
    std::string line;
    enum class Type {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    Type type = Type::NONE;
    ShaderSources ans;
    while (std::getline(ifs, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("Vertex") != std::string::npos) {
                type = Type::VERTEX;
            }else if (line.find("Fragment") != std::string::npos) {
                type = Type::FRAGMENT;
            }
        } else {
            //写入数据了
            if (type == Type::VERTEX) {
                ans.vertexrSources += line + '\n';
            } else if (type == Type::FRAGMENT) {
                ans.fragmentSources += line + '\n';
            }
        }
    }

    return ans;
}


//* glGetError使用示例
static void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* func, const char* file, int line) {
    if (GLenum error = glGetError()) {//有错误则进入
        std::cerr << "error:(" << error << " ) " << func << " " << file << " " << line << std::endl;
        return false;
    }
    return true;
}
 //* x为oepngl的方法
#define GLCall(x) GLClearError();\
    x;\
    assert(GLLogCall(#x,__FILE__,__LINE__));

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
/**
 * 返回着色器id
*/
static unsigned int CompileShader(unsigned int type, const char* source) {
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);

	//差错处理。。。。
    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		//获取长度
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		// ...省略
        std::cerr << (type == GL_VERTEX_SHADER ? "GL_VERTEX_SHADER" : "GL_FRAGMENT_SHADER") << " error" << std::endl;
        return 0;
    }

    return id;
}
static unsigned int CreateShader(const char* vertexShader, const char* fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vertex = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	//附加到着色器程序，做成完整的渲染管线
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
	glLinkProgram(program);
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        // glGetProgramInfoLog(program, 512, nullptr, infoLog);
        //....
        std::cerr << "链接失败" << std::endl;
        return 0;
    }
    // 验证着色器程序对象的有效性
    glValidateProgram(program);

	glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
	if (!success) {
    	// glGetProgramInfoLog(program, 512, nullptr, infoLog);
    	std::cerr << "Shader program validation failed\n" << "Error message: " << std::endl;
	}
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}

int main() {
	glfwInit();//初始化失败会自动调用glfwTerminate
	/*
        GLFW_OPENGL_COMPAT_PROFILE 允许使用较旧版本的 OpenGL 和固定功能管线，
        而 GLFW_OPENGL_CORE_PROFILE 则限制使用较旧的特性和函数，以便使用现代的 OpenGL 功能和着色器编程
    */
    //告诉GLFW使用的oepngl版本3.3（主版本major，此版本minor）
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 使用核心模式
    //! 在opengl核心模式下，VAO 是必须，绑定VAO才能进行渲染
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    // 创建窗口对象
    GLFWwindow* window = glfwCreateWindow(800, 600, "LEARNOPENGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "failed to create GLFW windwo" << std::endl;
        glfwTerminate();//终止
        /*
            此函数销毁所有剩余的窗口和游标，恢复任何修改的gamma坡道
            并释放任何其他已分配的资源。
        */
        return -1;
    }
    glfwMakeContextCurrent(window);
    //使指定窗口的上下文为调用线程的当前上下文

    //调用opengl时需要初始化GLAD
    // glfwGetProcAddress:返回当前上下文的指定函数的地址
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -2;
    }

    glViewport(0, 0, 200, 200);//视口实际上就是在窗口对象中显示大小
    // 函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）。
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// float vertices[] = {
    //     -0.5f, -0.5f, // left  
    //     0.5f, -0.5f, // right 
    //     0.5f,  0.5f  // top   
    // }; 
	//& 存在内存浪费
	// float vertices[] = {
    //     -0.5f, -0.5f,  
    //     0.5f, -0.5f, 
    //     0.5f,  0.5f,

	// 	-0.5f, -0.5f,   
	// 	0.5f,  0.5f,
	// 	-0.5f, 0.5f
    // }; 
	float vertices[] = {
        -0.5f, -0.5f, //0  
        0.5f, -0.5f,  //1
        0.5f,  0.5f,  //2
		-0.5f, 0.5f   //3
    };
    unsigned int indices[] = {
        0, 1, 2,
        0, 3, 2
	};

    //core模式下必须绑定VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);


    unsigned int VBO;
    //创建缓冲区对象名称
    glGenBuffers(1, &VBO);
	// 将缓冲区对象名称绑定到目标缓冲区类型上
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //-创建并初始化缓冲区对象的数据存储
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//使用索引，同样需要创建索引缓冲区
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//告诉oepngl如何解析顶点数据,glVertexAttribPointer实际上还会连接VAO和VBO
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	// 启用顶点属性数组
    glEnableVertexAttribArray(0);
	// const char *vertexShaderSource = "#version 330 core\n"
	// "layout (location = 0) in vec2 aPos;\n"
	// "void main()\n"
	// "{\n"
	// "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
	// "}\n";

    // const char* fragmentShaderSource =
    //     "#version 330 core\n"
    //     "layout (location = 0) out vec4 color;\n"
    //     "uniform vec4 u_Color;\n"
    //     "void main()\n"
    //     "{\n"
    //     "   color = u_Color;\n"
    //     "}\n";
    // int program = CreateShader(vertexShaderSource, fragmentShaderSource);

    ShaderSources sources = ParseShader("./shader.shader");

    int program = CreateShader(sources.vertexrSources.c_str(), sources.fragmentSources.c_str());
    glUseProgram(program);  // 激活程序
    // 通过uniform修改颜色
    int location = glGetUniformLocation(program, "u_Color");
    glUniform4f(location, 0.8f, 0.3f, 0.4f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        // processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // glBindVertexArray(VBO);
        glUseProgram(program);           // 激活程序

        // 渲染管线
        // glDrawArrays(GL_TRIANGLES, 0, 3);//三个顶点
        //glDrawArrays(GL_TRIANGLES, 0, 6);//正方形
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		
		glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(program);
    glfwTerminate();

    return 0;
}
