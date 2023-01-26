#include <VoxelToy/Graphics/OpenGLContext.hpp>
#include <VoxelToy/Graphics/Renderer.hpp>
#include <VoxelToy/Graphics/Shader.hpp>
#include <VoxelToy/Graphics/Texture.hpp>
#include <VoxelToy/Graphics/VertexArray.hpp>
#include <VoxelToy/Graphics/VertexBuffer.hpp>

//#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <VoxelToy/Window/Window.hpp>

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0f;
float lastY =  600.0f / 2.0f;
float fov   =  45.0f;
//float cameraSpeed = 2.5f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void processInput(GLFWwindow *window);


const unsigned int SCR_WIDTH = 2400;
const unsigned int SCR_HEIGHT = 1200;

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


int main(int argc, char** argv)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////	glfw setups /////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto window = std::make_unique<VoxelToy::Window>();
	window->CreateWindow();


	glfwSetFramebufferSizeCallback(window->GetWindow(), framebuffer_size_callback);
	glfwSetCursorPosCallback(window->GetWindow(), mouse_callback);
	glfwSetScrollCallback(window->GetWindow(), scroll_callback);
	glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	VoxelToy::OpenGLContext GLContext (window->m_Window);
	GLContext.Init();

	VoxelToy::Renderer::Init();

    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f)
    };

	auto VAO = std::make_unique<VoxelToy::VertexArray>();
	auto VBO = std::make_unique<VoxelToy::VertexBuffer>(vertices, sizeof(vertices));
	auto layout = std::make_unique<VoxelToy::VertexBufferLayout>();
	layout->Push<float>(3);
	layout->Push<float>(2);
	VAO->AddVertexBuffer(*VBO, *layout);

	auto ourShader = std::make_unique<VoxelToy::Shader>(RESOURCES_DIR "/shader/camera.vs", RESOURCES_DIR "/shader/camera.fs");
	auto ourTexture = std::make_unique<VoxelToy::Texture>(RESOURCES_DIR "/texture/block/lime_concrete_powder.png");
    ourShader->Bind();
	ourTexture->Bind(0);
    ourShader->SetUniform1i("texture1", 0);


    /* Loop until the user closes the window */
    while (!window->ShouldWindowbeClosed())
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

		processInput(window->GetWindow());

		VoxelToy::Renderer::SetClearColor(glm::vec4(0.3f, 0.77f, 1.0f, 0.0f));
        VoxelToy::Renderer::Clear();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(fov), static_cast<float>(window->SCR_WIDTH) / static_cast<float>(window->SCR_HEIGHT) , 0.1f, 100.0f);
        ourShader->SetUniformMat4f("projection", projection);

        // camera/view transformation
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        ourShader->SetUniformMat4f("view", view);

		for(int i=-10; i<10; ++i)
		{
			for(int j=-10; j<10; ++j)
			{
				glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
				model = glm::translate(model, glm::vec3((float)i, 0, (float)j));
				//			float angle = 50.0f ;
				//			model = glm::rotate(model, glm::radians(angle), glm::vec3(5.0f, 5.0f, 0.0f));
				ourShader->SetUniformMat4f("model", model);
				VoxelToy::Renderer::Draw();
			}
		}

//		for(auto cubePosition : cubePositions)
//		{
//			// calculate the model matrix for each object and pass it to shader before drawing
//			glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//			model = glm::translate(model, cubePosition);
////			float angle = 50.0f ;
////			model = glm::rotate(model, glm::radians(angle), glm::vec3(5.0f, 5.0f, 0.0f));
//			ourShader->SetUniformMat4f("model", model);
//			VoxelToy::Renderer::Draw();
//		}

        window->SwapBuffer();
		window->PollEvents();
    }
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	(void)window;
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	(void)window;
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	(void) window; (void) xoffset;
	fov -= static_cast<float>(yoffset);
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}


void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = static_cast<float>(2.5f * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}



