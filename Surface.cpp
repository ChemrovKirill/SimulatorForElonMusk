#include "Surface.h"

#define MAX_ANGLE 70

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
    texture.setRepeated(true);
    Generate(10);
}

void Surface::GenerateSlope(Vector2f& point, const int& x_boarder, const size_t& rough, const float& angle) {
    while (point.x < x_boarder) {
        float slope_direction = 0;
        surface.append(Vertex(point, Color::White));
        surface.append(Vertex(Vector2f(point.x, down_board), Color::White));
        if (rand() % 100 < 50) {
            slope_direction = ((float)(rand() % 100)) / 100.0 - 0.5f;
        }
        point.x += x_spacing;
        point.y += (float)(rough)*slope_direction;
        point.y += -tan(RAD * angle) * x_spacing;
    }
}

void Surface::SetTexture() {
    int count = surface.getVertexCount();
    for (int i = 0; i < count; ++i) {
        surface[i].texCoords = Vector2f(surface[i].position.x, surface[i].position.y);
        surface[i].color = Color::Red;
        if (surface[i].position.x == 0) {
            iter_0 = i;
            std::cout << "iter_0 = " << iter_0 << std::endl;
            std::cout << surface.getVertexCount() << std::endl;
        }
    }
    int start = rand() % count;
    int end = start + rand() % (count / 10);
    for (int i = start; i < end && i < count; ++i) {
        surface[i].color = Color::Magenta;
    }
}

void Surface::Generate(const size_t& rough) {
    surface.clear();
    Vector2f point = left_position;
    srand(time(NULL));

    float angle;
    float prev_angle = 0;
    int step = pixel_size / 30;
    while (point.x < left_position.x + pixel_size) {
        int down_turn_board = down_board - tan(MAX_ANGLE) * 2 * step;
        int up_turn_board = up_board + tan(MAX_ANGLE) * 2 * step;
        if (point.y > down_turn_board) {
            angle = rand() % 50 + 10;
        }
        else if (point.y < up_turn_board) {
            angle = rand() % 50 - 60;
        }
        else {
            angle = rand() % (MAX_ANGLE * 2) - MAX_ANGLE;
        }
        if (abs(angle - prev_angle) > 0) {
            GenerateSlope(point, point.x + step / 6, 20, (prev_angle + (angle - prev_angle) / 3));
            GenerateSlope(point, point.x + step / 6, 20, (prev_angle + 2 * (angle - prev_angle) / 3));
        }
        prev_angle = angle;
        int rand_rough = ((rand() % 3) + 1) * rough;
        GenerateSlope(point, point.x + step, rand_rough, angle);
        if (rand() % 10 < 3) {
            GenerateSlope(point, point.x + step, rand_rough, rand() % 30);
        }
    }
    SetTexture();
}

void Surface::Draw(RenderWindow& window) const {
    window.draw(surface, &texture);
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


