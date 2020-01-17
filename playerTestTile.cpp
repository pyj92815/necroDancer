#include "stdafx.h"
#include "playerTestTile.h"
#include "player.h"

HRESULT playerTestTile::init()
{
	for (int i = 0;i < TESTTILENUMY;i++)
	{
		for (int j = 0;j < TESTTILENUMX; j++)
		{
			tile* node;
			node = new tile;
			node->init("floor",j, i,TESTTILESIZE, TESTTILESIZE);
			_vTiles.push_back(node);
		}
	}
	return S_OK;
}

void playerTestTile::release()
{
}

void playerTestTile::update()
{
	findSight();
}

void playerTestTile::render()
{
	for (_viTiles = _vTiles.begin(); _viTiles != _vTiles.end(); ++_viTiles)
	{
		(*_viTiles)->render(getMemDC());
	}
}

void playerTestTile::findSight()
{
	// ���� ���� �̿ϼ� 
	for (int i = 0;i < _vTiles.size();i++)
	{
		//�÷��̾��� ��ġ�� ��ø�Ǵ� Ÿ�� 
		if (PtInRect(&_vTiles[i]->getRect(), PointMake(_player->getPlayer().x, _player->getPlayer().y)))
		{
			for (int j = 0; j < _vTiles.size();j++)
			{
				// �÷��̾�� �Ÿ��� ��� 
				float sightNum = getDistance(_player->getPlayer().x, _player->getPlayer().y, _vTiles[j]->getCenter().x, _vTiles[j]->getCenter().y);
				// �þ߰� ���� 
				if (sightNum < (TESTTILESIZE * _player->getSight())) 
				{
					_vTiles[j]->setAlphaValue(0);
				}
				else if (sightNum < ((TESTTILESIZE * 2) * _player->getSight()))
				{
					_vTiles[j]->setAlphaValue(50);
				}
				else if (sightNum < ((TESTTILESIZE * 3) * _player->getSight()))
				{
					_vTiles[j]->setAlphaValue(160);
				}
				else
				{
					_vTiles[j]->setAlphaValue(200);
				}
			}
			break;
		}
	}
}
