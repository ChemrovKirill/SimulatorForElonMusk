#include "Surface.h"

size_t screen_x() {
    return VideoMode::getDesktopMode().width;
}
size_t screen_y() {
    return VideoMode::getDesktopMode().height;
}
size_t window_x() {
    return screen_x() - 200;
}
size_t window_y() {
    return screen_y() - 200;
}

Surface::Surface(const String& f, const float& spacing)
: x_spacing(spacing), file(f) {
    pixel_size = 20 * window_x();
    left_position = Vector2f(-pixel_size/2, window_y() - 100);
    vertex_count = size_t(pixel_size / x_spacing);
    surface.setPrimitiveType(TriangleStrip);
    image.loadFromFile("images/" + file);
    texture.loadFromImage(image);
    Generate(10);
}

void Surface::GenerateSlope(Vector2f& point, const int& x_boarder, const size_t& rough, int& i, const float& angle) {
    while (point.x < x_boarder) {
        float slope_direction = 0;
        surface.append(Vertex(point, Color::Red));
        surface[i].texCoords = Vector2f(x_spacing * ((i / 2) % 2), down_board - point.y);
        surface.append(Vertex(Vector2f(point.x, down_board), Color::Red));
        ++i;
        surface[i].texCoords = Vector2f(x_spacing * ((i / 2) % 2), 0);
        ++i;
        if (rand() % 100 < 50) {
            slope_direction = ((float)(rand() % 100)) / 100 - 0.5f;
            std::cout << "1 ";
        }
        point.x += x_spacing;
        point.y += (float)(rough)*slope_direction;
        point.y += -tan(RAD * angle) * x_spacing;
    }
}

void Surface::Generate(const size_t& rough) {
    surface.clear();
    Vector2f point = left_position;
    srand(time(NULL));
    
    std::cout << vertex_count << std::endl;
    float angle;
    float prev_angle = 0;
    for (int i = 0; i <= 2* vertex_count;) {
        if (point.y > down_board * 2.0 / 3) {
            angle = rand() % 50 + 10;
        }
        else if (point.y < up_board * 2.0 / 3) {
            angle = rand() % 50 - 60;
        }
        else {
            angle = rand() % 140 - 70;
        }
        if (abs(angle - prev_angle) > 60) {
            GenerateSlope(point, point.x + pixel_size / 180, 20, i, (prev_angle + (angle - prev_angle)/3));
            GenerateSlope(point, point.x + pixel_size / 180, 20, i, (prev_angle + 2*(angle - prev_angle) / 3));
        }
        prev_angle = angle;
        GenerateSlope(point, point.x + pixel_size/30, 20, i, angle);
    }
}

//else {
        //    std::cout << "2 ";
        //    if (slope_direction < 0.5 && slope_direction > 0) {
        //        std::cout << "2down ";
        //        slope_direction += (((float)(rand() % 100)) / 50.0);
        //    }
        //    else if (slope_direction > -0.5 && slope_direction < 0) {
        //        std::cout << "2up ";
        //        slope_direction -= ((float)(rand() % 100)) / 100 - 0.5f;
        //    }
        //}
        //point.y += (float)(rand() % rough) * slope_direction;

void Surface::Draw(RenderWindow& window) const {
    window.draw(surface, &texture);
}
