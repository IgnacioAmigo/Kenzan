#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>
#include <stdio.h>
#include <stdlib.h>
#include<vector>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
//"ヒーロー見参" en UTF-8
const char* WINDOW_TITLE = "\xE3\x83\x92\xE3\x83\xBC\xE3\x83\xAD\xE3\x83\xBC\xE8\xA6\x8B\xE5\x8F\x82";

bool m_running = true;


#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))


SDL_Window* m_window = NULL;

GLuint shaders[2];
GLuint vao;
GLuint offsetLocation;
GLuint timeLocation;
GLuint loopDurationLocation;
GLuint fragloopDurationLocation;

GLuint offsetUniform;

GLuint frustumScaleUnif;
GLuint zNearUnif, zFarUnif;

/*renderer shiet*/
GLuint positionBufferObject;
const float vertexPositions[] = {
	 0.25f,  0.25f, -1.25f, 1.0f,
	 0.25f, -0.25f, -1.25f, 1.0f,
	-0.25f,  0.25f, -1.25f, 1.0f,

	 0.25f, -0.25f, -1.25f, 1.0f,
	-0.25f, -0.25f, -1.25f, 1.0f,
	-0.25f,  0.25f, -1.25f, 1.0f,

	 0.25f,  0.25f, -2.75f, 1.0f,
	-0.25f,  0.25f, -2.75f, 1.0f,
	 0.25f, -0.25f, -2.75f, 1.0f,

	 0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f,  0.25f, -2.75f, 1.0f,
	-0.25f, -0.25f, -2.75f, 1.0f,

	-0.25f,  0.25f, -1.25f, 1.0f,
	-0.25f, -0.25f, -1.25f, 1.0f,
	-0.25f, -0.25f, -2.75f, 1.0f,

	-0.25f,  0.25f, -1.25f, 1.0f,
	-0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f,  0.25f, -2.75f, 1.0f,

	 0.25f,  0.25f, -1.25f, 1.0f,
	 0.25f, -0.25f, -2.75f, 1.0f,
	 0.25f, -0.25f, -1.25f, 1.0f,

	 0.25f,  0.25f, -1.25f, 1.0f,
	 0.25f,  0.25f, -2.75f, 1.0f,
	 0.25f, -0.25f, -2.75f, 1.0f,

	 0.25f,  0.25f, -2.75f, 1.0f,
	 0.25f,  0.25f, -1.25f, 1.0f,
	-0.25f,  0.25f, -1.25f, 1.0f,

	 0.25f,  0.25f, -2.75f, 1.0f,
	-0.25f,  0.25f, -1.25f, 1.0f,
	-0.25f,  0.25f, -2.75f, 1.0f,

	 0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f, -0.25f, -1.25f, 1.0f,
	 0.25f, -0.25f, -1.25f, 1.0f,

	 0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f, -0.25f, -1.25f, 1.0f,




	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,

	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,

	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,

	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,

	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,

	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,

	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,

	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,

	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,

	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,

};


void ComputePositionOffsets(float &fXOffset, float &fYOffset)
{
	const float fLoopDuration = 5.0f;
	const float fScale = 3.14159f * 2.0f / fLoopDuration;

	float fElapsedTime = SDL_GetTicks() / 1000.0f;

	float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);

	fXOffset = cosf(fCurrTimeThroughLoop * fScale) ;
	fYOffset = sinf(fCurrTimeThroughLoop * fScale);
}

