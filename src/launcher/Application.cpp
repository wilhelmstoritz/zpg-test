#include "Application.h"
#include "data.h"

// --- callbacks ---------------------------------------------------------------
static void callbackError(int t_error, const char* t_description) { fputs(t_description, stderr); }
static void callbackKey(GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods) {
	if (t_key == GLFW_KEY_ESCAPE && t_action == GLFW_PRESS)
		glfwSetWindowShouldClose(t_window, GL_TRUE);

	printf("callback:key [%d,%d,%d,%d]\n", t_key, t_scancode, t_action, t_mods);
}
static void callbackWindowFocus(GLFWwindow* t_window, int t_focused) { printf("callback:window_focus\n"); }
static void callbackWindowIconify(GLFWwindow* t_window, int t_iconified) { printf("callback:window_iconify\n"); }
static void callbackWindowSize(GLFWwindow* t_window, int t_width, int t_height) {
	glViewport(0, 0, t_width, t_height);

	printf("callback:window_size %d, %d\n", t_width, t_height);
}
static void callbackCursor(GLFWwindow* t_window, double t_x, double t_y) { printf("callback:cursor\n"); }
static void callbackButton(GLFWwindow* t_window, int t_button, int t_action, int t_mode) {
	if (t_action == GLFW_PRESS) printf("callback:button [%d,%d,%d]\n", t_button, t_action, t_mode);
}

// initialization of static class members
//Application* Application::_instance = nullptr;
std::unique_ptr<Application> Application::_instance = nullptr;
std::mutex Application::_mtx;

// --- public ------------------------------------------------------------------
Application* Application::getInstance() {
	std::lock_guard<std::mutex> lock(_mtx);
	if (_instance == nullptr) {
		//_instance = new Application();
		_instance.reset(new Application());
	}

	//return _instance;
	return _instance.get();
}

void Application::addShader(const std::string t_name, MyShader* t_shader) { this->m_shaders[t_name] = t_shader; }
void Application::addShaderProgram(const std::string t_name, MyShaderProgram* t_shaderProgram) { this->m_shaderPrograms[t_name] = t_shaderProgram; }
void Application::addVBO(const std::string t_name, MyVBO* t_VBO) { this->m_VBOs[t_name] = t_VBO; }
void Application::addVAO(const std::string t_name, MyVAO* t_VAO) { this->m_VAOs[t_name] = t_VAO; }

MyShader* Application::getShader(const std::string t_name) { return this->m_shaders[t_name]; }
MyShaderProgram* Application::getShaderProgram(const std::string t_name) { return this->m_shaderPrograms[t_name]; }
MyVBO* Application::getVBO(const std::string t_name) { return this->m_VBOs[t_name]; }
MyVAO* Application::getVAO(const std::string t_name) { return this->m_VAOs[t_name]; }

void Application::addRenderingData(MyShaderProgram* t_shaderProgram, MyVAO* t_VAO, GLint t_first, GLsizei t_count) {
	this->m_renderingData.push_back(renderingDataT(t_shaderProgram, t_VAO, t_first, t_count));
}

void Application::createShaders() {
	// vertex shaders
	MyVertexShader* myVertexShader = new MyVertexShader(DEFAULT_VERTEX_SHADER);
	this->addShader("v_default", myVertexShader);

	myVertexShader = new MyVertexShader(DEFAULT_VERTEX_SHADER_COLORFROMPOSITION);
	this->addShader("v_defaultColorFromPosition", myVertexShader);

	myVertexShader = new MyVertexShader(DEFAULT_VERTEX_SHADER_COLORDATA);
	this->addShader("v_defaultColorData", myVertexShader);

	// fragment shaders
	MyFragmentShader* myFragmentShader = new MyFragmentShader(DEFAULT_FRAGMENT_SHADER);
	this->addShader("f_default", myFragmentShader);

	myFragmentShader = new MyFragmentShader(DEFAULT_FRAGMENT_SHADER_COLORFROMPOSITION);
	this->addShader("f_defaultColorFromPosition", myFragmentShader);

	myFragmentShader = new MyFragmentShader(DEFAULT_FRAGMENT_SHADER_COLORDATA);
	this->addShader("f_defaultColorData", myFragmentShader);

	myFragmentShader = new MyFragmentShader(YELLOW_FRAGMENT_SHADER);
	this->addShader("f_yellow", myFragmentShader);

	// shader programs
	MyShaderProgram* myShaderProgram = new MyShaderProgram(*this->getShader("v_default"), *this->getShader("f_default"));
	this->addShaderProgram("default", myShaderProgram);

	myShaderProgram = new MyShaderProgram(*this->getShader("v_defaultColorFromPosition"), *this->getShader("f_defaultColorFromPosition"));
	this->addShaderProgram("defaultColorFromPosition", myShaderProgram);

	myShaderProgram = new MyShaderProgram(*this->getShader("v_defaultColorData"), *this->getShader("f_defaultColorData"));
	this->addShaderProgram("defaultColorData", myShaderProgram);

	myShaderProgram = new MyShaderProgram(*this->getShader("v_default"), *this->getShader("f_yellow"));
	this->addShaderProgram("yellow", myShaderProgram);
}

