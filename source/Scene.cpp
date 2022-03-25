#include "../include/Scene.h"

mySoundEngline SSound;

Scene::Scene(Role* camera)
{
	pos = mid;
	//初始化时随机加入三个场景，相机位置处在中间场景中
	mid_model = front_model = back_model = glm::mat4(1.0f);
	//中间走廊
	Corridor corridor_mid(straight_model, straightCorridor, zN, glm::mat4(1.0f));
	corridor_mid.lamp_model = lamp_model;
	//后走廊
	back_model = glm::translate(back_model, glm::vec3(2, 0, 0));
	back_model = glm::rotate(back_model, glm::radians(180.0f), glm::vec3(0, 1.0, 0));
	Corridor corridor_back(cornerR_model, cornerCorridorR, zP, back_model);
	corridor_back.lamp_model = lamp_model;
	//前走廊
	front_model = glm::translate(front_model, glm::vec3(0.0f, 0.0f, -10.0f));
	Corridor corridor_front(stairU_model, stairsCorridorU, zN, front_model);
	corridor_front.lamp_model = lamp_model;

	//入队列
	corridorList.push_back(corridor_front);
	corridorList.push_back(corridor_mid);
	corridorList.push_back(corridor_back);

	this->camera = camera;

	ghostPos = glm::vec3(1, 1.3, -5);
}

Scene::~Scene()
{
	delete straight_model;
	delete cornerL_model;
	delete cornerR_model;
	delete stairU_model;
	delete stairD_model;
}

void Scene::updateCorridor() //判断相机位置，生成新的走廊，放在应该放的地方
{
	if ((pos = getPos()) == mid) //在中间走廊无需操作
		return;

	corridorType newCorridorType;
	corridorDir newCorridorDir;

	Corridor* temp = NULL;
	Corridor* temp1 = NULL;
	if (pos == front)
	{
		corridorList.pop_back();
		temp = &corridorList[0];
		temp1 = &corridorList[1];
	}
	else
	{
		corridorList.erase(corridorList.begin());
		temp = &corridorList[1];
		temp1 = &corridorList[0];
	}

	if (temp1->dir == temp->dir && temp1->type != cornerCorridorL && temp1->type != cornerCorridorR)
	{
		temp1->dir = corridorDir((temp1->dir + 2) % 4);
		std::swap(temp1->inf, temp1->loc);
		switch (temp1->dir)
		{
		case xP:
			temp1->loc += glm::vec3(0, 0, -2);
			temp1->inf += glm::vec3(0, 0, -2);
			break;
		case zP:
			temp1->loc += glm::vec3(2, 0, 0);
			temp1->inf += glm::vec3(2, 0, 0);
			break;
		case xN:
			temp1->loc += glm::vec3(0, 0, 2);
			temp1->inf += glm::vec3(0, 0, 2);
			break;
		case zN:
			temp1->loc += glm::vec3(-2, 0, 0);
			temp1->inf += glm::vec3(-2, 0, 0);
			break;
		}
	}
	if (temp1->type == cornerCorridorL && temp1->dir != ((temp->dir + 2) % 4))
	{
		temp1->type = cornerCorridorR;
		std::swap(temp1->inf, temp1->loc);
		switch (temp1->dir)
		{
		case xP:
			temp1->loc += glm::vec3(2, 0, 0);
			temp1->inf += glm::vec3(0, 0, 2);
			break;
		case zP:
			temp1->loc += glm::vec3(0, 0, 2);
			temp1->inf += glm::vec3(-2, 0, 0);
			break;
		case xN:
			temp1->loc += glm::vec3(0, 0, -2);
			temp1->inf += glm::vec3(-2, 0, 0);
			break;
		case zN:
			temp1->loc += glm::vec3(0, 0, -2);
			temp1->inf += glm::vec3(2, 0, 0);
			break;
		}
		temp1->dir = corridorDir((temp1->dir + 1) % 4);
	}
	else if (temp1->type == cornerCorridorR && temp1->dir != ((temp->dir + 2) % 4))
	{
		temp1->type = cornerCorridorL;
		std::swap(temp1->inf, temp1->loc);
		switch (temp1->dir)
		{
		case xP:
			temp1->loc += glm::vec3(-2, 0, 0);
			temp1->inf += glm::vec3(0, 0, 2);
			break;
		case zP:
			temp1->loc += glm::vec3(0, 0, -2);
			temp1->inf += glm::vec3(-2, 0, 0);
			break;
		case xN:
			temp1->loc += glm::vec3(2, 0, 0);
			temp1->inf += glm::vec3(0, 0, -2);
			break;
		case zN:
			temp1->loc += glm::vec3(0, 0, 2);
			temp1->inf += glm::vec3(2, 0, 0);
			break;
		}
		int i = (temp1->dir - 1 < 0) ? (temp1->dir + 3) : temp1->dir - 1;
		temp1->dir = corridorDir(i);
	}

	//确定类型
	Model* newCorridorModel = NULL;
	newCorridorType = genNewCorridor(temp->type);
	switch (newCorridorType)
	{
	case straightCorridor:
		if (rand() % 2)
			newCorridorModel = straight_model;
		else
			newCorridorModel = straight_model1;
		break;
	case cornerCorridorL:
		newCorridorModel = cornerL_model;
		break;
	case cornerCorridorR:
		newCorridorModel = cornerR_model;
		break;
	case stairsCorridorU:
		newCorridorModel = stairU_model;
		break;
	case stairsCorridorD:
		newCorridorModel = stairD_model;
		break;
	}

	//确定方向
	if (temp->type == cornerCorridorL)
	{
		int i = (temp->dir - 1) < 0 ? (temp->dir + 3) : (temp->dir - 1);
		newCorridorDir = corridorDir(i);
	}
	else if (temp->type == cornerCorridorR)
	{
		newCorridorDir = corridorDir((temp->dir + 1) % 4);
	}
	else
		newCorridorDir = temp->dir;

	//确定变换矩阵
	glm::mat4 model(1.0f);
	model = glm::translate(model, temp->inf); //平移到接口
	switch (newCorridorDir)
	{
	case xP:
		model = glm::rotate(model, glm::radians(-90.f), glm::vec3(0, 1, 0));
		break;
	case zP:
		model = glm::rotate(model, glm::radians(-180.f), glm::vec3(0, 1, 0));
		break;
	case xN:
		model = glm::rotate(model, glm::radians(-270.f), glm::vec3(0, 1, 0));
		break;
	case zN:
		break;
	}

	Corridor newCorridor(newCorridorModel, newCorridorType, newCorridorDir, model);
	newCorridor.lamp_model = lamp_model;

	if (pos == front)
	{
		corridorList.insert(corridorList.begin(), newCorridor);
	}
	else
		corridorList.push_back(newCorridor);

	// debug
	/*cout << "front.type: " << corrider_typename[corridorList[0].type]
		 << "\tmid.type: " << corrider_typename[corridorList[1].type]
		 << "\tback.type: " << corrider_typename[corridorList[2].type] << endl;*/
}

