#include "GameState.hpp"
#include "HelpState.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"
#include <iostream>
#include <sstream>

namespace BubbleBash
{
    GameState::GameState(GameDataRef data, int i) : _data(data), level(i)
    {

        for (int i = 1; i <= 8; i++)
            for (int j = 1; j <= 8; j++)
            {
                grid[i][j].kind = rand() % 7;
                grid[i][j].col = j;
                grid[i][j].row = i;
                grid[i][j].x = j * ts;
                grid[i][j].y = i * ts;
            }
    }

    void GameState::Init()
    {
        this->_data->assets.PauseOrGame_State.push_back(0);
        obj.mC.restart();
        obj.runTime = 0;
        obj.bPaused = false;
        this->_data->assets.score =0;

        this->_data->assets.LoadTexture("Background", GAME_WINDOW_STATE_FILEPATH);
        this->_data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);

        this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON_FILEPATH);
        this->_data->assets.LoadTexture("Help Button", HELP_BUTTON_FILEPATH);

        this->_data->assets.LoadTexture("Bubbles", BUBBLES_FILEPATH);

        _background.setTexture(this->_data->assets.GetTexture("Background"));
        _gridSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));

        _pausebutton.setTexture(this->_data->assets.GetTexture("Pause Button"));
        _helpbutton.setTexture(this->_data->assets.GetTexture("Help Button"));

        _bubbles.setTexture(this->_data->assets.GetTexture("Bubbles"));

        _gridSprite.setPosition(500, 200);

        _pausebutton.setPosition(50, 400);
        _helpbutton.setPosition(50, 500);

        if (!font.loadFromFile(MARKER_FONT_FILEPATH))
        {
            throw("COULD NOT LOAD FONT");
        }

        text_time.setFont(font);
        text_time.setCharacterSize(35);
        text_time.setColor(sf::Color::Yellow);
        text_time.setPosition(50, 100);

        text_score.setFont(font);
        text_score.setCharacterSize(35);
        text_score.setColor(sf::Color::Yellow);
        text_score.setPosition(50, 155);

        text_time.setString("Time Remaining : ");
        text_score.setString("Current Score : ");

        time_text.setFont(font);
        time_text.setCharacterSize(35);
        time_text.setColor(sf::Color::Yellow);
        time_text.setPosition(310, 100);

        this->_data->assets._music.openFromFile(GAME_PLAY_MUSIC_FILEPATH);
        this->_data->assets._music.setVolume(50);
        this->_data->assets._music.setLoop(true);
        this->_data->assets._music.play();
    }

    void GameState::HandleInput()
    {
        sf::Event event;

        while (this->_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                this->_data->assets._music.stop();
                this->_data->window.close();
            }

            else if (this->_data->input.IsSpriteClicked(this->_pausebutton, sf::Mouse::Left, this->_data->window))
            {
                obj.Pause();
                this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
            }
            else if (this->_data->input.IsSpriteClicked(this->_helpbutton, sf::Mouse::Left, this->_data->window))
            {
                this->_data->assets._music.stop();
                this->_data->machine.AddState(StateRef(new HelpState(_data)), true);
            }

            if (event.type == sf::Event::EventType::KeyPressed)
            {
                // Up and down to control volume
                if (event.key.code == sf::Keyboard::Down)
                    this->_data->assets._music.setVolume(_data->assets._music.getVolume() - 10);

                if (event.key.code == sf::Keyboard::Key::Up)
                    this->_data->assets._music.setVolume(_data->assets._music.getVolume() + 10);
            }
        }
    }

    void GameState::Update(float dt)
    {
        time = obj.GetElapsedSeconds();
        time = TIME_EASY - level * 10 - time;
        std::stringstream ss;
        ss << time;
        time_text.setString(ss.str().c_str());

        if (this->_data->assets.PauseOrGame_State.back() == 1)
        {
            obj.Start();
            this->_data->assets.PauseOrGame_State.pop_back();
        }

        if (time < 1)
        {
            this->_data->machine.AddState(StateRef(new GameOverState(_data)), true);
        }
    }

    void GameState::Draw(float dt)
    {
        this->_data->window.clear(sf::Color::Black);

        this->_data->window.draw(this->_background);
        this->_data->window.draw(this->_gridSprite);

        this->_data->window.draw(this->_pausebutton);
        this->_data->window.draw(this->_helpbutton);

        this->_data->window.draw(text_time);
        this->_data->window.draw(text_score);

        this->_data->window.draw(time_text);

        processEvents();
        update();
        render();

        this->_data->window.display();
    }

    void GameState::swap(piece p1, piece p2)
    {
        int aux1 = p1.row;
        p1.row = p2.row;
        p2.row = aux1;
        int aux2 = p1.col;
        p1.col = p2.col;
        p2.col = aux2;
        grid[p1.row][p1.col] = p1;
        grid[p2.row][p2.col] = p2;
    }
    int GameState::NoMoreMoves(piece grid[10][10])
    {
        int i, j;

        for (i = 1; i <= 8; i++)
            for (j = 1; j <= 7; j++)
            {
                if (grid[i][j].kind == grid[i][j + 1].kind)
                {

                    if (i != 1)
                    {
                        if (j != 1)
                        {
                            if (grid[i - 1][j - 1].kind == grid[i][j].kind)
                                return 0;
                        }
                        if (j + 2 <= 8)
                        {
                            if (grid[i - 1][j + 2].kind == grid[i][j].kind)
                                return 0;
                        }
                    }

                    if (j - 2 > 0)
                    {
                        if (grid[i][j - 2].kind == grid[i][j].kind)
                            return 0;
                    }
                    if (j + 3 <= 8)
                    {
                        if (grid[i][j + 3].kind == grid[i][j].kind)
                            return 0;
                    }

                    if (i + 1 <= 8)
                    {
                        if (j + 1 <= 8)
                        {
                            if (grid[i + 1][j + 1].kind == grid[i][j].kind)
                                return 0;
                        }
                        if (j + 2 <= 8)
                        {
                            if (grid[i + 1][j + 2].kind == grid[i][j].kind)
                                return 0;
                        }
                    }
                }
            }

        for (i = 1; i < 8; i++)
            for (j = 1; j <= 8; j++)
            {
                if (grid[i][j].kind == grid[i + 1][j].kind)
                {

                    if (j != 1)
                    {
                        if (i != 1)
                        {
                            if (grid[i - 1][j - 1].kind == grid[i][j].kind)
                                return 0;
                        }
                        if (i + 2 <= 8)
                        {
                            if (grid[i + 2][j - 1].kind == grid[i][j].kind)
                                return 0;
                        }
                    }

                    if (i - 2 >= 1)
                    {
                        if (grid[i - 2][j].kind == grid[i][j].kind)
                            return 0;
                        if (i + 3 <= 8)
                        {
                            if (grid[i + 3][j].kind == grid[i][j].kind)
                                return 0;
                        }

                        if (j + 1 <= 8)
                        {
                            if (i + 1 <= 8)
                            {
                                if (grid[i + 1][j + 1].kind == grid[i][j].kind)
                                    return 0;
                            }
                            if (i + 2 <= 8)
                            {
                                if (grid[i + 2][j + 1].kind == grid[i][j].kind)
                                    return 0;
                            }
                        }
                    }
                }

                return 1;
            }
    }

    void GameState::processEvents()
    {
        sf::Event e;
        while (this->_data->window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                this->_data->window.close();

            if (e.type == sf::Event::MouseButtonPressed)
                if (e.key.code == sf::Mouse::Left)
                {
                    if (!isSwap && !isMoving)
                        click++;
                    pos = sf::Mouse::getPosition(this->_data->window) - offset;
                }
        }

        isMoving = false;
        for (int i = 1; i <= 8; i++)
            for (int j = 1; j <= 8; j++)
            {
                piece &p = grid[i][j];
                int dx, dy;
                for (int n = 0; n < 4; n++)
                {
                    dx = p.x - p.col * ts;
                    dy = p.y - p.row * ts;
                    if (dx)
                        p.x -= dx / abs(dx);
                    if (dy)
                        p.y -= dy / abs(dy);
                }
                if (dx || dy)
                    isMoving = 1;
            }

        if (!isMoving)
            for (int i = 1; i <= 8; i++)
                for (int j = 1; j <= 8; j++)
                    if (grid[i][j].match)
                        if (grid[i][j].alpha > 10)
                        {
                            grid[i][j].alpha -= 10;
                            isMoving = true;
                        }

        int somme = 0;
        for (int i = 1; i <= 8; i++)
            for (int j = 1; j <= 8; j++)
                somme += grid[i][j].match;

        if (isSwap && !isMoving)
        {
            if (somme == 0)
                if (special == false)
                    swap(grid[y0][x0], grid[y][x]);
            isSwap = 0;
            special = false;
        }

        int l = 0;
        int a = NoMoreMoves(grid);
        if (a == 1)
        {
            for (int i = 1; i <= 8; i++)
                for (int j = 8; j > 0; j--)
                {
                    grid[i][j].kind = rand() % 7;
                    grid[i][j].y = -ts * l++;
                    grid[i][j].match = 0;
                    grid[i][j].alpha = 255;
                }
        }
    }
    void GameState::update()
    {
        if (!isMoving)
        {
            for (int i = 8; i > 0; i--)
                for (int j = 1; j <= 8; j++)
                    if (grid[i][j].match)
                        for (int n = i; n > 0; n--)
                            if (!grid[n][j].match)
                            {
                                swap(grid[n][j], grid[i][j]);
                                break;
                            };

            for (int j = 1; j <= 8; j++)
                for (int i = 8, n = 0; i > 0; i--)
                    if (grid[i][j].match)
                    {
                        grid[i][j].kind = rand() % 7;
                        grid[i][j].y = -ts * n++;
                        grid[i][j].match = 0;
                        grid[i][j].alpha = 255;
                    }
        }
    }

    void GameState::render()
    {

        if (click == 1)
        {
            x0 = pos.x / ts + 1;
            y0 = pos.y / ts + 1;
        }
        if (click == 2)
        {
            x = pos.x / ts + 1;
            y = pos.y / ts + 1;
            if (abs(x - x0) + abs(y - y0) == 1)
            {
                swap(grid[y0][x0], grid[y][x]);
                isSwap = 1;
                click = 0;
                max--;
            }
            else
            {
                click = 1;
            }
        }

        //related to score

        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Yellow);
        text.setPosition(260, 160);

        text.setString(std::to_string(this->_data->assets.score));

        for (int i = 1; i <= 8; i++)
            for (int j = 1; j <= 8; j++)
            {

                if ((grid[i][j].kind == grid[i + 1][j].kind) && (grid[i][j].kind == grid[i - 1][j].kind))
                {
                    special = false;
                    if (isMoving == false)
                        this->_data->assets.score += 10;
                    for (int n = -1; n <= 1; n++)
                    {
                        grid[i + n][j].match++;
                    }
                }

                if ((grid[i][j].kind == grid[i][j + 1].kind) && (grid[i][j].kind == grid[i][j - 1].kind))
                {
                    special = false;
                    if (isMoving == false)
                        this->_data->assets.score += 10;
                    for (int n = -1; n <= 1; n++)
                        grid[i][j + n].match++;
                }

                for (int i = 1; i + 3 <= 8; i++)
                    for (int j = 1; j <= 8; j++)
                    {
                        if ((grid[i][j].kind == grid[i + 1][j].kind) && (grid[i][j].kind == grid[i + 2][j].kind) && (grid[i][j].kind == grid[i + 3][j].kind) && (grid[i][j].kind != grid[i + 4][j].kind) && (grid[i][j].kind != grid[i - 1][j].kind))
                        {
                            int l = 0;
                            if (isMoving == false)
                                this->_data->assets.score += 20;
                            //4 bubbles
                            special = true;
                            
                            //nej.setPosition(grid[i][j].x-0.8,grid[i][j].y-0.8);
                            for (int n = 1; n <= 8; n++)
                            {
                                grid[n][j].kind = rand() % 7;
                                grid[n][j].y = -ts * l++;
                                grid[n][j].match = 0;
                                grid[n][j].alpha = 255;
                            }
                        }
                    };

                for (int i = 1; i <= 8; i++)
                    for (int j = 1; j + 3 <= 8; j++)
                    {
                        if ((grid[i][j].kind == grid[i][j + 1].kind) && (grid[i][j].kind == grid[i][j + 2].kind) && (grid[i][j].kind == grid[i][j + 3].kind) && (grid[i][j].kind != grid[i][j + 4].kind) && (grid[i][j].kind != grid[i][j - 1].kind))
                        {
                            int l = 0;
                            if (isMoving == false)
                                this->_data->assets.score += 20;
                            //4 bubbles
                            special = true;
                            //nej.setPosition(grid[i][j].x-0.8, grid[i][j].y-0.8);
                            for (int n = 1; n <= 8; n++)
                            {
                                grid[i][n].kind = rand() % 7;
                                grid[i][n].y = -ts * l++;
                                grid[i][n].match = 0;
                                grid[i][n].alpha = 255;
                            }
                        }
                    }

                for (int i = 1; i + 4 <= 8; i++)
                    for (int j = 1; j <= 8; j++)
                    {

                        if ((grid[i][j].kind == grid[i + 1][j].kind) && (grid[i][j].kind == grid[i + 2][j].kind) && (grid[i][j].kind == grid[i + 3][j].kind) && (grid[i][j].kind == grid[i + 4][j].kind))
                        {
                            int l = 0;
                            special = true;
                            if (isMoving == false)
                                this->_data->assets.score += 30;
                            //5 bubbles
                            piece pp = grid[i][j];
                            for (int n = 1; n <= 8; n++)
                                for (int m = 1; m <= 8; m++)
                                {

                                    if (grid[n][m].kind == pp.kind)
                                    {
                                        grid[n][m].kind = rand() % 7;
                                        grid[n][m].y = -ts * l++;
                                        grid[n][m].match = 0;
                                        grid[n][m].alpha = 255;
                                    }
                                }
                        }
                    }
                for (int i = 1; i <= 8; i++)
                    for (int j = 1; j + 4 <= 8; j++)
                    {

                        if ((grid[i][j].kind == grid[i][j + 1].kind) && (grid[i][j].kind == grid[i][j + 2].kind) && (grid[i][j].kind == grid[i][j + 3].kind) && (grid[i][j].kind == grid[i][j + 4].kind))
                        {
                            special = true;
                            if (isMoving == false)
                                this->_data->assets.score += 30;
                            int l = 0;
                            //5 bubbles
                            piece pp = grid[i][j];
                            for (int n = 1; n <= 8; n++)
                                for (int m = 1; m <= 8; m++)
                                {

                                    if (grid[n][m].kind == pp.kind)
                                    {
                                        grid[n][m].kind = rand() % 7;
                                        grid[n][m].y = -ts * l++;
                                        grid[n][m].match = 0;
                                        grid[n][m].alpha = 255;
                                    }
                                }
                        }
                    }

                if ((grid[i][j].kind == grid[i + 1][j].kind) && (grid[i][j].kind == grid[i + 2][j].kind) && (grid[i][j].kind == grid[i][j + 1].kind) && (grid[i][j].kind == grid[i][j + 2].kind))
                {
                    int l = 0;
                    special = true;
                    if (isMoving == false)
                        this->_data->assets.score += 25;
                    for (int n = i; n <= i + 2; n++)
                        for (int m = j; m <= j + 2; m++)
                        {
                            grid[n][m].kind = rand() % 7;
                            grid[n][m].y = -ts * l++;
                            grid[n][m].match = 0;
                            grid[n][m].alpha = 255;
                        };
                }
                if ((grid[i][j].kind == grid[i + 1][j].kind) && (grid[i][j].kind == grid[i + 2][j].kind) && (grid[i][j].kind == grid[i][j - 1].kind) && (grid[i][j].kind == grid[i][j - 2].kind))
                {
                    int l = 0;
                    special = true;
                    if (isMoving == false)
                        this->_data->assets.score += 25;
                    for (int n = i; n <= i + 2; n++)
                        for (int m = j - 2; m <= j; m++)
                        {
                            grid[n][m].kind = rand() % 7;
                            grid[n][m].y = -ts * l++;
                            grid[n][m].match = 0;
                            grid[n][m].alpha = 255;
                        };
                }
                if ((grid[i][j].kind == grid[i - 1][j].kind) && (grid[i][j].kind == grid[i - 2][j].kind) && (grid[i][j].kind == grid[i][j - 1].kind) && (grid[i][j].kind == grid[i][j - 2].kind))
                {
                    int l = 0;
                    special = true;
                    if (isMoving == false)
                        this->_data->assets.score += 25;
                    for (int n = i - 2; n <= i; n++)
                        for (int m = j - 2; m <= j; m++)
                        {
                            grid[n][m].kind = rand() % 7;
                            grid[n][m].y = -ts * l++;
                            grid[n][m].match = 0;
                            grid[n][m].alpha = 255;
                        };
                }
                if ((grid[i][j].kind == grid[i - 1][j].kind) && (grid[i][j].kind == grid[i - 2][j].kind) && (grid[i][j].kind == grid[i][j + 1].kind) && (grid[i][j].kind == grid[i][j + 2].kind))
                {
                    int l = 0;
                    special = true;
                    if (isMoving == false)
                        this->_data->assets.score += 25;
                    for (int n = i - 2; n <= i; n++)
                        for (int m = j; m <= j + 2; m++)
                        {
                            grid[n][m].kind = rand() % 7;
                            grid[n][m].y = -ts * l++;
                            grid[n][m].match = 0;
                            grid[n][m].alpha = 255;
                        };
                }

                if ((grid[i][j].kind == grid[i + 1][j].kind) && (grid[i][j].kind == grid[i - 1][j].kind) && (grid[i][j].kind == grid[i][j + 1].kind) && (grid[i][j].kind == grid[i][j + 2].kind))
                {
                    int l = 0;
                    special = true;
                    if (isMoving == false)
                        this->_data->assets.score += 25;
                    for (int n = i - 1; n <= i + 1; n++)
                        for (int m = j; m <= j + 2; m++)
                        {
                            grid[n][m].kind = rand() % 7;
                            grid[n][m].y = -ts * l++;
                            grid[n][m].match = 0;
                            grid[n][m].alpha = 255;
                        };
                }
                if ((grid[i][j].kind == grid[i + 1][j].kind) && (grid[i][j].kind == grid[i - 1][j].kind) && (grid[i][j].kind == grid[i][j - 1].kind) && (grid[i][j].kind == grid[i][j - 2].kind))
                {
                    int l = 0;
                    special = true;
                    if (isMoving == false)
                        this->_data->assets.score += 25;
                    for (int n = i - 1; n <= i + 1; n++)
                        for (int m = j - 2; m <= j; m++)
                        {
                            grid[n][m].kind = rand() % 7;
                            grid[n][m].y = -ts * l++;
                            grid[n][m].match = 0;
                            grid[n][m].alpha = 255;
                        };
                }
                if ((grid[i][j].kind == grid[i + 1][j].kind) && (grid[i][j].kind == grid[i + 2][j].kind) && (grid[i][j].kind == grid[i][j - 1].kind) && (grid[i][j].kind == grid[i][j + 1].kind))
                {
                    int l = 0;
                    special = true;
                    if (isMoving == false)
                        this->_data->assets.score += 25;
                    for (int n = i; n <= i + 2; n++)
                        for (int m = j - 1; m <= j + 1; m++)
                        {
                            grid[n][m].kind = rand() % 7;
                            grid[n][m].y = -ts * l++;
                            grid[n][m].match = 0;
                            grid[n][m].alpha = 255;
                        };
                }
                if ((grid[i][j].kind == grid[i - 1][j].kind) && (grid[i][j].kind == grid[i - 2][j].kind) && (grid[i][j].kind == grid[i][j - 1].kind) && (grid[i][j].kind == grid[i][j + 1].kind))
                {
                    int l = 0;
                    special = true;
                    if (isMoving == false)
                        this->_data->assets.score += 25;
                    for (int n = i - 2; n <= i; n++)
                        for (int m = j - 1; m <= j + 1; m++)
                        {
                            grid[n][m].kind = rand() % 7;
                            grid[n][m].y = -ts * l++;
                            grid[n][m].match = 0;
                            grid[n][m].alpha = 255;
                        };
                }
            }

        for (int i = 1; i <= 8; i++)
            for (int j = 1; j <= 8; j++)
            {
                piece p = grid[i][j];
                _bubbles.setTextureRect(sf::IntRect(p.kind * 49, 0, 49, 49));
                _bubbles.setColor(sf::Color(255, 255, 255, p.alpha));
                _bubbles.setPosition(p.x, p.y);
                _bubbles.move(offset.x - ts, offset.y - ts);
                this->_data->window.draw(_bubbles);

                this->_data->window.draw(text);
            }

        this->_data->window.display();
    }

}