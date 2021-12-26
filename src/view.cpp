#include <view.h>
#include "ball.h"
#include <string>

View::View(Model& model)
        :model_(model)
{
    for (int i = 0; i < 9; ++i) {
        score_sprites_.emplace_back(std::string("Score " + std::to_string(i)), sans_);
    }
}

void View::draw(ge211::Sprite_set& s)
{
    if(!model_.game_started)
    {
        s.add_sprite(StartScreen, {0, 0}, 0);
        return;
    }

    if(model_.game_ended && model_.winner_ == 0)
    {
        s.add_sprite(Player1Win, {0,0}, 0);
        return;
    }

    if(model_.game_ended && model_.winner_ == 1)
    {
        s.add_sprite(Player2Win, {0,0}, 0);
        return;
    }

    s.add_sprite(background, {0,0}, -1);
    for (int i = 0; i < model_.rocks_.size(); i++) {
        if(model_.rocks_[i].onscreen_)
            s.add_sprite(Rock, model_.rocks_[i].rock.top_left(), 0);
    }

    int xl = model_.right_player_.get_paddle_rectangle().top_left().x -30;
    int xr = model_.left_player_.get_paddle_rectangle().top_left().x - 47;
    s.add_sprite(ball_sprite_, model_.ball_.top_left(), 0);
    s.add_sprite(leftpl, {xl, model_.right_player_.get_paddle_rectangle().top_left().y} , 0);
    s.add_sprite(rightpl, {xr, model_.left_player_.get_paddle_rectangle().top_left().y}, 0);

    s.add_sprite(score_sprites_[model_.left_player_.score_], {200, 100},1);
    s.add_sprite(score_sprites_[model_.right_player_.score_], {model_.geometry_.scene_dims.width - 300, 100},1);
}


