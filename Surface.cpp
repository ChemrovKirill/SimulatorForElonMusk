#include "Surface.h"

size_t screen_x() {
    return VideoMode::getDesktopMode().width;
}
size_t screen_y() {
    return VideoMode::getDesktopMode().height;
}
size_t window_x() {
    return screen_x() - 300;
}
size_t window_y() {
    return screen_y() - 300;
}

void mix(std::vector<int>& v) {
    for (int i = 0; i < v.size(); ++i) {
        int j = rand() % v.size();
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
}

Surface::Surface(const String& f, const int& _rough, const int& snow_cov, std::map<Hole, int> prob, int m_angle)
: rough(_rough), file(f), snow_coverage(snow_cov), probability(prob), max_angle(m_angle) {
    pixel_size = 20 * window_x();
    left_position = Vector2f(-pixel_size/2, window_y() - 100);
    vertex_count = size_t(pixel_size / x_spacing);
    surface.setPrimitiveType(TriangleStrip);
    Generate();
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

void Surface::SetTexture() {
    texture.loadFromFile("images/" + file);
    texture.setRepeated(true);
    int count = surface.getVertexCount();
    for (int i = 0; i < count; ++i) {
        surface[i].texCoords = surface[i].position;
        surface[i].color = surface_color;
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
            meteorite[i].color = meteorites_color;
        }
    }
    for (auto& lake : lakes) {
        count = lake.getVertexCount();
        for (int i = 0; i < count; ++i) {
            lake[i].color = lakes_color;
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
