#include "ball.h"
#include <vector>
#include <paddle.h>

Ball::Ball(int r, ge211::Dimensions vel, ge211::Position c)
        : radius_   (r)
        , velocity_ (vel)
        , center_   (c)
        , live_     (true)
{ }

// Returns the position of the top-left corner of the ball's "bounding box"
ge211::Position Ball::top_left() const
{
    ge211::Position c = this->center_;
    c = c.left_by(this->radius_);
    c = c.up_by(this->radius_);
    return c;
}

// Returns a ball with updated position
Ball Ball::next() const
{
    Ball result(*this);
    result.center_ += velocity_;
    return result;
}

//Checks for collision with top of screen
bool Ball::ball_hits_top() const
{
    int ball_top = center_.y - radius_;
    return ball_top < 0;
}

//Checks for collision with bottom of screen
bool Ball::ball_hits_bottom(int screen_height) const
{
    int ball_bottom = center_.y + radius_;
    return ball_bottom > screen_height;
}

//Checks for collision with left side of screen
bool Ball::ball_hits_left_side() const
{
    int ball_left_side  = center_.x - radius_;
    return ball_left_side < 0;
}

//Checks for collision with right side of screen
bool Ball::ball_hits_right_side(int screen_width) const
{
    int ball_right_side = center_.x + radius_;
    return ball_right_side > screen_width;
}

//Checks for collision with a rock
bool Ball::ball_hits_rock(Rock const& rock) const
{
    int ball_left_side  = center_.x - radius_;
    int ball_right_side = center_.x + radius_;
    int ball_top = center_.y - radius_;
    int ball_bottom = center_.y + radius_;

    int rock_left_side = rock.rock.top_left().x;
    int rock_top = rock.rock.top_left().y;
    int rock_right_side = rock.rock.bottom_right().x;
    int rock_bottom = rock.rock.bottom_right().y;

    return !(ball_right_side < rock_left_side || rock_right_side < ball_left_side || ball_bottom < rock_top || rock_bottom < ball_top);
}

//Checks for collision with a paddle
bool Ball::ball_hits_paddle(Paddle p) const
{
    int ball_left_side  = center_.x - radius_;
    int ball_right_side = center_.x + radius_;
    int ball_top = center_.y - radius_;
    int ball_bottom = center_.y + radius_;

    int paddle_left_side = p.get_paddle_rectangle().top_left().x;
    int paddle_top = p.get_paddle_rectangle().top_left().y;
    int paddle_right_side = p.get_paddle_rectangle().bottom_right().x;
    int paddle_bottom = p.get_paddle_rectangle().bottom_right().y;

    return !(ball_right_side < paddle_left_side || paddle_right_side < ball_left_side || ball_bottom < paddle_top || paddle_bottom < ball_top);
}

//Destroys a rock
bool Ball::destroy_rock(std::vector<Rock>& rocks)
{
    for (Rock& r: rocks) {
        if (ball_hits_rock(r) && r.onscreen_) {
            r.onscreen_ = false;
            return true;
        }
    }
    return false;
}

//Invert velocitie components
void Ball::reflect_vertical()
{
    velocity_.height *= -1;
}

void Ball::reflect_horizontal()
{
    velocity_.width *= -1;
}

//Change velocity from hitting paddle
void Ball::reflect_off_paddle(Paddle p) {
    int b = (center_.y - p.p_.center().y);
    b *= 0.05;
    velocity_.height = b;
    reflect_horizontal();

    if(velocity_.width < 0)
    velocity_.width -= std::rand() % 4;
    if(velocity_.width > 0)
        velocity_.width += std::rand() % 4;
}



