/**
* @file artery.h
* @brief ®¬¼Ît¯Ìwb_t@C
* @version 3.0
* @author ¼Ã®åw îñÈw¤È fBAÈwêU X¤º   351203192   ¼ú± NN
* @date 2013/10/18
*/

#ifndef _TMATSU_ARTERY_H_
#define _TMATSU_ARTERY_H_

#include <vector>
#include <mist/machine_learning.h>
#include "vessel.h"
#include <algorithm>

namespace tmatsu
{
	namespace artery
	{
		/// @brief ®¬¼ð\í·ñ^
		enum Name 
		{
			NAME_OTHER, ///< @brief »Ì¼
			NAME_AO, ///< @brief  å®¬
			NAME_CA, ///< @brief  o®¬
			NAME_CHA, ///< @brief Ì®¬
			NAME_PHA, ///< @brief ÅLÌ®¬
			NAME_LHA, ///< @brief ¶Ì®¬
			NAME_RHA, ///< @brief EÌ®¬
			NAME_GDA, ///< @brief Ý\ñw°®¬
			NAME_LGA, ///< @brief ¶Ý®¬
			NAME_RGA, ///< @brief EÝ®¬
			NAME_LGEA, ///< @brief ¶ÝåÔ®¬
			NAME_RGEA, ///< @brief EÝåÔ®¬
			NAME_SA, ///< @brief äB®¬
			NAME_SMA, ///< @brief ã°Ô®¬
#ifdef _TARGET_HYPOGASTRIC
			NAME_IMA, ///< @brief º°Ô®¬
			NAME_LRA, ///< @brief ¶t®¬
			NAME_RRA, ///< @brief Et®¬
			NAME_LCIA, ///< @brief ¶°®¬
			NAME_RCIA, ///< @brief E°®¬
			NAME_LIIA, ///< @brief ¶à°®¬
			NAME_RIIA, ///< @brief Eà°®¬
			NAME_LEIA, ///< @brief ¶O°®¬
			NAME_REIA, ///< @brief EO°®¬
#endif //_TARGET_HYPOGASTRIC
			NAME_END, ///< @brief ®¬¼ÌöÌ
			NAME_BEGIN = NAME_OTHER + 1, ///< @brief ®¬¼Ìæª
			NAME_NUM = NAME_END - 1 ///< @brief ®¬¼Ì
		};
	
		using vessel::CTImage;
		using vessel::MarkImage;
		using vessel::ThicknessImage;
		using vessel::LabelImage;
		using vessel::FeatureVector;
		using vessel::Likelihood;

		/// @brief ÞxÖðµ¤NX
		class LikelihoodFunction
		{
			vessel::Classifier classifiers_[ NAME_NUM ]; ///< @brief ¯Êí
		public:
			template < class Container >
			void learn( const Container &samples );
			bool read( const char *path_name );
			bool write( const char *path_name )const;
			Likelihood< Name > operator( )( Name parent, const FeatureVector &feature );
		private:
			static std::string file_name( const std::string &path_name, Name artery_name );
		};

		/// @brief ®¬Ø\¢ðµ¤NX
		class Tree : public vessel::Tree< Name >
		{
			bool exist_cia; ///< @brief CIAª¶Ý·é©Ç¤©
		protected:
			virtual Point root_point( const ThicknessImage &centerline ) const;
			virtual Point root_point(const ThicknessImage &centerline, Point seedPoint) const;
			virtual const_iterator reference_branch( )const;
			virtual Name reject_name( )const;
			virtual Likelihood< Name > default_likelihood( )const;
			virtual size_t name_number( )const;
			virtual std::string to_string( const Name &name )const;
			virtual size_t to_index( const Name &name )const;
			virtual Name to_name( const std::string &str )const;
			virtual void construct_postprocess( );
			virtual void labeling_preprocess( );
			virtual void labeling_postprocess( );
			virtual unsigned char to_label( Name name )const;
		private:
			std::pair< iterator, iterator > find_eia_end( );
		};
		
		std::string to_string( Name name );
		size_t to_index( Name name );
		Name to_name( const std::string &str );
		Name to_name( size_t idx );

