#pragma once

#include "model.h"
#include <ge211.h>

struct View
{
    explicit View(Model&);

    void draw(ge211::Sprite_set& set);

private:
    Model const& model_;
    std::vector<ge211::Text_sprite> score_sprites_;

    //Image sprites for later
    ge211::Circle_sprite    const ball_sprite_    {model_.geometry_.ball_radius, ge211::Color::white()};


    ge211::Image_sprite const Rock {"Rock.png"};
    ge211::Image_sprite const leftpl {"lplayer.png"};
    ge211::Image_sprite const rightpl {"rplayer.png"};
    ge211::Image_sprite const background {"background.png"};
    ge211::Image_sprite const Player1Win {"Player1Wins.png"};
    ge211::Image_sprite const Player2Win {"Player2Wins.png"};
    ge211::Image_sprite const StartScreen {"StartScreen.png"};

    ge211::Font sans_{"sans.ttf", 30};
};