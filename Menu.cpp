#include "Menu.h"
#include "Surface.h"

using namespace sf;

void Menu(RenderWindow & window) {
	bool isMenu = true;
	std::vector<Object> buttons;
	buttons.push_back(Object("Button_Start.png", { 500, 200 }, 489, 139, 0));
	buttons.push_back(Object("Button_Exit.png", { 500, 400 }, 489, 139, 0));
	Texture bg_texture;
	bg_texture.loadFromFile("images/background.png");
	bg_texture.setRepeated(true);
	Sprite bg_sprite;
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setTextureRect({ 0, 0, int(window_x()), int(window_y()) });

	int selected_button = 0;

	while (isMenu) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
				isMenu = false;
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::W || event.key.code == Keyboard::Up) {
					selected_button = (selected_button + 1) % buttons.size();
				}
				if (event.key.code == Keyboard::S || event.key.code == Keyboard::Down) {
					selected_button = (selected_button - 1) % buttons.size();
				}
			}
		}

		window.clear();
		window.draw(bg_sprite);


		for (int i = 0; i < buttons.size(); ++i) {
			IntRect b_rect(buttons[i].GetPosition().x, buttons[i].GetPosition().y,
							buttons[i].GetWidth(), buttons[i].GetHeight());
			if (b_rect.contains(Mouse::getPosition(window))) {
				selected_button = i;
			}
			buttons[i].Sprite().setColor(Color(0x0000f0ff));
		}

		buttons[selected_button].Sprite().setColor(Color(0xf00000ff));
		for (int i = 0; i < buttons.size(); ++i) {
			buttons[i].Draw(window);
		}

		window.display();

		if (Mouse::isButtonPressed(Mouse::Left) || Keyboard::isKeyPressed(Keyboard::Enter)) {
			switch (selected_button) {
			case 0:
				isMenu = false;
				break;	
			case 1:
				window.close();
				isMenu = false;
				break;
			default:
				break;
			}
		}
	}
}

