#include "World.h"
#include "Samus.h"
#include "FlyingBat.h"
#include "SpiderBug.h"

World::World()
{
}

World::World(LPD3DXSPRITE spriteHandler, Metroid * scene)
{
	//Gán
	this->spriteHandler = spriteHandler;
	this->scene = scene;

	//Khởi tạo các đối tượng trong World
	samus = new Samus(spriteHandler, this);
	//bat = new FlyingBat(spriteHandler, this);
	//spider = new SpiderBug(spriteHandler, this);
}

World::~World()
{
	delete(samus);
	//delete(bat);
	//delete(spider);
}

void World::Update(float time)
{
	samus->UpdateObject(time);
	//bat->UpdateObject(time);
	//spider->UpdateObject(time);
}

void World::Render()
{
	samus->Render();
	//bat->Render();
	//spider->Render();
}
