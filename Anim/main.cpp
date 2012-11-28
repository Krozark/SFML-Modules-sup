//Charge l'image de zelda
	sf::Image imgZelda;
	imgZelda.LoadFromFile("A_000.png");
	imgZelda.SetSmooth(false);
	imgZelda.CreateMaskFromColor(sf::Color(255,0,255));
 
	//Créer 4 animation de 8 frame chaque à partir de l'image imgZelda
	ImgAnim zelda(imgZelda,8,4);
	while(1)
	{
		const sf::Input& Input = App.GetInput();
		if(Input.IsKeyDown(sf::Key::Left) )
		{
			zelda.Move(-SPEED,0.f);
			zelda.setAnimRow(3);
			zelda.play();
		}
 
		if(Input.IsKeyDown(sf::Key::Right) )
		{			
			zelda.Move(SPEED,0.f);
			zelda.setAnimRow(1);
			zelda.play();
		}
		if(Input.IsKeyDown(sf::Key::Up))
		{
			zelda.Move(0.f,-SPEED);
			zelda.setAnimRow(2);
			zelda.play();
		}
		if(Input.IsKeyDown(sf::Key::Down))
		{
			zelda.Move(0.f,SPEED);
			zelda.setAnimRow(0);
			zelda.play();
		}
		if(!Input.IsKeyDown(sf::Key::Down) &&
			!Input.IsKeyDown(sf::Key::Up) &&
			!Input.IsKeyDown(sf::Key::Right) &&
			!Input.IsKeyDown(sf::Key::Left))
		{
			zelda.stop();
		}
		App.Draw(zelda);
	}
