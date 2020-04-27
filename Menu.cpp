#include "Menu.h"


using namespace sf;

void Menu(RenderWindow & window) {
	bool isMenu = true;
	std::vector<Button> buttons;
    float x_pos = window_x() / 2 - 175;
    buttons.push_back(Button( "Start", { x_pos, 200 } ));
    buttons.push_back(Button( "Exit", { x_pos, 400 } ));
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
            IntRect b_rect = buttons[i].GetIntRect();
			if (b_rect.contains(Mouse::getPosition(window))) {
				selected_button = i;
			}
			buttons[i].SetSelected(0);
		}

		buttons[selected_button].SetSelected(1);
		for (int i = 0; i < buttons.size(); ++i) {
			buttons[i].Draw(window);
		}

		window.display();

		if (Mouse::isButtonPressed(Mouse::Left) || Keyboard::isKeyPressed(Keyboard::Enter)) {
			switch (selected_button) {
			case 0:
				StartGame(window);
				//isMenu = false;
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

void StartGame(RenderWindow& window) {
    //5ea71d5d
    //5ea71d85
    //5ea71d8f
    unsigned int seed = time(NULL);
    std::cout << "seed: " << seed << std::endl;
    srand(seed);

    bool if_back = 0;
    Surface s = PlanetSelection(window, if_back);
    if(if_back) {
        return;
    }

    float dt = 0, time = 0;
    Clock deltaTime;

    Lunar_Lander_Mark1 lander(Vector2f(0, s.YtoX(200) - 500));

    View view;
    view.setCenter(sf::Vector2f(window_x() / 2, window_y() / 2));
    view.setSize(sf::Vector2f(window_x(), window_y()));


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape) {
                    window.setView(View({0, 0, float(window_x()), float(window_y())}));
                    return;
                }
            }
        }

       if (dt > 0.5){
            dt = 0;
            //deltaTime.restart().asSeconds();
            continue;
       }

        window.clear();

        lander.control();

        lander.CollisionDetection(s, window);

        lander.UpdateShipPosition(dt);

        lander.DrawShip(window);

        lander.drow_all(window, true, true, false, true, true);

        view.setCenter(lander.GetCenterPosition());
        window.setView(view);

        s.Update(dt);
        s.Draw(window);

        lander.CollisionDetection(s, window);
        lander.CollisionModelDrow(window);

        window.display();

        time += dt;
        //std::cout << dt << std::endl;
        dt = deltaTime.restart().asSeconds();
        while (Keyboard::isKeyPressed(Keyboard::Space)) { dt = deltaTime.restart().asSeconds(); }
    }
}