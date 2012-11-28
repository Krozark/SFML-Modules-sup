/*!
* \brief Gestion des collisions entre deux sf::Sprites en gérant la transparence ( pixel perfect ).
* \author 
* \note Utilise la version pre-1.3.
* \warning Les deux Sprites ne doivent pas avoir subis de rotation!!
* \param s1 : premier sf::Sprite.
* \param s2 : deuxième sf::Sprite.
* \param AlphaMax : seuil de transparence : -1 par defaut (PixelPerfect désactivé)
* \return true si collision il y a, false en cas contraire.
*/
inline bool AreColliding(const sf::Sprite& s1, const sf::Sprite& s2, const int AlphaMax = -1)
{
    // Définition deux objets représentant les dimensions de s1 et s2.
    // Si les Sprites ont été tournés, les calculs ne fonctionneront pas!
    sf::Vector2f pos = s1.GetPosition() - s1.GetCenter();
    const sf::FloatRect r1(pos.x, pos.y, pos.x + s1.GetSize().x, pos.y + s1.GetSize().y);
    pos = s2.GetPosition() - s2.GetCenter();
    const sf::FloatRect r2(pos.x, pos.y, pos.x + s2.GetSize().x, pos.y + s2.GetSize().y);
 
    // Espace de collision potentiel.
    sf::FloatRect zone;
 
    // Testons si les Sprites se superposent.
    if (r1.Intersects(r2, &zone))
    {
        if (AlphaMax >= 0)
        {
            int left1 = static_cast<int>(zone.Left - r1.Left);
            int top1 = static_cast<int>(zone.Top - r1.Top);
 
            int left2 = static_cast<int>(zone.Left - r2.Left);
            int top2 = static_cast<int>(zone.Top - r2.Top);
 
            int width = static_cast<int>(zone.GetWidth());
            int height = static_cast<int>(zone.GetHeight());
 
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    if (s1.GetPixel(x+left1, y+top1).a > AlphaMax && s2.GetPixel(x+left2, y+top2).a > AlphaMax)
                        return true;
                }
            }
 
            return false;
        }
 
        return true;
    }
 
    return false;
}


/*!
* \brief Gestion des collisions entre deux cercles
* \param p1 : Centre du premier cercle
* \param r1 : Rayon du premier cercle
* \param p2 : Centre du second cercle
* \param r2 : Rayon du second cercle
* \return true si collision il y a, false en cas contraire.
*/
inline bool AreColliding(const sf::Vector2f& p1, const float r1, const sf::Vector2f& p2, const float r2)
{
    if (Distance(p1, p2) <= r1+r2)
        return true;
 
    return false;
}


/*!
* \brief Gestion des collisions entre deux sf::Sprites, qui donne la direction du choc pour le sprite 1.
* \author Scaerloc
* \note on peut la mixer avec la fonction "pixel-perfect" ci-dessus, pour faire du pixel perfect.
* \param sprite1 : premier sf::Sprite, qui est la cible (typiquement, un personnage qui veut savoir s'il peut se déplacer dans telle ou telle         direction)
* \param sprite2 : deuxième sf::Sprite, qui est l'obstacle.
* \return un vector de 5 booléens (toutes directions, haut, bas, gauche et droite), qui valent true si le sprite 2 rentre dans le sprite 1 par la     direction définie.
*/
 
// énumération des directions
enum {DIR_DROITE = 0, DIR_GAUCHE = 1, DIR_HAUTE = 2, DIR_BAS = 3, TOUTES_DIR = 4};
 
std::vector < bool > collisionSprites(sf::Sprite sprite1, sf::Sprite sprite2)
{
 
    std::vector < bool > collisionsV(5, false);
 
 
 
       /*Creation des rectangles représentants les surfaces (noms honteusements pompés à la fonction de pixel perfect ;)*/
       sf::FloatRect r1(sprite1.GetLeft(), sprite1.GetTop(), sprite1.GetLeft() + sprite1.GetWidth(), sprite1.GetTop() + sprite1.GetHeight()),
                r2(sprite2.GetLeft(), sprite2.GetTop(), sprite2.GetLeft() + sprite2.GetWidth(), sprite2.GetTop() + sprite2.GetHeight()),
                zone;
 
 
 
       if (r1.Intersects(r2, &zone))
       {
           collisionsV[TOUTES_DIR] = true;
 
        if (zone.Left < r1.Left + r1.GetWidth()/2 && zone.GetHeight() > MARGE_COLLISION_BAS) // si cela arrive par la gauche
            collisionsV[DIR_GAUCHE] = true;                                                  // on met le bool "gauche" à true, etc...
        if (zone.Right > r1.Left + r1.GetWidth()/2 && zone.GetHeight() > MARGE_COLLISION_BAS)
            collisionsV[DIR_DROITE] = true;
 
        if (zone.Top > r1.Top + r1.GetHeight()/2)
            collisionsV[DIR_BAS] = true;
        if (zone.Bottom < r1.Top + r1.GetHeight()/2)
            collisionsV[DIR_HAUTE] = true;
    }
 
return collisionsV; // on renvoie le vector de booléens
}



