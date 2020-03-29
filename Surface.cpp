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
    pixel_size = 10 * window_x();
    left_position = Vector2f(-pixel_size/2, window_y() - 100);
    vertex_count = size_t(pixel_size / x_spacing);
    surface.setPrimitiveType(TriangleStrip);
    image.loadFromFile("images/" + file);
    texture.loadFromImage(image);
    texture.setRepeated(true);
    Generate(10);
}

int Surface::Get_iter_0() const { return iter_0; }
float Surface::YtoX(const float& x) {
    int iter = iter_0 + 1 + 2*int(x)/ x_spacing;
    if (x < left_position.x || x > left_position.x + vertex_count*x_spacing) {
        throw std::out_of_range("Surface::YtoX()");
    }
    return surface[iter].position.y;
}

float Surface::Get_spacing() const { return x_spacing; }
size_t Surface::Get_VertexCount() const {
    return surface.getVertexCount();
}
Vertex Surface::GetVertex(const int& i) const {
    if (i >= 0 && i < surface.getVertexCount()) {
        return surface[i];
    }
}

void Surface::GenerateLake(Vector2f& point, const int& x_boarder, const size_t& rough) {
    int level = point.y;
    int iter = surface.getVertexCount();
    float length = x_boarder - point.x;
    int angles[10];
    for (int i = 0; i < 10; ++i) {
        angles[i] = rand() % (MAX_ANGLE-10)+10;
        std::cout << i << ": " << angles[i] << std::endl;
        GenerateSlope(point, point.x + length / 20, rough, -angles[i]);
    }
    for (int i = 0; i < 10; ++i) {
        int j = rand() % 10;
        int temp = angles[i];
        angles[i] = angles[j];
        angles[j] = temp;
    }
    for (int i = 0; i < 10; ++i) {
        GenerateSlope(point, point.x + length / 20, rough, angles[i]);
    }
    VertexArray lake;
    lake.setPrimitiveType(TrianglesStrip);
    Vector2f v1, v2;
    while (iter < surface.getVertexCount()) {
        v2 = Vector2f(surface[iter].position.x, level+rand()%3+10);
        lake.append(Vertex(v2, Color::Blue));
        ++iter;
        v1 = Vector2f(surface[iter].position.x, surface[iter].position.y);
        lake.append(Vertex(v1, Color::Blue));
        ++iter;
    }
   // lake.append(Vertex(Vector2f(v2.x+x_spacing,v2.y), Color::Blue));

    lakes.push_back(lake);
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
    lakes.clear();
    Vector2f point = left_position;
    srand(time(NULL));

    float angle;
    float prev_angle = 0;
    int step = pixel_size / 30;
    while (point.x < left_position.x + pixel_size) {
        int down_turn_board = down_board - tan(MAX_ANGLE) * 4 * step;
        int up_turn_board = up_board + tan(MAX_ANGLE) * 4 * step;
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
        if (rand() % 10 < 5) {
            //GenerateSlope(point, point.x + step, rand_rough, rand() % 30);
            if (rand() % 10 < 10) {
              GenerateLake(point, point.x + step, rand_rough);
            }
            //GenerateSlope(point, point.x + step, rand_rough, rand() % 30);
        }
    }
    SetTexture();
}

void Surface::Update(const float& dt) {
    static float timer = 0.5;
    timer += dt;
    if (timer > 1) {
        timer = -1;
    }
    float shift;
    for (auto& lake : lakes) {
        for (int i = 0; i < lake.getVertexCount(); i += 2) {
            if((i/2)%3 == 0) {
                shift = timer / abs(timer) * 3 * dt;
            }
            else if((i / 2) % 3 == 2) {
                shift = -timer / abs(timer) * 3 * dt;
            }
            lake[i].position.y += shift;

        }
    }
}

void Surface::Draw(RenderWindow& window) const {
    for (const auto& lake : lakes) {
        window.draw(lake);
    }
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