void AdjustVertexData(float fXOffset, float fYOffset)
{
	/*std::vector<float> fNewData(ARRAY_COUNT(vertexPositions));
	memcpy(&fNewData[0], vertexPositions, sizeof(vertexPositions));

	for (int iVertex = 0; iVertex < ARRAY_COUNT(vertexPositions); iVertex += 4)
	{
		fNewData[iVertex] += fXOffset;
		fNewData[iVertex + 1] += fYOffset;
	}

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexPositions), &fNewData[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/
}


GLuint CreateShader(GLenum eShaderType, char* strShaderFile)
{

 	GLuint shader = glCreateShader(eShaderType);
	const char *strFileData = strShaderFile;
	glShaderSource(shader, 1, &strFileData, NULL);

	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch (eShaderType)
		{
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}

	return shader;
}



GLuint CreateProgram(GLuint* shaderList, int listSize)
{
	GLuint program = glCreateProgram();

	for (size_t iLoop = 0; iLoop < listSize; iLoop++)
		glAttachShader(program, shaderList[iLoop]);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
	
	return program;
}


void InitializeVertexBuffer()
{
	glGenBuffers(1, &positionBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

char* ReadFile(char* filename) {
	FILE *f;
	fopen_s(&f,filename, "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET); 

	char *string = (char*) malloc(fsize + 1);
	fread(string, fsize, 1, f);
	fclose(f);

	string[fsize] = 0;
	return string;
}


GLuint theProgram;

void InitializeProgram()
{	
	char* tempBuffer = ReadFile("./Renderer/Shaders/vertex_shader.glsl");
	shaders[0] = (CreateShader(GL_VERTEX_SHADER, tempBuffer));
	free(tempBuffer);
	tempBuffer = ReadFile("./Renderer/Shaders/plain_fragment_shader.glsl");
	shaders[1] = (CreateShader(GL_FRAGMENT_SHADER, tempBuffer));
	free(tempBuffer);

	theProgram = CreateProgram(shaders,2);

	offsetLocation = glGetUniformLocation(theProgram, "offset");
	timeLocation = glGetUniformLocation(theProgram, "time");
	loopDurationLocation = glGetUniformLocation(theProgram, "loopDuration");
	fragloopDurationLocation = glGetUniformLocation(theProgram, "fragloopDuration");
	glUseProgram(theProgram);
	glUniform1f(loopDurationLocation, 5.0f);
	glUniform1f(fragloopDurationLocation, 1.0f);
	glUseProgram(0);
	frustumScaleUnif = glGetUniformLocation(theProgram, "frustumScale");
	zNearUnif = glGetUniformLocation(theProgram, "zNear");
	zFarUnif = glGetUniformLocation(theProgram, "zFar");

	glUseProgram(theProgram);
	glUniform1f(frustumScaleUnif, 1.0f);
	glUniform1f(zNearUnif, 1.0f);
	glUniform1f(zFarUnif, 300.0f);


	glDeleteShader(shaders[0]);
	glDeleteShader(shaders[1]);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
}

void init_opengl_context(SDL_Window* _window) {


	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GLContext m_context = SDL_GL_CreateContext(_window);

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
	}


	//Use Vsync
	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	}
	//glEnable(GL_DEPTH_TEST); // enable depth-testing
	//glDepthFunc(GL_LESS);
	glewExperimental = GL_TRUE;
	printf("OpenGL loaded\n");
	printf("Vendor:   %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version:  %s\n", glGetString(GL_VERSION));

}

void draw(float a) {

	glClearColor(0.5, (a++ / 1000.f), 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	float fXOffset = 0.0f, fYOffset = 0.0f;
	ComputePositionOffsets(fXOffset, fYOffset);
	AdjustVertexData(fXOffset, fYOffset);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(theProgram);
	glUniform2f(offsetLocation, fXOffset, fYOffset);
	glUniform1f(timeLocation, SDL_GetTicks()/1000.0f);


	size_t colorData = sizeof(vertexPositions) / 2;
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorData);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glUseProgram(0);


	SDL_GL_SwapWindow(m_window);
}

int main(int argc, char *args[]) {
	m_window = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		m_window = SDL_CreateWindow(
			WINDOW_TITLE,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_OPENGL
		);

		init_opengl_context(m_window);
		InitializeVertexBuffer();
		InitializeProgram();
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		float a = 0;
		float fScaleAddition = 0.f;
		while (m_running){
			SDL_Event ev;

			while (SDL_PollEvent(&ev)) {
				if (ev.type == SDL_QUIT)
					m_running = false;
				else
					if (ev.type == SDL_KEYDOWN) {
						glUseProgram(theProgram);
						if (ev.key.keysym.sym ==SDLK_UP){
							fScaleAddition += 0.1f;
						}
						else if (ev.key.keysym.sym == SDLK_DOWN) {
							fScaleAddition -= 0.1f;
						}
						glUniform1f(frustumScaleUnif, 1.0f+fScaleAddition);
						glUseProgram(0);

					}
			}
			
			draw(a);
		}
	}
	// Your code here
	return 0;
}

