#include "LightManager.h"
 
Light_Manager::Light_Manager()
{
    m_lightSmooth=0;
 
    m_render=new sf::Sprite;
    m_render->FlipY(true);
    m_render->SetImage(m_renderImg);
    m_render->SetBlendMode(sf::Blend::Multiply);
 
    // Chargement du postFX pour adoucir les bords.
    BlurEffect.LoadFromFile("blur.sfx");
    BlurEffect.SetTexture("framebuffer", NULL);
 
}
Light_Manager::~Light_Manager()
{
    m_wall.clear();
    m_StaticLight.clear();
    m_DynamicLight.clear();
    delete m_render;
}
 
// Les différents moyens d'ajouter des lumières
 
Light_Entity Light_Manager::Add_Dynamic_Light()
{
    m_DynamicLight.push_back(Light ());
    return Light_Entity((int)m_DynamicLight.size()-1,true);
}
Light_Entity Light_Manager::Add_Dynamic_Light(Light light)
{
    m_DynamicLight.push_back(light);
    return Light_Entity((int)m_DynamicLight.size()-1,true);
}
Light_Entity Light_Manager::Add_Dynamic_Light(sf::Vector2f position, float intensity, float radius, int quality, sf::Color color)
{
    m_DynamicLight.push_back(Light (position,intensity,radius,quality,color));
    return Light_Entity((int)m_DynamicLight.size()-1,true);
}
 
 
// Notez bien qu'on calcule les lumières statiques lors de leur ajout.
 
Light_Entity Light_Manager::Add_Static_Light(Light light)
{
    m_StaticLight.push_back(light);
    m_StaticLight.back().Generate(m_wall);
    return Light_Entity((int)m_StaticLight.size()-1,false);
}
Light_Entity Light_Manager::Add_Static_Light(sf::Vector2f position, float intensity, float radius, int quality, sf::Color color)
{
    m_StaticLight.push_back(Light (position,intensity,radius,quality,color));
    m_StaticLight.back().Generate(m_wall);
    return Light_Entity((int)m_StaticLight.size()-1,false);
}
 
// Ajouter un mur
 
Wall_Entity Light_Manager::Add_Wall(sf::Vector2f pt1,sf::Vector2f pt2)
{
    m_wall.push_back(Wall (pt1,pt2));
    return Wall_Entity(m_wall.size()-1);
}
 
// On désactive une lumière
void Light_Manager::Delete_Light(Light_Entity e)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            m_DynamicLight[e.ID()].m_actif=false;
    else
        if(e.ID()>=0&&e.ID()<(int)m_StaticLight.size())
            m_StaticLight[e.ID()].m_actif=false;
}
 
// On supprime un mur
void Light_Manager::Delete_Wall(Wall_Entity e)
{
    m_wall.erase(m_wall.begin()+e.ID());
}
 
void Light_Manager::Delete_All_Wall()
{
    m_wall.clear();
}
void Light_Manager::Delete_All_Light()
{
    m_StaticLight.clear();
    m_DynamicLight.clear();
}
 
// On calcule toutes les lumières dynamiques actives
void Light_Manager::Generate()
{
    for(Iter=m_DynamicLight.begin();Iter!=m_DynamicLight.end();++Iter)
        if(Iter->m_actif)
            Iter->Generate(m_wall);
}
 
// On calcul une lumière en particulier
void Light_Manager::Generate(Light_Entity e)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            m_DynamicLight[e.ID()].Generate(m_wall);
}
 
// On crée une image avec toutes les lumières actives
void Light_Manager::Draw(sf::RenderWindow *App)
{
    App->Clear(m_basicLight);
 
    for(Iter=m_DynamicLight.begin();Iter!=m_DynamicLight.end();++Iter)
        if(Iter->m_actif)
            Iter->Draw(App);
    for(Iter=m_StaticLight.begin();Iter!=m_StaticLight.end();++Iter)
        if(Iter->m_actif)
            Iter->Draw(App);
 
    for(int i=m_lightSmooth;i>0;i--)
    {
        BlurEffect.SetParameter("offset",i*0.005/m_lightSmooth);
        App->Draw(BlurEffect);
    }
 
    m_renderImg.CopyScreen(*App);
    m_render->SetImage(m_renderImg);
}
 
// On modifie ou récupère les attributs de lumières dynamiques
 
void Light_Manager::SetPosition(Light_Entity e, sf::Vector2f p)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            m_DynamicLight[e.ID()].SetPosition(p);
}
void Light_Manager::SetQuality(Light_Entity e, int q)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            m_DynamicLight[e.ID()].SetQuality(q);
}
void Light_Manager::SetRadius(Light_Entity e, int r)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            m_DynamicLight[e.ID()].SetRadius(r);
}
void Light_Manager::SetColor(Light_Entity e, sf::Color c)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            m_DynamicLight[e.ID()].SetColor(c);
}
void Light_Manager::SetIntensity(Light_Entity e, int i)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            m_DynamicLight[e.ID()].SetIntensity(i);
}
 
 
float Light_Manager::GetIntensity(Light_Entity e)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            return m_DynamicLight[e.ID()].GetIntensity();
    return 0;
}
float Light_Manager::GetRadius(Light_Entity e)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            return m_DynamicLight[e.ID()].GetRadius();
    return 0;
}
int Light_Manager::GetQuality(Light_Entity e)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            return m_DynamicLight[e.ID()].GetQuality();
 
    return 0;
}
sf::Color Light_Manager::GetColor(Light_Entity e)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            return m_DynamicLight[e.ID()].GetColor();
 
    return sf::Color (0,0,0);
}
sf::Vector2f Light_Manager::GetPosition(Light_Entity e)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            return m_DynamicLight[e.ID()].GetPosition();
 
    return sf::Vector2f (0,0);
}
 
 
 
// On modifie ou récupère différents attributs des murs
 
void Light_Manager::SetPosition(Wall_Entity e, sf::Vector2f p)
{
    if(e.ID()>=0&&e.ID()<(int)m_wall.size())
    {
        sf::Vector2f buffer=m_wall[e.ID()].pt1;
        m_wall[e.ID()].pt1=p;
        m_wall[e.ID()].pt2.x= m_wall[e.ID()].pt2.x + (p.x-buffer.x);
        m_wall[e.ID()].pt2.y= m_wall[e.ID()].pt2.y + (p.y-buffer.y);
    }
}

