/*
    Realice una aplicación que coloque el cuadrado representado por el sprite cuad_yellow.png
en pantalla. Dicho cuadrado debe poder ser movido con las teclas de dirección del teclado. Si
se presiona la barra espaciadora el cuadrado debe cambiar a un círculo representado por el
Sprite rcircleg.png. Bajo ninguna circunstancia la figura puede abandonar la zona visible de
pantalla. Ambos sprites deben representarse del mismo tamaño en pantalla.

NOTA: Intente que ambas imagenes pudieran tener la misma dimensión en pantalla pero no pude lograrlo.
Me gustaría tener una devolución para poder corregir y aprender de estos ejercicios.
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

sf::Texture TextureCuadrado;
sf::Texture TextureCirculo;

float escalaX, escalaY;
float alto_cuadrado, ancho_cuadrado;
float alto_circulo, ancho_circulo;

int main() {
    // Crear la ventana
    sf::RenderWindow window(sf::VideoMode(800, 600,32), "Cambio de sprite con la barra y moverlos por la pantalla");

    // Cargar las texturas
 
    if (!TextureCuadrado.loadFromFile("cuad_yellow.png")) {
        return -1;  // Error al cargar la textura
    }
    // Dimensiones del cuadrado
    alto_cuadrado = (float)TextureCuadrado.getSize().y;
    ancho_cuadrado = (float)TextureCuadrado.getSize().x;


   
    if (!TextureCirculo.loadFromFile("rcircleg.png")) {
        return -1;  // Error al cargar la textura
    }

    // Dimensiones del circulo
    alto_circulo = (float)TextureCirculo.getSize().y;
    ancho_circulo = (float)TextureCirculo.getSize().x;

    // Comparamos para ver que imagen es la más grande
    if (alto_cuadrado > alto_circulo && ancho_cuadrado > ancho_circulo) {
        escalaY = alto_circulo / alto_cuadrado;
        escalaX = ancho_circulo / ancho_cuadrado;
    }
    
    // Crear sprites
    sf::Sprite sprite(TextureCuadrado);
    sprite.setScale(escalaX, escalaY);
    sprite.setPosition(400, 300);  // Posición inicial

    bool isCircle = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Cambiar entre cuadrado y círculo al presionar la barra espaciadora
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                isCircle = !isCircle;
                if (isCircle) {
                    sprite.setTexture(TextureCirculo);
                    //sprite.setScale(1.25f, 1.25f);
                }
                else {
                    sprite.setTexture(TextureCuadrado);
                    //sprite.setScale(0.25f, 0.25f);
                }
            }
        }

        // Mover el sprite con las teclas de dirección
        float speed = 0.50f; // Valor para cambiar la velocidad de desplazamiento por la pantalla
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sprite.getPosition().x > 0) {
            sprite.move(-speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sprite.getPosition().x < 800 - sprite.getGlobalBounds().width) {
            sprite.move(speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sprite.getPosition().y > 0) {
            sprite.move(0, -speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sprite.getPosition().y < 600 - sprite.getGlobalBounds().height) {
            sprite.move(0, speed);
        }

        // Limpiar la ventana
        window.clear(sf::Color::White);

        // Dibujar el sprite en la ventana
        window.draw(sprite);

        // Mostrar la ventana
        window.display();
    }

    return 0;
}