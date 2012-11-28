#ifndef HPP_KEYS
#define HPP_KEYS

#include <map>

#include <SFML/Window.hpp>

struct TKey
{
    public:
        // ---------------------------------
        // Constructeur et destructeur par défaut
        // ---------------------------------
        TKey(void);
        ~TKey(void);

        // ---------------------------------
        // Constructeur par copie
        // ---------------------------------
        TKey(const TKey &other);

        // ---------------------------------
        // Constructeurs prenant un type d'évènement et sa valeur
        // ---------------------------------
        TKey(const sf::Event::EventType &evtType, const sf::Key::Code code, const bool alt = false, const bool ctrl = false, const bool shift = false);
        TKey(const sf::Event::EventType &evtType, const sf::Mouse::Button button);
        TKey(const sf::Event::EventType &evtType, const int joyId, const int button);

        // ---------------------------------
        // Constructeurs prenant un évènement
        // ---------------------------------
        TKey(const sf::Event &evt);

        // ---------------------------------
        // Test de l'évènement
        // ---------------------------------
        bool Test(const sf::Event &evt) const;



        // ---------------------------------
        // Données membres
        // ---------------------------------
        sf::Event event;

};

class CKeys
{
    public:
        // ---------------------------------
        // Constructeurs par défaut
        // ---------------------------------
        CKeys(void);
        ~CKeys(void);

        // ---------------------------------
        // Récupère une Key avec son identifiant
        // ---------------------------------
        TKey & operator[](const std::string &name);

    private:
        typedef std::map<std::string, TKey> TKeys;

        // ---------------------------------
        // Données membres
        // ---------------------------------
        TKeys mKeys;

};

#endif // HPP_KEYS
