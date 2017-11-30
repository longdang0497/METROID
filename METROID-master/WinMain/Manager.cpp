#include "Manager.h"

Manager::Manager(LPDIRECT3DDEVICE9 d3ddv)
{
	m_d3ddv = d3ddv;
}

Manager::~Manager()
{
	if (m_d3ddv) { m_d3ddv = nullptr; delete m_d3ddv; }
}

void Manager::CheckDistance()
{

}

void Manager::_CreateBullets(int X, int Y, int VX, int VY)
{
	weapon.push_back( new Bullet( &m_d3ddv, X, Y, VX, VY) );
}

void Manager::UpdateObject(int delta)
{
	for (int i = 0; i < weapon.size(); i++)
	{
		weapon[i]->UpdateObject(delta);
	}
}

void Manager::Render()
{
	for (int i = 0; i < weapon.size(); i++)
	{
		weapon[i]->Render();
	}
}
