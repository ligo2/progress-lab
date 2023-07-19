#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>

struct ShaderSources {
    std::string vertexrSources;
    std::string fragmentSources;
};
ShaderSources ParseShader(const std::string& filePath) {
    std::ifstream ifs(filePath);
    std::string line;
    //状态机
    enum class Type {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    Type type = Type::NONE;
    ShaderSources ans;
    while (std::getline(ifs, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("Vertex") != std::string::npos) {
                type = Type::VERTEX;
            } else if (line.find("Fragment") != std::string::npos) {
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
        return 0;
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //! 在opengl核心模式下，VAO 是必须，绑定VAO才能进行渲染
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    glViewport(0, 0, 800, 600);//视口实际上就是在窗口对象中显示大小
    // 函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）。

    ShaderSources sources = ParseShader("./shader.glsl");

    int program = CreateShader(sources.vertexrSources.c_str(), sources.fragmentSources.c_str());
    glUseProgram(program);
    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
	};

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	// 启用顶点属性数组
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    stbi_set_flip_vertically_on_load(true);
     //纹理
    unsigned int TBO;//纹理缓冲对象
    glGenTextures(1, &TBO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TBO);

    // 加载并生成纹理
    int width, height, numChannels;
    unsigned char* data = stbi_load("container.jpg", &width, &height, &numChannels, 0);
    if (data == nullptr) {
        std::cerr << "stbi_load1 failed" << std::endl;
        return -1;
    }
    // 当前绑定的纹理对象就会被附加上纹理图像。
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);//设置多级渐远纹理


    unsigned int TBO2;
    glGenTextures(1, &TBO2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, TBO2);
    // 第二个纹理单元
    unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &numChannels, 0);
    if (data2 == nullptr) {
        std::cerr << "stbi_load2 failed" << std::endl;
        return -2;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
    glGenerateMipmap(GL_TEXTURE_2D);//设置多级渐远纹理

    stbi_image_free(data);  //释放图像的内存
    stbi_image_free(data2); 

    glUseProgram(program);  // 激活程序
    // 设置uniform变量之前激活着色器程序。告诉OpenGL每个着色器采样器属于哪个纹理单元
    glUniform1i(glGetUniformLocation(program, "Texture"), 0); 
    glUniform1i(glGetUniformLocation(program, "Face"), 1); 
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TBO);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, TBO2);

        glBindVertexArray(VAO);
        glUseProgram(program);           // 激活程序
        glUniform1i(glGetUniformLocation(program, "Texture"), 0); 
        glUniform1i(glGetUniformLocation(program, "Face"), 1); 
        // 渲染管线
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		
		glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(program);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    

    glfwTerminate();

    return 0;
}

