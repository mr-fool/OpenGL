float functionX(float radius, float u, float v) {
	radius * cos(2.f * PI * u) * sin(PI * v)
}
float functionY(float radius, float u, float v) {
	radius * sin(2.f * PI * u) * sin(PI * v)
}
float functionZ(float radius, float u, float v) {
	radius * cos(PI * v)) + center
}
void Scene::generateSphere(vector<vec3>& positions, vector<vec3>& normals, vector<vec2>& uvs, vector<unsigned int>& indices, vec3 center, float radius, int divisions) {
	objects.clear();
	rectangle.verts.clear();
	rectangle.uvs.clear();
	MyTexture texture;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	float step = 1.f / (float)(divisions - 1);
	float u = 0.f;

	// Traversing the planes of time and space
	for (int i = 0; i < divisions; i++) {
		float v = 0.f;

		//Traversing the planes of time and space (again)
		for (int j = 0; j < divisions; j++) {
			/*vec3 pos = vec3(radius * cos(2.f * PI * u) * sin(PI * v),
				radius * sin(2.f * PI * u) * sin(PI * v),
				radius * cos(PI * v)) + center;*/
			vec3 pos = vec3(u, v, 0.0f);
			vec3 normal = normalize(pos - center);
			//std::cout << "rectangle.verts.push_back " + glm::to_string(pos) << std::endl;

			rectangle.verts.push_back(pos);
			//rectangle.verts.push_back(normal);
			rectangle.uvs.push_back(vec2(u, v));

			pos = vec3(u + step, v, 0.0f);
			//std::cout << "rectangle.verts.push_back " + glm::to_string(pos) << std::endl;

			rectangle.verts.push_back(pos);
			//rectangle.verts.push_back(normal);
			rectangle.uvs.push_back(vec2(u, v));

			pos = vec3(u, v + step, 0.0f);
			//std::cout << "rectangle.verts.push_back " + glm::to_string(pos) << std::endl;

			rectangle.verts.push_back(pos);
			//rectangle.verts.push_back(normal);
			rectangle.uvs.push_back(vec2(u, v));

			pos = vec3(u + step, v + step, 0.0f);
			//std::cout << "rectangle.verts.push_back " + glm::to_string(pos) << std::endl;

			rectangle.verts.push_back(pos);
			//rectangle.verts.push_back(normal);
			rectangle.uvs.push_back(vec2(u, v));

			pos = vec3(u, v + step, 0.0f);
			//std::cout << "rectangle.verts.push_back " + glm::to_string(pos) << std::endl;

			rectangle.verts.push_back(pos);
			//rectangle.verts.push_back(normal);
			rectangle.uvs.push_back(vec2(u, v));

			pos = vec3(u + step, v, 0.0f);
			//std::cout << "rectangle.verts.push_back " + glm::to_string(pos) << std::endl;

			rectangle.verts.push_back(pos);
			//rectangle.verts.push_back(normal);
			rectangle.uvs.push_back(vec2(u, v));

			v += step;
		}

		u += step;

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
