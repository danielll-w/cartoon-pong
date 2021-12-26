#pragma once
#include <ge211.h>

struct Geometry
{
    // Constructs an instance with the default parameters.
    Geometry() noexcept;

    // The dimensions of the whole window:
    ge211::Dimensions scene_dims;

    // The dimensions of the paddles
    ge211::Dimensions paddle_dims_;

    // The radius of the ball:
    int ball_radius;

    //The radius of the rock
    int rock_size_;

    // The ball's initial velocity {width, height}:
    ge211::Dimensions ball_velocity0;

    // The maximum amount that bouncing off the paddle boosts the ball's x
    // velocity component:
    int max_boost;
};