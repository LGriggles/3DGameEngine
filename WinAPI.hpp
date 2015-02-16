#ifndef WINAPI_HPP
#define WINAPI_HPP

//C++
#include <vector>
using std::vector;
//SFML
#include <SFML\Graphics.hpp>

/*! Interfaces with windows API */
class WinAPIinterface
{
public:
	void spawnContextMenu(sf::Vector2i position);		//!< Spawn a context menu at the specified location
};
/*! Holds the windows api object */
namespace WindowsAPIinterface
{
	extern WinAPIinterface winAPIinterface;				//!< the windows api interface, contained under an elegant namespace
}

#endif // !WINAPI_HPP