		/// @brief ÅàãÉ é[_ðæ¾·é
		/// @param[in] centerline cüæ
		/// @return ÅàãÉ é[_ÌÀW
		Point Tree::root_point( const ThicknessImage &centerline )const
		{
			for ( size_t k = 0; k < centerline.depth( ); k++ )
			{
				for ( size_t j = 0; j < centerline.height( ); j++ )
				{
					for ( size_t i = 0; i < centerline.width( ); i++ )
					{
						try
						{
							if ( centerline( i, j, k ) )
							{
								size_t cnt = 0; // ×ÚæfÌ
							
								for ( size_t l = 0; l < TOPOLOGY; l++ )
								{
									try
									{
										if ( centerline( Point( i, j, k ) + TOPOLOGICAL( neighborhood )[ l ] ) )
										{
											cnt++;
										}
									}

									catch ( ThicknessImage::InvalidPoint )
									{
									}
								}

								if ( cnt == 1 )
								{
									return Point( i, j, k );
								}
							}
						}

						catch ( ThicknessImage::InvalidPoint )
						{
						}
					}
				}
			}
	
			return Point( SIZE_MAX, SIZE_MAX, SIZE_MAX );
		}

		/// @brief the closest point of the seed point is token as root.
		Point Tree::root_point( const ThicknessImage &centerline, Point seedPoint ) const
		{
			std::vector<Point> candidateRoots;
			for (size_t k = 0; k < centerline.depth(); k++)
			{
				for (size_t j = 0; j < centerline.height(); j++)
				{
					for (size_t i = 0; i < centerline.width(); i++)
					{
						try
						{
							if (centerline(i, j, k))
							{
								size_t cnt = 0;

								for (size_t l = 0; l < TOPOLOGY; l++)
								{
									if (centerline(Point(i, j, k) + TOPOLOGICAL(neighborhood)[l]))
									{
										cnt++;
									}
								}

								if (cnt == 1)
								{
									candidateRoots.push_back(Point(i, j, k));
								}
							}
						}
						catch (ThicknessImage::InvalidPoint)
						{
						}
					}
				}
			}

			if (candidateRoots.empty())
				return Point(-1, -1, -1);
			
			std::vector<double> distance(candidateRoots.size());
			for (int i = 0; i < candidateRoots.size(); ++i)
			{
				auto offset = seedPoint - candidateRoots[i];
				auto dist = std::sqrt(offset.x*offset.x + offset.y*offset.y + offset.z*offset.z);
				distance[i] = dist;
			}

			auto minmax= minmax_element(distance.begin(), distance.end());
			auto pos = std::distance(distance.begin(), minmax.first);

			return candidateRoots[abs(pos)];
		}
		
		/// @brief î}ðæ¾·é
		/// @return î}ÌèQÆ
		inline Tree::const_iterator Tree::reference_branch( )const
		{	
			return preorder_begin( );
		}

		/// @brief WFNg¼ðæ¾·é
		/// @return WFNg¼
		inline Name Tree::reject_name( )const
		{
			return NAME_OTHER;
		} 

		/// @brief ªÌe}ÌÞxÆµÄµíêéÞxÌKèlðæ¾·é
		/// @return ÞxÌKèl
		inline Likelihood< Name > Tree::default_likelihood( )const
		{
			Likelihood< Name > likelihood; //Þx

			likelihood.insert( likelihood.end( ), Likelihood< Name >::value_type( NAME_AO, 1 ) );
			
			return likelihood;
		}
		
		/// @brief WFNg¼ðÜÞ¼OÌðæ¾·é
		/// @return ¼OÌ
		inline size_t Tree::name_number( )const
		{
			return NAME_NUM + 1;
		}

		/// @brief ¼Oð¶ñÉÏ··é
		/// @param[in] name Ï··é¼O
		/// @return ¼Oð\·¶ñ
		inline std::string Tree::to_string( const Name &name )const
		{
			return artery::to_string( name );
		}

		/// @brief ¼OðCfbNXÉÏ··é
		/// @param[in] name Ï··é¼O
		/// @return ¼OÉÎ·éCfbNX
		inline size_t Tree::to_index( const Name &name )const
		{
			return artery::to_index( name );
		}
	
		/// @brief ¶ñð¼OÉÏ··é
		/// @param[in] str Ï··é¶ñ
		/// @return ¶ñÌ\·¼O
		inline Name Tree::to_name( const std::string &str )const
		{
			return artery::to_name( str );
		}
	
