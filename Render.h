#define NOMINMAX
#include <mutex>
enum shapes{ CUBE, PYRAMID, SPHERE };
struct Property
{
	int id;
	shapes shape;
	unsigned int color;
	int position[3];
	float scale;
	float angleX;
	float angleY;
	float angleZ;
	bool deleted;
	bool added;
	std::string name;
	Property() :
		deleted(false),
		added(true),
		color(4294967040),
		scale(1.0f),
		angleX(0.0f),
		angleY(0.0f),
		angleZ(0.0f)
	{
		for (auto &el : position)
			el = 0;
	}
	
};

class Render
{
public:
	
	~Render();
	void onDisplay();
	void StartRendering();
private:
	void drawPyramid(const Property &);
	void drawCube(const Property &);
	void drawSphere(const Property &);
};