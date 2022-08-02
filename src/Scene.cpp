#include "Scene.h"

Scene::Scene() : player((Scene::grid_max_columns / 2), (Scene::grid_max_rows / 2)), 
                camera(bn::camera_ptr::create(0, 0)),
                pkm_bg(bn::regular_bg_items::pokemon_map_static.create_bg((Scene::grid_cell_width / 2), (Scene::grid_cell_height / 2)))

{
    Reset();
    
    
    pkm_bg.set_camera(camera);
    player.player_sprite.set_camera(camera);
    //Scene_ptr->player.teste_sprite.set_camera(camera);
}

Scene::~Scene() = default;

void Scene::Reset() {
    player.MoveTo(grid_max_columns / 2, grid_max_rows / 2);
    player.nextPos_x = player.x; 
    player.nextPos_y = player.y;
    player.spritePos_x = player.sprite_x(player.x);
    player.spritePos_y = player.sprite_y(player.y);
}