		/// @brief ¼OðxlÉÏ··é
		/// @param[in] name Ï··é¼O
		/// @return ¼OÉÎ·éxl
		inline unsigned char Tree::to_label( Name name )const
		{
			switch ( name )
			{
			case NAME_AO:
				return vessel::LABEL_AO;
			case NAME_CA:
				return vessel::LABEL_C;
			case NAME_CHA:
				return vessel::LABEL_CH;
			case NAME_PHA:
				return vessel::LABEL_PH;
			case NAME_LHA:
				return vessel::LABEL_LH;
			case NAME_RHA:
				return vessel::LABEL_RH;
			case NAME_GDA:
				return vessel::LABEL_GD;
			case NAME_LGA:
				return vessel::LABEL_LG;
			case NAME_RGA:
				return vessel::LABEL_RG;
			case NAME_LGEA:
				return vessel::LABEL_LGE;
			case NAME_RGEA:
				return vessel::LABEL_RGE;
			case NAME_SA:
				return vessel::LABEL_S;
			case NAME_SMA:
				return vessel::LABEL_SM;
#ifdef _TARGET_HYPOGASTRIC
			case NAME_IMA:
				return vessel::LABEL_IM;
			case NAME_LRA:
				return vessel::LABEL_LR;
			case NAME_RRA:
				return vessel::LABEL_RR;
			case NAME_LCIA:
				return vessel::LABEL_LCI;
			case NAME_RCIA:
				return vessel::LABEL_RCI;
			case NAME_LEIA:
				return vessel::LABEL_LEI;
			case NAME_REIA:
				return vessel::LABEL_REI;
			case NAME_LIIA:
				return vessel::LABEL_LII;
			case NAME_RIIA:
				return vessel::LABEL_RII;
#endif //_TARGET_HYPOGASTRIC
			default:
				return vessel::LABEL_OTHER;
			}
		}
			
		/// @brief ·³ªZ¢[Ì}ðíµCZí}ÌÈ¢}ðe}Æ·é
		inline void Tree::construct_postprocess( )
		{	
			//double avg = 0, var = 0; // vÊ
			//double th = 0; // èl
			//size_t cnt = 0; // tÌ

			//// èlðZo·é
			//for ( iterator iter = begin( ); iter != end( ); iter++ )
			//{
			//	if ( is_leaf( iter ) )
			//	{
			//		double len = length( iter ); // ·³

			//		avg += len;
			//		var += std::pow( len, 2 );
			//		cnt++;
			//	}
			//}

			//avg /= cnt;
			//var = var / cnt - std::pow( avg, 2 );
			//th = avg;

			// } èðs¤
			for ( iterator iter = begin( ); iter != end( ); )
			{
				if ( is_leaf( iter ) && ( iter->value.path.size( ) <= PRUN_THRESHOLD ) )
				{
					iter = erase( iter );
				}
				else
				{
					iter++;
				}
			}

			// }ð·é
			for ( iterator iter = begin( ); iter != end( ); )
			{
				if ( !has_sibling( iter ) && !is_root( iter ) )
				{
					iterator parent_branch = parent( iter ); // e}
					Shift shift = iter->value.start_pt - parent_branch->value.end_pt; // e}ÌI_©çn_ÖÌxNg

					// I_ðXV·é
					parent_branch->value.end_pt = iter->value.end_pt;

					// oHðXV·é
					for ( size_t i = 0; i < TOPOLOGY; i++ )
					{
						if ( TOPOLOGICAL( neighborhood )[ i ] == shift )
						{
							parent_branch->value.path.insert( iter->value.path.end( ), i );
							break;
						}
					}

					parent_branch->value.path.splice( parent_branch->value.path.end( ), iter->value.path );

					// q}ðí·é
					iter = erase( iter );
				}
				else
				{
					iter++;
				}
			}
		}
		
