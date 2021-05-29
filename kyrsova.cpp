#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int Long = 23;
const int width = 14;
const int four = 4;

int field[Long][width] = { 0 };

struct Point
{
    int x, y;
} a[4], b[4];

int figures[7][4] =
{
    1,3,5,7, 
    2,4,5,7, 
    3,5,4,6, 
    3,5,4,7, 
    2,3,5,7, 
    3,5,7,6, 
    2,3,4,5, 
};

 bool endGameIfNeeded()
{
	for (int i = 0; i < width; i++)
	{
		if (field[1][i]) {
			return false;
		}
	}

	
	return true;
}

bool check()
{
    for (int i = 0; i < four; i++)
        if (a[i].x < 0 || a[i].x >= width || a[i].y >= Long) return 0;
        else if (field[a[i].y][a[i].x]) return 0;
    return 1;
    	
};


void startGame(RenderWindow *window) {
	bool isPlaying = true;

	Texture t1, t2, t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/ramka.png");
    t3.loadFromFile("images/frame2.png");

    Sprite s(t1), background(t2), frame(t3);

    int dx = 0; bool rotate = 0; int colorNum = 1;
    float timer = 0, delay = 0.3;

    Clock clock;


    while (isPlaying)
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window->pollEvent(e))
        {
			if(e.type == Event::Closed)
			window->close();
            if (e.type == Event::KeyPressed)
                if (e.key.code == Keyboard::Up) rotate = true;
                else if (e.key.code == Keyboard::Left) dx = -1;
                else if (e.key.code == Keyboard::Right) dx = 1;
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
			delay = 0.05;

       //Move 
        for (int i = 0; i < four; i++) { 
			b[i] = a[i]; a[i].x += dx; 
		}
		
        if (!check()) 
			for (int i = 0; i < four; i++) 
				a[i] = b[i];

        //Rotate
        if (rotate)
        {
            Point p = a[1]; 
            for (int i = 0; i < four; i++) {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }
            
            if (!check()) 
				for (int i = 0; i < four; i++) 
					a[i] = b[i];
        }

        //Tick
        if (timer > delay)
        {
            for (int i = 0; i < four; i++) { 
				b[i] = a[i]; a[i].y += 1; 
			}

            if (!check())
            {
                for (int i = 0; i < four; i++) field[b[i].y][b[i].x] = colorNum;

                colorNum = 1 + rand() % 7;
                int n = rand() % 7;
                for (int i = 0; i < four; i++)
                {
                    a[i].x = figures[n][i] % 2;
                    a[i].y = figures[n][i] / 2;
                }
            }

            timer = 0;
        }

        
        int k = Long - 1;
        for (int i = Long - 1; i > 0; i--)
        {
            int count = 0;
            for (int j = 0; j < width; j++)
            {
                if (field[i][j]) count++;
                field[k][j] = field[i][j];
            }
            if (count < width){
			 	k--;
			 	
			 
			}
        }

        dx = 0; rotate = 0; delay = 0.3;
       

    
        window->clear(Color::White);
        window->draw(background);

        for (int i = 0; i < Long; i++)
            for (int j = 0; j < width; j++)
            {
                if (field[i][j] == 0) continue;
                s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
                s.setPosition(j * 18, i * 18);
                s.move(28, 31); 
                window->draw(s);
            }

        for (int i = 0; i < four; i++)
        {
            s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
            s.setPosition(a[i].x * 18, a[i].y * 18);
            s.move(28, 31); 
            window->draw(s);
            
        }
	
        window->draw(frame);
        window->display();
      
        isPlaying = endGameIfNeeded();
    }
}

void afterGameFinished(RenderWindow *window) {
	
	while(window->isOpen()){
    	
    	Event e;
        while (window->pollEvent(e)) {       
			if(e.type == Event :: Closed)
				window->close();
					sf::Font font;
    	font.loadFromFile("C:/WINDOWS/Fonts/arial.ttf");
		sf::Text text("GAME OVER", font);
		text.setCharacterSize(30);
		text.setStyle(sf::Text::Bold);
		text.setPosition(65, 30);
    	text.setFillColor(sf::Color::Red);
		window->draw(text);
		window->display();
    
	
		
        }
    	
	}
}

int main()
{	
    srand(time(0));
    RenderWindow window(VideoMode(320, 480), "The Game!");
	startGame(&window);
	afterGameFinished(&window);

	
    return 0;
}
