
//#include "stdafx.h"

#include "PathIO.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include <sstream> // std::stringstream

#include "MyColor.h"

// split string
std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

// split string
std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}


PathIO::PathIO()
{
}

PathIO::~PathIO()
{
}

/*

file format:

	[num_region] # first line only	
	foreground_color [region number]  c0 c1 c2 c3...
	background_color [region number]   c0 c1 c2 c3...
	[region number] [is_closed_path] [path_type] x0 y0 x1 y1 x2 y2...
	[region number] [is_closed_path] [path_type] x0 y0 x1 y1 x2 y2...
	[region number] [is_closed_path] [path_type] x0 y0 x1 y1 x2 y2...
	...
	
	EOF


explanation:

	region number lets us to know a certain path belongs to a certain region.
	a region has it's own vector field


	is_closed_path = 1, if it's closed
	is_closed_path = 0, if it's an open path

	path_type are either SHAPE_PATH or FIELD_PATH (see APath.h)

*/

void PathIO::SaveRegions(std::vector<ARegion> regions, std::string filename)
{
	std::ofstream* f = new std::ofstream();
	f->open(filename);

	// first line tells us how many regions there are
	*f << regions.size() << "\n";

	// iterate
	for (size_t a = 0; a < regions.size(); a++)
	{
		ARegion aRegion = regions[a];

		if (aRegion._boundaryFColors.size() > 0)
		{
			*f << "foreground_color " << a << " ";
			for (size_t c = 0; c < aRegion._boundaryFColors.size(); c++)
			{
				*f << aRegion._boundaryFColors[c];
				if (c < aRegion._boundaryFColors.size() - 1) { *f << " "; }
			}
			*f << "\n";
		}

		if (aRegion._boundaryBColors.size() > 0)
		{
			*f << "background_color " << a << " ";
			for (size_t c = 0; c < aRegion._boundaryBColors.size(); c++)
			{
				*f << aRegion._boundaryBColors[c];
				if (c < aRegion._boundaryBColors.size() - 1) { *f << " "; }
			}
			*f << "\n";
		}


		if (aRegion._boundaryFColorsRGB.size() > 0)
		{
			*f << "foreground_color_rgb " << a << " ";
			for (size_t c = 0; c < aRegion._boundaryFColorsRGB.size(); c++)
			{
				MyColor col = aRegion._boundaryFColorsRGB[c];
				*f << col._r << "," << col._g << "," << col._b;
				if (c < aRegion._boundaryFColorsRGB.size() - 1) { *f << " "; }
			}
			*f << "\n";
		}

		if (aRegion._boundaryBColorsRGB.size() > 0)
		{
			*f << "background_color_rgb " << a << " ";
			for (size_t c = 0; c < aRegion._boundaryBColorsRGB.size(); c++)
			{
				MyColor col = aRegion._boundaryBColorsRGB[c];
				*f << col._r << "," << col._g << "," << col._b;
				if (c < aRegion._boundaryBColorsRGB.size() - 1) { *f << " "; }
			}
			*f << "\n";
		}

		// BOUNDARY_PATH = 0,
		for (int b = 0; b < aRegion._boundaryPaths.size(); b++)
		{
			APath boundaryPath = aRegion._boundaryPaths[b];
			SavePath(f, boundaryPath, a);
		}

		// DETAIL_PATH = 1,
		/*for (int b = 0; b < aRegion._detailPaths.size(); b++)
		{
			APath boundaryPath = aRegion._boundaryPaths[b];
			//...not yet implemented
		}*/
		
		// FOCAL_PATH = 2,
		for (int b = 0; b < aRegion._focalPaths.size(); b++)
		{
			APath focalPath = aRegion._focalPaths[b];
			SavePath(f, focalPath, a);
		}
		
		// FIELD_PATH = 3,
		for (int b = 0; b < aRegion._fieldPaths.size(); b++)
		{
			APath fieldPath = aRegion._fieldPaths[b];
			SavePath(f, fieldPath, a);
		}

		// SEED_PATH = 4,
		/*for (int b = 0; b < aRegion._seedPaths.size(); b++)
		{
			APath seedPath = aRegion._seedPaths[b];
			SavePath(f, seedPath, a);
		}*/

		// STREAM_LINE = 5
		for (int b = 0; b < aRegion._streamLines.size(); b++)
		{
			APath streamPath;
			streamPath.isClosed = false;
			streamPath.pathType = STREAM_LINE;
			streamPath.points = aRegion._streamLines[b];
			SavePath(f, streamPath, a);
		}

		// SKELETON_LINE = 6
		for (int b = 0; b < aRegion._skeletonLines.size(); b++)
		{
			APath streamPath;
			streamPath.isClosed = false;
			streamPath.pathType = SKELETON_LINE;
			streamPath.points = aRegion._skeletonLines[b];
			SavePath(f, streamPath, a);
		}

		// HOLES = 7
		for (int b = 0; b < aRegion._holes.size(); b++)
		{
			APath streamPath;
			streamPath.isClosed = false;
			streamPath.pathType = HOLE;
			streamPath.points = aRegion._holes[b];
			SavePath(f, streamPath, a);
		}

		// BOUNDARY MST
		//for (int b = 0; b < aRegion._boundaryMSTPath.size(); b++)
		//{
		//	SavePath(f, aRegion._boundaryMSTPath[b], a);
		//}
	}

	f->close();

	delete f;
}

