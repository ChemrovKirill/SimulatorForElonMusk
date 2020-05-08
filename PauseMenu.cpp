#include "Menu.h"

bool PauseMenu(RenderWindow& window, bool& isPaused, View& view) {
    std::vector<Button> buttons;
    float x_pos = -175 + view.getCenter().x;
    float y_pos = view.getCenter().y - window_y() / 2;
    buttons.push_back(Button("Continue", { x_pos, y_pos + 200 }));
    buttons.push_back(Button("Menu", { x_pos, y_pos + 400 }));

    static int selected_button = 0;

    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed) {
            window.close();
            return 0;
        }
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Escape) {
                isPaused = false;
            }
            if (event.key.code == Keyboard::W || event.key.code == Keyboard::Up) {
                selected_button = (selected_button + 1) % buttons.size();
            }
            if (event.key.code == Keyboard::S || event.key.code == Keyboard::Down) {
                selected_button = (selected_button - 1) % buttons.size();
            }
        }
        if (event.type == Event::KeyReleased || event.type == Event::MouseButtonReleased) {
            if (event.key.code == Keyboard::Enter || event.mouseButton.button == Mouse::Left) {
                switch (selected_button) {
                case 0:
                    isPaused = false;
                    return 1;
                    break;
                case 1:
                    return 0;
                    break;
                default:
                    break;
                }
            }
        }
    }
    for (int i = 0; i < buttons.size(); ++i) {
        IntRect b_rect = buttons[i].GetIntRect();
        Vector2i mouse_pos = Mouse::getPosition(window);
        mouse_pos.x += (view.getCenter().x - window_x() / 2);
        mouse_pos.y += (view.getCenter().y - window_y() / 2);
        if (b_rect.contains(mouse_pos)) {
            selected_button = i;
        }
        buttons[i].SetSelected(0);
    }

    buttons[selected_button].SetSelected(1);
    for (int i = 0; i < buttons.size(); ++i) {
        buttons[i].Draw(window);
    }

    //view.setCenter(sf::Vector2f(window_x() / 2, window_y() / 2));
    view.setSize(sf::Vector2f(window_x(), window_y()));
    window.setView(view);
}