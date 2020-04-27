#include "Surface.h"

void Surface::Generate() {
    surface.clear();
    lakes.clear();
    glaciers.clear();
    Vector2f point = left_position;

    float angle = 0;
    float prev_angle = 0;
    while (point.x < left_position.x + pixel_size) {
        int down_turn_board = down_board - tan(max_angle) * 6 * step;   //down y from which U-turn starts
        int up_turn_board = up_board + tan(max_angle) * 4 * step;       //up y from which U-turn starts
        if (point.y > down_turn_board) {
            angle = rand() % 50 + 10;
        }
        else if (point.y < up_turn_board) {
            angle = rand() % 50 - 60;
        }
        else {
            angle = rand() % (max_angle * 2 + 1) - max_angle;
        }
        if (abs(angle - prev_angle) > 0) {
            GenerateSlope(point, point.x + step / 6, 2 * rough, (prev_angle + (angle - prev_angle) / 3));
            GenerateSlope(point, point.x + step / 6, 2 * rough, (prev_angle + 2 * (angle - prev_angle) / 3));
        }
        prev_angle = angle;
        int rand_rough = ((rand() % 3) + 1) * rough;
        GenerateSlope(point, point.x + step, rand_rough, angle);
        float size = (rand() % 20+1.0) / 10;
        switch (rand() % 5) {
        case 0:
            if (rand() % 100 < probability[Hole::LAKE]) {
                GenerateHole(point, point.x + size*step, Hole::LAKE);
            }
            break;
        case 1:
            if (rand() % 100 < probability[Hole::ICE]) {
                GenerateHole(point, point.x + size*step, Hole::ICE);
            }
            break;
        case 2:
            if (rand() % 100 < probability[Hole::METEORITE]) {
                GenerateHole(point, point.x + size*step / 2, Hole::METEORITE);
            }
            break;
        case 3:
            if (rand() % 100 < probability[Hole::EMPTY_U]) {
                GenerateHole(point, point.x + size*step / 2, Hole::EMPTY_U);
            }
            break;
        case 4:
            if (rand() % 100 < probability[Hole::EMPTY_V]) {
                GenerateHole(point, point.x + size*step, Hole::EMPTY_V);
            }
            break;           
        default:
            break;
        }
        //FLAT
        if (rand() % 100 < 20) {
            int angle = 0;
            planes[point.x] = point.x + step * size;
            GenerateSlope(point, point.x + step*size, rough*0, angle);
        }
        //GenerateSlope(point, point.x + step, rand_rough, rand() % 30);
    }
    GenerateSnow();
    ColorGenerate();
    SetTexture();
}

void Surface::ColorGenerate() {
    //***SURFACE__COLOR***//
    switch (rand() % 17) {
    case 0:
        surface_color = Color(0xb00000ff); //dark red
        break;
    case 1:
        surface_color = Color(0x600000ff); //darker red
        break;
    case 2:
        surface_color = Color(0x0000b0ff); //dark blue
        break;
    case 3:
        surface_color = Color(0x000060ff); //darker blue
        break;
    case 4:
        surface_color = Color(0x00b000ff); //dark green
        break;
    case 5:
        surface_color = Color(0x006000ff); //darker green
        break;
    case 6:
        surface_color = Color(0x800080ff); //purple
        break;
    case 7:
        surface_color = Color(0x4b0082ff); //indigo
        break;
    case 8:
        surface_color = Color(0xff00ffff); //pink
        break;
    case 9:
        surface_color = Color(0x808080ff); //grey
        break;
    case 10:
        surface_color = Color(0x708090ff); //slate gray
        break;
    case 11:
        surface_color = Color(0x2f4f4fff); //dark slate grey
        break;
    case 12:
        surface_color = Color(0xfcdd76ff); //sand
        break;
    case 13:
        surface_color = Color(0xcccc00ff); //dark yellow
        break;
    case 14:
        surface_color = Color(0x808000ff); //olive
        break;
    case 15:
        surface_color = Color(0xd18800ff); //dark orange
        break;
    case 16:
        surface_color = Color(0x452d01ff); //brown
        break;
    }
    //***LAKES__COLOR***//
    switch (rand() % 4) {
    case 0:
        lakes_color = Color(0x30c25ad0); //green
        break;
    case 1:
        lakes_color = Color(0x3030dfd0); //blue
        break;
    case 2:
        lakes_color = Color(0x9f0000d0); //red
        break;
    case 3:
        lakes_color = Color(0xffcf00d0); //yellow
        break;
    }
    //***METEORITES__COLOR***//
    switch (rand() % 5) {
    case 0:
        meteorites_color = Color(0xb00000ff); //dark red
        break;
    case 1:
        meteorites_color = Color(0x708090ff); //slate gray
        break;
    case 2:
        meteorites_color = Color(0xcccc00ff); //dark yellow
        break;
    case 3:
        meteorites_color = Color(0x4b0082ff); //indigo
        break;
    case 4:
        meteorites_color = Color(0xd18800ff); //dark orange
        break;
    }
}

void Surface::Generate_V(Vector2f& point, const float& step, const int& step_count, const int& loc_rough) {
    std::vector<int> angles(step_count);
    for (auto& angle : angles) {
        angle = rand() % (60) + 10;
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
    for (int i = step_count - 1; i >= 0; --i) {
        angles[i] = i * a_step;
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
        Generate_V(point, step, step_count, 2 * rough);
    case Hole::LAKE:
        Generate_V(point, step, step_count, 0);
        break;
    case Hole::ICE:
        Generate_V(point, step, step_count, 5 * rough);
        break;
    case Hole::METEORITE:
    case Hole::EMPTY_U:
        Generate_U(point, step, step_count, 3 * rough);
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
        int dy;
        while (iter < hole_board) {
            dy = rand() % slope / 10.0 * x_spacing;
            if (iter < mid_iter) {
                v2.y -= dy;
            }
            else {
                v2.y += dy;
            }
            v2.x = surface[iter].position.x;
            glacier.append(Vertex(v2, Color::White)); //top
            v1 = Vector2f(surface[iter].position); //bottom
            glacier.append(Vertex(v1, Color::White));
            iter += 2;
        }
        //smoothing
        int Count = glacier.getVertexCount();
        int dif = glacier[Count - 1].position.y - glacier[Count - 2].position.y;
        std::cout << dif << std::endl;
        if(dif > 30) {
            for (int i = 1; i < 5; ++i) {
              glacier[Count -10 + 2 * i].position.y += dif*i/5;
            }
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
        meteorite.append(Vertex({ v.x + x_spacing / 2, mid_level }, Color::Cyan));
        iter += 2;
        while (iter < hole_board - 2) {
            v = surface[iter].position;
            meteorite.append(Vertex(v, Color::Cyan));
            ++iter;
            v.y = -v.y + 2 * mid_level + rand() % 20 - 10;
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
    while (i + 2 < surface.getVertexCount()) {
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
            i += 2 * piece_lengh;
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