#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

int main() {
	int width, height, terraintype, terrainvariant, smoothness;

	cout << "MagicWar random map generator" << endl;
	cout << "Map width : ";
	cin >> width;
	cout << "Map height : ";
	cin >> height;
	cout << "Terrain type : ";
	cin >> terraintype;
	cout << "Terrain variant : ";
	cin >> terrainvariant;
	cout << "Smootness (recommended 3 to 5) : ";
	cin >> smoothness;
	cout << "Generating map..." << endl;

	float *map = new float[(width + 1) * (height + 1)];

	srand(time(0));

	for (unsigned int x = 0; x <= width; x++) {
		for (unsigned int y = 0; y <= width; y++) {
			map[x * width + y] = (float)rand() / (float)RAND_MAX * 50.f - 23.f;
		}
	}

	for (int i = 0; i < smoothness; i++) {
		for (unsigned int x = 0; x <= width; x++) {
			for (unsigned int y = 0; y <= height; y++) {
				float h = 0, k = 0;
				for (int dx = -1; dx <= 1; dx++) {
					for (int dy = -1; dy <= 1; dy++) {
						if (x + dx >= 0 && y + dy >= 0 && x + dx <= width && y + dy <= height) {
							k++;
							h += map[(x + dx) * width + (y + dy)];
						}
					}
				}
				map[x * width + y] = h / k;
			}
		}
	}

	ofstream file("newmap.map", ios::out);

	if (file) {
		file << width << " " << height << endl;
		for (unsigned int x = 0; x <= width; x++) {
			for (unsigned int y = 0; y <= height; y++) {
				file << map[x * width + y] << " " << 0 << " " << terraintype << " "
					<< terrainvariant << " " << true << endl;
			}
		}
		cout << "How many random units to place : ";
		int n;
		cin >> n;
		file << n << endl;
		cout << "These units will be selected in : tree1(10) mine1(1)" << endl;
		vector<string> types;
		types.push_back("tree1"); types.push_back("mine1");
		for (int i = 0; i < 9; i++) types.push_back("tree1");
		for (int i = 0; i < n; i++) {
			file << types[(float)(rand() / (float)RAND_MAX * (float)types.size())] << " " <<
				(float)(rand() / (float)RAND_MAX * width) << " " << (float)(rand() / (float)RAND_MAX * height) << endl;
		}
		//Bases positions
		file << width / 4 << " " << height / 4 << endl;
		file << width / 4 * 3 << " " << height / 4 * 3 << endl;
		file << width / 4 << " " << height / 4 * 3 << endl;
		file << width / 4 * 3 << " " << height / 4 << endl;
		file << width / 2 << " " << height / 4 << endl;
		file << width / 2 << " " << height / 4 * 3 << endl;
		file << width / 4 << " " << height / 2 << endl;
		file << width / 4 * 3 << " " << height / 2 << endl;

		file.close();
		cout << "Done, saved to newmap.map" << endl;
	} else {
		cout << "Error : cannot open output file." << endl;
	}
}
