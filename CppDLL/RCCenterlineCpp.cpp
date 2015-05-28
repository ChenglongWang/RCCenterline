#include "mist/mist.h"
#include "mist/vector.h"
#include "mist/filter/thinning.h"
#include <algorithm>
#include "fit.h"


extern "C"
{
	__declspec(dllexport) bool _stdcall Run(const mist::array3<short> *originImage, mist::array3<short>* centerlineImage, int target, bool oppsite = false);
}

inline mist::vector3<int> MapWorldToVoxel(double x, double y, double z,
	const double* origin, const double* reso, const int* dims)
{
	int i, loc[3];
	double d(0.0);

	double pos[3] = { x, y, z };

	//
	//  Compute the ijk location
	//
	for (i = 0; i < 3; i++)
	{
		d = pos[i] - origin[i];
		loc[i] = floor((d / reso[i]) + 0.5);
		if (loc[i] < 0 || loc[i] > dims[i] - 1)
		{
			return mist::vector3<int>(0, 0, 0);
		}
		// since point id is relative to the first point actually stored
	}
	//
	//  From this location get the point id
	//
	mist::vector3<int> ijk(loc[0], loc[1], loc[2]);
	return ijk;
}

bool _stdcall Run(const mist::array3<short> *originImage, mist::array3<short>* centerAxis, int target, bool oppsite)
{
	if (originImage == nullptr)
		return false;

	mist::array3<short> targetImage(*originImage);
	mist::array3<short> centerlineImage(originImage->size1(), originImage->size2(), originImage->size3(), originImage->reso1(), originImage->reso2(), originImage->reso3());
	for_each(targetImage.begin(), targetImage.end(), [target](short& v){if (v != target) v = 0; });

	mist::euclidean::thinning26(targetImage, centerlineImage);

	std::vector<size_t> points_id;
	for (size_t x = 0; x < centerlineImage.size(); ++x)
	{
		if (centerlineImage[x] != 0)
			points_id.push_back(x);
	}

	int centroid[3] = { 0 };
	double direction[3] = { 0 };
	ls::Fit linearFitter;
	linearFitter.LinearFit(originImage, points_id);
	linearFitter.GetCentroid(centroid);
	linearFitter.GetDirection(direction);

	double extent[3];
	extent[0] = originImage->size1() * originImage->reso1();
	extent[1] = originImage->size2() * originImage->reso2();
	extent[2] = originImage->size3() * originImage->reso3();

	double origin[3] = { 0 };
	double reso[3] = { originImage->reso1(), originImage->reso2(), originImage->reso3() };
	int dims[3] = { originImage->size1(), originImage->size2(), originImage->size3() };

	double k1 = direction[1] / direction[0];
	double k2 = direction[2] / direction[0];
	if (oppsite)//for temp
	{
		for (double x = centroid[0]; x > 0; x -= 0.1)
		{
			auto y = static_cast<int>(k1 * (x - centroid[0]) + centroid[1]);
			auto z = static_cast<int>(k2 * (x - centroid[0]) + centroid[2]);
		
			if (x > 0 && x < originImage->size1() && y > 0 && y < originImage->size2() && z > 0 && z < originImage->size3())
			{
				(*centerAxis)(x, y, z) = 5;
			}
		}
	}
	else
	{
		for (double x = centroid[0]; x < originImage->size1(); x += 0.1)
		{
			auto y = static_cast<int>(k1 * (x - centroid[0]) + centroid[1]);
			auto z = static_cast<int>(k2 * (x - centroid[0]) + centroid[2]);

			if (x > 0 && x < originImage->size1() && y > 0 && y < originImage->size2() && z > 0 && z < originImage->size3())
			{
				(*centerAxis)(x, y, z) = 5;
			}
		}
	}

    return true;
}
