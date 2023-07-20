EXEC = transform
$(EXEC): demo.cc /opt/glad/src/glad.c
	g++ -o $@ $^ -lpthread -lglfw -lGL -I/mycode/company_study/opengl_study/texture/include/glm/glm
clean:
	rm -f $(EXEC)
