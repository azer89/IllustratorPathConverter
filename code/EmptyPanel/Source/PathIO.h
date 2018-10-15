

#include <vector>
#include "ARegion.h"
#include <cstring>

class PathIO
{
public:
	PathIO();
	~PathIO();

	// save to a file
	//void SavePath(std::vector<APath> paths, std::string filename);
	void SaveRegions(std::vector<ARegion> regions, std::string filename);

	// [region number] [is_closed_path] [path_type] x0 y0 x1 y1 x2 y2...
	void SavePath(std::ofstream* f, APath aPath, int no_region);
	
	// load from a file
	//std::vector<APath> LoadPath(std::string filename);
	std::vector<ARegion> LoadRegions(std::string filename);

};
