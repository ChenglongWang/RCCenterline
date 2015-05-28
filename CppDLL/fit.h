#pragma once
#include <vector>
#include "mist/mist.h"
#include "eigen.h"
#include <algorithm>

namespace ls{
	class Fit{
	private:
//		std::vector<double> _factor; ///<拟合后的方程系数
		int _centroid[3];
		double _direction[3];
		double ssr;                 ///<回归平方和
		double sse;                 ///<(剩余平方和)
		double rmse;                ///<RMSE均方根误差
		std::vector<double> fitedYs;
	public:
		Fit():ssr(0),sse(0),rmse(0)
		{
			_centroid[0] = _centroid[1] = _centroid[2] = 0;
			_direction[0] = _direction[1] = _direction[2] = 0;
		}
		~Fit(){}

		inline bool ComputeIJK(size_t id, int IJK[3], size_t dim_x, size_t dim_y, size_t dim_z)
		{
			if(id < 0) 
				return false;

			IJK[0] = id % dim_x;
			IJK[1] = (id / dim_x) % dim_y;
			IJK[2] = id / (dim_x * dim_y);
			
			return true;
		}

		bool ComputeIJK(const std::vector<size_t>& points, std::vector<std::vector<int>>& IJKContainer, int dim_x, int dim_y, int dim_z)
		{
			if (IJKContainer.size() != 3)
				return false; 

			for_each(IJKContainer.begin(), IJKContainer.end(), [](std::vector<int>& v){ v.clear(); });

			int ijk[3] = {0};
			for (size_t i = 0; i < points.size(); ++i)
			{
				ComputeIJK(points[i], ijk, dim_x, dim_y, dim_z);
				IJKContainer[0].push_back(ijk[0]);
				IJKContainer[1].push_back(ijk[1]);
				IJKContainer[2].push_back(ijk[2]);
			}

			return true;
		}

		bool LinearFit(const mist::array3<short>* originImage, const std::vector<size_t>& points, bool isSaveFitYs=false)
		{
			int ijk[3];
			int centroid[3];
			double direction[3];

			std::vector<int> container_x, container_y, container_z;
			std::vector<std::vector<int>> IJKContainer(3);
			IJKContainer[0] = container_x;
			IJKContainer[1] = container_y;
			IJKContainer[2] = container_z;

			if (!ComputeIJK(points, IJKContainer, originImage->size1(), originImage->size2(), originImage->size3()))
				return false;

			if (!ComputeCentroid(IJKContainer, centroid))
				return false;

			double covariance[6] = { 0 };
			for(size_t i=0; i < points.size(); ++i)
			{
				int offset_x = IJKContainer[0][i] - centroid[0];
				int offset_y = IJKContainer[1][i] - centroid[1];
				int offset_z = IJKContainer[2][i] - centroid[2];

				covariance[0] += offset_x * offset_x;
				covariance[1] += offset_x * offset_y;
				covariance[2] += offset_y * offset_y;
				covariance[3] += offset_x * offset_z;
				covariance[4] += offset_y * offset_z;
				covariance[5] += offset_z * offset_z;
			}

			auto quality = Fitting(covariance, direction);
			_centroid[0] = centroid[0];
			_centroid[1] = centroid[1];
			_centroid[2] = centroid[2];
			_direction[0] = direction[0];
			_direction[1] = direction[1];
			_direction[2] = direction[2];

//			calcError(x,y,length,this->ssr,this->sse,this->rmse,isSaveFitYs);
			return true;
		}
/*		///
		/// \brief 多项式拟合，拟合y=a0+a1*x+a2*x^2+……+apoly_n*x^poly_n
		/// \param x 观察值的x
		/// \param y 观察值的y
		/// \param poly_n 期望拟合的阶数，若poly_n=2，则y=a0+a1*x+a2*x^2
		/// \param isSaveFitYs 拟合后的数据是否保存，默认是
		/// 
		template<typename T>
		void polyfit(const std::vector<typename T>& x
			,const std::vector<typename T>& y
			,int poly_n
			,bool isSaveFitYs=true)
		{
			polyfit(&x[0],&y[0],getSeriesLength(x,y),poly_n,isSaveFitYs);
		}
		template<typename T>
		void polyfit(const T* x,const T* y,size_t length,int poly_n,bool isSaveFitYs=true)
		{
			factor.resize(poly_n+1,0);
			int i,j;
			//double *tempx,*tempy,*sumxx,*sumxy,*ata;
			std::vector<double> tempx(length,1.0);

			std::vector<double> tempy(y,y+length);

			std::vector<double> sumxx(poly_n*2+1);
			std::vector<double> ata((poly_n+1)*(poly_n+1));
			std::vector<double> sumxy(poly_n+1);
			for (i=0;i<2*poly_n+1;i++){
				for (sumxx[i]=0,j=0;j<length;j++)
				{
					sumxx[i]+=tempx[j];
					tempx[j]*=x[j];
				}
			}
			for (i=0;i<poly_n+1;i++){
				for (sumxy[i]=0,j=0;j<length;j++)
				{
					sumxy[i]+=tempy[j];
					tempy[j]*=x[j];
				}
			}
			for (i=0;i<poly_n+1;i++)
				for (j=0;j<poly_n+1;j++)
					ata[i*(poly_n+1)+j]=sumxx[i+j];
			gauss_solve(poly_n+1,ata,factor,sumxy);
			//计算拟合后的数据并计算误差
			fitedYs.reserve(length);
			calcError(&x[0],&y[0],length,this->ssr,this->sse,this->rmse,isSaveFitYs);

		}
		*/

