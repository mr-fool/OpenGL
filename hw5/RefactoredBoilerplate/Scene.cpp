void Scene::generateSphere(vector<vec3>& positions, vector<vec3>& normals, vector<vec2>& uvs, vector<unsigned int>& indices, vec3 center, float radius, int divisions) {
	objects.clear();
	rectangle.verts.clear();
	rectangle.uvs.clear();
	MyTexture texture;
	float step = 1.f / (float)(divisions - 1);
	float u = 0.f;

	// Traversing the planes of time and space
	for (int i = 0; i < divisions; i++) {
		float v = 0.f;

		//Traversing the planes of time and space (again)
		for (int j = 0; j < divisions; j++) {
			vec3 pos = vec3(radius * cos(2.f * PI * u) * sin(PI * v),
				radius * sin(2.f * PI * u) * sin(PI * v),
				radius * cos(PI * v)) + center;

			vec3 normal = normalize(pos - center);
			//std::cout << "rectangle.verts.push_back " + glm::to_string(pos) << std::endl;

			rectangle.verts.push_back(pos);
			rectangle.verts.push_back(normal);
			rectangle.uvs.push_back(vec2(u, v));

			v += step;
		}

		u += step;
	}
	for (int i = 0; i < divisions - 1; i++)
	{
		for (int j = 0; j < divisions - 1; j++)
		{
			unsigned int p00 = i * divisions + j;
			unsigned int p01 = i * divisions + j + 1;
			unsigned int p10 = (i + 1) * divisions + j;
			unsigned int p11 = (i + 1) * divisions + j + 1;

			indices.push_back(p00);
			indices.push_back(p10);
			indices.push_back(p01);

			indices.push_back(p01);
			indices.push_back(p10);
			indices.push_back(p11);
		}
	}
	rectangle.drawMode = GL_TRIANGLES;
	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(rectangle);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(rectangle);

	//Add the triangle to the scene objects
	objects.push_back(rectangle);
}
