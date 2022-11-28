#include "my_bn_headers.h"
#include <bn_sprite_text_generator.h>

#include "common_info.h"
#include "common_variable_8x16_sprite_font.h"
//criado durante a build

#include "Scene.h"

#include "bn_music_items.h"
#include "bn_sound_items.h"

//namespace Assets{
//}



namespace Background_0{
    /* Data of Background*/
}

int main()
{
    bn::core::init();

    bn::unique_ptr<Scene> Scene_ptr(new Scene());


    bn::music_items::speed_eaters_2.play(0.2);

    while(true)
    {
        if(bn::keypad::start_pressed()) {
            Scene_ptr->Reset();
        }
        Scene_ptr->player->Update(Scene_ptr->camera);

        bn::core::update();
        bn::hw::core::wait_for_vblank();
    }
}