		void GetCentroid(int center[3])
		{
			center[0] = _centroid[0];
			center[1] = _centroid[1];
			center[2] = _centroid[2];
		}

		void GetDirection(double direction[3])
		{
			direction[0] = _direction[0];
			direction[1] = _direction[1];
			direction[2] = _direction[2];
		}

/*		/// 
		/// \brief 获取拟合方程对应的y值，前提是拟合时设置isSaveFitYs为true
		///
		void getFitedYs(std::vector<double>& fitedYs){fitedYs = this->fitedYs;}

		/// 
		/// \brief 根据x获取拟合方程的y值
		/// \return 返回x对应的y值
		///
		template<typename T>
		double getY(const T x) const
		{
			double ans(0);
			for (size_t i=0;i<_factor.size();++i)
			{
				ans += _factor[i]*pow((double)x,(int)i);
			}
			return ans;
		}
		/// 
		/// \brief 获取斜率
		/// \return 斜率值
		///
		double getSlope(){return _factor[1];}
		/// 
		/// \brief 获取截距
		/// \return 截距值
		///
		double getIntercept(){return _factor[0];}
		/// 
		/// \brief 剩余平方和
		/// \return 剩余平方和
		///
		double getSSE(){return sse;}
		/// 
		/// \brief 回归平方和
		/// \return 回归平方和
		///
		double getSSR(){return ssr;}
		/// 
		/// \brief 均方根误差
		/// \return 均方根误差
		///
		double getRMSE(){return rmse;}
		/// 
		/// \brief 确定系数，系数是0~1之间的数，是数理上判定拟合优度的一个量
		/// \return 确定系数
		///
		double getR_square(){return 1-(sse/(ssr+sse));}
		/// 
		/// \brief 获取两个vector的安全size
		/// \return 最小的一个长度
		///
		template<typename T>
		size_t getSeriesLength(const std::vector<typename T>& x
			,const std::vector<typename T>& y)
		{
			return (x.size() > y.size() ? y.size() : x.size());
		}
		/// 
		/// \brief 计算均值
		/// \return 均值
		///
		template <typename T>
		static T Mean(const std::vector<T>& v)
		{
			return Mean(&v[0],v.size());
		}
		template <typename T>
		static T Mean(const T* v,size_t length)
		{
			T total(0);
			for (size_t i=0;i<length;++i)
			{
				total += v[i];
			}
			return (total / length);
		}
		/// 
		/// \brief 获取拟合方程系数的个数
		/// \return 拟合方程系数的个数
		///
		size_t getFactorSize(){return _factor.size();}
		/// 
		/// \brief 根据阶次获取拟合方程的系数，
		/// 如getFactor(2),就是获取y=a0+a1*x+a2*x^2+……+apoly_n*x^poly_n中a2的值
		/// \return 拟合方程的系数
		///
		double getFactor(size_t i){return _factor.at(i);}
		*/
	private:
		bool ComputeCentroid(const std::vector<std::vector<int>>& IJKContainer, int centerPoint[3])
		{
			if (IJKContainer.size() != 3 ||
				IJKContainer[0].size() != IJKContainer[1].size() ||
				IJKContainer[1].size() != IJKContainer[2].size() ||
				IJKContainer[2].size() != IJKContainer[0].size())
				return false;

			auto container_x = IJKContainer[0];
			auto container_y = IJKContainer[1];
			auto container_z = IJKContainer[2];

			int sum_x = 0, sum_y = 0, sum_z = 0;
			for (size_t i = 0; i < container_x.size(); ++i)
			{
				sum_x += container_x[i];
				sum_y += container_y[i];
				sum_z += container_z[i];
			}

			centerPoint[0] = static_cast<int>(sum_x / container_x.size());
			centerPoint[1] = static_cast<int>(sum_y / container_x.size());
			centerPoint[2] = static_cast<int>(sum_z / container_x.size());

			return true;
		}

