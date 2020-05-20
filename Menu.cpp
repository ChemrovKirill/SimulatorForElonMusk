#include "Menu.h"

using namespace sf;

int SoundVolume;
int MusicVolume;

void Menu(RenderWindow & window) {
    unsigned int seed = time(NULL);
    std::cout << "seed: " << seed << std::endl;
    srand(seed);

    SoundVolume = 100;
    MusicVolume = 100;
    Music music;
    //switch (rand() % 4) {
    //case 0:
    //    music.openFromFile("music/phantom_from_space.wav");
    //    break;
    //case 1:
    //    music.openFromFile("music/decisions.wav");
    //    break;
    //case 2:
    //    music.openFromFile("music/myst_on_the_moor.wav");
    //    break;
    //case 3:
    //    music.openFromFile("music/deep_haze.wav");
    //    break;
    //}
    music.openFromFile("music/deep_haze.wav");
    music.setLoop(true);
    music.setVolume(MusicVolume);
    music.play();

    Text MusicBy;
    Font font;
    font.loadFromFile("fonts/FRAHV.ttf");
    MusicBy = Text("Music: Kevin MacLeod - Deep Haze", font, 30);
    MusicBy.setPosition({ window_x() - MusicBy.getLocalBounds().width-30, window_y() - MusicBy.getLocalBounds().height -30});

    Object title("Title.png", { 0, 0 }, 500, 200, 0);
    title.SetPosition({ (window_x() - title.GetWidth()) / 2, 20 }, 0);
    title.Sprite().setColor(Color(0x0000b0ff));

	bool isMenu = true;
	std::vector<Button> buttons;
    float x_pos = window_x() / 2 - 175;
    buttons.push_back(Button( "Start", { x_pos, 300 } ));
    buttons.push_back(Button("Settings", { x_pos, 450 }));
    buttons.push_back(Button( "Exit", { x_pos, 600 } ));
	Texture bg_texture;
	bg_texture.loadFromFile("images/background.png");
	bg_texture.setRepeated(true);
	Sprite bg_sprite;
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setTextureRect({ 0, 0, int(window_x()), int(window_y()) });
	
	int selected_button = 0;

    View view; 

	while (isMenu && window.isOpen()) {
		Event event;
		
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
				isMenu = false;
			}
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::W || event.key.code == Keyboard::Up) {
					selected_button = (selected_button - 1 + buttons.size()) % buttons.size();
				}
				if (event.key.code == Keyboard::S || event.key.code == Keyboard::Down) {
					selected_button = (selected_button + 1 + buttons.size()) % buttons.size();
				}
			}
            if (event.type == Event::KeyReleased || event.type == Event::MouseButtonReleased) {
                if (event.key.code == Keyboard::Enter || event.mouseButton.button == Mouse::Left) {
                    switch (selected_button) {
                    case 0: //start
                        StartGame(window);
                        //isMenu = false;
                        break;
                    case 1: //settings
                        Settings(window, music);
                        break;
                    case 2: //exit
                        window.close();
                        isMenu = false;
                        break;
                    default:
                        break;
                    }
                }
            }
			

		}

        view.setCenter(sf::Vector2f(window_x() / 2, window_y() / 2));
        view.setSize(sf::Vector2f(window_x(), window_y()));
        window.setView(view);

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

        title.Draw(window);
        window.draw(MusicBy);

		window.display();
	}
}

Lander_Parametr par; //for STM32

