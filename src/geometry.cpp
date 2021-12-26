#include "geometry.h"

Geometry::Geometry() noexcept
        : ball_radius    {5}
        , max_boost      {4}
        , ball_velocity0 {4, 0}
        , scene_dims     {1024, 768}
        , paddle_dims_   {20, 300}
        , rock_size_ {13}
{ }