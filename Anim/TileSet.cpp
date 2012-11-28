#include "TileSet.hpp"
 
// Par defaut
TileSet::TileSet(float NewTileWidth, float NewTileHeight)
{
    TileWidth = NewTileWidth;
    TileHeight = NewTileHeight;
}
 
// Par copie
TileSet::TileSet(const TileSet& Cpy):
sf::Drawable(Cpy)
{
    TileWidth = Cpy.TileWidth;
    TileHeight = Cpy.TileHeight;
    myType = Cpy.myType;
    myTile = Cpy.myTile;
}
 
// destructeur
TileSet::~TileSet()
{
 
}
 
// Largeur des Tiles
void TileSet::SetTileWidth(float NewTileWidth)
{
    TileWidth = NewTileWidth;
}
 
// Hauteur des Tiles
void TileSet::SetTileHeight(float NewTileHeight)
{
    TileHeight = NewTileHeight;
}
 
// Largeur des Tiles
float TileSet::GetTileWidth() const
{
    return TileWidth;
}
 
// Hauteur des Tiles
float TileSet::GetTileHeight() const
{
    return TileHeight;
}
 
// Taille des Tiles
void TileSet::SetTileSize(float NewTileWidth, float NewTileHeight)
{
    TileWidth = NewTileWidth;
    TileHeight = NewTileHeight;
}
 
// Taille des Tiles
void TileSet::SetTileSize(const sf::Vector2f& TileSize)
{
    TileWidth = TileSize.x;
    TileHeight = TileSize.y;
}
 
// Taille des Tiles
sf::Vector2f TileSet::GetTileSize() const
{
    return sf::Vector2f(TileWidth, TileHeight);
}
 
// Affichage
void TileSet::Render(const sf::RenderWindow& Window) const
{
    // On parcoure le tableau
    for (std::map<int, std::map<int, int> >::const_iterator it = myTile.begin(); it != myTile.end(); ++it)
    {
        for (std::map<int, int>::const_iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
        {
            std::map<int, Frame>::const_iterator TypeIt = myType.find( it2->second );
 
            // Si le type de tile éxiste
            if (TypeIt != myType.end())
            {
 
            // On dessine une tile
            glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
 
                    glTranslatef(it->first * TileWidth, it2->first * TileHeight, 0);
 
                    glColor4ub(TypeIt->second.Color.r, TypeIt->second.Color.g, TypeIt->second.Color.b, TypeIt->second.Color.a);
 
                // Si on doit y afficher une image
                if (TypeIt->second.Image != NULL)
                {
                    sf::Rect<float> Rect = TypeIt->second.Image->GetTexCoords(TypeIt->second.Rect);
 
                    TypeIt->second.Image->Bind();
 
                    glBegin(GL_QUADS);
                        glTexCoord2f(Rect.Left,  Rect.Top);    glVertex2f(0,     0);
                        glTexCoord2f(Rect.Left,  Rect.Bottom); glVertex2f(0,     TileHeight);
                        glTexCoord2f(Rect.Right, Rect.Bottom); glVertex2f(TileWidth, TileHeight);
                        glTexCoord2f(Rect.Right, Rect.Top);    glVertex2f(TileWidth, 0);
                    glEnd();
 
                }
                // Sinon
                else
                {
                    // Disable texturing
                    glDisable(GL_TEXTURE_2D);
 
                    // Draw the colored rectangle
                    glBegin(GL_QUADS);
                        glVertex2f(0,     0);
                        glVertex2f(0,     TileHeight);
                        glVertex2f(TileWidth, TileHeight);
                        glVertex2f(TileWidth, 0);
                    glEnd();
                }
 
                glMatrixMode(GL_MODELVIEW);
                    glPopMatrix();
            }
        }
    }
}
 
// retoune l'abscisse tableau
int TileSet::ScreenXToTileX(float ScreenX)
{
    return static_cast<int>(ScreenX/TileWidth);
}
 
// retourne l'ordonnée tableau
int TileSet::ScreenYToTileY(float ScreenY)
{
    return static_cast<int>(ScreenY/TileHeight);
}
 
// Accès au Type de la case X, Y
int& TileSet::operator () (int X, int Y)
{
    return myTile[X][Y];
}
 
// Accès au Type de la case X, Y : constant
int TileSet::operator () (int X, int Y) const
{
    std::map<int, std::map<int, int> >::const_iterator It = myTile.find( X );
 
    if (It != myTile.end())
    {
        std::map<int, int>::const_iterator It2 = It->second.find( Y );
        if (It2 != It->second.end())
            return It2->second;
        else
            return 0;
    }
    else
        return 0;
}
 
// retourne la Frame de type 'Key'
const Frame& TileSet::GetType(int Key)
{
    return myType[Key];
}
 
// Enregistre une nouvelle Frame pour le type 'Key'
void TileSet::SetType(int Key, const Frame& NewType)
{
    myType[Key] = NewType;
}
 
// Nombre de Tiles dans la map
size_t TileSet::Size() const
{
    return myTile.size();
}
 
// Nombre de types différents
size_t TileSet::TypeNb() const
{
    return myType.size();
}
 
// Plus tard, nous pourrons ajouter différentes fonctions liées au fait qu'une 'Anim' est une ressource
// Par exemple : LoadFromFile, SaveToFile etc...


