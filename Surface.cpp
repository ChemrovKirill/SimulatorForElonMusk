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

void mix(std::vector<int>& v) {
    for (int i = 0; i < v.size(); ++i) {
        int j = rand() % v.size();
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
}

Surface::Surface(const String& f, const int& _rough, const int& snow_cov)
: rough(_rough), file(f), snow_coverage(snow_cov) {
    pixel_size = 4 * window_x();
    left_position = Vector2f(-pixel_size/2, window_y() - 100);
    vertex_count = size_t(pixel_size / x_spacing);
    surface.setPrimitiveType(TriangleStrip);
    Generate();
}

void Surface::Generate() {
    surface.clear();
    lakes.clear();
    glaciers.clear();
    Vector2f point = left_position;
    srand(time(NULL));
    //srand(1234567890);

    float angle = 0;
    float prev_angle = 0;
    while (point.x < left_position.x + pixel_size) {
        int down_turn_board = down_board - tan(MAX_ANGLE) * 4 * step;   //down y from which U-turn starts
        int up_turn_board = up_board + tan(MAX_ANGLE) * 4 * step;       //up y from which U-turn starts
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
            GenerateSlope(point, point.x + step / 6, 2*rough, (prev_angle + (angle - prev_angle) / 3));
            GenerateSlope(point, point.x + step / 6, 2*rough, (prev_angle + 2 * (angle - prev_angle) / 3));
        }
        prev_angle = angle;
        int rand_rough = ((rand() % 3) + 1) * rough;
        GenerateSlope(point, point.x + step, rand_rough, angle);
        if (rand() % 10 < 5) {
            //GenerateSlope(point, point.x + step, rand_rough, rand() % 30);
            switch (rand() % 5) {
            case 0:
                GenerateHole(point, point.x + step, Hole::LAKE);
                break;
            case 1:
                GenerateHole(point, point.x + step, Hole::ICE);
                break;
            case 2:
                GenerateHole(point, point.x + step / 2, Hole::METEORITE);
                break;
            case 3:
                GenerateHole(point, point.x + step, Hole::EMPTY_U);
                break;
            case 4:
                GenerateHole(point, point.x + step, Hole::EMPTY_V);
                break;
            }
            //GenerateSlope(point, point.x + step, rand_rough, rand() % 30);
        }
    }
    GenerateSnow();
    SetTexture();
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
    if (i >= 0 && i < surface.getVertexCount()) { return surface[i]; }
    else if (i < 0) { return surface[0]; }
    else { return surface[surface.getVertexCount() - 1]; }
}

void Surface::Generate_V(Vector2f& point, const float& step, const int& step_count, const int& loc_rough) {
    std::vector<int> angles(step_count);
    for (auto& angle : angles) {
        angle = rand() % (MAX_ANGLE - 10) + 10;
        GenerateSlope(point, point.x + step, loc_rough, -angle);
    }
    mix(angles);
    for (const auto& angle : angles) {
        GenerateSlope(point, point.x + step, loc_rough, angle);
    }
}

void Surface::Generate_U(Vector2f& point, const float& step, const int& step_count, const int& loc_rough) {
    std::vector<int> angles(step_count);
    float a_step = 80 / step_count;
    for (int i = step_count - 1; i >=0; --i) {
        angles[i] = i*a_step;
        GenerateSlope(point, point.x + step, loc_rough, -angles[i]);
    }
    //mix(angles);
    for (const auto& angle : angles) {
        GenerateSlope(point, point.x + step, loc_rough, angle);
    }
}

