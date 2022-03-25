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
	glm::mat4 model; //�任����
	Shader* shader;
	//����ʵ�ֵĳ�Աto be added

public: 
	//��ʼ���ƣ���ɫ��
	Lamp(Model* lamp_model, glm::mat4 model_);
	void render(Role*camera);
};

class Paint
{
public:
	Model* _model;
	glm::mat4 model; //�任����
	Shader* shader;
	//����ʵ�ֵĳ�Աto be added

public:
	//��ʼ���ƣ���ɫ��
	Paint(Model* paint_model, glm::mat4 model_);
	void render(Role* camera);
};



