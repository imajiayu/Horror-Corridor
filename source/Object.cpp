#include "../include/Object.h"

Lamp::Lamp(Model* lamp_model, glm::mat4 model_)
{
	//Object(lamp_model, model_, shader);
	//灯的着色器声明时默认初始化
	this->shader = lamp_shader;
	this->_model = lamp_model;
	this->model = model_;
}

void Lamp::render(Role* camera)
{
	shader->use();
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera->GetViewMatrix();
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
	model = glm::scale(model, glm::vec3(0.7));
	shader->setMat4("model", this->model);
	extern glm::vec3 pointLightOff;
	shader->setVec3("pointLightOff", pointLightOff);
	extern bool spotLightOff;
	shader->setVec3("spotLightOff", glm::vec3(spotLightOff));

	// spotLight
	shader->setVec3("spotLight.position", camera->Position);
	shader->setVec3("spotLight.direction", camera->Front);
	shader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	shader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	shader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	shader->setFloat("spotLight.constant", 1.0f);
	shader->setFloat("spotLight.linear", 0.09);
	shader->setFloat("spotLight.quadratic", 0.1);
	shader->setFloat("spotLight.cutOff", glm::cos(glm::radians(8.0f)));
	shader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

	shader->setVec3("viewPos", camera->Position);

	_model->Draw(*shader);
}


Paint::Paint(Model* paint_model, glm::mat4 model_) 
{
	this->shader = paint_shader;
	this->_model = paint_model;
	this->model = model_;
}

void Paint::render(Role* camera)
{
	shader->use();
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera->GetViewMatrix();
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
	model = glm::scale(model, glm::vec3(0.7));
	shader->setMat4("model", this->model);
	extern bool spotLightOff;
	shader->setVec3("spotLightOff", glm::vec3(spotLightOff));
	extern glm::vec3 pointLightOff;
	shader->setVec3("lightOff", pointLightOff);

	//fs
	shader->setVec3("viewPos", camera->Position);
	shader->setInt("material.diffuse", 0);
	shader->setInt("material.specular", 1);
	shader->setInt("material.normalMap", 2);
	shader->setFloat("material.shininess", 32.0f);

	// pointLight
	shader->setVec3("pointLight.ambient", 0.05f, 0.05f, 0.05f);
	shader->setVec3("pointLight.diffuse", 0.8f, 0.8f, 0.8f);
	shader->setVec3("pointLight.specular", 0.5f, 0.5f, 0.5f);
	shader->setFloat("pointLight.constant", 2.0f);
	shader->setFloat("pointLight.linear", 0.09);
	shader->setFloat("pointLight.quadratic", 0.032);

	// spotLight
	shader->setVec3("spotLight.position", camera->Position);
	shader->setVec3("spotLight.direction", camera->Front);
	shader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	shader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	shader->setVec3("spotLight.specular", 0.5f, 0.5f, 0.5f);
	shader->setFloat("spotLight.constant", 1.0f);
	shader->setFloat("spotLight.linear", 0.09);
	shader->setFloat("spotLight.quadratic", 0.032);
	shader->setFloat("spotLight.cutOff", glm::cos(glm::radians(8.0f)));
	shader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

	//shader->setVec3("viewPos", camera->Position);

	_model->Draw(*shader);
}