void Application::createModels() {
	// VBOs
	MyVBO* myVBO = new MyVBO(TRIANGLE_POINTS);
	this->addVBO("triangle", myVBO);

	myVBO = new MyVBO(TRIANGLE_POINTS_COLORDATA);
	this->addVBO("triangleColorData", myVBO);

	myVBO = new MyVBO(SQUARE_POINTS);
	this->addVBO("square", myVBO);

	// VAOs
	MyVAO* myVAO = new MyVAO();
	myVAO->addBuffer(*this->getVBO("triangle"), 0, 3, 0, NULL);
	this->addVAO("triangle", myVAO);

	myVAO = new MyVAO();
	myVAO->addBuffer(*this->getVBO("triangleColorData"), 0, 3, 6 * sizeof(float), (void*)0);
	myVAO->addBuffer(*this->getVBO("triangleColorData"), 1, 3, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	this->addVAO("triangleColorData", myVAO);

	myVAO = new MyVAO();
	myVAO->addBuffer(*this->getVBO("square"), 0, 3, 0, NULL);
	this->addVAO("square", myVAO);
}

void Application::createRenderingData() {
	// shader program + VAO = data to render
	//this->addRenderingData(this->getShaderProgram("default"), this->getVAO("triangle"), 0, 3);
	//this->addRenderingData(this->getShaderProgram("defaultColorFromPosition"), this->getVAO("triangle"), 0, 3);
	this->addRenderingData(this->getShaderProgram("defaultColorData"), this->getVAO("triangleColorData"), 0, 3);

	this->addRenderingData(this->getShaderProgram("yellow"), this->getVAO("square"), 0, 6);
}

void Application::run() {
	// rendering loop
	while (!glfwWindowShouldClose(this->m_window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// iterate thru draw data
		for (renderingDataT renderingData : this->m_renderingData) {
			renderingData.shaderProgram->use();
			renderingData.VAO->bind();
			glDrawArrays(GL_TRIANGLES, renderingData.first, renderingData.count);
		}

		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(this->m_window);
	}

	glfwDestroyWindow(this->m_window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}

// --- private -----------------------------------------------------------------
Application::Application() {
	this->init();
}

Application::~Application() {
	// cleanup
	for (const auto& item : this->m_VAOs) delete(item.second);
	for (const auto& item : this->m_VBOs) delete(item.second);
	for (const auto& item : this->m_shaderPrograms) delete(item.second);
	for (const auto& item : this->m_shaders) delete(item.second);
}

void Application::init() {
	glfwSetErrorCallback(callbackError);

	this->initWindow();

	// version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}

void Application::initWindow() {
	// init window
	if (!glfwInit()) {
		fprintf(stderr, "error >> could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	/*// inicializace konkretni verze
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //*/

	this->m_window = glfwCreateWindow(800, 600, "myZPG", NULL, NULL);
	if (!this->m_window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->m_window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// helpers
	int width, height;
	glfwGetFramebufferSize(this->m_window, &width, &height);
	glViewport(0, 0, width, height);

	float ratio = width / (float)height;
}



/*
void Application::addVertexShader(const std::string t_name, const char* t_source) {
	MyShader* shader = new MyVertexShader(t_source);
	this->m_shaders[t_name] = shader;
}

void Application::addFragmentShader(const std::string t_name, const char* t_source) {
	MyShader* shader = new MyFragmentShader(t_source);
	this->m_shaders[t_name] = shader;
}
*/
