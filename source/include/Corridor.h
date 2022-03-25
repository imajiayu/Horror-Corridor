#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "../include/shader_m.h"
#include "../include/model.h"
#include "../include/parameter.h"
#include "../include/Role.h"
#include"../include/Object.h"

enum corridorType //走廊类型
{
	straightCorridor,
	cornerCorridorL,
	cornerCorridorR,
	stairsCorridorU,
	stairsCorridorD
};

enum corridorDir //方向
{
	xP,
	zP,
	xN,
	zN
};

const int STAIRS_NUM = 20;

// debug
const char *const corrider_typename[] = {
	"straight",
	"cornerL",
	"cornerR",
	"stairsU",
	"stairsD",
	NULL};

class Corridor
{
public:
	corridorType type; //走廊类型
	corridorDir dir;   //方向
	glm::vec3 loc;	   //左下角的坐标

	glm::vec3 inf;	 //接口的左下角坐标
	glm::mat4 model; //变换矩阵
	Shader* shader;	 //着色器
	Model *_model;	 //模型类
	glm::vec3 lightPos;

	// std::vector<Object> objectList;走廊中物体列表
	Model* lamp_model;
	glm::mat4 lamp_pos; //灯变换矩阵
	glm::mat4 paint_pos1; //画变换矩阵1
	glm::mat4 paint_pos2; //画变换矩阵2
	glm::mat4 table_pos;
	glm::mat4 horse_pos;
	glm::mat4 bookcase_pos;

	int t1;
	int t2;

	bool is_back;

public:
	Corridor();
	Corridor(Model *corridor_model, corridorType type, corridorDir dir_, glm::mat4 model_); //根据走廊类型生成走廊
	void render(Role *camera);																																				//渲染前设定位置
	void setInCorridor(Role *camera);																																				// 碰撞检测，限制人物在走廊中
	bool isInCorridor(Role *camera);																																				//是否处于当前走廊之中

protected:
	float stairsPos(float stairs_z, float role_z);
};
