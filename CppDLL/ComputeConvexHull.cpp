#include "mist/mist.h"
#include "mist/vector.h"
#include "mist/filter/morphology.h"
#include "mist/operator/operator_array3.h"
#include <algorithm>
#include "mist/filter/thinning.h"
#include "./VesselLabeling/artery.h"
#include "./VesselLabeling/image.h"

extern "C"
{
	__declspec(dllexport) bool _stdcall ComputeConvexHull(const mist::array3<short> *originImage, int target, int seedLabel, mist::array3<short>* output);
}

bool ComputeIJK(size_t id, int IJK[3], size_t dim_x, size_t dim_y, size_t dim_z)
{
	if (id < 0)
		return false;

	IJK[0] = id % dim_x;
	IJK[1] = (id / dim_x) % dim_y;
	IJK[2] = id / (dim_x * dim_y);

	return true;
}

void TreeConstruct(const mist::array3<short>& image, tmatsu::artery::Tree& tree, tmatsu::Point seedPoint )
{
	tmatsu::artery::CTImage vessel(image);
	tmatsu::artery::ThicknessImage centerline;  

	vessel.thinning(centerline);
	tree.construct(centerline, seedPoint);
	vessel.clear();
	centerline.clear();
}

bool _stdcall ComputeConvexHull(const mist::array3<short> *originImage, int targetLabel, int seedLabel, mist::array3<short>* output)
{
	if (originImage == nullptr)
		return false;

	int seedIJK[3] = { 0 };
	size_t seedId(0);
	mist::array3<short> image(*originImage);
	for (size_t i = 0; i < image.size(); ++i)
	{
		if (image[i] == seedLabel)
			seedId = i;
		if (image[i] != targetLabel)
			image[i] = 0;
	}

	tmatsu::artery::Tree tree;
	ComputeIJK(seedId, seedIJK, originImage->size1(), originImage->size2(), originImage->size3());
	TreeConstruct(image, tree, tmatsu::Point(seedIJK[0], seedIJK[1], seedIJK[2]));
	for (auto iter = tree.begin(); iter != tree.end(); ++iter)
	{
		if (!iter.node()->eldest_child)
		{
			auto pt = iter->value.end_pt;
			(*output)(pt.x, pt.y, pt.z) = 10;
		}
	}

	return true;

	mist::euclidean::thinning26(image, *output);
	return true;

	mist::array3<short> image_prev(image);

	mist::erosion(image, 1);
	(*output) = image_prev - image;


	return true;
}