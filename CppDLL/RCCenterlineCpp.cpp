#include "mist/mist.h"
#include "mist/vector.h"
#include "mist/filter/thinning.h"
#include <algorithm>
#include "fit.h"


extern "C"
{
	__declspec(dllexport) bool _stdcall Run(const mist::array3<short> *originImage, mist::array3<short>* centerline, int target);
}

bool _stdcall Run(const mist::array3<short> *originImage, mist::array3<short>* centerlineImage, int target)
{
	if (originImage == nullptr)
		return false;

	mist::array3<short> targetImage(*originImage);

	for_each(targetImage.begin(), targetImage.end(), [target](short& v){if (v != target) v = 0; });

	mist::euclidean::thinning26(targetImage, *centerlineImage);

	std::vector<size_t> points_id;
	for (size_t i = 0; i < centerlineImage->size(); ++i)
	{
		if ((*centerlineImage)[i] != 0)
			points_id.push_back(i);
	}

	std::vector<double> factor;
	ls::Fit linearFitter;
	linearFitter.linearFit(originImage, points_id);
	linearFitter.getFactor(factor);

	double extent[3];
	extent[0] = originImage->size1() * originImage->reso1();
	extent[1] = originImage->size2() * originImage->reso2();
	extent[2] = originImage->size3() * originImage->reso3();



    return( true );
}
