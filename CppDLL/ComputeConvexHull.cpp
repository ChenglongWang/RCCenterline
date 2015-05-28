#include "mist/mist.h"
#include "mist/vector.h"
#include "mist/filter/morphology.h"
#include "mist/operator/operator_array3.h"
#include <algorithm>

extern "C"
{
	__declspec(dllexport) bool _stdcall ComputeConvexHull(const mist::array3<short> *originImage, int target, mist::array3<short>* output);
}

bool _stdcall ComputeConvexHull(const mist::array3<short> *originImage, int target, mist::array3<short>* output)
{
	if (originImage == nullptr)
		return false;

	mist::array3<short> image(*originImage);
	for_each(image.begin(), image.end(), [target](short& v){if (v != target) v = 0; });

	mist::erosion(image, 1);
	(*output) = (*originImage) - image;
	return true;
}