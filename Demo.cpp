#include "Demo.h"
using namespace std;

Demo::Demo() {

}
Demo::~Demo() {
}

// Initialization Things
void Demo::Init() {
	// build and compile our shader program
	// ------------------------------------
	shaderProgram = BuildShader("vertexShader.vert", "fragmentShader.frag", nullptr);

	BuildColoredPlane();

	// Pedestrian
	BuildHead();
	BuildBody();
	BuildHand();
	BuildLeg();

	/*
	// Windmill
	BuildFoundation();
	BuildCenter();
	BuildPinwheel();
	BuildPropeller();

	// Lamp
	BuildLamp();

	// Hedge
	BuildHedge();

	// Tree
	BuildDarkOak();
	BuildBirch();
	BuildDarkLeaf();
	BuildBirchLeaf();

	// Road
	BuildCobble();
	BuildStone();
	/**/

	InitCamera();
}
void Demo::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO1);
	glDeleteBuffers(1, &VBO1);
	glDeleteBuffers(1, &EBO1);
	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO2);
	glDeleteVertexArrays(1, &VAO3);
	glDeleteBuffers(1, &VBO3);
	glDeleteBuffers(1, &EBO3);
	glDeleteVertexArrays(1, &VAO4);
	glDeleteBuffers(1, &VBO4);
	glDeleteBuffers(1, &EBO4);
	glDeleteVertexArrays(1, &VAO5);
	glDeleteBuffers(1, &VBO5);
	glDeleteBuffers(1, &EBO5);
	/*
	glDeleteVertexArrays(1, &VAO6);
	glDeleteBuffers(1, &VBO6);
	glDeleteBuffers(1, &EBO6);
	glDeleteVertexArrays(1, &VAO7);
	glDeleteBuffers(1, &VBO7);
	glDeleteBuffers(1, &EBO7);
	glDeleteVertexArrays(1, &VAO8);
	glDeleteBuffers(1, &VBO8);
	glDeleteBuffers(1, &EBO8);
	glDeleteVertexArrays(1, &VAO9);
	glDeleteBuffers(1, &VBO9);
	glDeleteBuffers(1, &EBO9);
	glDeleteVertexArrays(1, &VAO10);
	glDeleteBuffers(1, &VBO10);
	glDeleteBuffers(1, &EBO10);
	glDeleteVertexArrays(1, &VAO11);
	glDeleteBuffers(1, &VBO11);
	glDeleteBuffers(1, &EBO11);
	glDeleteVertexArrays(1, &VAO12);
	glDeleteBuffers(1, &VBO12);
	glDeleteBuffers(1, &EBO12);
	glDeleteVertexArrays(1, &VAO13);
	glDeleteBuffers(1, &VBO13);
	glDeleteBuffers(1, &EBO13);
	glDeleteVertexArrays(1, &VAO14);
	glDeleteBuffers(1, &VBO14);
	glDeleteBuffers(1, &EBO14);
	glDeleteVertexArrays(1, &VAO15);
	glDeleteBuffers(1, &VBO15);
	glDeleteBuffers(1, &EBO15);
	glDeleteVertexArrays(1, &VAO16);
	glDeleteBuffers(1, &VBO16);
	glDeleteBuffers(1, &EBO16);
	glDeleteVertexArrays(1, &VAO17);
	glDeleteBuffers(1, &VBO17);
	glDeleteBuffers(1, &EBO17);
	/**/
}

// Running Things
void Demo::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	
	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.01f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.01f;
		}
	}

	// update camera movement
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
		kakiTanganGerak = true;
		gerakBadan = 0;
		arahBadan = 0.0f;
	}
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
		kakiTanganGerak = true;
		gerakBadan = 3;
		arahBadan = 3.1f;
	}
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
		kakiTanganGerak = true;
		gerakBadan = 1;
		arahBadan = 1.6f;
	}
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
		kakiTanganGerak = true;
		gerakBadan = 2;
		arahBadan = -1.6f;
	}
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		kakiTanganGerak = true;
		gerakBadan = 4;
		arahBadan = 0.8f;
	}
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		kakiTanganGerak = true;
		gerakBadan = 5;
		arahBadan = -0.8f;
	}
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED/ 200);
		StrafeCamera(CAMERA_SPEED/ 200);
		kakiTanganGerak = true;
		gerakBadan = 6;
		arahBadan = -2.4f;
	}
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		kakiTanganGerak = true;
		gerakBadan = 7;
		arahBadan = 2.4f;
	}
	if (glfwGetKey(window, GLFW_KEY_W) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_A) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) != GLFW_PRESS) {
		kakiTanganGerak = false;
	}
}