void PathIO::SavePath(std::ofstream* f, APath aPath, int no_region)
{
	// no region (metadata)
	*f << no_region << " ";

	// is_closed_path (metadata)
	if (aPath.isClosed) { *f << "1" << " "; }
	else { *f << "0" << " "; }

	// path type (metadata)
	*f << aPath.pathType << " ";

	// points
	for (size_t b = 0; b < aPath.points.size(); b++)
	{
		*f << std::setprecision(20) << aPath.points[b].x << " " << std::setprecision(20) << aPath.points[b].y;
		if (b < aPath.points.size() - 1) { *f << " "; }
	}
	*f << "\n";
}

/*void PathIO::SavePath(std::vector<APath> paths, std::string filename)
{
	std::ofstream f;
	f.open(filename);

	for (size_t a = 0; a < paths.size(); a++)
	{
		APath aPath = paths[a];

		// is_closed_path metadata
		if (aPath.isClosed) { f << "1" << " "; }
		else { f << "0" << " "; }

		// path type metadata
		f << aPath.pathType << " ";

		// points
		for (size_t b = 0; b < aPath.points.size(); b++)
		{
			f << std::setprecision(20) << aPath.points[b].x << " " << std::setprecision(20) << aPath.points[b].y;
			if (b < aPath.points.size() - 1) { f << " "; }
		}
		f << "\n";
	}


	f.close();
}*/

/*
One path per line
format:
x0 y0 x1 y1 x2 y2...
*/

/*std::vector<APath> PathIO::LoadPath(std::string filename)
{
	std::vector<APath> paths;

	std::ifstream myfile(filename);
	while (!myfile.eof())
	{
		APath aPath;

		std::string line;
		std::getline(myfile, line);

		std::vector<std::string> arrayTemp = split(line, ' ');

		if (arrayTemp.size() == 0) { continue; }

		std::vector<std::string> metadataArray(arrayTemp.begin(), arrayTemp.begin() + 2); // this is metadata
		std::vector<std::string> pathArray(arrayTemp.begin() + 2, arrayTemp.end()); // this is path

		// read path
		if (pathArray.size() < 2) { continue; }
		size_t halfLength = pathArray.size() / 2;
		for (size_t a = 0; a < halfLength; a++)
		{
			int idx = a * 2;
			double x = std::stod(pathArray[idx]);
			double y = std::stod(pathArray[idx + 1]);
			aPath.points.push_back(AVector(x, y));
		}

		// read metadata
		aPath.isClosed = (int)std::stoi(metadataArray[0]);		// is it closed
		aPath.pathType = (PathType)std::stoi(metadataArray[1]); // path type

		// push the new path
		paths.push_back(aPath);
	}

	myfile.close();

	return paths;
}*/