		/// @brief ¶°®¬CE°®¬¨æÑ å®¬ð[x[XÅÎt¯é
		inline void Tree::labeling_preprocess( )
		{
			std::pair< iterator, iterator > eia_end_branches = find_eia_end( ); // O°®¬Ì[}
			std::pair< iterator, iterator > eia_start_branches; // °®¬ÌJn}

			// E°®¬ðÎt¯é
			for ( iterator iter = eia_end_branches.first; iter != end( ); iter = parent( iter ) )
			{
				iter->name = NAME_RCIA;
			}

			// ¶°®¬¨æÑ å®¬ðÎt¯é
			for ( iterator iter = eia_end_branches.second; iter != end( ); iter = parent( iter ) )
			{
				if ( iter->name == NAME_RCIA )
				{
					iter->name = NAME_AO;
				}
				else
				{
					iter->name = NAME_LCIA;
				}
			}

			// °®¬ÌJn}ðTõ·é
			eia_start_branches.first = std::find( begin( ), end( ), NAME_RCIA );
			eia_start_branches.second = std::find( begin( ), end( ), NAME_LCIA );

			if ( eia_start_branches.first->value.thk < eia_start_branches.second->value.thk )
			{
				std::swap( eia_start_branches.first, eia_start_branches.second );
				std::swap( eia_end_branches.first, eia_end_branches.second );
			}
			
			// °®¬ª¶ÝµÈ¢ÈçÎ¼Oðt¯È¨·
			if ( eia_start_branches.second->value.thk <= 0 || eia_start_branches.first->value.thk / eia_start_branches.second->value.thk > THICKNESS_THRESHOLD )
			{
				exist_cia = false;

				// ¾¢Çð å®¬ÉhèÖ¦é
				for ( iterator iter = eia_end_branches.first; iter != end( ) && iter->name != NAME_AO; iter = parent( iter ) )
				{
					iter->name = NAME_AO;
				}

				// ×¢Çðí·é
				for ( iterator iter = eia_end_branches.second; iter != end( ) && iter->name != NAME_AO; iter = parent( iter ) )
				{
					iter->name = NAME_OTHER;
				}
			}
			else
			{
				exist_cia = true;
			}

			//exist_cia = true;

#if 0
			for ( const_iterator iter = ++preorder_begin( ); iter != preorder_end( ); iter++ )
			{
				if ( iter->name != NAME_AO && parent( iter )->name == NAME_AO )
				{
					std::cout << bifurcation_num( iter ) + 1 << std::endl;
				}
			}

			std::cin.get( );
#endif
		}
		
		/// @brief ¶O°®¬¨æÑEO°®¬ð[x[XÅÎt¯C]ªÈÅLÌ®¬ª êÎ»êð·é
		inline void Tree::labeling_postprocess( )
		{
			iterator leia_end = end( ), reia_end = end( ); // O°®¬Ì[}
			iterator leia_start = end( ), reia_start = end( ); // O°®¬ÌJn}
			iterator pha_start = end( ), pha_end = end( ), lha_end = end( ), rha_end = end( ); // Ì®¬

			if ( exist_cia )
			{
				// ¼Ì°®¬Ì[}ðTõ·é
				for ( iterator iter = postorder_begin( ); iter != postorder_end( ); iter++ )
				{
					if ( iter->name == NAME_LCIA && is_leaf( iter ) )
					{
						leia_end = iter;
					}
					else if ( iter->name == NAME_RCIA && is_leaf( iter ) )
					{
						reia_end = iter;
					}
				}

				// à°®¬ÌJn}ðTõ·é
				for ( iterator iter = leia_end; iter != end( ) && iter->name != NAME_AO && leia_start == end( ); iter = parent( iter ) )
				{
					for ( iterator sibling_iter = child_begin( parent( iter ) ); sibling_iter != child_end( parent( iter ) ); sibling_iter++ )
					{
						if ( sibling_iter->name == NAME_LIIA )
						{
							leia_start = iter;
							break;
						}
					}
				}
				
				for ( iterator iter = reia_end; iter != end( ) && iter->name != NAME_AO && reia_start == end( ); iter = parent( iter ) )
				{
					for ( iterator sibling_iter = child_begin( parent( iter ) ); sibling_iter != child_end( parent( iter ) ); sibling_iter++ )
					{
						if ( sibling_iter->name == NAME_RIIA )
						{
							reia_start = iter;
							break;
						}
					}
				}

				// ¼Ì°®¬Ì¼Oðt¯¼·
				if ( leia_start != end( ) )
				{
					for ( iterator iter = leia_end; iter != parent( leia_start ); iter = parent( iter ) )
					{
						iter->name = NAME_LEIA;
					}
				}

				if ( reia_start != end( ) )
				{
					for ( iterator iter = reia_end; iter != parent( reia_start ); iter = parent( iter ) )
					{
						iter->name = NAME_REIA;
					}
				}
			}
			else
			{
				// °®¬ðí·é
				for ( iterator iter = begin( ); iter != end( ); iter++ )
				{
					switch ( iter->name )
					{
					case NAME_LCIA:
					case NAME_RCIA:
					case NAME_LIIA:
					case NAME_RIIA:
						iter->name = NAME_OTHER;
					}
				}
			}

			// ÅLÌ®¬ðTõ·é
			for ( iterator iter = preorder_begin( ); iter != preorder_end( ); iter++ )
			{
				if ( iter->name == NAME_PHA )
				{
					pha_start = iter;
					break;
				}
			}

			// Ì®¬ðTõ·é
			for ( iterator iter = subtree( pha_start ).postorder_begin( ); iter != subtree( pha_start ).postorder_end( ); iter++ )
			{
				if ( iter->name == NAME_PHA )
				{
					pha_end = pha_end == end( ) ? iter : pha_end;
				}
				else if ( iter->name == NAME_LHA )
				{
					lha_end = lha_end == end( ) ? iter : lha_end;
				} 
				else if ( iter->name == NAME_RHA )
				{
					rha_end = rha_end == end( ) ? iter : rha_end;
				}
			}

			// ÅLÌ®¬ð·é
			for ( iterator iter = pha_end; iter != parent( pha_start ); iter = parent( iter ) )
			{
				if ( lha_end == end( ) && rha_end == end( ) )
				{
					iter->name = NAME_OTHER;
				}
				else if ( lha_end != end( ) && rha_end == end( ) )
				{
					iter->name = NAME_LHA;
				}
				else if ( lha_end == end( ) && rha_end != end( ) )
				{
					iter->name = NAME_RHA;
				}
			}
		}
		
