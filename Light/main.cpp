
#include "LightManager.h"

int main()
{
    // Création de la fenêtre de rendu.
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Holyspirit Light Test");

    // Création de l'horloge pour gérer le temps.
    sf::Clock Clock;

    // Création d'un tableau dynamique qui contient les images des murs.
    std::vector <sf::Shape> Wall;

    // On ajoute des lignes à "Wall" pour représenter les murs de facon graphique.
    Wall.push_back(sf::Shape::Line(450,  325, 300,  200, 5, sf::Color(255,255,255)));
    Wall.push_back(sf::Shape::Line(250, 240, 400, 365, 5, sf::Color(255,255,255)));
    Wall.push_back(sf::Shape::Line(125, 125, 100, 100, 5, sf::Color(255,255,255)));
    Wall.push_back(sf::Shape::Line(500, 200, 600, 300, 5, sf::Color(255,255,255)));
    Wall.push_back(sf::Shape::Line(500, 300, 600, 200, 5, sf::Color(255,255,255)));
    Wall.push_back(sf::Shape::Line(125, 425, 125, 475, 5, sf::Color(255,255,255)));
    Wall.push_back(sf::Shape::Line(125, 475, 175, 475, 5, sf::Color(255,255,255)));

    // Création du Light_Manager, c'est lui qui va s'occupper de gérer les lumières.
    Light_Manager *Manager;
    Manager=Light_Manager::GetInstance();

    Manager->m_lightSmooth=2;
    Manager->m_basicLight=sf::Color(32,32,32);

    // On ajoute des murs au Light_Manager, ce sont ces murs qui sont pris en compte lors du calcul des lumières
    // (Position du point 1, Position du point 2).

    Manager->Add_Wall(sf::Vector2f(450,325),sf::Vector2f(300,200));
    Manager->Add_Wall(sf::Vector2f(250,240),sf::Vector2f(400,365));
    Manager->Add_Wall(sf::Vector2f(100,100),sf::Vector2f(125,125));
    Manager->Add_Wall(sf::Vector2f(500,200),sf::Vector2f(600,300));
    Manager->Add_Wall(sf::Vector2f(500,300),sf::Vector2f(600,200));
    Manager->Add_Wall(sf::Vector2f(125,425),sf::Vector2f(125,475));
    Manager->Add_Wall(sf::Vector2f(125,475),sf::Vector2f(175,475));


    // Création des Light_Entity, ce sont elles qui permettent de modifier les lumières par après, comme changer de position, de couleur, etc
    Light_Entity light,light2,light3,directional_light;

    // On ajoute une lumière dynamique au Light_Manager et on dit que c'est "light" qui la représente.
    light=Manager->Add_Dynamic_Light();
    light2=Manager->Add_Dynamic_Light();
    // On ajoute une lumière dynamique à la position (600,600), d'intensité 255, de rayon 160, de qualité 16 et de couleur verte.
    light3=Manager->Add_Dynamic_Light(sf::Vector2f(600,200),255,160,16,sf::Color(0,255,0));

    // On ajoute une lumière statique à la position (110,490), d'intensité 160, de rayon 96, de qualité 8 et de couleur blanche. On ne la raccorde pas à une
    // Light_Entity car c'est une lumière statique et qui n'est donc pas modifiable.
    Manager->Add_Static_Light(sf::Vector2f(110,490),160,96,8,sf::Color(255,255,255));

    // On donne la position (375,275) à la lumière raccordée à "light".
    Manager->SetPosition(light,sf::Vector2f(375,275));

    // On donne une intensité de 255 à la lumière raccordée à "light".
    Manager->SetIntensity(light,255);

    // On donne un rayon de 128 à la lumière raccordée à "light".
    Manager->SetRadius(light,128);

    // On donne une qualité de 16 à la lumière raccordée à "light".
    Manager->SetQuality(light,16);

    // On donne une couleur rouge à la lumière raccordée à "light".
    Manager->SetColor(light,sf::Color(255,0,0));


    // Même chose que juste au dessus, mais avec "light2"
    Manager->SetPosition(light2,sf::Vector2f(175,50));
    Manager->SetIntensity(light2,255);
    Manager->SetRadius(light2,128);
    Manager->SetQuality(light2,16);
    Manager->SetColor(light2,sf::Color(0,0,255));


    directional_light = Manager->Add_Dynamic_Directional_Light(sf::Vector2f(750,310),255,384,90,45,sf::Color(255,128,255));



    // Création d'une image qui servira d'image de fond, on charge donc l'image "test.png".
    sf::Image Image;
    Image.LoadFromFile("test.png");
    sf::Sprite background;
    background.SetImage(Image);
    background.Resize(800,600);

    // Création d'une sf::String pour afficher les FPS
    sf::Text FPS;
    // Création d'un buffer pour préparer le texte des FPS
    char buffer[255];

    // Création de variables pour la gestion du temps.
    float AfficherFPS=0,LightRefresh=0;

    //Création de bool pour faire rebondir les lumières
    bool allerX=true,allerY=true;
    bool allerX2=true,allerY2=true;

    float angle = 90;

    // Exécution de la boucle principale
    while (App.IsOpened())
    {
        // Traitement des évènements
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Fenêtre fermée : on quitte
            if (Event.Type == sf::Event::Closed)
                App.Close();
        }

        // On ajoute le temps écoulé
        AfficherFPS+=Clock.GetElapsedTime();
        LightRefresh+=Clock.GetElapsedTime();

        angle += Clock.GetElapsedTime() * 20;


        //On déplace la "light" en fonction du temps, avec allerX et allerY pour savoir si on monte ou on descend.
        if(allerX)
            Manager->SetPosition(light,sf::Vector2f(Manager->GetPosition(light).x+100*Clock.GetElapsedTime(),Manager->GetPosition(light).y));
        else
            Manager->SetPosition(light,sf::Vector2f(Manager->GetPosition(light).x-100*Clock.GetElapsedTime(),Manager->GetPosition(light).y));

        if(allerY)
            Manager->SetPosition(light,sf::Vector2f(Manager->GetPosition(light).x,Manager->GetPosition(light).y+100*Clock.GetElapsedTime()));
        else
            Manager->SetPosition(light,sf::Vector2f(Manager->GetPosition(light).x,Manager->GetPosition(light).y-100*Clock.GetElapsedTime()));

        //Si la "light" sort d'une certaine zone, on modifie allerX et/ou allerY pour faire rebondir.
        if(Manager->GetPosition(light).x>800)
            allerX=false;
        if(Manager->GetPosition(light).x<0)
            allerX=true;

        if(Manager->GetPosition(light).y>600)
            allerY=false;
        if(Manager->GetPosition(light).y<0)
            allerY=true;

        // Ce ne sert que pour la démo technique et n'intervient pas dans l'utilisation du moteur de lumières


        // Idem mais avec light2
        if(allerX2)
            Manager->SetPosition(light2,sf::Vector2f(Manager->GetPosition(light2).x+125*Clock.GetElapsedTime(),Manager->GetPosition(light2).y));
        else
            Manager->SetPosition(light2,sf::Vector2f(Manager->GetPosition(light2).x-125*Clock.GetElapsedTime(),Manager->GetPosition(light2).y));

        if(allerY2)
            Manager->SetPosition(light2,sf::Vector2f(Manager->GetPosition(light2).x,Manager->GetPosition(light2).y+125*Clock.GetElapsedTime()));
        else
            Manager->SetPosition(light2,sf::Vector2f(Manager->GetPosition(light2).x,Manager->GetPosition(light2).y-125*Clock.GetElapsedTime()));

        if(Manager->GetPosition(light2).x>800)
            allerX2=false;
        if(Manager->GetPosition(light2).x<0)
            allerX2=true;

        if(Manager->GetPosition(light2).y>600)
            allerY2=false;
        if(Manager->GetPosition(light2).y<0)
            allerY2=true;


        // On récupère la position de la souris
        const sf::Input& Input = App.GetInput();
        // On place light 3 à cette position, avec un tout petit décalage, pour éviter d'avoir une lumière pile sur l'axe d'un mur, ça peut engendrer des problèmes pour le moment.
        Manager->SetPosition(light3,sf::Vector2f(Input.GetMouseX(),Input.GetMouseY()));

        Manager->SetOtherParameter(directional_light,ANGLE,angle);

        Clock.Reset();

        //Vous pouvez changer le 0.025 par une autre valeur si vous voulez que les lumières ne se rafraichissent que toutes les x secondes, au lieu de le faire à chaque tour de boucle.
        if(LightRefresh>0.025)
        {
            // On re-calcule les lumières
            Manager->Generate();
            LightRefresh=0;
        }

        // Efface l'écran (remplissage avec du noir)
        App.Clear();

        // On affiche le fond
        App.Draw(background);

        // On affiches les murs
        for(int w=0;w<(int)Wall.size();w++)
            App.Draw(Wall[w]);

        // On affiche les lumières
        Manager->Draw(&App);

        // On affiche les FPS
        if(AfficherFPS>0.2)
        {
            float Framerate = 1.f / App.GetFrameTime();
            sprintf(buffer,"%i",(int)Framerate);
            FPS.SetString(buffer);
            AfficherFPS=0;
        }
        App.Draw(FPS);



        // Affichage du contenu de la fenêtre à l'écran
        App.Display();
    }

     Manager->Kill();

    return EXIT_SUCCESS;
}



