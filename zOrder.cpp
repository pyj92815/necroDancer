#include "stdafx.h"
#include "zOrder.h"
#include "playerManager.h"
#include "EnemyManager.h"
#include "player.h"
#include "slaveManager.h"
#include "slave.h"

zOrder::zOrder()
{
}

zOrder::~zOrder()
{
}

HRESULT zOrder::init()
{

	return S_OK;
}

void zOrder::release()
{
}

void zOrder::update()
{
	_zOrderVector = ZorderUpdate(_zOrderVector);
}

void zOrder::render()
{

	for (int i = 0; i < _zOrderVector.size(); ++i)
	{
		if (_zOrderVector[i]->Object->tile != NULL)
		{
			
				if (_zOrderVector[i]->Object->tile->wall != W_NONE)
				{
					if (_zOrderVector[i]->Object->tile->alphaValue <= 0)
					{
						//IMAGEMANAGER->findImage("wallTiles")->frameRender(CAMERAMANAGER->getWorldDC(), _zOrderVector[i]->Object->tile->rc.left, _zOrderVector[i]->Object->tile->rc.top - 30, _zOrderVector[i]->Object->tile->wallFrameX, _zOrderVector[i]->Object->tile->wallFrameY);
						IMAGEMANAGER->findImage("wallTiles")->frameRender(CAMERAMANAGER->getWorldDC(), _zOrderVector[i]->Object->tile->rc.left, _zOrderVector[i]->Object->tile->rc.top - 30, _zOrderVector[i]->Object->tile->wallFrameX, _zOrderVector[i]->Object->tile->wallFrameY);
					}
					else
					{
						IMAGEMANAGER->findImage("wallTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _zOrderVector[i]->Object->tile->rc.left, _zOrderVector[i]->Object->tile->rc.top - 30, _zOrderVector[i]->Object->tile->wallFrameX, _zOrderVector[i]->Object->tile->wallFrameY, _zOrderVector[i]->Object->tile->alphaValue);

					}
				}	
			continue;
		}
		//플레이어 
		if (_zOrderVector[i]->Object->pm != NULL)
		{
			_zOrderVector[i]->Object->pm->render();
			continue;
		}
		else if (_zOrderVector[i]->Object->player != NULL)
		{
			_zOrderVector[i]->Object->player->render();
			continue;
		}

		if (_zOrderVector[i]->Object->enemy != NULL)
		{
			_zOrderVector[i]->Object->enemy->render();
			continue;
		}

		if (_zOrderVector[i]->Object->slaveEnemy != NULL)
		{
			_zOrderVector[i]->Object->slaveEnemy->render();
		}
		if (_zOrderVector[i]->Object->deathMetalboss != NULL && !_zOrderVector[i]->Object->deathMetalboss->getBoss_Dead())
		{
			_zOrderVector[i]->Object->deathMetalboss->render();
		}
	}
}

vector<tagzOrder*> zOrder::ZorderUpdate(vector<tagzOrder*> num)
{
	tagzOrder* instance = new tagzOrder();
	for (int j = 0;j < num.size();j++)
	{
		for (int i = j + 1;i < num.size();i++)
		{
			if (*(num[j]->y) > * (num[i]->y))
			{
				if (num[i]->Object->pm != NULL
					&& num[i]->y +
					(num[i]->Object->pm->getPlayerInfo()->getPlayer().rc.top -
						num[i]->Object->pm->getPlayerInfo()->getPlayer().rc.bottom))
				{
					instance = num[j];
					num[j] = num[i];
					num[i] = instance;
				}
				else
				{
					instance = num[j];
					num[j] = num[i];
					num[i] = instance;
				}
			}
		}
	}

	return num;
}

void zOrder::zOrderSetup(int idx, int idy, vector<tagTile*>* tagTile, playerManager* pm, EnemyManager* em)
{
	_zOrderVector.clear();
	int startX = idx;
	int startY = idy - 10;
	if (idx < 0) startX = 0;
	if (idy - 10 < 0) startY = 0;

	// 2n+ 1 개 만큼
	for (int i = startY; i < startY + 21; i++)
	{
		for (int j = startX; j < startX + 1; j++)
		{
			if (i > TILEY) continue;
			if (j > TILEX) continue;

			tagClass* tile;
			tile = new tagClass;
			ZeroMemory(tile, sizeof(tile));
			tile->pm = NULL;
			tile->enemy = NULL;
			tile->player = NULL;
			tile->slaveEnemy = NULL;
			tile->slaveMoster = NULL;
			tile->tile = (*tagTile)[i * TILEX + j];
			float* ins = new float;
			*ins = (float)(*tagTile)[i * TILEX + j]->rc.bottom;
			_zOrderVector.push_back(new tagzOrder(ins, tile));
		}
	}

	tagClass* player;
	player = new tagClass;
	ZeroMemory(player, sizeof(player));
	player->pm = pm;
	player->tile = NULL;
	player->enemy = NULL;
	player->slaveEnemy = NULL;
	player->slaveMoster = NULL;
	player->player = NULL;
	_zOrderVector.push_back(new tagzOrder(pm->getPlayerInfo()->getPlayerY(), player));
}

void zOrder::zOrderSetup(int idx, int idy, tagTile* tagTile, playerManager* pm, EnemyManager* em)
{
	_zOrderVector.clear();
	int startX = idx;
	int startY = idy - 10;
	if (idx < 0) startX = 0;
	if (idy - 10 < 0) startY = 0;

	// 2n+ 1 개 만큼
	for (int i = startY; i < startY + 21; i++)
	{
		for (int j = startX; j < startX + 1; j++)
		{
			if (i > TILEY) continue;
			if (j > TILEX) continue;

			tagClass* tile;
			tile = new tagClass;
			ZeroMemory(tile, sizeof(tile));
			tile->pm = NULL;
			tile->enemy = NULL;
			tile->tile = &tagTile[i * TILEX + j];
			float* ins = new float;
			*ins = (float)tagTile[i * TILEX + j].rc.bottom;
			_zOrderVector.push_back(new tagzOrder(ins, tile));
		}
	}

	tagClass* player;
	player = new tagClass;
	ZeroMemory(player, sizeof(player));
	player->pm = pm;
	player->enemy = NULL;
	player->tile = NULL;
	_zOrderVector.push_back(new tagzOrder(pm->getPlayerInfo()->getPlayerY(), player));
}

void zOrder::zOrderSetup(int idx, int idy, tagTile* tagTile, player* user, slaveManager* slave, deathMetal* metal)
{
	_zOrderVector.clear();
	int startX = idx;
	int startY = idy - 10;
	if (idx < 0) startX = 0;
	if (idy - 10 < 0) startY = 0;

	// 2n+ 1 개 만큼
	for (int i = startY; i < startY + 21; i++)
	{
		for (int j = startX; j < startX + 1; j++)
		{
			if (i > TILEY) continue;
			if (j > TILEX) continue;

			tagClass* tile;
			tile = new tagClass;
			ZeroMemory(tile, sizeof(tile));
			tile->pm = NULL;
			tile->enemy = NULL;
			tile->player = NULL;
			tile->slaveEnemy = NULL;
			tile->slaveMoster = NULL;
			tile->deathMetalboss = NULL;
			tile->tile = &tagTile[i * TILEX + j];
			float* ins = new float;
			*ins = (float)tagTile[i * TILEX + j].rc.bottom;
			_zOrderVector.push_back(new tagzOrder(ins, tile));
		}
	}

	tagClass* player;
	player = new tagClass;
	ZeroMemory(player, sizeof(player));
	player->pm = NULL;
	player->enemy = NULL;
	player->tile = NULL;
	player->slaveEnemy = NULL;
	player->slaveMoster = NULL;
	player->deathMetalboss = NULL;
	player->player = user;

	_zOrderVector.push_back(new tagzOrder(player->player->getPlayerY(), player));

	tagClass* slaves;
	slaves = new tagClass;
	ZeroMemory(slaves, sizeof(slaves));
	slaves->player = NULL;
	slaves->pm = NULL;
	slaves->enemy = NULL;
	slaves->tile = NULL;
	slaves->deathMetalboss = NULL;
	slaves->slaveEnemy = NULL;
	slaves->slaveMoster = slave;

	for (int i = 0; i < slaves->slaveMoster->get_SlaveList().size(); ++i)
	{

		tagClass* enemy;
		enemy = new tagClass;
		ZeroMemory(enemy, sizeof(enemy));
		enemy->pm = NULL;
		enemy->player = NULL;
		enemy->enemy = NULL;
		enemy->tile = NULL;
		enemy->slaveMoster = NULL;
		enemy->deathMetalboss = NULL;
		enemy->slaveEnemy = slaves->slaveMoster->get_SlaveList()[i];
		float* ins = new float;
		*ins = (float)enemy->slaveEnemy->get_Slave()->pos.rc.bottom;
		_zOrderVector.push_back(new tagzOrder(ins, enemy));
	}


	tagClass* deathmetal;
	deathmetal = new tagClass;
	deathmetal->pm = NULL;
	deathmetal->player = NULL;
	deathmetal->enemy = NULL;
	deathmetal->tile = NULL;
	deathmetal->slaveMoster = NULL;
	deathmetal->deathMetalboss = metal;
	deathmetal->slaveEnemy = NULL;
	float* ins = new float;
	*ins = deathmetal->deathMetalboss->getBoss_Rect().bottom;
	
	_zOrderVector.push_back(new tagzOrder(ins, deathmetal));
	
	

	//_zOrderVector.push_back(new tagzOrder(slaves->slaveMoster..)

}