		/// @brief O°®¬Ì[}Ìgðæ¾·é
		/// @return O°®¬Ì[}ÌgDfirstªEO°®¬Csecondª¶O°®¬
		inline std::pair< Tree::iterator, Tree::iterator > Tree::find_eia_end( )
		{
			std::pair< iterator, iterator > eia_end_branches = std::make_pair( end( ), end( ) );

			for ( iterator iter = begin( ); iter != end( ); iter++ )
			{
				if ( is_leaf( iter ) )
				{
					//if ( iter->value.end_pt.x <= get_size( ).x / 2 && ( eia_end_branches.first == end( ) || iter->value.end_pt.z > eia_end_branches.first->value.end_pt.z || ( iter->value.end_pt.z == eia_end_branches.first->value.end_pt.z && iter->value.thk > eia_end_branches.first->value.thk ) ) )
					//{
					//	eia_end_branches.first = iter;
					//}
					//else if ( iter->value.end_pt.x >= get_size( ).x / 2 && ( eia_end_branches.second == end( ) || iter->value.end_pt.z > eia_end_branches.second->value.end_pt.z || ( iter->value.end_pt.z == eia_end_branches.second->value.end_pt.z && iter->value.thk > eia_end_branches.second->value.thk ) ) )
					//{
					//	eia_end_branches.second = iter;
					//}
					
					if ( iter->value.end_pt.x <= get_size( ).x / 2 && iter->value.end_pt.z >= BOTTOM_THRESHOLD( get_size( ).z ) && ( eia_end_branches.first == end( ) || iter->value.thk > eia_end_branches.first->value.thk ) )
					{
						eia_end_branches.first = iter;
					}
					else if ( iter->value.end_pt.x >= get_size( ).x / 2 && iter->value.end_pt.z >= BOTTOM_THRESHOLD( get_size( ).z ) && ( eia_end_branches.second == end( ) || iter->value.thk > eia_end_branches.second->value.thk ) )
					{
						eia_end_branches.second = iter;
					}		
				}
			}

			return eia_end_branches;
		}

