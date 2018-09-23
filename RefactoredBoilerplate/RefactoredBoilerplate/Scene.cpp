Geometry* Scene::createSquare(double side_length) {

	Geometry *square = new Geometry();

	//Create the first iteration of square and diamond
	square->verts.push_back(vec3(-side_length, -side_length, 1.0f));
	square->verts.push_back(vec3(-side_length, side_length, 1.0f));
	square->verts.push_back(vec3(side_length, side_length, 1.0f));
	square->verts.push_back(vec3(side_length, -side_length, 1.0f));

	// set initial dimensions of the square
	square->drawMode = GL_LINE_LOOP;
	square->colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	square->colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	square->colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	square->colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	return square;
}
Geometry* Scene::createDiamond(double side_length) {

	Geometry *diamond = new Geometry();

	//Create the first iteration of square and diamond
	diamond->verts.push_back(vec3(0.0, -side_length , 1.0f));
	diamond->verts.push_back(vec3(-side_length, 0.0f , 1.0f));
	diamond->verts.push_back(vec3(0.0 , side_length , 1.0f));
	diamond->verts.push_back(vec3(side_length, 0.0f, 1.0f));


	// set initial dimensions of the square
	diamond->drawMode = GL_LINE_LOOP;
	diamond->colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	diamond->colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	diamond->colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	diamond->colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	
	return diamond;
}


void Scene::diamondAndSquare(int level, vector<Geometry> &objects) {
	objects.clear();
	double side_length = 0.9;
	double size = side_length / 2;

	for (int i = 1; i <= level; i++) {
		Geometry square = *Scene::createSquare(size);
		Geometry diamond =  *Scene::createDiamond(size);

		RenderingEngine::assignBuffers(square);
		RenderingEngine::assignBuffers(diamond);

		RenderingEngine::setBufferData(square);
		RenderingEngine::setBufferData(diamond);
		objects.push_back(square);
		objects.push_back(diamond);
		size = size/2;
	}
	
}
