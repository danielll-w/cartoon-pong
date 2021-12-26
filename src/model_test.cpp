#include "model.h"
#include <catch.h>
#include "controller.h"
#include "view.h"

struct Test_access
{
    Model& m_;
    Controller& c;

    void pause()
    {
        c.on_key_down(ge211::Key::code('p'));
    }

    void update()
    {
        c.on_frame(1);
    }

    Ball& ball(){
        return m_.ball_;
    }
    std::vector<Rock>& rock_t()
    { return m_.rocks_;
    }

    std::vector<Rock>& add_rock_t()
    {
        m_.rocks_[std::rand() % 10].onscreen_= true;
        return m_.rocks_;
    }

    int rocks_number_t()
    {
        return m_.rocks_number();
    }
};


TEST_CASE("Pause and game started")
{
    Model m;
    Controller c(m);

    Test_access t {m,c};

    CHECK(m.pause == false);
    CHECK(m.game_started == false);
    m.start_game();
    CHECK(m.game_started == true);

    t.pause();
    CHECK(m.pause == true);
}

TEST_CASE("Hits top or bottom")
{
    Model m;
    Controller c(m);

    Test_access t {m,c};

    m.ball_.center_ = {10,-100};
    ge211::Dimensions old_ball_velocity = m.ball_.velocity_;

    t.update();

    old_ball_velocity.height *= -1;

    //y velocity should be negated as specified
    CHECK(m.ball_.velocity_.height == old_ball_velocity.height);
}


TEST_CASE("Point scored and ball reset")
{
    Model m;
    Controller c(m);

    Test_access t {m,c};


    int p2_old_score = m.left_player_.score_;
    m.ball_.center_.x = 2000;

    m.start_game();
    t.update();


    //Check to see if ball getting past player 1 increments player 2's score
    CHECK(m.left_player_.score_ == p2_old_score + 1);
}

TEST_CASE("Put rock on the screen")
{
    Model model;
    Controller c(model);
    Test_access t {model,c};
    model.start_game();
    model.ball_.center_.y = -100;
    model.ball_.velocity_.width = 0;
    t.update();
    t.update();
    t.update();
    CHECK(t.rocks_number_t() == 3);
    t.update();
    CHECK(t.rocks_number_t() == 3);
}


TEST_CASE("Destroying and returning rocks")
{
    Model model;
    Controller c(model);
    Test_access t {model,c};
    model.start_game();
    model.ball_.center_.y = -100;
    model.ball_.velocity_.width = 0;
    model.ball_.velocity_.height = 0;
    t.update();
    t.update();
    t.update();


    CHECK(t.rocks_number_t() == 3);

    for (Rock& r: model.rocks_) {
        if(r.onscreen_ == true) {
            model.ball_.center_ = r.rock.center();
            break;
        }
    }
    t.ball().destroy_rock(t.rock_t());
    model.ball_.center_.y = -100;
    CHECK(t.rocks_number_t() == 2);
    t.update();
    CHECK(t.rocks_number_t() == 3);
}

TEST_CASE("Winner")
{
    Model model;
    Controller c(model);
    Test_access t {model,c};
    model.start_game();
    model.left_player_.increment_score();
    model.left_player_.increment_score();
    model.left_player_.increment_score();
    t.update();
    CHECK(model.left_player_.score_ == 3);
    model.left_player_.increment_score();
    t.update();
    CHECK(model.winner_ == 0);
}