void StartGame(RenderWindow& window) {
	
    Music music;
    switch (rand() % 4) {
    case 0:
        music.openFromFile("music/phantom_from_space.wav");
        break;
    case 1:
        music.openFromFile("music/decisions.wav");
        break;
    case 2:
        music.openFromFile("music/myst_on_the_moor.wav");
        break;
    case 3:
        music.openFromFile("music/deep_haze.wav");
        break;
    }
    music.setLoop(true);
    music.setVolume(10);
    music.play();
    //5ea71d5d
    //5ea71d85
    //5ea71d8f
    unsigned int seed = time(NULL);
    std::cout << "seed: " << seed << std::endl;
    srand(seed);

    bool if_Menu = 0;
    Surface surface = PlanetSettings(window, if_Menu);
    if(if_Menu) {
        return;
    }

    Ship* lander = ShipSettings(window, Vector2f(0, surface.YtoX(200) - 500), if_Menu);
    lander->AddMainForces(surface.GetGravity());
    if (if_Menu) {
        return;
    }
	Interface interf(lander->GetHeight(),lander->GetAngle(),0,0,0,0,0, "Strat");
    //Lunar_Lander_Mark1_STM32 l(Vector2f(0, s.YtoX(200) - 500));   //for STM32
    //Lunar_Lander_Mark1 l(Vector2f(0, s.YtoX(200) - 500));
    //RickAndMorty l(Vector2f(0, s.YtoX(200) - 500));

    Vector2f start_pos = Vector2f(0, surface.YtoX(200) - 500);

    Space space("Space2.png", start_pos);


    while (!if_Menu) {

        Ship* lander = ShipSettings(window, start_pos, if_Menu);
        lander->AddMainForces(surface.GetGravity());
        if (if_Menu) {
            return;
        }

        //Lunar_Lander_Mark1_STM32 l(Vector2f(0, s.YtoX(200) - 500));   //for STM32
        //Lunar_Lander_Mark1 l(Vector2f(0, s.YtoX(200) - 500));
        //RickAndMorty l(Vector2f(0, s.YtoX(200) - 500));   

        View view;
        view.setCenter(sf::Vector2f(window_x() / 2, window_y() / 2));
        view.setSize(sf::Vector2f(window_x(), window_y()));

        float dt = 0, time = 0;
        Clock deltaTime;

        bool isPaused = 0;
        bool Restart = 0;

        while (window.isOpen() && !Restart)
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
                        window.setView(View({ 0, 0, float(window_x()), float(window_y()) }));
                        isPaused = (isPaused + 1) % 2;
                        window.clear();
                    }
                }
            }

            //pause in case of window moving
            if (dt > 0.3) {
                dt = 0;
                //deltaTime.restart().asSeconds();
                continue;
            }

            //START_DRAWING
            window.clear();

        surface.Draw(window);
		interf.SetAngle(lander->GetAngle());
		interf.SetHeight(-lander->GetPosition().y);
		interf.SetAngVelocity(lander->GetAngleVelocity());
		interf.SetFuel(lander->GetFuel());
		interf.SetVelocityX(lander->GetVelocity().x);
		interf.SetVelocityY(lander->GetVelocity().y);
		interf.SetCoordinate_X(lander->GetPosition().x);
		interf.SetStatus(lander->GetStatusText());
		interf.Draw(window, view);
        //END_DRAWING
            space.Draw(window);

            lander->DrawShip(window);
            lander->draw_all(window, true, true, true, true, true);
            lander->DrawFlyStatus(dt);

            view.setCenter(lander->GetCenterPosition());
            window.setView(view);

            surface.Draw(window);
            //END_DRAWING

            if (isPaused) {
                dt = 0;
                if (!PauseMenu(window, isPaused, Restart, view)) { //if main menu
                    return;
                }

            }
            else {
                lander->control();
                //lander->updateAirForce(surface.GetAirDensity());
                lander->UpdateShipPosition(dt);
                lander->CollisionDetection(surface, window);
                //l.control_STM(par);

                space.Update(view);

                surface.Update(dt);
                par.data_update(lander);

                USART(par, par.data_to_send()); //for STM32
            }

            USART(par, par.data_to_send()); //for STM32
        }
		

            time += dt;
            //std::cout << dt << std::endl;
            dt = deltaTime.restart().asSeconds();

            //std::cout <<  lander->GetFuel() << std::endl;

            window.display();
            //while (Keyboard::isKeyPressed(Keyboard::Space)) { dt = deltaTime.restart().asSeconds(); }
        }
        delete lander;
    }

    return;
}