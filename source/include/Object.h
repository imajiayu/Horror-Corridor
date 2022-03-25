#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/shader_m.h"
#include "../include/model.h"
#include "../include/parameter.h"
#include"../include/Role.h"

class Lamp
{	
public:
	Model* _model;
	glm::mat4 model; //变换矩阵
	Shader* shader;
	//发光实现的成员to be added

public: 
	//初始化灯，着色器
	Lamp(Model* lamp_model, glm::mat4 model_);
	void render(Role*camera);
};

class Paint
{
public:
	Model* _model;
	glm::mat4 model; //变换矩阵
	Shader* shader;
	//发光实现的成员to be added

public:
	//初始化灯，着色器
	Paint(Model* paint_model, glm::mat4 model_);
	void render(Role* camera);
};



