EXEC = triangle
$(EXEC): demo.cc /opt/glad/src/glad.c
	g++ -o $@ $^ -lpthread -lglfw -lGL 
clean:
	rm -f $(EXEC)