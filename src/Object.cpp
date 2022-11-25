#include "Object.h"
#include "Scene.h"

// correção em posição global
bn::fixed Object::GridToSpritePos_x(int gridPos_x) {
	return (gridPos_x * Scene::grid_cell_width) - ((Scene::grid_max_columns / 2) * Scene::grid_cell_width);
}

bn::fixed Object::GridToSpritePos_y(int gridPos_y) {
	return (gridPos_y * Scene::grid_cell_height) - ((Scene::grid_max_rows / 2) * Scene::grid_cell_height);
}

bn::rect collider;

Object::Object(int pos_x, int pos_y, int coll_width, int coll_height) :
	x(pos_x),
	y(pos_y),
	spritePos_x(GridToSpritePos_x(x)),
	spritePos_y(GridToSpritePos_y(y)),
	collider(spritePos_x.integer(), spritePos_y.integer(), coll_width, coll_height),
	object_sprite(object_sprite_ROM.create_sprite(spritePos_x, spritePos_y))
{}

Object::~Object(){}