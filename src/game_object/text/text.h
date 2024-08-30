#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "mgtv_library.h"

#include "game_object/game_object.h"

using std::string;
using mgtv_library::console::COLOR;


namespace pong_in_console
{
	class Text : public GameObject
	{
	public:
		Text(int x, int y, string text, COLOR color, bool withFrame = false);
		~Text();

		void draw() override;

		void setColor(COLOR color);

	private:
		string text;
		COLOR color;

		bool withFrame;
	};

	// Declarar las funciones.
	// Aplicar esto con las opciones del men� principal.
	// Brindar la posibilidad de que tengan marco.
	// Utilizar el struct de posicion que heredan del gameobject. Lo mismo con el tama�o.
	//
	// Pensar si el tama�o es necesario para este caso espec�fico.
}

#endif // !TEXT_H