void Demo::Update(double deltaTime) {
	angle += (float)((deltaTime * 1.5f) / 100);

	if ((lebarGerakan < -0.3f || lebarGerakan > 0.3f)) {
		speedX *= -1;
	}
	lebarGerakan += (float)((deltaTime * speedX) / 1000);

	if ((lebarGerakan < -0.3f || lebarGerakan > 0.3f)) {
		speedZ *= -1;
	}
	lebarGerakan += (float)((deltaTime * speedZ) / 1000);
}

void Demo::Render() {
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(55.0f / 255.0f, 198.0f / 255.0f, 255.0f / 255.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(fovy, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	GLint projLoc = glGetUniformLocation(this->shaderProgram, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// LookAt camera (position, target/direction, up)
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	GLint viewLoc = glGetUniformLocation(this->shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	// Set Lighting Attribute
	//GLint lightPosLoc = glGetUniormLocation(this->)

	// Pedestrian
	DrawHead();
	DrawBody();
	DrawHand(1, 1.3, 4, 0);
	DrawHand(2, -1.3, 4, 0);
	DrawLeg(1, -0.5, 1, 0);
	DrawLeg(2, 0.5, 1, 0);

	/*
	// Windmill
	DrawFoundation();

	DrawCenter(0, 10, 37.7, 5, 7.5, 0.5);
	DrawPinwheel(0, 0, 13.5, 37.5, 5, 0.5, 0.5);
	DrawPinwheel(0, 0, 10, 37.5, 5, 0.5, 0.5);
	DrawPinwheel(0, 0, 6.5, 37.5, 5, 0.5, 0.5);
	DrawPinwheel(0, -2.5, 10, 37.5, 0.5, 7.5, 0.5);
	DrawPinwheel(0, 0, 10, 37.5, 0.5, 7.5, 0.5);
	DrawPinwheel(0, 2.5, 10, 37.5, 0.5, 7.5, 0.5);

	DrawCenter(0, 25, 39, 1, 1, 5);
	DrawCenter(0, 25, 36.5, 1.5, 1.5, 1.5);
	DrawPinwheel(1, 0, 25, 36.5, 30, 2, 0.1);
	DrawPinwheel(1, 0, 25, 36.5, 2, 30, 0.1);
	DrawPropeller(0, 25, 37.5, 32, 4, 0.1);
	DrawPropeller(0, 25, 37.5, 4, 32, 0.1);

	// Lamp
	const int totalLamp = 2;
	double lampX[totalLamp] = {};
	double lampZ[totalLamp] = {};

	lampX[0] = 10;
	lampZ[0] = 0;

	lampX[1] = -10;
	lampZ[1] = 0;

	for (int i = 0; i < totalLamp; i++) {
		DrawPinwheel(0, lampX[i], 0, lampZ[i], 1.5, 0.5, 1.5);
		DrawCenter(lampX[i], 2, lampZ[i], 0.75, 3, 0.75);
		DrawPinwheel(0, lampX[i], 3, lampZ[i], 2, 0.5, 2);
		DrawLamp(lampX[i], 3.75, lampZ[i]);
	}
	
	// Hedge
	const int totalHedge = 4;
	double hedgeX[totalHedge] = {};
	double hedgeZ[totalHedge] = {};
	double hedgeXSize[totalHedge] = {};
	double hedgeZSize[totalHedge] = {};

	hedgeX[0] = 0;
	hedgeZ[0] = 20;
	hedgeXSize[0] = 15;
	hedgeZSize[0] = 5;

	hedgeX[1] = 0;
	hedgeZ[1] = -20;
	hedgeXSize[1] = 15;
	hedgeZSize[1] = 5;

	hedgeX[2] = 20;
	hedgeZ[2] = 20;
	hedgeXSize[2] = 5;
	hedgeZSize[2] = 15;

	hedgeX[3] = -20;
	hedgeZ[3] = 20;
	hedgeXSize[3] = 5;
	hedgeZSize[3] = 15;

	for (int i = 0; i < totalHedge; i++) {
		DrawPinwheel(0, hedgeX[i], 0, hedgeZ[i], hedgeXSize[i], 0.5, hedgeZSize[i]);
		DrawHedge(hedgeX[i], 3, hedgeZ[i], hedgeXSize[i], 5, hedgeZSize[i]);
	}

	// Tree
	const int totalTree = 2;
	double treeX[totalTree] = {};
	double treeZ[totalTree] = {};
	string treeType[totalTree] = {};

	treeX[0] = 20;
	treeZ[0] = 0;
	treeType[0] = "Oak";

	treeX[1] = -20;
	treeZ[1] = 0;
	treeType[1] = "Birch";

	for (int i = 0; i < totalTree; i++) {
		if (treeType[i] == "Oak") {
			DrawDarkOak(treeX[i], -0.5, treeZ[i], 1.5, 10, 1.5);
			DrawDarkLeaf(treeX[i]+1.5, 10, treeZ[i]-1, 4.5, 5, 4.5);
			DrawDarkLeaf(treeX[i]-1.5, 12.5, treeZ[i], 4.5, 5, 4.5);
			DrawDarkLeaf(treeX[i]-3, 9.5, treeZ[i]+1, 4.5, 5, 4.5);
		}
		else {
			

			DrawBirch(treeX[i], -0.5, treeZ[i], 1.5, 10, 1.5);
			DrawBirchLeaf(treeX[i] - 1.5, 10, treeZ[i] - 1, 4.5, 5, 4.5);
			DrawBirchLeaf(treeX[i] + 1.5, 12.5, treeZ[i], 4.5, 5, 4.5);
			DrawBirchLeaf(treeX[i] + 3, 9.5, treeZ[i] + 1, 4.5, 5, 4.5);
		}
	}

	// Road
	DrawCobble(0, -0.5, 0, 3, 0.1, 20);
	DrawStone(3, -0.5, 0, 3, 0.1, 20);
	DrawStone(-3, -0.5, 0, 3, 0.1, 20);
	/**/

	// Plane
	DrawColoredPlane();

	glDisable(GL_DEPTH_TEST);
}

// Plane Things
void Demo::BuildColoredPlane()
{
	// Load and create a texture 
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("grass.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	//// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-100.0, -0.5, -100.0,  0,  0,
		 100.0, -0.5, -100.0, 10,  0,
		 100.0, -0.5,  100.0, 10, 10,
		-100.0, -0.5,  100.0,  0, 10,
	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	glGenVertexArrays(1, &VAO1);
	glGenBuffers(1, &VBO1);
	glGenBuffers(1, &EBO1);

	glBindVertexArray(VAO1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
}
void Demo::DrawColoredPlane()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 1);

	glBindVertexArray(VAO1); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// Pedestrian Things
void Demo::BuildHead() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image(skinType.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, (2.0f / 16.0f), (4.0f / 8.0f),  // 0
		0.5, -0.5, 0.5,  (4.0f / 16.0f), (4.0f / 8.0f),   // 1
		0.5,  0.5, 0.5,  (4.0f / 16.0f), (6.0f / 8.0f),   // 2
		-0.5,  0.5, 0.5, (2.0f / 16.0f), (6.0f / 8.0f),  // 3

		// right	
		0.5, -0.5,  0.5, (4.0f / 16.0f), (4.0f / 8.0f),  // 4
		0.5, -0.5, -0.5, (6.0f / 16.0f), (4.0f / 8.0f),  // 5
		0.5,  0.5, -0.5, (6.0f / 16.0f), (6.0f / 8.0f),  // 6
		0.5,  0.5,  0.5, (4.0f / 16.0f), (6.0f / 8.0f),  // 7

		// back
		-0.5, -0.5, -0.5, (6.0f / 16.0f), (4.0f / 8.0f), // 8 
		0.5,  -0.5, -0.5, (8.0f / 16.0f), (4.0f / 8.0f), // 9
		0.5,   0.5, -0.5, (8.0f / 16.0f), (6.0f / 8.0f), // 10
		-0.5,  0.5, -0.5, (6.0f / 16.0f), (6.0f / 8.0f), // 11

		// left
		-0.5, -0.5, -0.5, (0.0f / 16.0f), (4.0f / 8.0f), // 12
		-0.5, -0.5,  0.5, (2.0f / 16.0f), (4.0f / 8.0f), // 13
		-0.5,  0.5,  0.5, (2.0f / 16.0f), (6.0f / 8.0f), // 14
		-0.5,  0.5, -0.5, (0.0f / 16.0f), (6.0f / 8.0f), // 15

		// upper
		0.5, 0.5,  0.5,  (2.0f / 16.0f), (6.0f / 8.0f),   // 16
		-0.5, 0.5,  0.5, (4.0f / 16.0f), (6.0f / 8.0f),  // 17
		-0.5, 0.5, -0.5, (4.0f / 16.0f), (8.0f / 8.0f),  // 18
		0.5, 0.5, -0.5,  (2.0f / 16.0f), (8.0f / 8.0f),  // 19

		// bottom
		-0.5, -0.5, -0.5, (4.0f / 16.0f), (6.0f / 8.0f), // 20
		0.5, -0.5, -0.5,  (6.0f / 16.0f), (6.0f / 8.0f),  // 21
		0.5, -0.5,  0.5,  (6.0f / 16.0f), (8.0f / 8.0f),  // 22
		-0.5, -0.5,  0.5, (4.0f / 16.0f), (8.0f / 8.0f), // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawHead()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO2); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(0 + pindahX, 6, 0 + pindahZ));

	model = glm::rotate(model, arahBadan, glm::vec3(0, 1, 0));

	model = glm::scale(model, glm::vec3(1.5, 1.5, 1.5));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildBody() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image(skinType.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, (5.0f / 16.0f), (0.0f / 8.0f),  // 0
		0.5, -0.5, 0.5,  (7.0f / 16.0f), (0.0f / 8.0f),   // 1
		0.5,  0.5, 0.5,  (7.0f / 16.0f), (3.0f / 8.0f),   // 2
		-0.5,  0.5, 0.5, (5.0f / 16.0f), (3.0f / 8.0f),  // 3

		// right	
		0.5, -0.5,  0.5, (4.0f / 16.0f), (0.0f / 8.0f),  // 4
		0.5, -0.5, -0.5, (5.0f / 16.0f), (0.0f / 8.0f),  // 5
		0.5,  0.5, -0.5, (5.0f / 16.0f), (3.0f / 8.0f),  // 6
		0.5,  0.5,  0.5, (4.0f / 16.0f), (3.0f / 8.0f),  // 7

		// back
		-0.5, -0.5, -0.5, (8.0f / 16.0f), (0.0f / 8.0f), // 8 
		0.5,  -0.5, -0.5, (10.0f / 16.0f), (0.0f / 8.0f), // 9
		0.5,   0.5, -0.5, (10.0f / 16.0f), (3.0f / 8.0f), // 10
		-0.5,  0.5, -0.5, (8.0f / 16.0f), (3.0f / 8.0f), // 11

		// left
		-0.5, -0.5, -0.5, (7.0f / 16.0f), (0.0f / 8.0f), // 12
		-0.5, -0.5,  0.5, (8.0f / 16.0f), (0.0f / 8.0f), // 13
		-0.5,  0.5,  0.5, (8.0f / 16.0f), (3.0f / 8.0f), // 14
		-0.5,  0.5, -0.5, (7.0f / 16.0f), (3.0f / 8.0f), // 15

		// upper
		0.5, 0.5,  0.5,  (5.0f / 16.0f), (3.0f / 8.0f),   // 16
		-0.5, 0.5,  0.5, (7.0f / 16.0f), (3.0f / 8.0f),  // 17
		-0.5, 0.5, -0.5, (7.0f / 16.0f), (4.0f / 8.0f),  // 18
		0.5, 0.5, -0.5,  (5.0f / 16.0f), (4.0f / 8.0f),  // 19

		// bottom
		-0.5, -0.5, -0.5, (7.0f / 16.0f), (3.0f / 8.0f), // 20
		0.5, -0.5, -0.5,  (9.0f / 16.0f), (3.0f / 8.0f),  // 21
		0.5, -0.5,  0.5,  (9.0f / 16.0f), (4.0f / 8.0f),  // 22
		-0.5, -0.5,  0.5, (7.0f / 16.0f), (4.0f / 8.0f), // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);
	glGenBuffers(1, &EBO3);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawBody()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO3); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(0+pindahX, 4, 0+pindahZ));

	model = glm::rotate(model, arahBadan, glm::vec3(0, 1, 0));

	model = glm::scale(model, glm::vec3(2, 3, 1));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildHand() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image(skinType.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, (11.0f / 16.0f), (0.0f / 8.0f),  // 0
		0.5, -0.5, 0.5,  (12.0f / 16.0f), (0.0f / 8.0f),   // 1
		0.5,  0.5, 0.5,  (12.0f / 16.0f), (3.0f / 8.0f),   // 2
		-0.5,  0.5, 0.5, (11.0f / 16.0f), (3.0f / 8.0f),  // 3

		// right	
		0.5, -0.5,  0.5, (10.0f / 16.0f), (0.0f / 8.0f),  // 4
		0.5, -0.5, -0.5, (11.0f / 16.0f), (0.0f / 8.0f),  // 5
		0.5,  0.5, -0.5, (11.0f / 16.0f), (3.0f / 8.0f),  // 6
		0.5,  0.5,  0.5, (10.0f / 16.0f), (3.0f / 8.0f),  // 7

		// back
		-0.5, -0.5, -0.5, (13.0f / 16.0f), (0.0f / 8.0f), // 8 
		0.5,  -0.5, -0.5, (14.0f / 16.0f), (0.0f / 8.0f), // 9
		0.5,   0.5, -0.5, (14.0f / 16.0f), (3.0f / 8.0f), // 10
		-0.5,  0.5, -0.5, (13.0f / 16.0f), (3.0f / 8.0f), // 11

		// left
		-0.5, -0.5, -0.5, (12.0f / 16.0f), (0.0f / 8.0f), // 12
		-0.5, -0.5,  0.5, (13.0f / 16.0f), (0.0f / 8.0f), // 13
		-0.5,  0.5,  0.5, (13.0f / 16.0f), (3.0f / 8.0f), // 14
		-0.5,  0.5, -0.5, (12.0f / 16.0f), (3.0f / 8.0f), // 15

		// upper
		0.5, 0.5,  0.5,  (11.0f / 16.0f), (3.0f / 8.0f),   // 16
		-0.5, 0.5,  0.5, (12.0f / 16.0f), (3.0f / 8.0f),  // 17
		-0.5, 0.5, -0.5, (12.0f / 16.0f), (4.0f / 8.0f),  // 18
		0.5, 0.5, -0.5,  (11.0f / 16.0f), (4.0f / 8.0f),  // 19

		// bottom
		-0.5, -0.5, -0.5, (12.0f / 16.0f), (3.0f / 8.0f), // 20
		0.5, -0.5, -0.5,  (13.0f / 16.0f), (3.0f / 8.0f),  // 21
		0.5, -0.5,  0.5,  (13.0f / 16.0f), (4.0f / 8.0f),  // 22
		-0.5, -0.5,  0.5, (12.0f / 16.0f), (4.0f / 8.0f), // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO4);
	glGenBuffers(1, &VBO4);
	glGenBuffers(1, &EBO4);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO4);

	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawHand(int rotate, double positionX, double positionY, double positionZ)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO4); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(pindahX, pindahY, pindahZ));

	model = glm::rotate(model, arahBadan, glm::vec3(0, 1, 0));

	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));

	if (kakiTanganGerak) {
		if (rotate == 1) {
			model = glm::rotate(model, lebarGerakan, glm::vec3(1, 0, 0));
		}
		else if (rotate == 2) {
			model = glm::rotate(model, -lebarGerakan, glm::vec3(1, 0, 0));
		}
	}

	model = glm::scale(model, glm::vec3(0.7, 3, 1));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildLeg() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image(skinType.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, (1.0f / 16.0f), (0.0f / 8.0f),  // 0
		0.5, -0.5, 0.5,  (2.0f / 16.0f), (0.0f / 8.0f),   // 1
		0.5,  0.5, 0.5,  (2.0f / 16.0f), (3.0f / 8.0f),   // 2
		-0.5,  0.5, 0.5, (1.0f / 16.0f), (3.0f / 8.0f),  // 3

		// right	
		0.5, -0.5,  0.5, (0.0f / 16.0f), (0.0f / 8.0f),  // 4
		0.5, -0.5, -0.5, (1.0f / 16.0f), (0.0f / 8.0f),  // 5
		0.5,  0.5, -0.5, (1.0f / 16.0f), (3.0f / 8.0f),  // 6
		0.5,  0.5,  0.5, (0.0f / 16.0f), (3.0f / 8.0f),  // 7

		// back
		-0.5, -0.5, -0.5, (3.0f / 16.0f), (0.0f / 8.0f), // 8 
		0.5,  -0.5, -0.5, (4.0f / 16.0f), (0.0f / 8.0f), // 9
		0.5,   0.5, -0.5, (4.0f / 16.0f), (3.0f / 8.0f), // 10
		-0.5,  0.5, -0.5, (3.0f / 16.0f), (3.0f / 8.0f), // 11

		// left
		-0.5, -0.5, -0.5, (2.0f / 16.0f), (0.0f / 8.0f), // 12
		-0.5, -0.5,  0.5, (3.0f / 16.0f), (0.0f / 8.0f), // 13
		-0.5,  0.5,  0.5, (3.0f / 16.0f), (3.0f / 8.0f), // 14
		-0.5,  0.5, -0.5, (2.0f / 16.0f), (3.0f / 8.0f), // 15

		// upper
		0.5, 0.5,  0.5,  (1.0f / 16.0f), (3.0f / 8.0f),   // 16
		-0.5, 0.5,  0.5, (2.0f / 16.0f), (3.0f / 8.0f),  // 17
		-0.5, 0.5, -0.5, (2.0f / 16.0f), (4.0f / 8.0f),  // 18
		0.5, 0.5, -0.5,  (1.0f / 16.0f), (4.0f / 8.0f),  // 19

		// bottom
		-0.5, -0.5, -0.5, (2.0f / 16.0f), (3.0f / 8.0f), // 20
		0.5, -0.5, -0.5,  (3.0f / 16.0f), (3.0f / 8.0f),  // 21
		0.5, -0.5,  0.5,  (3.0f / 16.0f), (4.0f / 8.0f),  // 22
		-0.5, -0.5,  0.5, (2.0f / 16.0f), (4.0f / 8.0f), // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO5);
	glGenBuffers(1, &VBO5);
	glGenBuffers(1, &EBO5);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO5);

	glBindBuffer(GL_ARRAY_BUFFER, VBO5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO5);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawLeg(int rotate, double positionX, double positionY, double positionZ)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO5); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(pindahX, pindahY, pindahZ));

	model = glm::rotate(model, arahBadan, glm::vec3(0, 1, 0));

	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));

	if (kakiTanganGerak) {
		if (rotate == 1) {
			model = glm::rotate(model, lebarGerakan, glm::vec3(1, 0, 0));
		}
		else if (rotate == 2) {
			model = glm::rotate(model, -lebarGerakan, glm::vec3(1, 0, 0));
		}
	}

	model = glm::scale(model, glm::vec3(1, 3, 1));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

