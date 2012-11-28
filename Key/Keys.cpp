#include "Keys.hpp"

TKey::TKey(void)
{
}

TKey::~TKey(void)
{
}

TKey::TKey(const TKey &other) :
event(other.event)
{
}

TKey::TKey(const sf::Event::EventType &evtType, const sf::Key::Code code, const bool alt, const bool ctrl, const bool shift)
{
    event.Type = evtType;
    event.Key.Code = code;
    event.Key.Alt = alt;
    event.Key.Control = ctrl;
    event.Key.Shift = shift;
}

TKey::TKey(const sf::Event::EventType &evtType, const sf::Mouse::Button button)
{
    event.Type = evtType;
    event.MouseButton.Button = button;
}

TKey::TKey(const sf::Event::EventType &evtType, const int joyId, const int button)
{
    event.Type = evtType;
    event.JoyButton.JoystickId = joyId;
    event.JoyButton.Button = button;
}

TKey::TKey(const sf::Event &evt) :
event(evt)
{
}

bool TKey::Test(const sf::Event &evt) const
{
    if (event.Type == evt.Type)
    {
        // Si l'évènement est un bouton du clavier
        if (((event.Type == sf::Event::KeyPressed) || (event.Type == sf::Event::KeyReleased))
        && (event.Key.Code == evt.Key.Code)
        && (event.Key.Alt == evt.Key.Alt)
        && (event.Key.Control == evt.Key.Control)
        && (event.Key.Shift == evt.Key.Shift))
                return true;

        // Si l'évènement est un bouton du joystick
        else if (((event.Type == sf::Event::JoyButtonPressed)
        || (event.Type == sf::Event::JoyButtonReleased))
        && (event.JoyButton.JoystickId == evt.JoyButton.JoystickId)
        && (event.JoyButton.Button == evt.JoyButton.Button))
                return true;

        // Si c'est un bouton de la souris
        else if (((event.Type == sf::Event::MouseButtonPressed)
        || (event.Type == sf::Event::MouseButtonReleased))
        && (event.MouseButton.Button == evt.MouseButton.Button))
                return true;
    }
    return false;
}



CKeys::CKeys(void)
{
}

CKeys::~CKeys(void)
{
}

TKey & CKeys::operator[](const std::string &name)
{
    return mKeys[name];
}