		/// @brief wKðs¤
		/// @param[in] samples ³tf[^DSTLReiÆÝÈ¹È¯êÎÈçÈ¢
		template < class Container >
		inline void LikelihoodFunction::learn( const Container &samples )
		{
			for ( Name n = NAME_BEGIN; n < NAME_END; n = static_cast< Name >( n + 1 ) )
			{
				std::vector< mist::machine_learning::feature > features; // ³tf[^
				size_t cnt = 0; // ³tf[^Ì

				// ³tf[^Ìðßé
				for ( Container::const_iterator iter = samples.begin( ); iter != samples.end( ); iter++ )
				{
					Name parent_name = to_name( iter->parent_category ); // e}Ì¼O

					// f[^ð¦é
					if ( parent_name == n && parent_name != NAME_LEIA && parent_name != NAME_REIA )
					{
						cnt++;
					}
				}

				// ³tf[^ðì¬·é
				features.reserve( cnt );
					
				for ( Container::const_iterator iter = samples.begin( ); iter != samples.end( ); iter++ )
				{
					Container::value_type sample = *iter; // ³tf[^

					// O°®¬ð»Ì¼Åu«·¦é
					switch ( to_name( sample.parent_category ) )
					{
					case NAME_LEIA:
					case NAME_REIA:
						sample.parent_category = to_string( NAME_OTHER );
					}

					// ³tf[^ð}ü·é
					if ( to_name( sample.parent_category ) == n )
					{
						switch ( to_name( sample.category ) )
						{
						case NAME_LEIA:
						case NAME_REIA:
							sample.category = to_string( NAME_OTHER );
						}

						features.push_back( sample );
					}
				}

				// wKðs¤
				classifiers_[ to_index( n ) ].learn( features, LEARN_ITERATION );
			}
		}
		
		/// @brief t@CQðÇÝÞ
		/// @param[in] path_name ÇÝÞt@CQÌ épX¼
		/// @retval true ÇÝÝÉ¬÷µ½
		/// @retval false ÇÝÝÉ¸sµ½
		inline bool LikelihoodFunction::read( const char *path_name )
		{
			for ( Name n = NAME_BEGIN; n < NAME_END; n = static_cast< Name >( n + 1 ) )
			{
				if ( !classifiers_[ to_index( n ) ].load( file_name( path_name, n ) ) )
				{
					return false;
				}
			}

			return true;
		}
	
		/// @brief t@CQÖ«Þ
		/// @param[in] path_name «Þt@CQÌ épX¼
		/// @retval true «ÝÉ¬÷µ½
		/// @retval false «ÝÉ¸sµ½
		inline bool LikelihoodFunction::write( const char *path_name )const
		{
			for ( Name n = NAME_BEGIN; n < NAME_END; n = static_cast< Name >( n + 1 ) )
			{
				if ( !classifiers_[ to_index( n ) ].save( file_name( path_name, n ) ) )
				{
					return false;
				}
			}

			return true;
		}
	
		/// @brief ÞxÌgðæ¾·é
		/// @param[in] parent e}Ét¯çêÄ¢éÆ¼è·éÇ¼
		/// @param[in] feature ¢mf[^
		/// @return ÞxÌg
		inline Likelihood< Name > LikelihoodFunction::operator( )( Name parent, const FeatureVector &feature )
		{
			std::vector< mist::machine_learning::pair< double, std::string > > ranks; // N
			Likelihood< Name > likelihoods; // Þx

			switch ( parent )
			{
			case NAME_AO:
			case NAME_CA:
			case NAME_CHA:
			case NAME_PHA:
			case NAME_LHA:
			case NAME_RHA:
			case NAME_GDA:
			case NAME_LGA:
			case NAME_RGA:
			case NAME_LGEA:
			case NAME_RGEA:
			case NAME_SA:
			case NAME_SMA:
#ifdef _TARGET_HYPOGASTRIC
			case NAME_IMA:
			case NAME_LRA:
			case NAME_RRA:
			case NAME_LCIA:
			case NAME_RCIA:
			case NAME_LIIA:
			case NAME_RIIA:
			case NAME_LEIA:
			case NAME_REIA:
#endif //_TARGET_HYPOGASTRIC
				// NðvZ·é
				classifiers_[ to_index( parent ) ].compute_category_ranks( feature, ranks );

				// ÞxÉÏ··é
				likelihoods.clear( );

				for ( std::vector< mist::machine_learning::pair< double, std::string > >::const_iterator iter = ranks.begin( ); iter != ranks.end( ); iter++ )
				{
					likelihoods.insert( likelihoods.end( ), Likelihood< Name >::value_type( to_name( iter->value ), iter->key ) );
				}

				break;
			}

			return likelihoods;
		}
		
		/// @brief ¯Êít@C¼ðæ¾·é
		/// @param[in] path_namr pX¼
		/// @param[in] vessel_name e}Ét¯çêÄ¢éÆ¼è·éÇ¼
		/// @param t@C¼
		inline std::string LikelihoodFunction::file_name( const std::string &path_name, Name vessel_name )
		{
			return path_name + "\\classifier" + to_string( vessel_name ) + ".txt";
		}
		