void Scene::render()
{
	lightTwinkle();
	//先渲染中间走廊，再渲染两边
	corridorList[1].render(camera);
	corridorList[0].render(camera);
	corridorList[2].render(camera);


	if (cameraPos.size() < 250)
		cameraPos.push(camera->Position);
	glm::mat4 ghostmodel(1.0f);
	Paint ghost(ghost_model, ghostmodel);
	if (ghostPos != cameraPos.back() || cameraPos.size() == 250)
	{
		ghost.model = glm::translate(glm::mat4(1.0f), cameraPos.front());
		cameraPos.pop();
	}
	//ghost.model = glm::translate(ghost.model, glm::vec3(0,-1,0));
	ghost.model = glm::scale(ghost.model, glm::vec3(0.16f));
	ghost.render(camera);

	float x = cameraPos.front().x - camera->Position.x;
	float y = cameraPos.front().y - camera->Position.y;
	float z = cameraPos.front().z - camera->Position.z;
	float d = sqrt(x * x + y * y + z * z);
	SSound.playFewSecond("resources/musics/heartbeat.mp3", 0.5 + d / 5);
	if (d < 1)
		SSound.playFewSecond("resources/musics/near.mp3", 1.5);


}

corridorType Scene::genNewCorridor(corridorType mid) //随机返回一种走廊类型
{
	if (mid == straightCorridor) //直走廊只能接转弯或上下楼
	{
		corridorType list[4] = { cornerCorridorL, cornerCorridorR, stairsCorridorU, stairsCorridorD };
		int rand_num = rand() % 4;
		return list[rand_num];
	}
	else if (mid == cornerCorridorL || mid == cornerCorridorR) //转弯走廊不能再接转弯走廊
	{
		corridorType list[3] = { stairsCorridorU, stairsCorridorD, straightCorridor };
		int rand_num = rand() % 3;
		return list[rand_num];
	}
	else
	{
		corridorType list[3] = { cornerCorridorL, cornerCorridorR, straightCorridor }; //两个楼梯不能相邻
		int rand_num = rand() % 3;
		return list[rand_num];
	}
}

camera_pos Scene::getPos()
{
	if (corridorList[1].isInCorridor(camera))
	{
		corridorList[1].setInCorridor(camera);
		return mid;
	}
	else if (corridorList[0].isInCorridor(camera))
	{
		corridorList[0].setInCorridor(camera);
		return front;
	}
	else if (corridorList[2].isInCorridor(camera))
	{
		corridorList[2].setInCorridor(camera);
		return back;
	}
}

void Scene::lightTwinkle()
{
	float result = 0;
	int rnum = rand() % 400;
	int afterTwinkle = rand() % 800 + 200;
	extern int darkTime;

	//如果触发了闪烁效果
	if (!rnum && !darkTime)
	{
		darkTime = 1;
		result = 0;
		SSound.play2D("resources/musics/lamp.mp3", 0);
	}
	else
	{
		if (darkTime)
		{
			darkTime++;
			if (darkTime < 2)
				result = 0.5;
			else if (darkTime < 8)
				result = 0;
			else if (darkTime < 10)
				result = 0.5;
			else if (darkTime < 13)
				result = 0;
			else if (darkTime < 15)
				result = 0.5;
			else
				result = 0.05;
		}
		else
			result = 1;
	}
	if (darkTime >= 15 + afterTwinkle)
		darkTime = 0;

	extern glm::vec3 pointLightOff;
	pointLightOff = glm::vec3(result + 0.02, result, result);
}