		double Fitting(const double covariance[6], double direction[3])
		{
			double eigenValues[3];
			double eigenVectors[9];

			eigen_symmetric<double>(covariance, 3, eigenVectors, eigenValues);

			if (eigenValues[0] == eigenValues[1] &&
				eigenValues[0] == eigenValues[2])
			{
				direction[0] = 1;
				direction[1] = direction[2] = 0;
				return 0;
			}
			else
			{
				direction[0] = eigenVectors[0];
				direction[1] = eigenVectors[1];
				direction[2] = eigenVectors[2];
				return static_cast<double>(1 - eigenValues[1] / eigenValues[0]);
			}
		}

/*		template<typename T>
		void calcError(const T* x
			,const T* y
			,size_t length
			,double& r_ssr
			,double& r_sse
			,double& r_rmse
			,bool isSaveFitYs=true
			)
		{
			T mean_y = Mean<T>(y,length);
			T yi(0);
			fitedYs.reserve(length);
			for (int i=0; i<length; ++i)
			{
				yi = getY(x[i]);
				r_ssr += ((yi-mean_y)*(yi-mean_y));//计算回归平方和
				r_sse += ((yi-y[i])*(yi-y[i]));//残差平方和
				if (isSaveFitYs)
				{
					fitedYs.push_back(double(yi));
				}
			}
			r_rmse = sqrt(r_sse/(double(length)));
		}
		template<typename T>
		void gauss_solve(int n
			,std::vector<typename T>& A
			,std::vector<typename T>& x
			,std::vector<typename T>& b)
		{
			gauss_solve(n,&A[0],&x[0],&b[0]);	
		}
		template<typename T>
		void gauss_solve(int n
			,T* A
			,T* x
			,T* b)
		{
			int i,j,k,r;
			double max;
			for (k=0;k<n-1;k++)
			{
				max=fabs(A[k*n+k]); //find maximum
				r=k;
				for (i=k+1;i<n-1;i++){
					if (max<fabs(A[i*n+i]))
					{
						max=fabs(A[i*n+i]);
						r=i;
					}
				}
				if (r!=k){
					for (i=0;i<n;i++)
					{
						max=A[k*n+i];
						A[k*n+i]=A[r*n+i];
						A[r*n+i]=max;
					}
				}
				max=b[k];
				b[k]=b[r];
				b[r]=max;
				for (i=k+1;i<n;i++)
				{
					for (j=k+1;j<n;j++)
						A[i*n+j]-=A[i*n+k]*A[k*n+j]/A[k*n+k];
					b[i]-=A[i*n+k]*b[k]/A[k*n+k];
				}
			} 

			for (i=n-1;i>=0;x[i]/=A[i*n+i],i--)
				for (j=i+1,x[i]=b[i];j<n;j++)
					x[i]-=A[i*n+j]*x[j];
		}*/
	};
}