		/// @brief ¼Oð¶ñÉÏ··é
		/// @param[in] name Ï··é¼O
		/// @return ¼Oð\·¶ñ
		std::string to_string( Name name )
		{
			switch ( name )
			{
			case NAME_AO:
				return "Ao";
			case NAME_CA:
				return "CA";
			case NAME_CHA:
				return "CHA";
			case NAME_PHA:
				return "PHA";
			case NAME_LHA:
				return "LHA";
			case NAME_RHA:
				return "RHA";
			case NAME_GDA:
				return "GDA";
			case NAME_LGA:
				return "LGA";
			case NAME_RGA:
				return "RGA";
			case NAME_LGEA:
				return "LGEA";
			case NAME_RGEA:
				return "RGEA";
			case NAME_SA:
				return "SA";
			case NAME_SMA:
				return "SMA";
#ifdef _TARGET_HYPOGASTRIC
			case NAME_IMA:
				return "IMA";
			case NAME_LRA:
				return "LRA";
			case NAME_RRA:
				return "RRA";
			case NAME_LCIA:
				return "LCIA";
			case NAME_RCIA:
				return "RCIA";
			case NAME_LIIA:
				return "LIIA";
			case NAME_RIIA:
				return "RIIA";
			case NAME_LEIA:
				return "LEIA";
			case NAME_REIA:
				return "REIA";
#endif //_TARGET_HYPOGASTRIC
			default:
				return "other";
			}
		}

		/// @brief ¼OðCfbNXÉÏ··é
		/// @param[in] name Ï··é¼O
		/// @return ¼OÉÎ·éCfbNX
		size_t to_index( Name name )
		{
			return name == NAME_OTHER ? NAME_END - 1 : name - 1;
		}
	
		/// @brief ¶ñð¼OÉÏ··é
		/// @param[in] str Ï··é¶ñ
		/// @return ¶ñÌ\·¼O
		Name to_name( const std::string &str )
		{
			if ( str == "Ao" )
			{
				return NAME_AO;
			}
			else if ( str == "CA" )
			{
				return NAME_CA;
			}
			else if ( str == "CHA" )
			{
				return NAME_CHA;
			}
			else if ( str == "PHA" )
			{
				return NAME_PHA;
			}
			else if ( str == "LHA" )
			{
				return NAME_LHA;
			}
			else if ( str == "RHA" )
			{
				return NAME_RHA;
			}
			else if ( str == "GDA" )
			{
				return NAME_GDA;
			}
			else if ( str == "LGA" )
			{
				return NAME_LGA;
			}
			else if ( str == "RGA" )
			{
				return NAME_RGA;
			}
			else if ( str == "LGEA" )
			{
				return NAME_LGEA;
			}	
			else if ( str == "RGEA" )
			{
				return NAME_RGEA;
			}
			else if ( str == "SA" )
			{
				return NAME_SA;
			}
			else if ( str == "SMA" )
			{
				return NAME_SMA;
			}
#ifdef _TARGET_HYPOGASTRIC
			else if ( str == "IMA" )
			{
				return NAME_IMA;
			}
			else if ( str == "LRA" )
			{
				return NAME_LRA;
			}
			else if ( str == "RRA" )
			{
				return NAME_RRA;
			}
			else if ( str == "LCIA" )
			{
				return NAME_LCIA;
			}
			else if ( str == "RCIA" )
			{
				return NAME_RCIA;
			}
			else if ( str == "LIIA" )
			{
				return NAME_LIIA;
			}
			else if ( str == "RIIA" )
			{
				return NAME_RIIA;
			}
			else if ( str == "LEIA" )
			{
				return NAME_LEIA;
			}
			else if ( str == "REIA" )
			{
				return NAME_REIA;
			}
#endif //_TARGET_HYPOGASTRIC
			else
			{
				return NAME_OTHER;
			} 
		}
	
		/// @brief CfbNXð¼OÉÏ··é
		/// @param[in] idx Ï··éCfbNX
		/// @return CfbNXÌ\·¼O
		Name to_name( size_t idx )
		{
			return idx == NAME_END - 1 ? NAME_OTHER : static_cast< Name >( idx + 1 );
		}
	}
}

#endif //_TMATSU_ARTERY_H_