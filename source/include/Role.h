#if !defined(ROLE_H)
#define ROLE_H

#include "camera.h"
//#include "Scene.h"

const float ROLE_HEIGHT = 1.3; // 人物高
const float ROLE_WIDTH = 0.5;  // 人物宽
// const float ROLE_RANGE = 0.4;  // 人物前后距离

class Role : public Camera
{
public:
	//基点和观察点在顶面正方体中心
	// constructor with vectors
	Role(glm::vec3 position = glm::vec3(ROLE_WIDTH / 2, ROLE_HEIGHT, -ROLE_WIDTH / 2), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH, float height = ROLE_HEIGHT, float width = ROLE_WIDTH)
		: Camera(position, up, yaw, pitch), height(height), width(width)
	{
		position = glm::vec3(width / 2, height, -width / 2);
	}
	// constructor with scalar values
	// Role(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch, float height = ROLE_HEIGHT, float width = ROLE_WIDTH, float range = ROLE_RANGE)
	// 	: Camera(posX, posY, posZ, upX, upY, upZ, yaw, pitch), height(height), width(width), range(range) {}

	// void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	// {
	// 	float velocity = MovementSpeed * deltaTime;
	// 	if (direction == FORWARD)
	// 		Position += Front * velocity;
	// 	if (direction == BACKWARD)
	// 		Position -= Front * velocity;
	// 	if (direction == LEFT)
	// 		Position -= Right * velocity;
	// 	if (direction == RIGHT)
	// 		Position += Right * velocity;
	// 	glm::vec3 pos_rf = Position + Right * width + Front * range;
	// 	glm::vec3 pos_lf = Position + Front * range;
	// 	glm::vec3 pos_rb = Position + Right * width;
	// 	// Position必须位于地板上
	// }

public:
	float height;
	float width;
	// float range;
};

#endif // ROLE_H