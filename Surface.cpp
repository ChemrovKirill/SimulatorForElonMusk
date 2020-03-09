#include "Surface.h"

size_t screen_x = VideoMode::getDesktopMode().width;
size_t screen_y = VideoMode::getDesktopMode().height;
size_t window_x = screen_x - 200;
size_t window_y = screen_y - 200;


Surface::Surface() {
    pixel_size = window_x;
    center_position = Vector2f(0, window_y - 100);
    vertex_count = size_t(pixel_size / x_spacing);
    surface.setPrimitiveType(TriangleStrip);
    image.loadFromFile("images/" + file);
    texture.loadFromImage(image);
    Vector2f point = center_position;
    srand(time(NULL));
    float slope_direction;
    for (int i = 0; i <= 2 * vertex_count; ++i) {
        /*switch (rand() % 4)
        {
        case 0 :
            surface.append(Vertex(point, Color::Yellow));
            break;
        case 1:
            surface.append(Vertex(point, Color::Red));
            break;
        case 2:
            surface.append(Vertex(point, Color::Blue));
            break;
        case 3:
            surface.append(Vertex(point, Color::Green));
            break;
        }*/
        surface.append(Vertex(point, Color::White));
        surface[i].texCoords = Vector2f(x_spacing * ((i / 2) % 2), window_y - point.y);
        surface.append(Vertex(Vector2f(point.x, window_y), Color::Red));
        ++i;
        surface[i].texCoords = Vector2f(x_spacing * ((i / 2) % 2), 0);
        slope_direction = ((float)(rand() % 100)) / 100 - 0.5f;
        point.x += x_spacing;
        point.y += (float)(rand() % 40) * slope_direction;
    }
}


void Surface::Draw(RenderWindow& window) const {
    window.draw(surface, &texture);
}
