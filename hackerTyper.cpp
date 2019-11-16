#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

const int screen_x = 1000;
const int screen_y = 600;
const int font_size = 15;
const int string_number = 600 / (15 +2);

int getLen(std::ifstream* file)
{
    file->seekg(0, file->beg);    
    file->seekg(0, file->end);
    int len = file->tellg();
    file->seekg(0, file->beg);

    return len;
}

void changeText(char* textOnscreen, int* indexCounter, int* stringCounter)
{
    if (*stringCounter == string_number)
    {
        int nPosition = 0;
        for (int i = 0; i > -1; i++)
            if (textOnscreen[i] == '\n')
            {
                nPosition = i;
                break;
            }
        for(int j = 0; j <= *indexCounter - nPosition; j++)
            textOnscreen[j] = textOnscreen[j + nPosition + 1];
        for(int j = *indexCounter - nPosition; j <= *indexCounter; j++)
            textOnscreen[j] = ' ';

        *indexCounter = *indexCounter - nPosition - 1;
        *stringCounter = *stringCounter - 1;
    }
}

    void updatetextOnscreen(char* textOnscreen, char* buffer, int* indexCounter, int* stringCounter, int* textSymbCounter)
{
    for(int i = 0; i < 3; i++)
    {   
        textOnscreen[*indexCounter + 1] = buffer[*textSymbCounter + 1];
        if(buffer[*textSymbCounter + 1] == '\n')
            *stringCounter += 1;
        *textSymbCounter += 1;
        *indexCounter += 1;
        changeText(textOnscreen, indexCounter, stringCounter);
    }
}


main()
{
    sf::RenderWindow window(sf::VideoMode(screen_x, screen_y), "hacker typer");

    sf::Text text;

    sf::Font font; 
    font.loadFromFile("arial.ttf");

    text.setFont(font);

    text.setCharacterSize(font_size); 
    text.setFillColor(sf::Color::Green);
    text.setPosition(10, 0);

    std::ifstream file;    
    file.open("file.txt");
    int len = getLen(&file);
    char* buffer = new char[len];
    file.read(buffer, len);
    file.close();

    char *textOnscreen = new char [screen_x/ font_size * screen_y / font_size]; 
    for (int i = 0; i < (screen_x / font_size * screen_y / font_size); i++)
        textOnscreen[i] = ' ';

    int indexCounter = -1;
    int stringCounter = 0;
    int textSymbCounter = -1;

    sf::Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) 
                window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) // exit by escape
                    window.close();

                updatetextOnscreen(textOnscreen, buffer, &indexCounter, &stringCounter, &textSymbCounter);    // by any button
                text.setString(textOnscreen);     
			}
		}

        window.clear();
        window.draw(text);
        window.display();

    }

    delete[] buffer;
    delete[] textOnscreen;

} 
