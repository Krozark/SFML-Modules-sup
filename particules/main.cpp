#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "particle.h"

int main()
{
	int width	= 640;
	int height	= 480;

	sf::RenderWindow window( sf::VideoMode( width, height, 32 ), "Inside the Particle Storm" );
	window.UseVerticalSync( true );
	const sf::Input& input = window.GetInput();
	sf::Event events;
	sf::Font font;
	if( !font.LoadFromFile( "arial.ttf" ) ) return 1;
	sf::Text text( "", font, 10 );
	text.SetPosition( 10.0f, 10.0f );

	ParticleSystem particleSystem( width, height );
	//particleSystem.setPosition( width/2, height/2 );
	//particleSystem.setGravity( 1.0f, 1.0f );
	//particleSystem.setParticleSpeed( 80.0f );
	//particleSystem.setDissolve( true );
	//particleSystem.setDissolutionRate( 4 );
	//particleSystem.setShape( Shape::SQUARE );

	particleSystem.fuel( 1000 );

	float xpos = 320.0f;
	float ypos = 240.0f;
	float xgrv = 0.0f;
	float ygrv = 0.0f;

	while( window.IsOpened() )
	{
		window.GetEvent( events );
		if( events.Type == sf::Event::Closed )
			window.Close();
		if( events.Type == sf::Event::KeyPressed && events.Key.Code == sf::Key::Escape )
			window.Close();

		if( input.IsKeyDown( sf::Key::Space ) )
			particleSystem.fuel( 200 * window.GetFrameTime() );
		if( input.IsKeyDown( sf::Key::A ) )
			particleSystem.setPosition( --xpos, ypos );
		if( input.IsKeyDown( sf::Key::D ) )
			particleSystem.setPosition( ++xpos, ypos );
		if( input.IsKeyDown( sf::Key::W ) )
			particleSystem.setPosition( xpos, --ypos );
		if( input.IsKeyDown( sf::Key::S ) )
			particleSystem.setPosition( xpos, ++ypos );
		if( input.IsKeyDown( sf::Key::Left ) )
			particleSystem.setGravity( --xgrv * 0.1f, ygrv * 0.1f);
		if( input.IsKeyDown( sf::Key::Right ) )
			particleSystem.setGravity( ++xgrv * 0.1f, ygrv * 0.1f );
		if( input.IsKeyDown( sf::Key::Up ) )
			particleSystem.setGravity( xgrv * 0.1f, --ygrv * 0.1f );
		if( input.IsKeyDown( sf::Key::Down ) )
			particleSystem.setGravity( xgrv * 0.1f, ++ygrv * 0.1f );
		if( input.IsKeyDown( sf::Key::G ) )
			particleSystem.setGravity( 0.0f, 0.0f );
		if( input.IsKeyDown( sf::Key::P ) )
			particleSystem.setPosition( 320.0f, 240.0f );

		particleSystem.remove();
		particleSystem.update();
		particleSystem.render();
		
		text.SetString( particleSystem.getNumberOfParticlesString() );
		window.Clear( sf::Color::Black );
		window.Draw( particleSystem.getSprite() );
		window.Draw( text );
		window.Display();
	}

	return 0;
}
