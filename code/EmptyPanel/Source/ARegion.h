#ifndef AREGION_H
#define AREGION_H

#include "APath.h"
#include <vector>

#include "MyColor.h"

struct ARegion
{
	std::vector<std::vector<AVector>> _streamLines;
	std::vector<std::vector<AVector>> _skeletonLines;

	std::vector<APath> _boundaryPaths;

	std::vector<int>  _boundaryFColors; // foreground colors (pallette mode)
	std::vector<int>  _boundaryBColors; // background colors (pallette mode)

	std::vector<MyColor>  _boundaryFColorsRGB; // foreground colors (RGB mode)
	std::vector<MyColor>  _boundaryBColorsRGB; // background colors (RGB mode)

	//std::vector<APath> _detailPaths;
	std::vector<APath> _focalPaths;
	std::vector<APath> _fieldPaths;

	std::vector<APath> _boundaryMSTPath;

	std::vector<std::vector<AVector>> _holes;
	//std::vector<APath> _seedPaths;
};

#endif