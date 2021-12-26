#include "paddle.h"
#include <ge211.h>

Paddle::Paddle(int x, int y, int width, int height)
        : p_(ge211::Rectangle::from_center({x, y}, {width, height}))
        , score_(0)
        , able_to_move(false)
{}


ge211::Rectangle Paddle::get_paddle_rectangle() const
{
    return p_;
}

void Paddle::move(int v, double dt)
{
    if(up)
        p_.y -= 5*(v * dt);

    if(down)
        p_.y += 5*(v * dt);
}


void Paddle::set_live(bool b)
{
    able_to_move = b;
}

void Paddle::increment_score()
{
    score_++;
}