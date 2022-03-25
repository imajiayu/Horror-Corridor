#pragma once
#include "Corridor.h"
#include "model.h"
#include "Role.h"
#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <queue>
#include "../include/mySound.h"


enum camera_pos
{
	front,
	mid,
	back
};

class Scene
{
	std::vector<Corridor> corridorList;

public:
	Scene(Role *camera);
	~Scene();
	corridorType genNewCorridor(corridorType mid); //���ݵ�ǰ�м����� ����һ��������
	void updateCorridor();						   //�ı����ȶ���
	void render();
	camera_pos getPos();
	void lightTwinkle();

public:
	Role *camera;
	camera_pos pos;
	glm::mat4 mid_model; //���ȱ任����
	glm::mat4 front_model;
	glm::mat4 back_model;
	glm::vec3 mid_if; //�ӿ�����
	glm::vec3 front_if;
	glm::vec3 back_if;

	queue<glm::vec3> cameraPos;
	glm::vec3 ghostPos;
};
