#ifndef ZIGO_TILESET
#define ZIGO_TILESET
 
#include <map>
#include "Frame.hpp"
 
class TileSet : public sf::Drawable
{
    public:
 
    // Par defaut
    TileSet(float NewTileWidth = 0, float NewTileHeight = 0);
 
    // Par copie
    TileSet(const TileSet& Cpy);
 
    // destructeur
    virtual ~TileSet();
 
    // Largeur des Tiles
    void SetTileWidth(float NewTileWidth);
 
    // Hauteur des Tiles
    void SetTileHeight(float NewTileHeight);
 
    // Largeur des Tiles
    float GetTileWidth() const;
 
    // Hauteur des Tiles
    float GetTileHeight() const;
 
    // Taille des Tiles
    void SetTileSize(float NewTileWidth, float NewTileHeight);
 
    // Taille des Tiles
    void SetTileSize(const sf::Vector2f& TileSize);
 
    // Taille des Tiles
    sf::Vector2f GetTileSize() const;
 
    // Affichage
    virtual void Render(const sf::RenderWindow& Window) const;
 
    // retoune l'abcisse tableau
    int ScreenXToTileX(float ScreenX);
 
    // retourne l'ordonnée tableau
    int ScreenYToTileY(float ScreenY);
 
    // Accès au Type de la case X, Y
    int& operator () (int X, int Y);
 
    // Accès au Type de la case X, Y : constant
    int operator () (int X, int Y) const;
 
    // retourne la Frame de type 'Key'
    const Frame& GetType(int Key);
 
    // enregistre une nouvelle Frame pour le type 'Key'
    void SetType(int Key, const Frame& NewType);
 
    // Nombre de Tiles dans la map
    size_t Size() const;
 
    // Nombre de types différents
    size_t TypeNb() const;
 
    // Plus tard, nous pourrons ajouter différentes fonctions liées au fait qu'une 'Anim' est une ressource
    // Par exemple : LoadFromFile, SaveToFile etc...
 
    private:
    float TileWidth;
    float TileHeight;
    std::map<int, std::map<int, int> > myTile;
    std::map<int, Frame> myType;
};
 
#endif


