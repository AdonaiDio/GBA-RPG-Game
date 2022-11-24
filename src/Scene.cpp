#include "Scene.h"

Scene::Scene() : player((Scene::grid_max_columns / 2), (Scene::grid_max_rows / 2), 16, 16),
                object((Scene::grid_max_columns / 2)-3, (Scene::grid_max_rows / 2)-2,16,16),
                camera(bn::camera_ptr::create(0, 0)),
                pkm_bg(bn::regular_bg_items::pokemon_map_static.create_bg((Scene::grid_cell_width / 2), (Scene::grid_cell_height / 2)))

{
    Reset();
    pkm_bg.set_camera(camera);
    //associando Player e Object à camera
    player.player_sprite.set_camera(camera);
    object.object_sprite.set_camera(camera);

}

Scene::~Scene() = default;

//void Scene::isOnCollision() {
//    //BN_LOG(player.collider.x() ," ", object.collider.x());
//    if (player.collider.intersects(object.collider)) {
//        player.onCollision = true;
//        BN_LOG("Intersects! ON");
//    }
//}

void Scene::Reset() {
    player.MoveTo(grid_max_columns / 2, grid_max_rows / 2);
    player.nextPos_x = player.x; 
    player.nextPos_y = player.y;
    player.spritePos_x = player.sprite_x(player.x);
    player.spritePos_y = player.sprite_y(player.y);
    camera.set_position(player.spritePos_x,player.spritePos_y);
}