void Surface::GenerateHole(Vector2f& point, const int& x_boarder, Hole h) {
    int level = point.y;
    int step_count = 10; //only descent
    float length = x_boarder - point.x;
    float step = length / (2 * step_count + 2);
    GenerateSlope(point, point.x + step, rough, 40);    //ascent before hole
    int iter = surface.getVertexCount();

    switch (h) {
    case Hole::EMPTY_V:
        Generate_V(point, step, step_count, 2*rough);
    case Hole::LAKE:
        Generate_V(point, step, step_count, 0);
        break;
    case Hole::ICE:
        Generate_V(point, step, step_count, 5*rough);
        break;
    case Hole::METEORITE:
    case Hole::EMPTY_U:
        Generate_U(point, step, step_count, 3*rough);
        break;
    }

    int hole_board = surface.getVertexCount();
    GenerateSlope(point, point.x + step, rough, -40);   //descent before hole

    switch (h) {
    case Hole::EMPTY_V:
    case Hole::EMPTY_U:
        break;
    case Hole::LAKE:
    {
        VertexArray lake;
        lake.setPrimitiveType(TrianglesStrip);
        Vector2f v1, v2;
        while (iter < hole_board) {
            v2 = Vector2f(surface[iter].position.x, level + rand() % 3 + 20);
            lake.append(Vertex(v2, Color::Blue));
            ++iter;
            v1 = Vector2f(surface[iter].position.x, surface[iter].position.y);
            lake.append(Vertex(v1, Color::Blue));
            ++iter;
        }
        lakes.push_back(lake);
        break;
    }
    case Hole::ICE:
    {
        VertexArray glacier;
        glacier.setPrimitiveType(TrianglesStrip);
        Vector2f v1;
        Vector2f v2 = Vector2f(surface[iter].position.x, level);
        int mid_iter = (hole_board + iter) / 2;
        int slope = rand() % 20 + 20;
        while (iter < hole_board) {
            int dy = rand() % slope / 10.0 * x_spacing;
            if (iter < mid_iter) {
                v2.y -= dy;
            }
            else {
                v2.y += dy;
            }
            v2.x = surface[iter].position.x;
            glacier.append(Vertex(v2, Color::White));
            ++iter;
            v1 = Vector2f(surface[iter].position.x, surface[iter].position.y);
            glacier.append(Vertex(v1, Color::White));
            ++iter;
        }
        glaciers.push_back(glacier);
        break;
    }
    case Hole::METEORITE:
    {
        VertexArray meteorite;
        meteorite.setPrimitiveType(TrianglesStrip);
        Vector2f v = surface[iter].position;
        float mid_level = v.y;
        meteorite.append(Vertex({ v.x + x_spacing/2, mid_level }, Color::Cyan));
        iter += 2;
        while (iter < hole_board-2) {
            v = surface[iter].position;
            meteorite.append(Vertex(v, Color::Cyan));
            ++iter;
            v.y = -v.y + 2*mid_level + rand()%20 - 10;
            meteorite.append(Vertex(v, Color::Cyan));
            ++iter;
        }
        meteorite.append(Vertex({ v.x + x_spacing / 2, mid_level }, Color::Cyan));
        meteorites.push_back(meteorite);
        break;
    }
    }
}

void Surface::GenerateSnow() {
    int i = 0;
    int piece_lengh = 50;
    while (i+2 < surface.getVertexCount()) {
        if (rand() % 100 < snow_coverage) {
            VertexArray snow_piece;
            snow_piece.setPrimitiveType(TrianglesStrip);
            for (int j = 0; i < surface.getVertexCount() && j < piece_lengh; ++j) {
                Vector2f point = surface[i].position;
                snow_piece.append(Vertex(point, Color::White));
                point.y += 50;
                snow_piece.append(Vertex(point, Color::Transparent));
                i += 2;
            }
            snow.push_back(snow_piece);
            i -= 2;
        }
        else {
            i += 2*piece_lengh;
        }
    }
}

void Surface::GenerateSlope(Vector2f& point, const int& x_boarder, const int& loc_rough, const float& angle) {
    while (point.x < x_boarder) {
        float slope_direction = 0;
        surface.append(Vertex(point, Color::White));
        surface.append(Vertex(Vector2f(point.x, down_board), Color::White));
        if (rand() % 100 < 50) {
            slope_direction = ((float)(rand() % 100)) / 100.0 - 0.5f;
        }
        point.x += x_spacing;
        point.y += (float)(loc_rough)*slope_direction;
        point.y += -tan(RAD * angle) * x_spacing;
    }
}

void Surface::SetTexture() {
    texture.loadFromFile("images/" + file);
    texture.setRepeated(true);
    int count = surface.getVertexCount();
    for (int i = 0; i < count; ++i) {
        surface[i].texCoords = surface[i].position;
        surface[i].color = Color::White;
        if (surface[i].position.x == 0) {
            iter_0 = i;
        }
    }
    ice_texture.loadFromFile("images/ice.png");
    ice_texture.setRepeated(true);
    for (auto& glacier : glaciers) {
        count = glacier.getVertexCount();
        for (int i = 0; i < count; ++i) {
            glacier[i].texCoords = glacier[i].position;
            glacier[i].color = Color::White;
        }
    }
    meteorite_texture.loadFromFile("images/meteorite.png");
    meteorite_texture.setRepeated(true);
    for (auto& meteorite : meteorites) {
        count = meteorite.getVertexCount();
        for (int i = 0; i < count; ++i) {
            meteorite[i].texCoords = meteorite[i].position;
            meteorite[i].color = Color::Red;
        }
    }
    /*int start = rand() % count;
    int end = start + rand() % (count / 10);
    for (int i = start; i < end && i < count; ++i) {
        surface[i].color = Color::Magenta;
    }*/
}

void Surface::Update(const float& dt) { //water animation
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

    for (const auto& glacier : glaciers) {
        window.draw(glacier, &ice_texture);
    }

    for (const auto& meteorite : meteorites) {
        window.draw(meteorite, &meteorite_texture);
    }

    window.draw(surface, &texture);

    for (const auto& snow_piece : snow) {
        window.draw(snow_piece);
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
