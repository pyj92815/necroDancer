#include "stdafx.h"
#include "playerTestTile.h"

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
}

void playerTestTile::render()
{
	for (_viTiles = _vTiles.begin(); _viTiles != _vTiles.end(); ++_viTiles)
	{
		(*_viTiles)->render(getMemDC());
	}
}
