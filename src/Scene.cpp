#include "Scene.h"

Scene::Scene() : player(new Player((Scene::grid_max_columns / 2), (Scene::grid_max_rows / 2), 16, 16, this)),
                object((Scene::grid_max_columns / 2) + 1, (Scene::grid_max_rows / 2), 16, 16),
                camera(bn::camera_ptr::create(0, 0)),
                pkm_village1(bn::regular_bg_items::pkm_village1.create_bg((Scene::grid_cell_width / 2), (Scene::grid_cell_height / 2))),
                pkm_village2(bn::regular_bg_items::pkm_village2.create_bg((Scene::grid_cell_width / 2), (Scene::grid_cell_height / 2)))
                //pkm_village(bn::regular_bg_items::pkm_village.create_bg((Scene::grid_cell_width / 2), (Scene::grid_cell_height / 2)))
                //pkm_bg(bn::regular_bg_items::pokemon_map_static.create_bg((Scene::grid_cell_width / 2), (Scene::grid_cell_height / 2)))
                //pkm_bg_tiles(bn::regular_bg_tiles_items::pkm_tileset.create_tiles())
   

{
    Reset();
    //associando Player e Object à camera
    player->player_sprite.set_camera(camera);
    object.object_sprite.set_camera(camera);

    //pkm_village.set_camera(camera);
    pkm_village1.set_camera(camera);
    pkm_village2.set_camera(camera);
    pkm_village2.set_priority(2);

}

Scene::~Scene() = default;

void Scene::willCollide() {
    BN_LOG("Player_Pos x: ", player->x, ", y: ", player->y);
    BN_LOG("PlayerSprite_Pos x: ", player->spritePos_x, ", y: ", player->spritePos_y);
    //BN_LOG("PlayerRect_Pos x: ", player->collider.x(), ", y: ", player->collider.y());
    //BN_LOG("P_Rect top: ", player->collider.top(), ", left: ", player->collider.left(), ", bottom: ", player->collider.bottom(), ", right: ", player->collider.right());
    //BN_LOG("====");
    //BN_LOG("Object_Pos x: ", object.x, ", y: ", object.y);
    //BN_LOG("ObjectSprite_Pos x: ", object.spritePos_x, ", y: ", object.spritePos_y);
    //BN_LOG("ObjectRect_Pos x: ", object.collider.x(), ", y: ", object.collider.y());
    //BN_LOG("Obj_Rect top: ", object.collider.top(), ", left: ", object.collider.left(), ", bottom: ", object.collider.bottom(), ", right: ", object.collider.right());
    //BN_LOG("====");
    //BN_LOG("onCollision is ", player->onCollision);
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
    //primeiro ver se está dentro da área da cena
    //if(predictCollider.x() >= 0
    //  && predictCollider.y() >= 0
    //    && predictCollider.x() <= grid_max_columns
    //    && predictCollider.y() <= grid_max_rows){
        //testa a colisão com o novo collider e o objecto de colisão
        // gets the current map cell the sprite is on.
        //bn::fixed current_cell = (player->y) + player->x;
        //BN_LOG("currentCell: ", current_cell.integer());
        // at the moment all I am doing is checking if the cell is not the sky cell (aka not zero)
        //bool is_hit = pkm_village.map().cells_ref().value().at(current_cell.integer()) != 0;

        for (int i = 0; i < 123; i++) {
            int a = coliderMap[i][0] * grid_cell_width;
            int b = coliderMap[i][1] * grid_cell_height;
            BN_LOG("x");
            BN_LOG(a);
            BN_LOG("y");
            BN_LOG(b);
            if (predictCollider.contains(bn::point((coliderMap[i][0] * grid_cell_width) - ((grid_max_columns / 2) * grid_cell_width),
                (coliderMap[i][1] * grid_cell_height)-((grid_max_rows / 2) * grid_cell_height)))) {
                player->onCollision = true;
                BN_LOG("oh......");
            }
        }
        /*if (predictCollider.intersects(object.collider)) {
            player->onCollision = true;
            BN_LOG("onCollision NOW is ", player->onCollision);
        }*/
        //if (predictCollider.contains(bn::point(16, 16))) { //1 pixel em uma posição por pixel
        //    player->onCollision = true;
        //    BN_LOG("onCollision NOW is ", player->onCollision);
        //}
    //}
}


void Scene::Reset() {
    player->MoveTo(grid_max_columns / 2, 4+(grid_max_rows / 2));
    player->nextPos_x = player->x;
    player->nextPos_y = player->y;
    player->spritePos_x = player->sprite_x(player->x);
    player->spritePos_y = player->sprite_y(player->y);
    camera.set_position(player->spritePos_x, player->spritePos_y);
}