std::vector<ARegion> PathIO::LoadRegions(std::string filename)
{
	std::vector<ARegion> duhRegions;

	//int lineNumber = 0;

	std::ifstream myfile(filename);

	std::string firstLine;
	std::getline(myfile, firstLine);
	int numRegion = (int)std::stoi(firstLine);
	duhRegions = std::vector<ARegion>(numRegion);

	while (!myfile.eof())
	{
		APath aPath;

		std::string line;
		std::getline(myfile, line);
		std::vector<std::string> arrayTemp = split(line, ' ');
		if (arrayTemp.size() == 0) { continue; }

		if (arrayTemp[0] == "foreground_color")
		{
			int whatRegionDude = (int)std::stoi(arrayTemp[1]);
			std::vector<int> fColors;
			for (int a = 2; a < arrayTemp.size(); a++)
				{ fColors.push_back(std::stoi(arrayTemp[a])); }
			duhRegions[whatRegionDude]._boundaryFColors = fColors;

			continue;
		}
		else if (arrayTemp[0] == "background_color")
		{
			int whatRegionDude = (int)std::stoi(arrayTemp[1]);
			std::vector<int> bColors;
			for (int a = 2; a < arrayTemp.size(); a++)
				{ bColors.push_back(std::stoi(arrayTemp[a])); }
			duhRegions[whatRegionDude]._boundaryBColors = bColors;

			continue;
		}
		else if (arrayTemp[0] == "foreground_color_rgb")
		{
			int whatRegionDude = (int)std::stoi(arrayTemp[1]);

			std::vector<MyColor> fColors;
			for (int a = 2; a < arrayTemp.size(); a++)
			{
				std::vector<std::string> colTemp = split(arrayTemp[a], ',');
				MyColor col = MyColor(std::stoi(colTemp[0]), std::stoi(colTemp[1]), std::stoi(colTemp[2]));
				fColors.push_back(col);
			}
			duhRegions[whatRegionDude]._boundaryFColorsRGB = fColors;

			continue;
		}
		else if (arrayTemp[0] == "background_color_rgb")
		{
			int whatRegionDude = (int)std::stoi(arrayTemp[1]);

			std::vector<MyColor> bColors;
			for (int a = 2; a < arrayTemp.size(); a++)
			{
				std::vector<std::string> colTemp = split(arrayTemp[a], ',');
				MyColor col = MyColor(std::stoi(colTemp[0]), std::stoi(colTemp[1]), std::stoi(colTemp[2]));
				bColors.push_back(col);
			}
			duhRegions[whatRegionDude]._boundaryBColorsRGB = bColors;

			continue;
		}

		std::vector<std::string> metadataArray(arrayTemp.begin(), arrayTemp.begin() + 3); // this is metadata
		std::vector<std::string> pathArray(arrayTemp.begin() + 3, arrayTemp.end()); // this is path

		// read metadata
		int whatRegionDude = (int)std::stoi(metadataArray[0]);
		aPath.isClosed = (int)std::stoi(metadataArray[1]);		// is it closed
		aPath.pathType = (PathType)std::stoi(metadataArray[2]); // path type

		// read path
		if (pathArray.size() < 2) { continue; }
		size_t halfLength = pathArray.size() / 2;
		for (size_t a = 0; a < halfLength; a++)
		{
			int idx = a * 2;
			double x = std::stod(pathArray[idx]);
			double y = std::stod(pathArray[idx + 1]);
			aPath.points.push_back(AVector(x, y));
		}

		/*
			BOUNDARY_PATH = 0
			DETAIL_PATH   = 1
			FOCAL_PATH    = 2
			FIELD_PATH    = 3
			SEED_PATH     = 4
			STREAM_LINE   = 5
			SKELETON_LINE = 6
		*/
		if (aPath.pathType == BOUNDARY_PATH)
		{
			duhRegions[whatRegionDude]._boundaryPaths.push_back(aPath);
		}
		else if (aPath.pathType == DETAIL_PATH)
		{
			//duhRegions[whatRegionDude]._detailPaths.push_back(aPath);
		}
		else if (aPath.pathType == FOCAL_PATH)
		{
			duhRegions[whatRegionDude]._focalPaths.push_back(aPath);
		}
		else if (aPath.pathType == FIELD_PATH)
		{
			duhRegions[whatRegionDude]._fieldPaths.push_back(aPath);
		}
		else if (aPath.pathType == SEED_PATH)
		{
			//duhRegions[whatRegionDude]._seedPaths.push_back(aPath);
		}
		else if (aPath.pathType == SKELETON_LINE)
		{
			duhRegions[whatRegionDude]._skeletonLines.push_back(aPath.points);
		}
		else if (aPath.pathType == HOLE)
		{
			duhRegions[whatRegionDude]._holes.push_back(aPath.points);
		}
	}

	for (unsigned int a = 0; a < duhRegions.size(); a++)
	{
		if (duhRegions[a]._boundaryPaths.size() > 0    && 
			duhRegions[a]._boundaryFColors.size() == 0 && 
			duhRegions[a]._boundaryBColors.size() == 0)
		{
			std::cout << "region " << a << " doesn't have F and B colors\n";
			for (unsigned int b = 0; b < duhRegions[a]._boundaryPaths.size(); b++)
			{
				duhRegions[a]._boundaryFColors.push_back(7);
				duhRegions[a]._boundaryBColors.push_back(8);
			}
		}
	}

	myfile.close();

	return duhRegions;
}
