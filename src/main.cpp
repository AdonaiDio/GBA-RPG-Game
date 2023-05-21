#include "my_bn_headers.h"

#include "common_info.h"
#include "common_variable_8x16_sprite_font.h"
//criado durante a build

#include "Scene.h"


//namespace Assets{
//}



namespace Background_0{
    /* Data of Background*/
}

bn::fixed get_map_index(bn::fixed tile_x, bn::fixed tile_y, bn::fixed columns) {
    return (tile_y * columns) + tile_x;
}


int main()
{
    bn::core::init();

    std::unique_ptr<Scene> Scene_ptr(new Scene());

    bn::music_items::speed_eaters_2.play(0.2);

    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    text_generator.set_center_alignment();
    bn::vector<bn::sprite_ptr, 32> text_sprites;

    while(true)
    {
        text_sprites.clear();
        // generate the new text
        /*bn::string textCellIndex = bn::to_string<32>(Scene_ptr->pkm_village.map().cells_ref().value().at(
            get_map_index(Scene_ptr->player->x,
                Scene_ptr->player->y,
                bn::fixed(Scene_ptr->grid_max_columns)).integer()));*/
       

        text_generator.generate(0, -40, ("x: " + bn::to_string<32>(Scene_ptr->player->x) + 
                                        " y: " + bn::to_string<32>(Scene_ptr->player->y)), text_sprites);
        text_generator.set_bg_priority(2);

        if (bn::keypad::start_pressed()) {
            Scene_ptr->Reset();
        }
        Scene_ptr->player->Update(Scene_ptr->camera);

        bn::core::update();
        bn::hw::core::wait_for_vblank();
    }
}