/*
// Windmill Things
void Demo::BuildFoundation() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("redBrick.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -1, 0.9f,  0, 0,  // 0
		0.5, -1, 0.9f,   4, 0,  // 1
		0.25f, 1, 0.45f,  4, 4, // 2
		-0.25f, 1, 0.45f, 0, 4,  // 3

		// right1
		0.5, -1, 0.9f, 0, 0,  // 4
		1, -1, 0,      4, 0,  // 5
		0.5, 1, 0,     4, 4,  // 6
		0.25f, 1, 0.45f, 0, 4,  // 7

		// right2
		1, -1, 0,       0, 0, // 8 
		0.5f, -1, -0.9f,  4, 0, // 9
		0.25f, 1, -0.45f, 4, 4, // 10
		0.5, 1, 0,      0, 4, // 11

		// back
		0.5, -1, -0.9f,   0, 0, // 12
		-0.5, -1, -0.9f,  4, 0, // 13
		-0.25f, 1, -0.45f, 4, 4, // 14
		0.25f, 1, -0.45f,  0, 4, // 15

		// left2
		-0.5, -1, -0.9f,  0, 0, // 16
		-1, -1, 0,       4, 0, // 17
		-0.5, 1, 0,      4, 4, // 18
		-0.25f, 1, -0.45f, 0, 4, // 19

		// left1
		-1, -1, 0,      0, 0, // 20
		-0.5, -1, 0.9f,  4, 0, // 21
		-0.25f, 1, 0.45f, 4, 4, // 22
		-0.5, 1, 0,     0, 4, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO6);
	glGenBuffers(1, &VBO6);
	glGenBuffers(1, &EBO6);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO6);

	glBindBuffer(GL_ARRAY_BUFFER, VBO6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO6);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawFoundation()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO6); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(0, 0, 50));

	model = glm::scale(model, glm::vec3(20, 30, 20));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildCenter() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture4);
	glBindTexture(GL_TEXTURE_2D, texture4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("grayBrick.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO7);
	glGenBuffers(1, &VBO7);
	glGenBuffers(1, &EBO7);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO7);

	glBindBuffer(GL_ARRAY_BUFFER, VBO7);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO7);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawCenter(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture4);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO7); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));

	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildPinwheel() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture5);
	glBindTexture(GL_TEXTURE_2D, texture5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("whiteBrick.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO8);
	glGenBuffers(1, &VBO8);
	glGenBuffers(1, &EBO8);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO8);

	glBindBuffer(GL_ARRAY_BUFFER, VBO8);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO8);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawPinwheel(int rotate, double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture5);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO8); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));

	if (rotate == 1) {
		model = glm::rotate(model, angle, glm::vec3(0, 0, 1));
	}
	
	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildPropeller() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture8);
	glBindTexture(GL_TEXTURE_2D, texture8);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("propeller.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 10, 0, // 9
		0.5,   0.5, -0.5, 10, 10, // 10
		-0.5,  0.5, -0.5, 0, 10, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO11);
	glGenBuffers(1, &VBO11);
	glGenBuffers(1, &EBO11);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO11);

	glBindBuffer(GL_ARRAY_BUFFER, VBO11);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO11);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawPropeller(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture8);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO11); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));

	model = glm::rotate(model, angle, glm::vec3(0, 0, 1));

	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// Lamp Things
void Demo::BuildLamp() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture6);
	glBindTexture(GL_TEXTURE_2D, texture6);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("lamp.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO9);
	glGenBuffers(1, &VBO9);
	glGenBuffers(1, &EBO9);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO9);

	glBindBuffer(GL_ARRAY_BUFFER, VBO9);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO9);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawLamp(double positionX, double positionY, double positionZ)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture6);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO9); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));

	model = glm::scale(model, glm::vec3(1.25, 1.25, 1.25));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// Hedge Things
void Demo::BuildHedge() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("hedge.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 2, 0,   // 1
		0.5,  0.5, 0.5, 2, 2,   // 2
		-0.5,  0.5, 0.5, 0, 2,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 2, 0,  // 5
		0.5, -0.5, -0.5, 2, 2,  // 6
		0.5, -0.5,  0.5, 0, 2,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 2, 0, // 9
		0.5,   0.5, -0.5, 2, 2, // 10
		-0.5,  0.5, -0.5, 0, 2, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 2, 0, // 13
		-0.5,  0.5,  0.5, 2, 2, // 14
		-0.5,  0.5, -0.5, 0, 2, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 2, 0,  // 17
		-0.5, 0.5, -0.5, 2, 2,  // 18
		0.5, 0.5, -0.5, 0, 2,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 2, 0,  // 21
		0.5, -0.5,  0.5, 2, 2,  // 22
		-0.5, -0.5,  0.5, 0, 2, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO10);
	glGenBuffers(1, &VBO10);
	glGenBuffers(1, &EBO10);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO10);

	glBindBuffer(GL_ARRAY_BUFFER, VBO10);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO10);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawHedge(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture7);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO10); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));

	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// Tree Things
void Demo::BuildDarkOak() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture9);
	glBindTexture(GL_TEXTURE_2D, texture9);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("darkOak.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-1, 0, -1, 0, 0,  // 0
		1, 0, -1, 5, 0,   // 1
		0.25,  1, -0.25, 5, 5,   // 2
		-0.25,  1, -0.25, 0, 5,  // 3

		// right
		1, 0, -1, 0, 0,  // 0
		1, 0, 1, 5, 0,   // 1
		0.25,  1, 0.25, 5, 5,   // 2
		0.25,  1, -0.25, 0, 5,  // 3

		// back
		1, 0, 1, 0, 0,  // 0
		-1, 0, 1, 5, 0,   // 1
		-0.25,  1, 0.25, 5, 5,   // 2
		0.25,  1, 0.25, 0, 5,  // 3

		// left
		-1, 0, 1, 0, 0,  // 0
		-1, 0, -1, 5, 0,   // 1
		-0.25,  1, -0.25, 5, 5,   // 2
		-0.25,  1, 0.25, 5, 5,  // 3


	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14
	};

	glGenVertexArrays(1, &VAO12);
	glGenBuffers(1, &VBO12);
	glGenBuffers(1, &EBO12);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO12);

	glBindBuffer(GL_ARRAY_BUFFER, VBO12);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO12);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawDarkOak(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture9);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO12); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));

	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildBirch() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture10);
	glBindTexture(GL_TEXTURE_2D, texture10);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("birch.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-1, 0, -1, 0, 0,  // 0
		1, 0, -1, 5, 0,   // 1
		0.25,  1, -0.25, 5, 5,   // 2
		-0.25,  1, -0.25, 0, 5,  // 3

		// right
		1, 0, -1, 0, 0,  // 0
		1, 0, 1, 5, 0,   // 1
		0.25,  1, 0.25, 5, 5,   // 2
		0.25,  1, -0.25, 0, 5,  // 3

		// back
		1, 0, 1, 0, 0,  // 0
		-1, 0, 1, 5, 0,   // 1
		-0.25,  1, 0.25, 5, 5,   // 2
		0.25,  1, 0.25, 0, 5,  // 3

		// left
		-1, 0, 1, 0, 0,  // 0
		-1, 0, -1, 5, 0,   // 1
		-0.25,  1, -0.25, 5, 5,   // 2
		-0.25,  1, 0.25, 5, 5,  // 3


	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14
	};

	glGenVertexArrays(1, &VAO13);
	glGenBuffers(1, &VBO13);
	glGenBuffers(1, &EBO13);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO13);

	glBindBuffer(GL_ARRAY_BUFFER, VBO13);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO13);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawBirch(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture10);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO13); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));

	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildDarkLeaf() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture11);
	glBindTexture(GL_TEXTURE_2D, texture11);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("darkLeaf.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 5, 0,   // 1
		0.5,  0.5, 0.5, 5, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 5, 0,  // 5
		0.5, -0.5, -0.5, 5, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 5, 0, // 9
		0.5,   0.5, -0.5, 5, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 5, 0, // 13
		-0.5,  0.5,  0.5, 5, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 5, 0,  // 17
		-0.5, 0.5, -0.5, 5, 5,  // 18
		0.5, 0.5, -0.5, 0, 5,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 5, 0,  // 21
		0.5, -0.5,  0.5, 5, 5,  // 22
		-0.5, -0.5,  0.5, 0, 5, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO14);
	glGenBuffers(1, &VBO14);
	glGenBuffers(1, &EBO14);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO14);

	glBindBuffer(GL_ARRAY_BUFFER, VBO14);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO14);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawDarkLeaf(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture11);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO14); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));

	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildBirchLeaf() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture12);
	glBindTexture(GL_TEXTURE_2D, texture12);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("birchLeaf.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO15);
	glGenBuffers(1, &VBO15);
	glGenBuffers(1, &EBO15);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO15);

	glBindBuffer(GL_ARRAY_BUFFER, VBO15);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO15);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawBirchLeaf(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture12);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO14); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));

	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// Road Things
void Demo::BuildCobble() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture13);
	glBindTexture(GL_TEXTURE_2D, texture13);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("cobble.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 5,  // 18
		0.5, 0.5, -0.5, 0, 5,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO16);
	glGenBuffers(1, &VBO16);
	glGenBuffers(1, &EBO16);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO16);

	glBindBuffer(GL_ARRAY_BUFFER, VBO16);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO16);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawCobble(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture13);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO16); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));

	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildStone() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture14);
	glBindTexture(GL_TEXTURE_2D, texture14);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("stone.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 5,  // 18
		0.5, 0.5, -0.5, 0, 5,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO17);
	glGenBuffers(1, &VBO17);
	glGenBuffers(1, &EBO17);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO17);

	glBindBuffer(GL_ARRAY_BUFFER, VBO17);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO17);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawStone(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture14);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO17); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));

	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
/**/

// Camera Things
void Demo::InitCamera()
{
	posCamX = 0.0;
	posCamY = 12.5;
	posCamZ = -20.0;
	viewCamX = 0.0;
	viewCamY = 6.5;
	viewCamZ = 0.0;
	upCamX = 0.0;
	upCamY = 1.0;
	upCamZ = 0.0;
	CAMERA_SPEED = 0.01f;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void Demo::MoveCamera(float speed)
{
	double x = (viewCamX - posCamX) / 2;
	double z = (viewCamZ - posCamZ) / 2;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
	pindahX += x * speed;
	pindahZ += z * speed;
}
void Demo::StrafeCamera(float speed)
{
	double x = (viewCamX - posCamX)/2;
	double z = (viewCamZ - posCamZ)/2;
	double orthoX = -z;
	double orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
	pindahX += orthoX * speed;
	pindahZ += orthoZ * speed;
}

int main(int argc, char** argv) {
	RenderEngine &app = Demo();
	app.Start("Taman Kincir Angin", 1280, 720, true, false);
}