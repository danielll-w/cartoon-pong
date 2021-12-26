#include "model.h"
#include <ge211.h>
#include "controller.h"

Model::Model(Geometry const& geometry)
        : geometry_(geometry)
        , right_player_(Paddle{30, geometry_.scene_dims.height / 2, geometry_.paddle_dims_.width, geometry_.paddle_dims_.height})
        , left_player_(Paddle{geometry_.scene_dims.width - 30, geometry_.scene_dims.height / 2, geometry_.paddle_dims_.width, geometry_.paddle_dims_.height})
        , ball_({geometry_.ball_radius, geometry_.ball_velocity0, {geometry_.scene_dims.width / 2, geometry_.scene_dims.height / 2}})
{
    ball_.live_ = false;
    for (int i = -2; i < 2; ++i) {
        for (int j = -2; j < 2; ++j) {
            int offset_x = (geometry_.scene_dims.width/2) + 150*i;
            int offset_y = (geometry_.scene_dims.height / 2) + 150*j;
            rocks_.push_back(Rock{ge211::Rectangle::from_top_left({offset_x, offset_y}, {80, 80}), false});
        }
    }
}


void Model::start_game()
{
    game_started = true;
    right_player_.set_live(true);
    left_player_.set_live(true);
    ball_.live_ = true;
}

void Model::pause_game()
{
    pause = !pause;
}


void Model::update(double dt, ge211::Mixer* mixer)
{
    if (!ball_.live_ || pause)
        return;

    right_player_.move(100, dt);
    left_player_.move(100, dt);

    Ball next = ball_.next();

    if (next.ball_hits_left_side()) {
        ball_.live_ = false;
        ball_ = Ball({geometry_.ball_radius, geometry_.ball_velocity0, {geometry_.scene_dims.width / 2, geometry_.scene_dims.height / 2}});
        ball_.velocity_.width *= -1;
        right_player_.increment_score();
        std::string str = "score.wav";
        mixer->play_effect(ge211::Sound_effect(str, *mixer), 1.0);
        return;
    }

    if (next.ball_hits_right_side(geometry_.scene_dims.width)) {
        ball_.live_ = false;
        ball_ = Ball({geometry_.ball_radius, geometry_.ball_velocity0, {geometry_.scene_dims.width / 2, geometry_.scene_dims.height / 2}});
        left_player_.increment_score();
        std::string str = "score.wav";
        mixer->play_effect(ge211::Sound_effect(str, *mixer), 1.0);
        return;
    }

    if (next.ball_hits_top())
    {
        ball_.reflect_vertical();
    }

    if (next.ball_hits_bottom(geometry_.scene_dims.height)) {
        ball_.reflect_vertical();
    }

    if (next.destroy_rock(rocks_)) {
        ball_.reflect_vertical();
        ball_.reflect_horizontal();
    }

    if (next.ball_hits_paddle(right_player_)) {
        ball_.reflect_off_paddle(right_player_);
        std::string str = "paddlehit.wav";
        mixer->play_effect(ge211::Sound_effect(str, *mixer), 1.0);
    }

    if (next.ball_hits_paddle(left_player_)) {
        ball_.reflect_off_paddle(left_player_);
        std::string str = "paddlehit.wav";
        mixer->play_effect(ge211::Sound_effect(str, *mixer), 1.0);
    }

    if (left_player_.score_ > 3)
    {
        winner_ = 0;
        set_game_over();
    }

    if (right_player_.score_ > 3)
    {
        winner_ = 1;
        set_game_over();
    }

    if (rocks_number() < 3)
    {
        add_rock();
    }

    ball_ = ball_.next();
}

void Model::move_up_left_player(bool b){
    left_player_.up = b;
}

void Model::move_down_left_player(bool b){
    left_player_.down = b;
}

void Model::move_up_right_player(bool b){
    right_player_.up = b;
}

void Model::move_down_right_player(bool b){
    right_player_.down = b;
}

void Model::add_rock()
{
    rocks_[std::rand() % 15].onscreen_= true;
}

void Model::set_game_over()
{
    pause = true;
    game_ended = true;
}

int Model::rocks_number() {
   int result = 0;
    for (Rock& rock : rocks_)
    {
        if (rock.onscreen_)
            result++;
    }
    return result;
}