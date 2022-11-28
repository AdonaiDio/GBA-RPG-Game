#include "Scene.h"


Scene::Scene() : player (new Player((Scene::grid_max_columns / 2), (Scene::grid_max_rows / 2), 16, 16, this)),
                object((Scene::grid_max_columns / 2)+1, (Scene::grid_max_rows / 2),16,16),
                camera(bn::camera_ptr::create(0, 0)),
                //pkm_bg(bn::regular_bg_items::pokemon_map_static.create_bg((Scene::grid_cell_width / 2), (Scene::grid_cell_height / 2)))
                pkm_bg_tiles(bn::regular_bg_tiles_items::pkm_tileset.create_tiles())

{
    Reset();
    //associando Player e Object à camera
    //pkm_bg.set_camera(camera);
    //pkm_bg_tiles.set_camera(camera);
    player->player_sprite.set_camera(camera);
    object.object_sprite.set_camera(camera);

}

Scene::~Scene() = default;

void Scene::willCollide() {
    BN_LOG("Player_Pos x: ", player->x, ", y: ", player->y);
    BN_LOG("PlayerSprite_Pos x: ", player->spritePos_x, ", y: ", player->spritePos_y);
    BN_LOG("PlayerRect_Pos x: ", player->collider.x(), ", y: ", player->collider.y());
    BN_LOG("P_Rect top: ", player->collider.top(), ", left: ", player->collider.left(), ", bottom: ", player->collider.bottom(), ", right: ", player->collider.right());
    BN_LOG("====");
    BN_LOG("Object_Pos x: ", object.x, ", y: ", object.y);
    BN_LOG("ObjectSprite_Pos x: ", object.spritePos_x, ", y: ", object.spritePos_y);
    BN_LOG("ObjectRect_Pos x: ", object.collider.x(), ", y: ", object.collider.y());
    BN_LOG("Obj_Rect top: ", object.collider.top(), ", left: ", object.collider.left(), ", bottom: ", object.collider.bottom(), ", right: ", object.collider.right());
    BN_LOG("====");
    BN_LOG("onCollision is ", player->onCollision);
    //criar novo collider Temporario na nova posição a partir da direção recebida
    bn::rect predictCollider;
    predictCollider = player->collider;
    BN_LOG(">>Predict Collider x is ", predictCollider.x());
    //ajutar o Offset com base na direção do player
    switch (player->current_direction){
    case Player::Direction::up:
        predictCollider.set_y(predictCollider.y() - grid_cell_height); //subiu 1 grid
        break;
    case Player::Direction::down:
        predictCollider.set_y(predictCollider.y() + grid_cell_height); //desce 1 grid
        break;
    case Player::Direction::left:
        predictCollider.set_x(predictCollider.x() - grid_cell_width); //1 grid para a esquerda
        break;
    default:
    case Player::Direction::right:
        predictCollider.set_x(predictCollider.x() + grid_cell_width); //1 grid para a direita
        break;
    }
    //testa a colisão com o novo collider e o objecto de colisão
    if (predictCollider.intersects(object.collider)) {
        player->onCollision = true;
        BN_LOG("onCollision NOW is ", player->onCollision);
    }
    
}


void Scene::Reset() {
    player->MoveTo(grid_max_columns / 2, grid_max_rows / 2);
    player->nextPos_x = player->x;
    player->nextPos_y = player->y;
    player->spritePos_x = player->sprite_x(player->x);
    player->spritePos_y = player->sprite_y(player->y);
    camera.set_position(player->spritePos_x, player->spritePos_y);
}
