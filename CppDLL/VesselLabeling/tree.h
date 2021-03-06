/**
* @file tree.h
* @brief Ø\¢ReiNXÌwb_t@C
* @version 3.0
* @author ¼Ã®åw îñÈw¤È fBAÈwêU X¤º   351203192   ¼ú± NN
* @date 2013/10/18
*/

#ifndef _TMATSU_TREE_H_
#define _TMATSU_TREE_H_

#include <memory>
#include <exception>
#include <cstddef>
#include <climits>

namespace tmatsu 
{
	/// @brief ½ªØðµ¤ReiNX
	/// @tparam ValueType Ø\¢Ìm[hÌi[·éf[^^
	/// @tparam Allocator AP[^^DKèlÍSTLÌftHgAP[^
	/// @attention »ÝàÅAP[^Ígp³êÄ¢È¢
	template < class ValueType, class Allocator = std::allocator< ValueType > >
	class tree
	{
		/// @brief m[h
		struct Node
		{
			ValueType val; ///< @brief f[^
			Node *parent; ///< @brief e
			Node *eldest_child; ///< @brief ·q
			Node *youngest_child; ///< @brief q
			Node *elder_sibling; ///< @brief Z
			Node *younger_sibling; ///< @brief í
		public:
			Node( );
			Node( const Node &node );
			Node( const ValueType &val );
			~Node( );
			Node *preorder_hd( );
			const Node *preorder_hd( )const;
			Node *preorder_tl( );
			const Node *preorder_tl( )const;
			const Node *preorder_incr( const Node *root )const;
			const Node *preorder_decr( const Node *root )const;
#ifdef _INORDER_ITERATOR
			Node *inorder_hd( );
			const Node *inorder_hd( )const;
			Node *inorder_tl( );
			const Node *inorder_tl( )const;
			const Node *inorder_incr( const Node *root )const;
			const Node *inorder_decr( const Node *root )const;
#endif //_INORDER_ITERATOR
			Node *postorder_hd( );
			const Node *postorder_hd( )const;
			Node *postorder_tl( );
			const Node *postorder_tl( )const;
			const Node *postorder_incr( const Node *root )const;
			const Node *postorder_decr( const Node *root )const;
			Node *levelorder_hd( );
			const Node *levelorder_hd( )const;
			Node *levelorder_tl( );
			const Node *levelorder_tl( )const;
			const Node *levelorder_incr( const Node *root )const;
			const Node *levelorder_decr( const Node *root )const;
			Node *child_hd( );
			const Node *child_hd( )const;
			Node *child_tl( );
			const Node *child_tl( )const;
			const Node *child_incr( const Node *root )const;
			const Node *child_decr( const Node *root )const;
		};

		/// @brief ªØ
		class Subtree : public tree 
		{
		public:
			Subtree( const Node *root );
			virtual ~Subtree( );
		};

	public:
		/// @brief óÌØ\¢ÉÜÜêélðQÆµæ¤Æ·éÆ°çêéáO
		class invalid_tree : public std::exception
		{
		};

		typedef ValueType value_type; ///< @brief l
		typedef Allocator allocator_type; ///< @brief AP[^
		typedef size_t size_type; ///< @brief ³µ®
		typedef ptrdiff_t difference_type; ///< @brief t«®
		typedef typename Allocator::reference reference; ///< @brief QÆ
		typedef typename Allocator::const_reference const_reference; ///< @brief èQÆ
		typedef typename Allocator::pointer pointer; ///< @brief |C^
		typedef typename Allocator::const_pointer const_pointer; ///< @brief è|C^
	
		/// @brief Ø\¢ðûüÉ¸·éOiCe[^
		class const_iterator
		{
		public:
			typedef std::forward_iterator_tag iterator_category; ///< @brief Ce[^JeS
			typedef ValueType value_type; ///< @brief l
			typedef size_t size_type; ///< @brief ³µ®
			typedef ptrdiff_t difference_type; ///< @brief t«®
			typedef typename Allocator::reference reference; ///< @brief QÆ
			typedef typename Allocator::const_reference const_reference; ///< @brief èQÆ
			typedef typename Allocator::pointer pointer; ///< @brief |C^
			typedef typename Allocator::const_pointer const_pointer; ///< @brief è|C^

			/// @brief LøÈÔnðwµÄ¢È¢Ce[^ÌlðQÆµæ¤Æ·éÆ°çêéáO
			class invalid_iterator : public std::exception
			{
			};
		protected:
			const Node *node_; ///< @brief m[h
			const Node *root_; ///< @brief ª
			const Node *( Node::*incr_ )( const Node * )const; ///< @brief OiÖ
		public:
			const_iterator( );
			const_iterator( const const_iterator &iter );
			const_iterator( const Node *node, const Node *root, const Node *( Node::*incr )( const Node * )const );
			const Node *node( )const;
			const Node *root( )const;
			const Node *( Node::*incr( ) )( const Node * )const;
			const_iterator &operator++( );
			const_iterator operator++( int );
#ifdef _BIDIRECTIONAL_ITERATOR
			const_iterator &operator--( );
			const_iterator operator--( int );
#endif //_BIDIRECTIONAL_ITERATOR
			bool operator==( const const_iterator &iter )const;
			bool operator!=( const const_iterator &iter )const;
			const_reference operator*( );
			const_pointer operator->( );
		};

		/// @brief Ø\¢ðûüÉ¸·éOiCe[^
		class iterator : public const_iterator
		{
		public:
			iterator( );
			iterator( const iterator &iter );
			iterator( Node *node, const Node *root, const Node *( Node::*incr )( const Node * )const );
			Node *node( )const;
			iterator &operator++( );
			iterator operator++( int );
#ifdef _BIDIRECTIONAL_ITERATOR
			iterator &operator--( );
			iterator operator--( int );
#endif //_BIDIRECTIONAL_ITERATOR
			reference operator*( );
			pointer operator->( );
		};

		/// @brief Ø\¢ðtûüÉ¸·éOiCe[^
		class const_reverse_iterator
		{
		public:
			typedef std::forward_iterator_tag iterator_category; ///< @brief Ce[^JeS
			typedef ValueType value_type; ///< @brief l
			typedef size_t size_type; ///< @brief ³µ®
			typedef ptrdiff_t difference_type; ///< @brief t«®
			typedef typename Allocator::reference reference; ///< @brief QÆ
			typedef typename Allocator::const_reference const_reference; ///< @brief èQÆ
			typedef typename Allocator::pointer pointer; ///< @brief |C^
			typedef typename Allocator::const_pointer const_pointer; ///< @brief è|C^

			/// @brief LøÈÔnðwµÄ¢È¢Ce[^ÌlðQÆµæ¤Æ·éÆ°çêéáO
			class invalid_iterator : public std::exception
			{
			};
		protected:
			const Node *node_; ///< @brief m[h
			const Node *root_; ///< @brief ª
			const Node *( Node::*incr_ )( const Node * )const; ///< @brief OiÖ
		public:
			const_reverse_iterator( );
			const_reverse_iterator( const const_reverse_iterator &iter );
			const_reverse_iterator( const Node *node, const Node *root, const Node *( Node::*incr )( const Node * )const );
			const Node *node( )const;
			const Node *root( )const;
			const Node *( Node::*incr( ) )( const Node * )const;
			const_reverse_iterator &operator++( );
			const_reverse_iterator operator++( int );
#ifdef _BIDIRECTIONAL_ITERATOR
			const_reverse_iterator &operator--( );
			const_reverse_iterator operator--( int );
#endif //_BIDIRECTIONAL_ITERATOR
			bool operator==( const const_reverse_iterator &iter )const;
			bool operator!=( const const_reverse_iterator &iter )const;
			const_reference operator*( );
			const_pointer operator->( );
		};

		/// @brief Ø\¢ðtûüÉ¸·éOiCe[^
		class reverse_iterator : public const_reverse_iterator
		{
		public:
			reverse_iterator( );
			reverse_iterator( const reverse_iterator &iter );
			reverse_iterator( Node *node, const Node *root, const Node *( Node::*incr )( const Node * )const );
			Node *node( )const;
			reverse_iterator &operator++( );
			reverse_iterator operator++( int );
#ifdef _BIDIRECTIONAL_ITERATOR
			reverse_iterator &operator--( );
			reverse_iterator operator--( int );
#endif //_BIDIRECTIONAL_ITERATOR
			reference operator*( );
			pointer operator->( );
		};
	private:
		Node *root_; ///< @brief ª
	public:
		tree( );
		tree( const tree &tree );
		explicit tree( const Allocator &alloc );
		explicit tree( size_t cnt );
		tree( size_t cnt, const ValueType &val );
		tree( size_t cnt, const ValueType &val, const Allocator &alloc );
		template < class Iterator >
		tree( Iterator first, Iterator last );
		template < class Iterator >
		tree( Iterator first, Iterator last, const Allocator &alloc );
		virtual ~tree( );
		iterator begin( );
		const_iterator begin( )const;
		reverse_iterator rbegin( );
		const_reverse_iterator rbegin( )const;
		iterator end( );
		const_iterator end( )const;
		reverse_iterator rend( );
		const_reverse_iterator rend( )const;
		iterator preorder_begin( );
		const_iterator preorder_begin( )const;
		reverse_iterator preorder_rbegin( );
		const_reverse_iterator preorder_rbegin( )const;
		iterator preorder_end( );
		const_iterator preorder_end( )const;
		reverse_iterator preorder_rend( );
		const_reverse_iterator preorder_rend( )const;
#ifdef _INORDER_ITERATOR
		iterator inorder_begin( );
		const_iterator inorder_begin( )const;
		reverse_iterator inorder_rbegin( );
		const_reverse_iterator inorder_rbegin( )const;
		iterator inorder_end( );
		const_iterator inorder_end( )const;
		reverse_iterator inorder_rend( );
		const_reverse_iterator inorder_rend( )const;
#endif //_INORDER_ITERATOR
		iterator postorder_begin( );
		const_iterator postorder_begin( )const;
		reverse_iterator postorder_rbegin( );
		const_reverse_iterator postorder_rbegin( )const;
		iterator postorder_end( );
		const_iterator postorder_end( )const;
		reverse_iterator postorder_rend( );
		const_reverse_iterator postorder_rend( )const;
		iterator levelorder_begin( );
		const_iterator levelorder_begin( )const;
		reverse_iterator levelorder_rbegin( );
		const_reverse_iterator levelorder_rbegin( )const;
		iterator levelorder_end( );
		const_iterator levelorder_end( )const;
		reverse_iterator levelorder_rend( );
		const_reverse_iterator levelorder_rend( )const;
		template < class Iterator >
		iterator child_begin( Iterator parent );
		template < class Iterator >
		const_iterator child_begin( Iterator parent )const;
		template < class Iterator >
		reverse_iterator child_rbegin( Iterator parent );
		template < class Iterator >
		const_reverse_iterator child_rbegin( Iterator parent )const;
		template < class Iterator >
		iterator child_end( Iterator parent );
		template < class Iterator >
		const_iterator child_end( Iterator parent )const;
		template < class Iterator >
		reverse_iterator child_rend( Iterator parent );
		template < class Iterator >
		const_reverse_iterator child_rend( Iterator parent )const;
		template < class Iterator >
		void assign( Iterator first, Iterator last );
		void assign( size_t cnt, const ValueType &val );
		void swap( tree &tree );
		allocator_type get_allocator( )const;
		size_t size( )const;
		size_t max_size( )const;
		bool empty( )const;
		void resize( size_t cnt );
		void resize( size_t cnt, const ValueType &val );
		reference root( );
		const_reference root( )const;
		iterator insert( const_iterator parent, const ValueType &val );
		template < class Type >
		iterator insert( const_iterator parent, Type val );
		void insert( const_iterator parent, size_t cnt, const ValueType &val );
		template < class Iterator >
		void insert( const_iterator parent, Iterator first, Iterator last );
		void insert( const_iterator parent, const tree &tree );
		void insert( const_iterator parent, size_t cnt, const tree &tree );
		iterator insert( const_iterator parent, const_iterator younger_sibling, const ValueType &val );
		template < class Type >
		iterator insert( const_iterator parent, const_iterator younger_sibling, Type val );
		void insert( const_iterator parent, const_iterator younger_sibling, size_t cnt, const ValueType &val );
		template < class Iterator >
		void insert( const_iterator parent, const_iterator younger_sibling, Iterator first, Iterator last );
		void insert( const_iterator parent, const_iterator younger_sibling, const tree &tree );
		void insert( const_iterator parent, const_iterator younger_sibling, size_t cnt, const tree &tree );
		iterator erase( const_iterator pos );
		iterator erase( const_iterator first, const_iterator last );
		void clear( );
		template < class Iterator >
		Iterator parent( Iterator child )const;
		template < class Iterator >
		size_t depth( Iterator iter )const;
		template < class Iterator >
		bool is_root( Iterator iter )const;
		template < class Iterator >
		bool is_leaf( Iterator iter )const;
		template < class Iterator >
		bool has_sibling( Iterator iter )const;
		template < class Iterator, class ReferenceIterator >
		bool is_ancestor( Iterator iter, ReferenceIterator ref_iter )const;
		template < class Iterator, class ReferenceIterator >
		bool is_descendant( Iterator iter, ReferenceIterator ref_iter )const;
		template < class Iterator >
		Subtree subtree( Iterator root )const;
		template < class Iterator >
		void reverse( Iterator root, tree &tree );
		tree &operator=( const tree &tree );
		bool operator==( const tree &tree )const;
		bool operator!=( const tree &tree )const;
		bool operator<( const tree &tree )const;
		bool operator<=( const tree &tree )const;
		bool operator>( const tree &tree )const;
		bool operator>=( const tree &tree )const;
	private:
		explicit tree( const Node *root );
	};

	/// @brief ú»·é
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::tree( ) : root_( NULL )
	{
	}
	
	/// @brief Ø\¢ð¡»·é
	/// @param[in] tree ¡»·éØ\¢
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::tree( const tree &tree ) : root_( NULL )
	{
		operator=( tree );
	}

	/// @brief ú»·é
	/// @param[in] alloc AP[^
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::tree( const Allocator &alloc ) : root_( NULL )
	{
	}

	/// @brief øÌ¾¯f[^ðmÛµCª¨æÑ»ÌqÆ·é
	/// @param[in] cnt f[^Ì
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::tree( size_t cnt ) : root_( NULL )
	{
		insert( begin( ), cnt, ValueType( ) );
	}

	/// @brief øÌ¾¯øÌf[^ðmÛµCª¨æÑ»ÌqÆ·é
	/// @param[in] cnt f[^Ì
	/// @param[in] val f[^Ìúl
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::tree( size_t cnt, const ValueType &val ) : root_( NULL )
	{
		insert( begin( ), cnt, val );
	}

	/// @brief øÌ¾¯f[^ðmÛµCª¨æÑ»ÌqÆ·é
	/// @param[in] cnt f[^Ì
	/// @param[in] val f[^Ìúl
	/// @param[in] alloc AP[^
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::tree( size_t cnt, const ValueType &val, const Allocator &alloc ) : root_( NULL )
	{
		insert( begin( ), cnt, val );
	}


	/// @brief øÌf[^ð¡»µCª¨æÑ»ÌqÆ·é
	/// @attention øªØ\¢Å éêCeqÖWÍÛ¶³êÈ¢
	/// @param[in] first ¡»·éf[^Ìæªðw·Ce[^
	/// @param[in] last ¡»·éf[^ÌöÌðw·Ce[^
	template < class ValueType, class Allocator >
	template < class Iterator >
	inline tree< ValueType, Allocator >::tree( Iterator first, Iterator last ) : root_( NULL )
	{
		insert( begin( ), first, last );
	}

	/// @brief øÌf[^ð¡»µCª¨æÑ»ÌqÆ·é
	/// @attention øªØ\¢Å éêCeqÖWÍÛ¶³êÈ¢
	/// @param[in] first ¡»·éf[^Ìæªðw·Ce[^
	/// @param[in] last ¡»·éf[^ÌöÌðw·Ce[^
	/// @param[in] alloc AP[^
	template < class ValueType, class Allocator >
	template < class Iterator >
	inline tree< ValueType, Allocator >::tree( Iterator first, Iterator last, const Allocator &alloc ) : root_( NULL )
	{
		insert( begin( ), first, last );
	}
	
	/// @brief øÌm[hðªÆ·éØ\¢Ì[¢¡»ðì¬·é
	/// @param[in] root...¡»·éØ\¢Ìª
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::tree( const Node *root ) : root_( const_cast< Node * >( root ) )
	{
	}


	/// @brief ÌæðJú·é
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::~tree( )
	{
		delete root_;
		root_ = NULL;
	}

	/// @brief æªðw·Ce[^ðæ¾·é
	/// @return æªðw·Ce[^
	///
	/// gpá
	/// @code
	/// tmatsu::tree< int > t; // Ø\¢
	///
	/// // Ø\¢Ìem[hÌlðó·é
	/// for ( tmatsu::tree< int >::iterator iter = t.begin( ); iter != t.end( ); iter++ )
	/// {
	///		for ( size_t i = 0; i < t.depth( iter ); i++ )
	///		{
	///			std::cout << ' ';
	///		}
	///
	///		std::cout << *iter << std::endl;
	/// }
	/// @endcode
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::iterator tree< ValueType, Allocator >::begin( )
	{
		return preorder_begin( );
	}

	/// @brief æªðw·èCe[^ðæ¾·é
	/// @return æªðw·èCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_iterator tree< ValueType, Allocator >::begin( )const	
	{
		return preorder_begin( );
	}

	/// @brief öðw·tCe[^ðæ¾·é
	/// @return öðw·tCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::reverse_iterator tree< ValueType, Allocator >::rbegin( )
	{
		return preorder_rbegin( );
	}

	/// @brief öðw·ètCe[^ðæ¾·é
	/// @return öðw·ètCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_reverse_iterator tree< ValueType, Allocator >::rbegin( )const	
	{
		return preorder_rbegin( );
	}

	/// @brief öÌðw·Ce[^ðæ¾·é
	/// @return öÌðw·Ce[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::iterator tree< ValueType, Allocator >::end( )
	{
		return preorder_end( );
	}

	/// @brief öÌðw·èCe[^ðæ¾·é
	/// @return öÌðw·èCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_iterator tree< ValueType, Allocator >::end( )const
	{
		return preorder_end( );
	}

	/// @brief æªÌOðw·tCe[^ðæ¾·é
	/// @return æªÌOðw·tCe[^	
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::reverse_iterator tree< ValueType, Allocator >::rend( )
	{
		return preorder_rend( );
	}

	/// @brief æªÌOðw·ètCe[^ðæ¾·é
	/// @return æªÌOðw·ètCe[^	
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_reverse_iterator tree< ValueType, Allocator >::rend( )const
	{
		return preorder_rend( );
	}

	/// @brief æªðw·æs([³Dæ)ÌCe[^ðæ¾·é
	/// @return æªðw·æs([³Dæ)ÌCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::iterator tree< ValueType, Allocator >::preorder_begin( )
	{
		return iterator( root_ ? root_->preorder_hd( ) : NULL, root_, &Node::preorder_incr );
	}

	/// @brief æªðw·æs([³Dæ)ÌèCe[^ðæ¾·é
	/// @return æªðw·æs([³Dæ)ÌèCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_iterator tree< ValueType, Allocator >::preorder_begin( )const
	{
		return const_iterator( root_ ? root_->preorder_hd( ) : NULL, root_, &Node::preorder_incr );
	}

	/// @brief öðw·æs([³Dæ)ÌtCe[^ðæ¾·é
	/// @return öðw·æs([³Dæ)ÌtCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::reverse_iterator tree< ValueType, Allocator >::preorder_rbegin( )
	{
		return reverse_iterator( root_ ? root_->preorder_tl( ) : NULL, root_, &Node::preorder_decr );
	}

	/// @brief öðw·æs([³Dæ)ÌètCe[^ðæ¾·é
	/// @return öðw·æs([³Dæ)ÌètCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_reverse_iterator tree< ValueType, Allocator >::preorder_rbegin( )const
	{
		return const_reverse_iterator( root_ ? root_->preorder_tl( ) : NULL, root_, &Node::preorder_decr );
	}

	/// @brief öÌðw·æs([³Dæ)ÌCe[^ðæ¾·é
	/// @return öÌðw·æs([³Dæ)ÌCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::iterator tree< ValueType, Allocator >::preorder_end( )
	{
		return iterator( NULL, root_, &Node::preorder_incr );
	}

	/// @brief öÌðw·æs([³Dæ)ÌèCe[^ðæ¾·é
	/// @return öÌðw·æs([³Dæ)ÌèCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_iterator tree< ValueType, Allocator >::preorder_end( )const
	{
		return const_iterator( NULL, root_, &Node::preorder_incr );
	}

	/// @brief æªÌOðw·æs([³Dæ)ÌtCe[^ðæ¾·é
	/// @return æªÌOðw·æs([³Dæ)ÌtCe[^	
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::reverse_iterator tree< ValueType, Allocator >::preorder_rend( )
	{
		return reverse_iterator( NULL, root_, &Node::preorder_decr );
	}

	/// @brief æªÌOðw·æs([³Dæ)ÌètCe[^ðæ¾·é
	/// @return æªÌOðw·æs([³Dæ)ÌètCe[^	
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_reverse_iterator tree< ValueType, Allocator >::preorder_rend( )const
	{
		return const_reverse_iterator( NULL, root_, &Node::preorder_decr );
	}

#if _INORDER_ITERATOR
	/// @brief æªðw·ÔÌCe[^ðæ¾·é
	/// @attention Ø\¢ªñªØÅÈ¢êÌ®ìÍsè
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
 	/// @return æªðw·ÔÌCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::iterator tree< ValueType, Allocator >::inorder_begin( )
	{
		return iterator( root_ ? root_->inorder_hd( ) : NULL, NULL, &Node::inorder_incr, &Node::inorder_decr );
	}

	/// @brief æªðw·ÔÌèCe[^ðæ¾·é
	/// @attention Ø\¢ªñªØÅÈ¢êÌ®ìÍsè
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
 	/// @return æªðw·ÔÌèCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_iterator tree< ValueType, Allocator >::inorder_begin( )const
	{
		return const_iterator( root_ ? root_->inorder_hd( ) : NULL, NULL, &Node::inorder_incr, &Node::inorder_decr );
	}

	/// @brief öðw·ÔÌtCe[^ðæ¾·é
	/// @attention Ø\¢ªñªØÅÈ¢êÌ®ìÍsè
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
 	/// @return öðw·ÔÌtCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::reverse_iterator tree< ValueType, Allocator >::inorder_rbegin( )
	{
		return reverse_iterator( root_ ? root_->inorder_tl( ) : NULL, NULL, &Node::inorder_decr, &Node::inorder_incr );
	}

	/// @brief öðw·ÔÌètCe[^ðæ¾·é
	/// @attention Ø\¢ªñªØÅÈ¢êÌ®ìÍsè
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
 	/// @return öðw·ÔÌètCe[^	
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_reverse_iterator tree< ValueType, Allocator >::inorder_rbegin( )const
	{
		return const_reverse_iterator( root_ ? root_->inorder_tl( ) : NULL, NULL, &Node::inorder_decr, &Node::inorder_incr );
	}

	/// @brief öÌðw·ÔÌCe[^ðæ¾·é
	/// @attention Ø\¢ªñªØÅÈ¢êÌ®ìÍsè
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
 	/// @return öÌðw·ÔÌCe[^	
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::iterator tree< ValueType, Allocator >::inorder_end( )
	{
		return iterator( NULL, root_ ? root_->inorder_tl( ) : NULL, &Node::inorder_incr, &Node::inorder_decr );
	}

	/// @brief öÌðw·ÔÌèCe[^ðæ¾·é
	/// @attention Ø\¢ªñªØÅÈ¢êÌ®ìÍsè
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
 	/// @return öÌðw·ÔÌèCe[^	
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_iterator tree< ValueType, Allocator >::inorder_end( )const
	{
		return const_iterator( NULL, root_ ? root_->inorder_tl( ) : NULL, &Node::inorder_incr, &Node::inorder_decr );
	}

	/// @brief æªÌOðw·ÔÌtCe[^ðæ¾·é
	/// @attention Ø\¢ªñªØÅÈ¢êÌ®ìÍsè
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
 	/// @return æªÌOðw·ÔÌtCe[^		
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::reverse_iterator tree< ValueType, Allocator >::inorder_rend( )
	{
		return reverse_iterator( NULL, root_ ? root_->inorder_hd( ) : NULL, &Node::inorder_decr, &Node::inorder_incr );
	}
	
	/// @brief æªÌOðw·ÔÌètCe[^ðæ¾·é
	/// @attention Ø\¢ªñªØÅÈ¢êÌ®ìÍsè
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
 	/// @return æªÌOðw·ÔÌètCe[^		
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_reverse_iterator tree< ValueType, Allocator >::inorder_rend( )const
	{
		return const_reverse_iterator( NULL, root_ ? root_->inorder_hd( ) : NULL, &Node::inorder_decr, &Node::inorder_incr );
	}
#endif //_INORDER_ITERATOR

	/// @brief æªðw·ãsÌCe[^ðæ¾·é
	/// @return æªðw·ãsÌCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::iterator tree< ValueType, Allocator >::postorder_begin( )
	{
		return iterator( root_ ? root_->postorder_hd( ) : NULL, root_, &Node::postorder_incr );
	}

	/// @brief æªðw·ãsÌèCe[^ðæ¾·é
	/// @return æªðw·ãsÌèCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_iterator tree< ValueType, Allocator >::postorder_begin( )const
	{
		return const_iterator( root_ ? root_->postorder_hd( ) : NULL, root_, &Node::postorder_incr );
	}

	/// @brief öðw·ãsÌtCe[^ðæ¾·é
	/// @return öðw·ãsÌtCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::reverse_iterator tree< ValueType, Allocator >::postorder_rbegin( )
	{
		return reverse_iterator( root_ ? root_->postorder_tl( ) : NULL, root_, &Node::postorder_decr );
	}

	/// @brief öðw·ãsÌètCe[^ðæ¾·é
	/// @return öðw·ãsÌètCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_reverse_iterator tree< ValueType, Allocator >::postorder_rbegin( )const
	{
		return const_reverse_iterator( root_ ? root_->postorder_tl( ) : NULL, root_, &Node::postorder_decr );
	}

	/// @brief öÌðw·ãsÌCe[^ðæ¾·é
	/// @return öÌðw·ãsÌCe[^
	template < class ValueType, class Allocator >	
	inline typename tree< ValueType, Allocator >::iterator tree< ValueType, Allocator >::postorder_end( )
	{
		return iterator( NULL, root_, &Node::postorder_incr );
	}
	
	/// @brief öÌðw·ãsÌèCe[^ðæ¾·é
	/// @return öÌðw·ãsÌèCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_iterator tree< ValueType, Allocator >::postorder_end( )const
	{
		return const_iterator( NULL, root_, &Node::postorder_incr );
	}
	
	/// @brief æªÌOðw·ãsÌtCe[^ðæ¾·é
	/// @return æªÌOðw·ãsÌtCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::reverse_iterator tree< ValueType, Allocator >::postorder_rend( )
	{
		return reverse_iterator( NULL, root_, &Node::postorder_decr );
	}

	/// @brief æªÌOðw·ãsÌètCe[^ðæ¾·é
	/// @return æªÌOðw·ãsÌètCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_reverse_iterator tree< ValueType, Allocator >::postorder_rend( )const
	{
		return const_reverse_iterator( NULL, root_, &Node::postorder_decr );
	}

	/// @brief æªðw·x(Dæ)ÌCe[^ðæ¾·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @return	æªðw·x(Dæ)ÌCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::iterator tree< ValueType, Allocator >::levelorder_begin( )
	{
		return iterator( root_ ? root_->levelorder_hd( ) : NULL, root_, &Node::levelorder_incr );
	}

	/// @brief æªðw·x(Dæ)ÌèCe[^ðæ¾·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @return	æªðw·x(Dæ)ÌèCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_iterator tree< ValueType, Allocator >::levelorder_begin( )const
	{
		return const_iterator( root_ ? root_->levelorder_hd( ) : NULL, root_, &Node::levelorder_incr );
	}

	/// @brief öðw·x(Dæ)ÌtCe[^ðæ¾·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @return	öðw·x(Dæ)ÌtCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::reverse_iterator tree< ValueType, Allocator >::levelorder_rbegin( )
	{
		return reverse_iterator( root_ ? root_->levelorder_tl( ) : NULL, root_, &Node::levelorder_decr );
	}

	/// @brief öðw·x(Dæ)ÌètCe[^ðæ¾·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @return	öðw·x(Dæ)ÌètCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_reverse_iterator tree< ValueType, Allocator >::levelorder_rbegin( )const
	{
		return const_reverse_iterator( root_ ? root_->levelorder_tl( ) : NULL, root_, &Node::levelorder_decr );
	}

	/// @brief öÌðw·x(Dæ)ÌCe[^ðæ¾·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @return	öÌðw·x(Dæ)ÌCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::iterator tree< ValueType, Allocator >::levelorder_end( )
	{
		return iterator( NULL, root_, &Node::levelorder_incr );
	}
	
	/// @brief öÌðw·x(Dæ)ÌèCe[^ðæ¾·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @return	öÌðw·x(Dæ)ÌèCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_iterator tree< ValueType, Allocator >::levelorder_end( )const
	{
		return const_iterator( NULL, root_, &Node::levelorder_incr );
	}
	
	/// @brief æªÌOðw·x(Dæ)ÌtCe[^ðæ¾·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @return	æªÌOðw·x(Dæ)ÌtCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::reverse_iterator tree< ValueType, Allocator >::levelorder_rend( )
	{
		return reverse_iterator( NULL, root_, &Node::levelorder_decr );
	}

	/// @brief æªÌOðw·x(Dæ)ÌètCe[^ðæ¾·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @return	æªÌOðw·x(Dæ)ÌètCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_reverse_iterator tree< ValueType, Allocator >::levelorder_rend( )const
	{
		return const_reverse_iterator( NULL, root_, &Node::levelorder_decr );
	}

	/// @brief æªðw·qÌCe[^ðæ¾·é
	/// @param[in] parent æ¾·éCe[^Ìeðw·Ce[^
	/// @return	æªðw·qÌCe[^
	///
	/// gpá
	/// @code
	/// tmatsu::tree< int > t; // Ø\¢
	/// tmatsu::tree< int >::iterator node = std::find( t.begin( ), t.end( ), 100 ); // lª100Ìm[hðw·Ce[^
	/// 
	/// // qÌem[hÌlðó·é
	/// for ( tmatsu::tree< int >::iterator iter = t.child_begin( node ); iter != t.child_end( node ); iter++ )
	/// {
	///		std::cout << *iter << std::endl;
	/// }
	///
	/// // ZíÌem[hÌlðó·é
	/// for ( tmatsu::tree< int >::iterator iter = t.child_begin( t.parent( node ) ); iter != t.child_end( t.parent( node ) ); iter++ )
	/// {
	///		if ( iter != node )
	///		{
	///			std::cout << *iter << std::endl;
	///		}
	/// }
	/// @endcode
	template < class ValueType, class Allocator >
	template < class Iterator >
	inline typename tree< ValueType, Allocator >::iterator tree< ValueType, Allocator >::child_begin( Iterator parent )
	{
		return iterator( parent.node( ) ? const_cast< Node * >( parent.node( )->child_hd( ) ) : NULL, root_, &Node::child_incr );
	}

	/// @brief æªðw·qÌèCe[^ðæ¾·é
	/// @param[in] parent æ¾·éCe[^Ìeðw·Ce[^
	/// @return	æªðw·qÌèCe[^
	template < class ValueType, class Allocator >
	template < class Iterator >
	inline typename tree< ValueType, Allocator >::const_iterator tree< ValueType, Allocator >::child_begin( Iterator parent )const
	{
		return const_iterator( parent.node( ) ? parent.node( )->child_hd( ) : NULL, root_, &Node::child_incr );
	}
	
	/// @brief öðw·qÌtCe[^ðæ¾·é
	/// @param[in] parent æ¾·éCe[^Ìeðw·Ce[^
	/// @return	öðw·qÌtCe[^
	template < class ValueType, class Allocator >
	template < class Iterator >
	inline typename tree< ValueType, Allocator >::reverse_iterator tree< ValueType, Allocator >::child_rbegin( Iterator parent )
	{
		return reverse_iterator( parent.node( ) ? const_cast< Node * >( parent.node( )->child_tl( ) ) : NULL, root_, &Node::child_decr );
	}

	/// @brief öðw·qÌètCe[^ðæ¾·é
	/// @param[in] parent æ¾·éCe[^Ìeðw·Ce[^
	/// @return	öðw·qÌètCe[^
	template < class ValueType, class Allocator >
	template < class Iterator >
	inline typename tree< ValueType, Allocator >::const_reverse_iterator tree< ValueType, Allocator >::child_rbegin( Iterator parent )const
	{
		return const_reverse_iterator( parent.node( ) ? parent.node( )->child_tl( ) : NULL, root_, &Node::child_decr );
	}

	/// @brief öÌðw·qÌCe[^ðæ¾·é
	/// @param[in] parent æ¾·éCe[^Ìeðw·Ce[^
	/// @return	öÌðw·qÌCe[^
	template < class ValueType, class Allocator >
	template < class Iterator >
	inline typename tree< ValueType, Allocator >::iterator tree< ValueType, Allocator >::child_end( Iterator parent )
	{
		return iterator( NULL, root_, &Node::child_incr );
	}

	/// @brief öÌðw·qÌèCe[^ðæ¾·é
	/// @param[in] parent æ¾·éCe[^Ìeðw·Ce[^
	/// @return	öÌðw·qÌèCe[^
	template < class ValueType, class Allocator >
	template < class Iterator >
	inline typename tree< ValueType, Allocator >::const_iterator tree< ValueType, Allocator >::child_end( Iterator parent )const
	{
		return const_iterator( NULL, root_, &Node::child_incr );
	}

	/// @brief æªÌOðw·qÌtCe[^ðæ¾·é
	/// @param[in] parent æ¾·éCe[^Ìeðw·Ce[^
	/// @return	æªÌOðw·qÌtCe[^
	template < class ValueType, class Allocator >
	template < class Iterator >
	inline typename tree< ValueType, Allocator >::reverse_iterator tree< ValueType, Allocator >::child_rend( Iterator parent )
	{
		return reverse_iterator( NULL, root_, &Node::child_decr );
	}

	/// @brief æªÌOðw·qÌètCe[^ðæ¾·é
	/// @param[in] parent æ¾·éCe[^Ìeðw·Ce[^
	/// @return	æªÌOðw·qÌètCe[^
	template < class ValueType, class Allocator >
	template < class Iterator >
	inline typename tree< ValueType, Allocator >::const_reverse_iterator tree< ValueType, Allocator >::child_rend( Iterator parent )const
	{
		return const_reverse_iterator( NULL, root_, &Node::child_decr );
	}

	/// @brief øÌf[^ðãüµCª¨æÑ»ÌqÆ·é
	/// @attention øªØ\¢Å Á½êCeqÖWÍÛ¶³êÈ¢
	/// @param[in] first ¡»·éf[^Ìæªðw·Ce[^
	/// @param[in] last ¡»·éf[^ÌöÌðw·Ce[^
	template < class ValueType, class Allocator >
	template < class Iterator >
	inline void tree< ValueType, Allocator >::assign( Iterator first, Iterator last )
	{
		clear( );
		insert( begin( ), first, last );
	}

	/// @brief øÌ¾¯f[^ðãüµCª¨æÑ»ÌqÆ·é
	/// @param[in] cnt@ãü·éf[^Ì
	/// @param[in] val ãü·éf[^
	template < class ValueType, class Allocator >
	inline void tree< ValueType, Allocator >::assign( size_t cnt, const ValueType &val )
	{
		clear( );
		insert( begin( ), cnt, val );
	}

	/// @brief Ø\¢ðüêÖ¦é
	/// @param[inout] tree üêÖ¦éØ\¢
	template < class ValueType, class Allocator >
	inline void tree< ValueType, Allocator >::swap( tree &tree )
	{
		std::swap( root_, tree.root_ );
	}

	/// @brief AP[^ðæ¾·é
	/// @attention »ÝàÅAP[^ªgp³êÄ¢È¢½ß³Ó¡ÈlªÔé
	/// @return AP[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::allocator_type tree< ValueType, Allocator >::get_allocator( )const
	{
		return Allocator( );
	}
	
	/// @brief f[^ðæ¾·é
	/// @return f[^
	template < class ValueType, class Allocator >
	inline size_t tree< ValueType, Allocator >::size( )const
	{
		size_t cnt = 0; //f[^
	
		for ( const_iterator iter = begin( ); iter != end( ); iter++ )
		{
			cnt++;
		}

		return cnt;
	}

	/// @brief Ååf[^ðæ¾·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @return Ååf[^
	template < class ValueType, class Allocator >
	inline size_t tree< ValueType, Allocator >::max_size( )const
	{
		return SIZE_MAX;
	}
	
	/// @brief Ø\¢ªó©»è·é
	/// @retval true Ø\¢ÍóÅ é
	/// @retval fasle Ø\¢ÍóÅÈ¢
	template < class ValueType, class Allocator >
	inline bool tree< ValueType, Allocator >::empty( )const
	{
		return !root_;
	}

	/// @brief f[^ðÏXµCª¨æÑ»ÌqÆµÄVµ­mÛµ½m[hðftHgRXgN^Åú»·é
	/// @deprecated ³ÌlâeqÖWÍÛ¶³êÈ¢½ßgpÍ§³êÈ¢
	/// @param[in] cnt ÏXãÌf[^
	template < class ValueType, class Allocator >
	inline void tree< ValueType, Allocator >::resize( size_t cnt )
	{
		clear( );
		insert( begin( ), cnt, ValueType( ) );
	}

	/// @brief f[^ðÏXµCª¨æÑ»ÌqÆµÄVµ­mÛµ½m[hðøÅú»·é
	/// @deprecated eqÖWÍÛ¶³êÈ¢½ßgpÍ§³êÈ¢
	/// @param[in] cnt ÏXãÌf[^
	/// @param[in] val ÏXãÌf[^
	template < class ValueType, class Allocator >
	inline void tree< ValueType, Allocator >::resize( size_t cnt, const ValueType &val )
	{
		clear( );
		insert( begin( ), cnt, val );
	}

	/// @brief ªðæ¾·é
	/// @attention Ø\¢ªóÅ éêC invalid_tree áOð°é
	/// @return ªÌQÆ
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::reference tree< ValueType, Allocator >::root( )
	{
		if ( root_ )
		{
			return root_->val;
		}
		else
		{
			throw invalid_tree( );
		}
	}

	/// @brief ªðæ¾·é
	/// @attention Ø\¢ªóÅ éêC invalid_tree áOð°é
	/// @return ªÌèQÆ
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_reference tree< ValueType, Allocator >::root( )const
	{
		if ( root_ )
		{
			return root_->val;
		}
		else
		{
			throw invalid_tree( );
		}
	}

	/// @brief øÌf[^ð}ü·é
	/// @param[in] parent }ü·éÊuÌeðw·Ce[^
	/// @param[in] val }ü·éf[^
	/// @return }üµ½f[^ðw·Ce[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::iterator tree< ValueType, Allocator >::insert( const_iterator parent, const ValueType &val )
	{
		if ( root_ )
		{
			Node *parent_node = parent.node( ) ? const_cast< Node * >( parent.node( ) ) : root_; // }ü·ém[hÌe
			Node *child_node = new Node( val ); // }ü·ém[h

			// m[hðA·é
			child_node->parent = parent_node;
			child_node->elder_sibling = parent_node->youngest_child;
			parent_node->youngest_child = child_node;

			if ( child_node->elder_sibling )
			{
				child_node->elder_sibling->younger_sibling = child_node;
			}

			if ( !parent_node->eldest_child )
			{
				parent_node->eldest_child = child_node;
			}
		
			// øÌÊuÉ}ü·é
			return iterator( child_node, root_, parent.incr( ) );
		}
		else
		{
			// Ø\¢ªóÌÆ«ªÆµÄ}ü·é
			return iterator( root_ = new Node( val ), root_, parent.incr( ) );
		}
	}

	/// @brief øÌf[^ð}ü·é
	/// @param[in] parent }ü·éÊuÌeðw·Ce[^
	/// @param[in] val }ü·éf[^
	/// @return }üµ½f[^ðw·Ce[^
	template < class ValueType, class Allocator >
	template < class Type >
	inline typename tree< ValueType, Allocator >::iterator tree< ValueType, Allocator >::insert( const_iterator parent, Type val )
	{
		return insert( parent, static_cast< ValueType >( val ) );
	}

	/// @brief øÌ¾¯f[^ð}ü·é
	/// @param[in] parent }ü·éÊuÌeðw·Ce[^
	/// @param[in] cnt }ü·éf[^Ì
	/// @param[in] val }ü·éf[^
	template < class ValueType, class Allocator >
	inline void tree< ValueType, Allocator >::insert( const_iterator parent, size_t cnt, const ValueType &val )
	{
		for ( size_t i = 0; i < cnt; i++ )
		{
			insert( parent, val );
		}
	}

	/// @brief øÌf[^ð}ü·é
	/// @attention øªØ\¢Å éêCeqÖWÍÛ¶³êÈ¢
	/// @param[in] parent }ü·éÊuÌeðw·Ce[^
	/// @param[in] first }ü·éf[^Ìæªðw·Ce[^
	/// @param[in] last }ü·éf[^ÌöÌðw·Ce[^
	template < class ValueType, class Allocator >
	template < class Iterator >
	inline void tree< ValueType, Allocator >::insert( const_iterator parent, Iterator first, Iterator last )
	{
		for ( ; first != last; first++ )
		{
			insert( parent, *first );
		}
	}

	/// @brief øÌØ\¢ð}ü·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @param[in] parent }ü·éÊuÌeðw·Ce[^
	/// @param[in] tree }ü·éØ\¢
	template < class ValueType, class Allocator >
	inline void tree< ValueType, Allocator >::insert( const_iterator parent, const tree &tree )
	{
	}

	/// @brief øÌ¾¯Ø\¢ð}ü·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @param[in] parent }ü·éÊuÌeðw·Ce[^
	/// @param[in] cnt }ü·éØ\¢Ì
	/// @param[in] tree }ü·éØ\¢
	template < class ValueType, class Allocator >
	inline void tree< ValueType, Allocator >::insert( const_iterator parent, size_t cnt, const tree &tree )
	{
		for ( size_t i = 0; i < cnt; i++ )
		{
			insert( parent, tree );
		}
	}
	
	/// @brief øÌf[^ð}ü·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @param[in] parent }ü·éÊuÌeðw·Ce[^
	/// @param[in] younger_sibling }ü·éÊuÌíðw·Ce[^
	/// @param[in] val }ü·éf[^
	/// @return }üµ½f[^ðw·Ce[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::iterator tree< ValueType, Allocator >::insert( const_iterator parent, const_iterator younger_sibling, const ValueType &val )
	{
	}

	/// @brief øÌf[^ð}ü·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @param[in] parent }ü·éÊuÌeðw·Ce[^
	/// @param[in] younger_sibling }ü·éÊuÌíðw·Ce[^
	/// @param[in] val }ü·éf[^
	/// @return }üµ½f[^ðw·Ce[^
	template < class ValueType, class Allocator >
	template < class Type >
	inline typename tree< ValueType, Allocator >::iterator tree< ValueType, Allocator >::insert( const_iterator parent, const_iterator younger_sibling, Type val )
	{
		return insert( parent, younger_sibling, static_cast< ValueType >( val ) );
	}

	/// @brief øÌ¾¯f[^ð}ü·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @param[in] parent }ü·éÊuÌeðw·Ce[^
	/// @param[in] younger_sibling }ü·éÊuÌíðw·Ce[^
	/// @param[in] cnt }ü·éf[^Ì
	/// @param[in] val }ü·éf[^
	template < class ValueType, class Allocator >
	inline void tree< ValueType, Allocator >::insert( const_iterator parent, const_iterator younger_sibling, size_t cnt, const ValueType &val )
	{
		for ( size_t i = 0; i < cnt; i++ )
		{
			insert( parent, younger_sibling, val );
		}
	}

	/// @brief øÌf[^ð}ü·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @param[in] parent }ü·éÊuÌeðw·Ce[^
	/// @param[in] younger_sibling }ü·éÊuÌíðw·Ce[^
	/// @param[in] first }ü·éf[^Ìæªðw·Ce[^
	/// @param[in] last }ü·éf[^ÌöÌðw·Ce[^
	template < class ValueType, class Allocator >
	template < class Iterator >
	inline void tree< ValueType, Allocator >::insert( const_iterator parent, const_iterator younger_sibling, Iterator first, Iterator last )
	{
		for ( ; first != last; first++ )
		{
			insert( parent, younger_sibling, *first );
		}
	}

	/// @brief øÌØ\¢ð}ü·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @param[in] parent }ü·éÊuÌeðw·Ce[^
	/// @param[in] younger_sibling }ü·éÊuÌíðw·Ce[^
	/// @param[in] tree }ü·éØ\¢
	template < class ValueType, class Allocator >
	inline void tree< ValueType, Allocator >::insert( const_iterator parent, const_iterator younger_sibling, const tree &tree )
	{
	}

	/// @brief øÌ¾¯Ø\¢ð}ü·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @param[in] parent }ü·éÊuÌeðw·Ce[^
	/// @param[in] younger_sibling }ü·éÊuÌíðw·Ce[^
	/// @param[in] cnt }ü·éØ\¢Ì
	/// @param[in] tree }ü·éØ\¢
	template < class ValueType, class Allocator >
	inline void tree< ValueType, Allocator >::insert( const_iterator parent, const_iterator younger_sibling, size_t cnt, const tree &tree )
	{
		for ( size_t i = 0; i < cnt; i++ )
		{
			insert( parent, younger_sibling, tree );
		}
	}

	/// @brief øÌf[^ðí·é
	/// @param[in] pos í·éÊuðw·Ce[^
	/// @return íµ½f[^Ìðw·Ce[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::iterator tree< ValueType, Allocator >::erase( const_iterator pos )
	{
		Node *current = const_cast< Node * >( pos.node( ) ); // »ÝÌm[h

		if ( current )
		{
			Node *parent = pos.node( )->parent; // í·ém[hÌe
			iterator next = static_cast< iterator & >( pos ); // Ìm[hðw·Ce[^

			// Oi·é
			next++;

			// ÄA·é
			if ( parent )
			{
				// ZÆ·qÜ½ÍíðA·é
				if ( current->elder_sibling )
				{
					current->elder_sibling->younger_sibling = current->eldest_child ? current->eldest_child : current->younger_sibling;
				}
				
				if ( current->eldest_child )
				{
					current->eldest_child->elder_sibling = current->elder_sibling;
				}
				else if ( current->younger_sibling )
				{
					current->younger_sibling->elder_sibling = current->elder_sibling;
				}
			
				// íÆqÍZðA·é
				if ( current->younger_sibling )
				{
					current->younger_sibling->elder_sibling = current->youngest_child ? current->youngest_child : current->elder_sibling;
				}
				
				if ( current->youngest_child )
				{
					current->youngest_child->younger_sibling = current->younger_sibling;
				}
				else if ( current->elder_sibling )
				{
					current->elder_sibling->younger_sibling = current->younger_sibling;
				}

				// eÆqðA·é
				for ( Node *p = current->eldest_child; p; p = p->younger_sibling )
				{
					p->parent = parent;
				}

				if ( parent->eldest_child == current )
				{
					parent->eldest_child = current->eldest_child ? current->eldest_child : current->younger_sibling;
				}

				if ( parent->youngest_child == current )
				{
					parent->youngest_child = current->youngest_child ? current->youngest_child : current->elder_sibling;
				}
			
				// Ce[^Ìªðí·éÆ«ªðXV·é
				if ( current == next.root( ) )
				{
					next = iterator( next.node( ), current->parent, next.incr( ) );
				}
			}
			else
			{
				// ªðí·éÆ«·qðªÉÏX·é
				root_ = current->eldest_child;

				if ( root_ )
				{
					// ªÌqÆíðA·é
					if ( root_->youngest_child )
					{
						root_->youngest_child->younger_sibling = root_->younger_sibling;
					}

					// ªÌíðqÉÏX·é
					for ( Node *p = root_->younger_sibling; p; p = p->younger_sibling )
					{
						p->parent = root_;
					}

					if ( !root_->eldest_child )
					{
						root_->eldest_child = root_->younger_sibling;
					}

					if ( current->youngest_child != root_ )
					{
						root_->youngest_child = current->youngest_child;
					}

					// ªÌAðØf·é
					root_->parent = root_->younger_sibling = NULL;
				}
			
				// Ce[^Ìªðí·éÆ«ªðXV·é
				if ( current == next.root( ) )
				{
					next = iterator( next.node( ), root_, next.incr( ) );
				}
			}

			// í·é
			current->eldest_child = current->younger_sibling = NULL;
			delete current;

			return next;
		}
		else
		{
			// Ce[^ªI[ðwµÄ¢éÆ«®ìµÈ¢
			return iterator( static_cast< iterator & >( pos ) );
		}
	}

	/// @brief øÌf[^ðí·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @param[in] first í·éf[^Ìæªðw·Ce[^
	/// @param[in] last í·éf[^ÌöÌðw·Ce[^
	/// @return íµ½f[^Ìðw·Ce[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::iterator tree< ValueType, Allocator >::erase( const_iterator first, const_iterator last )
	{
	}

	/// @brief SÄÌf[^ðí·é
	template < class ValueType, class Allocator >
	inline void tree< ValueType, Allocator >::clear( )
	{
		delete root_;
		root_ = NULL;
	}

	/// @brief øÌeðw·Ce[^ðæ¾·é
	/// @attention øªªÅ éêC end( ) ªÔé
	/// @param[in] child æ¾·éCe[^Ìqðw·Ce[^
	/// @return	øÌeðw·Ce[^
	///
	/// gpá
	/// @code
	/// tmatsu::tree< int > t; // Ø\¢
	/// tmatsu::tree< int >::const_iterator node = std::find( t.begin( ), t.end( ), 100 ); // lª100Ìm[hðw·Ce[^
	/// 
	/// // æcÌem[hÌlðó·é
	/// for ( tmatsu::tree< int >::const_iterator iter = t.parent( node ); iter != t.end( ); iter = t.parent( iter ) )
	/// {
	///		for ( size_t i = 0; i < t.depth( iter ); i++ )
	///		{
	///			std::cout << ' ';
	///		}
	///
	///		std::cout << *iter << std::endl;
	/// }
	/// @endcode
	template < class ValueType, class Allocator >
	template < class Iterator >
	inline Iterator tree< ValueType, Allocator >::parent( Iterator child )const
	{
		return Iterator( child.node( ) ? child.node( )->parent : NULL, child.root( ), child.incr( ) );
	}
		
	/// @brief Ce[^Ìw·m[hÌ[³ðæ¾·é
	/// @param[in] iter [³ðæ¾·ém[hðw·Ce[^
	/// @return Ce[^Ìw·m[hÌ[³
	template < class ValueType, class Allocator >
	template < class Iterator >
	inline size_t tree< ValueType, Allocator >::depth( Iterator iter )const
	{
		size_t dpt = 0; // [³

		for ( const Node *p = iter.node( ); p && p != root_; p = p->parent )
		{
			dpt++;
		}

		return dpt;
	}
	
	/// @brief Ce[^Ìw·m[hªª©»è·é
	/// @param[in] iter »è·ém[hðw·Ce[^
	/// @retval true Ce[^Ìw·m[hÍªÅ é
	/// @retval false Ce[^Ìw·m[hÍªÅÈ¢
	template < class ValueType, class Allocator >
	template < class Iterator >
	inline bool tree< ValueType, Allocator >::is_root( Iterator iter )const
	{
		return iter.node( ) == iter.root( );
	}

	/// @brief Ce[^Ìw·m[hªt©»è
	/// @param[in] iter »è·ém[hðw·Ce[^
	/// @retval true Ce[^Ìw·m[hÍtÅ é
	/// @retval false Ce[^Ìw·m[hÍtÅÈ¢
	template < class ValueType, class Allocator >
	template < class Iterator >
	inline bool tree< ValueType, Allocator >::is_leaf( Iterator iter )const
	{
		return !iter.node( )->eldest_child;
	}
	
	/// @brief Ce[^Ìw·m[hªZíðÂ©»è
	/// @param[in] iter »è·ém[hðw·Ce[^
	/// @retval true Ce[^Ìw·m[hÍZíðÂ
	/// @retval false Ce[^Ìw·m[hÍZíðÂ
	template < class ValueType, class Allocator >
	template < class Iterator >
	inline bool tree< ValueType, Allocator >::has_sibling( Iterator iter )const
	{
		return ( iter.node( )->younger_sibling || iter.node( )->elder_sibling ) && !is_root( iter );
	}
	
	/// @brief iterªref_iterÌæc©»è
	/// @param[in] iter »è·ém[hðw·Ce[^
	/// @param[in] ref_iter îÆÈém[hðw·Ce[^
	/// @retval true iterÍref_iterÌæcÅ é
	/// @retval false iterÍref_iterÌæcÅÈ¢
	template < class ValueType, class Allocator >
	template < class Iterator, class ReferenceIterator >
	inline bool tree< ValueType, Allocator >::is_ancestor( Iterator iter, ReferenceIterator ref_iter )const
	{
		while ( !is_root( ref_iter ) )
		{
			ref_iter = parent( ref_iter );

			if ( iter == ref_iter )
			{
				return true;
			}
		}

		return false;
	}
	
	/// @brief iterªref_iterÌq·©»è
	/// @param[in] iter »è·ém[hðw·Ce[^
	/// @param[in] ref_iter îÆÈém[hðw·Ce[^
	/// @retval true iterÍref_iterÌq·Å é
	/// @retval false iterÍref_iterÌq·ÅÈ¢
	template < class ValueType, class Allocator >
	template < class Iterator, class ReferenceIterator >
	inline bool tree< ValueType, Allocator >::is_descendant( Iterator iter, ReferenceIterator ref_iter )const
	{
		return is_ancestor( ref_iter, iter );
	}

	/// @brief øðªÆ·éªØðæ¾·é
	/// @attention æ¾·éªØÍó¢¡»ÈÌÅCÀÌª~µ¢êÍRs[RXgN^Ü½ÍãüZqðpµÄªØð¡»·é
	/// @param[in] root æ¾·éªØÌªðw·Ce[^
	/// @return øðªÆ·éªØ
	///
	/// gpá
	/// @code
	/// tmatsu::tree< int > t; // Ø\¢
	/// tmatsu::tree< int > &s = t.subtree( std::find( t.begin( ), t.end( ), 100 ) ); // lª100Ìm[hðªÆ·éªØ
	/// 
	/// // ªØÌem[hÌlðó·é
	/// for ( tmatsu::tree< int >::const_iterator iter = s.begin( ); iter != s.end( ); iter++ )
	/// {
	///		for ( size_t i = 0; i < s.depth( iter ); i++ )
	///		{
	///			std::cout << ' ';
	///		}
	///
	///		std::cout << *iter << std::endl;
	/// }
	/// @endcode
	template < class ValueType, class Allocator >
	template < class Iterator >
	inline typename tree< ValueType, Allocator >::Subtree tree< ValueType, Allocator >::subtree( Iterator root )const
	{
		return Subtree( root.node( ) );
	}

	/// @brief tü«ÌØ\¢ðæ¾·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @param[in] root æ¾·éØ\¢ÌªÆÈém[hðw·Ce[^
	/// @param[out] tree æ¾·éØ\¢ði[·éÌæÌQÆ
	template < class ValueType, class Allocator >
	template < class Iterator >
	inline void tree< ValueType, Allocator >::reverse( Iterator root, tree &tree )
	{
	}

	/// @brief Ø\¢ð¡»·é
	/// @param[in] tree ¡»·éØ\¢
	/// @return ©ª©gÌQÆ
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator > &tree< ValueType, Allocator >::operator=( const tree &tree )
	{
		if ( this != &tree )
		{
			clear( );

			if ( tree.root_ )
			{
				Node *temp = tree.root_->younger_sibling; // ¡»·éØ\¢ÌªÌíðÞð·é

				tree.root_->younger_sibling = NULL;
				root_ = new Node( *tree.root_ );
				tree.root_->younger_sibling = temp;
			}
		}

		return *this;
	}

	/// @brief øÆµ¢Ø\¢©»è·é
	/// @param[in] tree »è·éØ\¢
	/// @retval true SÄÌm[hªøÆµ¢
	/// @retval false øÆÙÈém[hª¶Ý·é
	template < class ValueType, class Allocator >
	inline bool tree< ValueType, Allocator >::operator==( const tree &tree )const
	{
		for ( const_iterator left = begin( ), right = tree.begin( ); left != end( ) && right != tree.end( ); left++, right++ )
		{
			size_t left_child_cnt = 0, right_child_cnt = 0; // qÌ

			// lªµ¢©²×é
			if ( *left != *right )
			{
				return false;
			}

			// qÌªµ¢©²×é
			for ( const_iterator iter = child_begin( left ); iter != child_end( left ); iter++ )
			{
				left_child_cnt++;
			}

			for ( const_iterator iter =tree.child_begin( right ); iter != tree.child_end( right ); iter++ )
			{
				right_child_cnt++;
			}

			if ( left_child_cnt != right_child_cnt )
			{
				return false;
			}
		}

		return true;
	}

	/// @brief øÆµ­È¢Ø\¢©»è·é
	/// @param[in] tree »è·éØ\¢
	/// @retval true øÆÙÈém[hª¶Ý·é
	/// @retval false SÄÌm[hªøÆµ¢
	template < class ValueType, class Allocator >
	inline bool tree< ValueType, Allocator >::operator!=( const tree &tree )const
	{
		return !operator==( tree );
	}

	/// @brief øæè«Å¬³¢Ø\¢©»è·é
	/// @param[in] tree »è·éØ\¢
	/// @retval true øæè«Å¬³¢Ø\¢Å é
	/// @retval false øæè«Åå«¢Ü½Íµ¢Ø\¢Å é
	template < class ValueType, class Allocator >
	inline bool tree< ValueType, Allocator >::operator<( const tree &tree )const
	{
		const_iterator left, right; // Ce[^

		for ( left = begin( ), right = tree.begin( ); left != end( ) && right != tree.end( ); left++, right++ )
		{
			if ( *left < *right )
			{
				return true;
			}
			else if ( *right < *left )
			{
				return false;
			}
		}

		return left == end( ) && right != tree.end( );
	}

	/// @brief øæè«Å¬³¢Ü½Íµ¢Ø\¢©»è·é
	/// @param[in] tree »è·éØ\¢
	/// @retval true øæè«Å¬³¢Ü½Íµ¢Ø\¢Å é
	/// @retval false øæè«Åå«¢Ø\¢Å é
	template < class ValueType, class Allocator >
	inline bool tree< ValueType, Allocator >::operator<=( const tree &tree )const
	{
		return !operator>( tree );
	}

	/// @brief øæè«Åå«¢Ø\¢©»è·é
	/// @param[in] tree »è·éØ\¢
	/// @retval true øæè«Åå«¢Ø\¢Å é
	/// @retval false øæè«Å¬³¢Ü½Íµ¢Ø\¢Å é
	template < class ValueType, class Allocator >
	inline bool tree< ValueType, Allocator >::operator>( const tree &tree )const
	{
		return tree.operator<( *this );
	}

	/// @brief øæè«Åå«¢Ü½Íµ¢Ø\¢©»è·é
	/// @param[in] tree »è·éØ\¢
	/// @retval true øæè«Åå«¢Ü½Íµ¢Ø\¢Å é
	/// @retval false øæè«Å¬³¢Ø\¢Å é
	template < class ValueType, class Allocator >
	inline bool tree< ValueType, Allocator >::operator>=( const tree &tree )const
	{
		return !operator<( tree );
	}

	///@brief ú»·é
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::Node::Node( ) : parent( NULL ), eldest_child( NULL ), youngest_child( NULL ), elder_sibling( NULL ), younger_sibling( NULL )
	{
	}
		
	/// @brief m[hÆ»ÌZí¨æÑq·ð¡»·é
	/// @param[in] node ¡»·ém[h
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::Node::Node( const Node &node ) : val( node.val ), parent( NULL ), eldest_child( NULL ), youngest_child( NULL ), elder_sibling( NULL ), younger_sibling( NULL )
	{
		// qð¡»·é
		if ( node.eldest_child )
		{
			eldest_child = new Node( *node.eldest_child );

			for ( youngest_child = eldest_child; youngest_child && youngest_child->younger_sibling; youngest_child = youngest_child->younger_sibling )
			{
				youngest_child->parent = this;
			}

			if ( youngest_child )
			{
				youngest_child->parent = this;
			}
		}
	
		// Zíð¡»·é
		if ( node.younger_sibling )
		{
			younger_sibling = new Node( *node.younger_sibling );
			younger_sibling->elder_sibling = this;
		}
	}

	/// @brief øÅú»·é
	/// @param[in] val f[^Ìúl
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::Node::Node( const ValueType &val ) : val( val ), parent( NULL ), eldest_child( NULL ), youngest_child( NULL ), elder_sibling( NULL ), younger_sibling( NULL )
	{
	}

	/// @brief Ìæððú·é
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::Node::~Node( )
	{
		delete eldest_child;
		delete younger_sibling;
		eldest_child = younger_sibling = NULL;
	}

	/// @brief æs([³Dæ)ÌæªÌm[hðæ¾·é
	/// @attention ¶ÝµÈ¢êCNULLªÔé
	/// @return æs([³Dæ)ÌæªÌm[hÌ|C^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::preorder_hd( )
	{
		return this;
	}

	/// @brief æs([³Dæ)ÌæªÌm[hðæ¾·é
	/// @attention ¶ÝµÈ¢êCNULLªÔé
	/// @return æs([³Dæ)ÌæªÌm[hÌè|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::preorder_hd( )const
	{
		return this;
	}

	/// @brief æs([³Dæ)ÌöÌm[hðæ¾·é
	/// @attention ¶ÝµÈ¢êCNULLªÔé
	/// @return æs([³Dæ)ÌöÌm[hÌ|C^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::preorder_tl( )
	{
		return youngest_child ? youngest_child->preorder_tl( ) : this;
	}

	/// @brief æs([³Dæ)ÌöÌm[hðæ¾·é
	/// @attention ¶ÝµÈ¢êCNULLªÔé
	/// @return æs([³Dæ)ÌöÌm[hÌè|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::preorder_tl( )const
	{
		return youngest_child ? youngest_child->preorder_tl( ) : this;
	}
		
	/// @brief æs([³Dæ)ÅOi·é
	/// @attention ¼ãÉ¸·ém[hª¶ÝµÈ¢êCNULLªÔé
	/// @param[in] root ªðw·|C^
	/// @return æs([³Dæ)Å¼ãÉ¸·ém[hÌ|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::preorder_incr( const Node *root )const
	{
		if ( eldest_child )
		{
			// qª¢éÆ«·qðÔ·
			return eldest_child;
		}
		else
		{
			for ( const Node *p = this; p != root; p = p->parent )
			{
				if ( p->younger_sibling )
				{
					// ©ª©gÜ½ÍæcÉíª¢éÆ«íðÔ·
					return p->younger_sibling;
				}
			}
		}

		// Ô·m[hª¶ÝµÈ¢Æ«k|C^ðÔ·
		return NULL;
	}	

	/// @brief æs([³Dæ)ÅãÞ·é
	/// @attention ¼OÉ¸·ém[hª¶ÝµÈ¢êCNULLªÔé
	/// @param[in] root ªðw·|C^
	/// @return æs([³Dæ)Å¼OÉ¸·ém[hÌ|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::preorder_decr( const Node *root )const
	{
		if ( this == root )
		{
			// Ô·m[hª¶ÝµÈ¢Æ«k|C^ðÔ·
			return NULL;
		}

		for ( const Node *p = elder_sibling; p; p = p->youngest_child )
		{
			if ( !p->youngest_child )
			{
				// ZÜ½Í»Ìq·ÌqðÔ·
				return p;
			}
		}
			
		// ªÅÈ¢Æ«eðÔ·
		return parent;
	}

#ifdef _INORDER_ITERATOR
	/// @brief ÔÌæªÌm[hðæ¾·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @attention Ø\¢ªñªØÅÈ¢êÌ®ìÍsè
	/// @attention ¶ÝµÈ¢êCNULLªÔé
	/// @return ÔÌæªÌm[hÌ|C^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::inorder_hd( )
	{
		return eldest_child ? eldest_child->inorder_hd( ) : this;
	}

	/// @brief ÔÌæªÌm[hðæ¾·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @attention Ø\¢ªñªØÅÈ¢êÌ®ìÍsè
	/// @attention ¶ÝµÈ¢êCNULLªÔé
	/// @return ÔÌæªÌm[hÌè|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::inorder_hd( )const
	{
		return eldest_child ? eldest_child->inorder_hd( ) : this;
	}

	/// @brief ÔÌöÌm[hðæ¾·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @attention Ø\¢ªñªØÅÈ¢êÌ®ìÍsè
	/// @attention ¶ÝµÈ¢êCNULLªÔé
	/// @return ÔÌöÌm[hÌ|C^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::inorder_tl( )
	{
		return youngest_child ? youngest_child->inorder_tl( ) : this;
	}

	/// @brief ÔÌöÌm[hðæ¾·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @attention Ø\¢ªñªØÅÈ¢êÌ®ìÍsè
	/// @attention ¶ÝµÈ¢êCNULLªÔé
	/// @return ÔÌöÌm[hÌè|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::inorder_tl( )const
	{
		return youngest_child ? youngest_child->inorder_tl( ) : this;
	}

	/// @brief ÔÅOi·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @attention Ø\¢ªñªØÅÈ¢êÌ®ìÍsè
	/// @attention ¼ãÉ¸·ém[hª¶ÝµÈ¢êCNULLªÔé
	/// @param[in] root ªðw·|C^
	/// @return ÔÅ¼ãÉ¸·ém[hÌ|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::inorder_incr( const Node *root )const
	{
	}

	/// @brief ÔÅãÞ·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @attention Ø\¢ªñªØÅÈ¢êÌ®ìÍsè
	/// @attention ¼OÉ¸·ém[hª¶ÝµÈ¢êCNULLªÔé
	/// @param[in] root ªðw·|C^
	/// @return ÔÅ¼OÉ¸·ém[hÌ|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::inorder_decr( const Node *root )const
	{
	}
#endif //_INORDER_ITERATOR

	/// @brief ãsÌæªÌm[hðæ¾·é
	/// @attention ¶ÝµÈ¢êCNULLªÔé
	/// @return ãsÌæªÌm[hÌ|C^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::postorder_hd( )
	{
		return eldest_child ? eldest_child->postorder_hd( ) : this;
	}

	/// @brief ãsÌæªÌm[hðæ¾·é
	/// @attention ¶ÝµÈ¢êCNULLªÔé
	/// @return ãsÌæªÌm[hÌè|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::postorder_hd( )const
	{
		return eldest_child ? eldest_child->postorder_hd( ) : this;
	}

	/// @brief ãsÌöÌm[hðæ¾·é
	/// @attention ¶ÝµÈ¢êCNULLªÔé
	/// @return ãsÌöÌm[hÌ|C^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::postorder_tl( )
	{
		return this;
	}

	/// @brief ãsÌöÌm[hðæ¾·é
	/// @attention ¶ÝµÈ¢êCNULLªÔé
	/// @return ãsÌöÌm[hÌè|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::postorder_tl( )const
	{
		return this;
	}

	/// @brief ãsÅOi·é
	/// @attention ¼ãÉ¸·ém[hª¶ÝµÈ¢êCNULLªÔé
	/// @param[in] root ªðw·|C^
	/// @return ãsÅ¼ãÉ¸·ém[hÌ|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::postorder_incr( const Node *root )const
	{
		if ( this == root )
		{
			// Ô·m[hª¶ÝµÈ¢Æ«k|C^ðÔ·
			return NULL;
		}

		for ( const Node *p = younger_sibling; p; p = p->eldest_child )
		{
			if ( !p->eldest_child )
			{
				// íÜ½Í»Ìq·Ì·qðÔ·
				return p;
			}
		}
			
		// ªÅÈ¢Æ«eðÔ·
		return parent;
	}

	/// @brief ãsÅãÞ·é
	/// @attention ¼OÉ¸·ém[hª¶ÝµÈ¢êCNULLªÔé
	/// @param[in] root ªðw·|C^
	/// @return ãsÅ¼OÉ¸·ém[hÌ|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::postorder_decr( const Node *root )const
	{
		if ( youngest_child )
		{
			// qª¢éÆ«qðÔ·
			return youngest_child;
		}
		else
		{
			for ( const Node *p = this; p != root; p = p->parent )
			{
				if ( p->elder_sibling )
				{
					// ©ª©gÜ½ÍæcÉZª¢éÆ«íðÔ·
					return p->elder_sibling;
				}
			}
		}

		// Ô·m[hª¶ÝµÈ¢Æ«k|C^ðÔ·
		return NULL;
	}

	/// @brief x(Dæ)ÌæªÌm[hðæ¾·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @attention ¶ÝµÈ¢êCNULLªÔé
	/// @return x(Dæ)ÌæªÌm[hÌ|C^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::levelorder_hd( )
	{
		return this;
	}

	/// @brief x(Dæ)ÌæªÌm[hðæ¾·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @attention ¶ÝµÈ¢êCNULLªÔé
	/// @return x(Dæ)ÌæªÌm[hÌè|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::levelorder_hd( )const
	{
		return this;
	}

	/// @brief x(Dæ)ÌöÌm[hðæ¾·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @attention ¶ÝµÈ¢êCNULLªÔé
	/// @return x(Dæ)ÌöÌm[hÌ|C^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::levelorder_tl( )
	{
	}

	/// @brief x(Dæ)ÌöÌm[hðæ¾·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @attention ¶ÝµÈ¢êCNULLªÔé
	/// @return x(Dæ)ÌöÌm[hÌè|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::levelorder_tl( )const
	{
	}

	/// @brief x(Dæ)ÅOi·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @attention ¼ãÉ¸·ém[hª¶ÝµÈ¢êCNULLªÔé
	/// @param[in] root ªðw·|C^
	/// @return x(Dæ)Å¼ãÉ¸·ém[hÌ|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::levelorder_incr( const Node *root )const
	{
	}

	/// @brief x(Dæ)ÅãÞ·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @attention ¼OÉ¸·ém[hª¶ÝµÈ¢êCNULLªÔé
	/// @param[in] root ªðw·|C^
	/// @return x(Dæ)Å¼OÉ¸·ém[hÌ|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::levelorder_decr( const Node *root )const
	{
	}

	/// @brief ·qÌm[hðæ¾·é
	/// @attention ¶ÝµÈ¢êCNULLªÔé
	/// @return ·qÌm[hÌ|C^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::child_hd( )
	{
		return eldest_child;
	}

	/// @brief ·qÌm[hðæ¾·é
	/// @attention ¶ÝµÈ¢êCNULLªÔé
	/// @return ·qÌm[hÌè|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::child_hd( )const
	{
		return eldest_child;
	}

	/// @brief qÌm[hðæ¾·é
	/// @attention ¶ÝµÈ¢êCNULLªÔé
	/// @return qÌm[hÌ|C^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::child_tl( )
	{
		return youngest_child;
	}

	/// @brief ·qÌm[hðæ¾·é
	/// @attention ¶ÝµÈ¢êCNULLªÔé
	/// @return ·qÌm[hÌè|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::child_tl( )const
	{
		return youngest_child;
	}

	/// @brief ZíÔÅOi·é
	/// @attention ¼ãÉ¸·ém[hª¶ÝµÈ¢êCNULLªÔé
	/// @param[in] root ªðw·|C^
	/// @return ZíÔÅ¼ãÉ¸·ém[hÌ|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::child_incr( const Node *root )const
	{
		return younger_sibling;
	}

	/// @brief ZíÔÅãÞ·é
	/// @attention ¼OÉ¸·ém[hª¶ÝµÈ¢êCNULLªÔé
	/// @param[in] root ªðw·|C^
	/// @return ZíÔÅ¼OÉ¸·ém[hÌ|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::Node::child_decr( const Node *root )const
	{
		return elder_sibling;
	}

	/// @brief ú»·é
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::const_iterator::const_iterator( ) : node_( NULL ), root_( NULL ), incr_( &Node::preorder_incr )
	{
	}

	/// @brief Ce[^ð¡»·é
	/// @param[in] iter ¡»·éCe[^
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::const_iterator::const_iterator( const const_iterator &iter ) : node_( iter.node_ ), root_( iter.root_ ), incr_( iter.incr_ )
	{
	}

	/// @brief øÅú»·é
	/// @param[in] node Ce[^Ìw·m[hÌ|C^ 
	/// @param[in] root ¸·éØ\¢ÌªÌ|C^
	/// @param[in] incr OiÖ
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::const_iterator::const_iterator( const Node *node, const Node *root, const Node *( Node::*incr )( const Node * )const ) : node_( node ), root_( root ), incr_( incr )
	{
	}

	/// @brief Ce[^ªw·m[hðæ¾·é
	/// @return Ce[^ªw·m[hÌè|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::const_iterator::node( )const
	{
		return node_;
	}

	/// @brief ¸·éØ\¢Ìªðæ¾·é
	/// @return ¸·éØ\¢ÌªÌ|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::const_iterator::root( )const
	{
		return root_;
	}
	
	/// @brief OiÖðæ¾·é
	/// @return OiÖ
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *( tree< ValueType, Allocator >::Node::*tree< ValueType, Allocator >::const_iterator::incr( ) )( const Node * )const
	{
		return incr_;
	}

	/// @brief Oi·é
	/// @return OiãÌCe[^ÌQÆ
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_iterator &tree< ValueType, Allocator >::const_iterator::operator++( )
	{
		if ( node_ )
		{
			node_ = ( node_->*incr_ )( root_ );
		}

		return *this;
	}

	/// @brief Oi·é
	/// @param _~[
	/// @return OiOÌCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_iterator tree< ValueType, Allocator >::const_iterator::operator++( int )
	{
		const_iterator temp = *this; // »ÝÌm[h

		operator++( );

		return temp;
	}

#ifdef _BIDIRECTIONAL_ITERATOR
	/// @brief ãÞ·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @return ãÞãÌCe[^ÌQÆ
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_iterator &tree< ValueType, Allocator >::const_iterator::operator--( )
	{
		if ( prev_ )
		{
			node_ = prev_;
			prev_ = ( prev_->*decr_ )( );
		}
	
		return *this;
	}

	/// @brief ãÞ·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @param _~[
	/// @return ãÞOÌCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_iterator tree< ValueType, Allocator >::const_iterator::operator--( int )
	{
		const_iterator temp = *this; // »ÝÌm[h

		operator--( );

		return temp;
	}
#endif //_BIDIRECTIONAL_ITERATOR

	/// @brief Ce[^ªøÆµ¢©»è·é
	/// @attention ¸û@ª¯êÅ é©Íl¶µÈ¢
	/// @param[in] iter »è·éCe[^
	/// @retval true øÆ¯¶m[hðwµÄ¢é
	/// @retval false øÆÙÈém[hðwµÄ¢é
	template < class ValueType, class Allocator >
	inline bool tree< ValueType, Allocator >::const_iterator::operator==( const const_iterator &iter )const
	{
		return node_ == iter.node_; // && incr_ == iter.incr_;
	}

	/// @brief Ce[^ªøÆµ­È¢©»è·é
	/// @attention ¸û@ª¯êÅ é©Íl¶µÈ¢
	/// @param[in] iter »è·éCe[^
	/// @retval true øÆÙÈém[hðwµÄ¢é
	/// @retval false øÆ¯¶m[hðwµÄ¢é
	template < class ValueType, class Allocator >
	inline bool tree< ValueType, Allocator >::const_iterator::operator!=( const const_iterator &iter )const
	{
		return !operator==( iter );
	}

	/// @brief QÆªµðs¤
	/// @attention ³øÈm[hðwµÄ¢éêC invalid_iterator áOð°é
	/// @return Ce[^Ìw·f[^ÌèQÆ
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_reference tree< ValueType, Allocator >::const_iterator::operator*( )
	{
		if ( node_ )
		{
			return node_->val;
		}
		else
		{
			throw invalid_iterator( );
		}
	}

	/// @brief ÔÚoQÆðs¤
	/// @attention ³øÈm[hðwµÄ¢éêC invalid_iterator áOð°é
	/// @return Ce[^Ìw·IuWFNgÌè|C^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_pointer tree< ValueType, Allocator >::const_iterator::operator->( )
	{
		if ( node_ )
		{
			return &node_->val;
		}
		else
		{
			throw invalid_iterator( );
		}
	}

	/// @brief ú»·é
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::iterator::iterator( )
	{
	}

	/// @brief Ce[^ð¡»·é
	/// @param[in] iter ¡»·éCe[^
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::iterator::iterator( const iterator &iter ) : const_iterator( iter )
	{
	}

	/// @brief øÅú»·é
	/// @param[in] node Ce[^Ìw·m[hÌ|C^ 
	/// @param[in] root ¸·éØ\¢ÌªÌ|C^
	/// @param[in] incr OiÖ
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::iterator::iterator( Node *node, const Node *root, const Node *( Node::*incr )( const Node * )const ) : const_iterator( node, root, incr )
	{
	}

	/// @brief Ce[^ªw·m[hðæ¾·é
	/// @return Ce[^ªw·m[hÌ|C^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::iterator::node( )const
	{
		return const_cast< Node * >( node_ );
	}

	/// @brief Oi·é
	/// @return OiãÌCe[^ÌQÆ
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::iterator &tree< ValueType, Allocator >::iterator::operator++( )
	{
		if ( node_ )
		{
			node_ = ( node_->*incr_ )( root_ );
		}
	
		return *this;
	}

	/// @brief Oi·é
	/// @param _~[
	/// @return OiOÌCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::iterator tree< ValueType, Allocator >::iterator::operator++( int )
	{
		iterator temp = *this; // »ÝÌm[h

		operator++( );

		return temp;
	}

#ifdef _BIDIRECTIONAL_ITERATOR
	/// @brief ãÞ·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @return ãÞãÌCe[^ÌQÆ
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::iterator &tree< ValueType, Allocator >::iterator::operator--( )
	{
		if ( prev_ )
		{
			node_ = prev_;
			prev_ = ( prev_->*decr_ )( );
		}

		return *this;
	}

	/// @brief ãÞ·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @param _~[
	/// @return ãÞOÌCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::iterator tree< ValueType, Allocator >::iterator::operator--( int )
	{
		iterator temp = *this; // »ÝÌm[h

		operator--( );

		return temp;
	}
#endif //_BIDIRECTIONAL_ITERATOR

	/// @brief QÆªµðs¤
	/// @attention ³øÈm[hðwµÄ¢éêC invalid_iterator áOð°é
	/// @return Ce[^Ìw·f[^ÌQÆ
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::reference tree< ValueType, Allocator >::iterator::operator*( )
	{
		if ( node_ )
		{
			return const_cast< ValueType & >( node_->val );
		}
		else
		{
			throw invalid_iterator( );
		}
	}

	/// @brief ÔÚoQÆðs¤
	/// @attention ³øÈm[hðwµÄ¢éêC invalid_iterator áOð°é
	/// @return Ce[^Ìw·IuWFNgÌ|C^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::pointer tree< ValueType, Allocator >::iterator::operator->( )
	{
		if ( node_ )
		{
			return const_cast< ValueType * >( &node_->val );
		}
		else
		{
			throw invalid_iterator( );
		}
	}

	/// @brief ú»·é
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::const_reverse_iterator::const_reverse_iterator( ) : node_( NULL ), root_( NULL ), incr_( &Node::*preorder_incr )
	{
	}

	/// @brief Ce[^ð¡»·é
	/// @param[in] iter ¡»·éCe[^
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::const_reverse_iterator::const_reverse_iterator( const const_reverse_iterator &iter ) : node_( iter.node_ ), root_( iter.root_ ), incr_( iter.incr_ )
	{
	}

	/// @brief øÅú»·é
	/// @param[in] node Ce[^Ìw·m[hÌ|C^ 
	/// @param[in] root ¸·éØ\¢ÌªÌ|C^
	/// @param[in] incr OiÖ
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::const_reverse_iterator::const_reverse_iterator( const Node *node, const Node *root, const Node *( Node::*incr )( const Node * )const ) : node_( node ), root_( root ), incr_( incr )
	{
	}

	/// @brief Ce[^ªw·m[hðæ¾·é
	/// @return Ce[^ªw·m[hÌè|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::const_reverse_iterator::node( )const
	{
		return node_;
	}

	/// @brief ¸·éØ\¢Ìªðæ¾·é
	/// @return ¸·éØ\¢ÌªÌ|C^
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::const_reverse_iterator::root( )const
	{
		return root_;
	}
	
	/// @brief OiÖðæ¾·é
	/// @return OiÖ
	template < class ValueType, class Allocator >
	inline const typename tree< ValueType, Allocator >::Node *( tree< ValueType, Allocator >::Node::*tree< ValueType, Allocator >::const_reverse_iterator::incr( ) )( const Node * )const
	{
		return incr_;
	}

	/// @brief Oi·é
	/// @return OiãÌCe[^ÌQÆ
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_reverse_iterator &tree< ValueType, Allocator >::const_reverse_iterator::operator++( )
	{
		if ( node_ )
		{
			node_ = ( node_->*incr_ )( root_ );
		}

		return *this;
	}

	/// @brief Oi·é
	/// @param _~[
	/// @return OiOÌCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_reverse_iterator tree< ValueType, Allocator >::const_reverse_iterator::operator++( int )
	{
		const_reverse_iterator temp = *this; // »ÝÌm[h

		operator++( );

		return temp;
	}

#ifdef _BIDIRECTIONAL_ITERATOR
	/// @brief ãÞ·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @return ãÞãÌCe[^ÌQÆ
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_reverse_iterator &tree< ValueType, Allocator >::const_reverse_iterator::operator--( )
	{
		if ( prev_ )
		{
			node_ = prev_;
			prev_ = ( prev_->*decr_ )( );
		}

		return *this;
	}

	/// @brief ãÞ·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @param _~[
	/// @return ãÞOÌCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_reverse_iterator tree< ValueType, Allocator >::const_reverse_iterator::operator--( int )
	{
		const_reverse_iterator temp = *this; // »ÝÌm[h

		operator--( );

		return temp;
	}
#endif //_BIDIRECTIONAL_ITERATOR

	/// @brief Ce[^ªøÆµ¢©»è·é
	/// @attention ¸û@ª¯êÅ é©Íl¶µÈ¢
	/// @param[in] iter »è·éCe[^
	/// @retval true øÆ¯¶m[hðwµÄ¢é
	/// @retval false øÆÙÈém[hðwµÄ¢é
	template < class ValueType, class Allocator >
	inline bool tree< ValueType, Allocator >::const_reverse_iterator::operator==( const const_reverse_iterator &iter )const
	{
		return node_ == iter.node_; // && incr_ == iter.incr_;
	}

	/// @brief Ce[^ªøÆµ­È¢©»è·é
	/// @attention ¸û@ª¯êÅ é©Íl¶µÈ¢
	/// @param[in] iter »è·éCe[^
	/// @retval true øÆÙÈém[hðwµÄ¢é
	/// @retval false øÆ¯¶m[hðwµÄ¢é
	template < class ValueType, class Allocator >
	inline bool tree< ValueType, Allocator >::const_reverse_iterator::operator!=( const const_reverse_iterator &iter )const
	{
		return !operator==( iter );
	}

	/// @brief QÆªµðs¤
	/// @attention ³øÈm[hðwµÄ¢éêC invalid_iterator áOð°é
	/// @return Ce[^Ìw·f[^ÌèQÆ
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_reference tree< ValueType, Allocator >::const_reverse_iterator::operator*( )
	{
		if ( node_ )
		{
			return node_->val;
		}
		else
		{
			throw invalid_iterator( );
		}
	}

	/// @brief ÔÚoQÆðs¤
	/// @attention ³øÈm[hðwµÄ¢éêC invalid_iterator áOð°é
	/// @return Ce[^Ìw·IuWFNgÌè|C^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::const_pointer tree< ValueType, Allocator >::const_reverse_iterator::operator->( )
	{
		if ( node_ )
		{
			return &node_->val;
		}
		else
		{
			throw invalid_iterator( );
		}
	}

	/// @brief ú»·é
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::reverse_iterator::reverse_iterator( )
	{
	}

	/// @brief Ce[^ð¡»·é
	/// @param[in] iter ¡»·éCe[^
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::reverse_iterator::reverse_iterator( const reverse_iterator &iter ) : const_reverse_iterator( iter )
	{
	}

	/// @brief øÅú»·é
	/// @param[in] node Ce[^Ìw·m[hÌ|C^ 
	/// @param[in] root ¸·éØ\¢ÌªÌ|C^
	/// @param[in] incr OiÖ
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::reverse_iterator::reverse_iterator( Node *node, const Node *root, const Node *( Node::*incr )( const Node * )const ) : const_reverse_iterator( node, root, incr )
	{
	}

	/// @brief Ce[^ªw·m[hðæ¾·é
	/// @return Ce[^ªw·m[hÌ|C^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::Node *tree< ValueType, Allocator >::reverse_iterator::node( )const
	{
		return const_cast< Node * >( node_ );
	}

	/// @brief Oi·é
	/// @return OiãÌCe[^ÌQÆ
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::reverse_iterator &tree< ValueType, Allocator >::reverse_iterator::operator++( )
	{
		if ( node_ )
		{
			node_ = ( node_->*incr_ )( root_ );
		}

		return *this;
	}

	/// @brief Oi·é
	/// @param _~[
	/// @return OiOÌCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::reverse_iterator tree< ValueType, Allocator >::reverse_iterator::operator++( int )
	{
		reverse_iterator temp = *this; // »ÝÌm[h

		operator++( );

		return temp;
	}

#ifdef _BIDIRECTIONAL_ITERATOR
	/// @brief ãÞ·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @return ãÞãÌCe[^ÌQÆ
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::reverse_iterator &tree< ValueType, Allocator >::reverse_iterator::operator--( )
	{
		if ( prev_ )
		{
			node_ = prev_;
			prev_ = ( prev_->*decr_ )( );
		}

		return *this;
	}

	/// @brief ãÞ·é
	/// @attention ¢ÀÌ½ßgpµÄÍÈçÈ¢
	/// @param _~[
	/// @return ãÞOÌCe[^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::reverse_iterator tree< ValueType, Allocator >::reverse_iterator::operator--( int )
	{
		reverse_iterator temp = *this; // »ÝÌm[h

		operator--( );

		return temp;
	}
#endif //_BIDIRECTIONAL_ITERATOR

	/// @brief QÆªµðs¤
	/// @attention ³øÈm[hðwµÄ¢éêC invalid_iterator áOð°é
	/// @return Ce[^Ìw·f[^ÌQÆ
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::reference tree< ValueType, Allocator >::reverse_iterator::operator*( )
	{
		if ( node_ )
		{
			return const_cast< ValueType & >( node_->val );
		}
		else
		{
			throw invalid_iterator( );
		}
	}

	/// @brief ÔÚoQÆðs¤
	/// @attention ³øÈm[hðwµÄ¢éêC invalid_iterator áOð°é
	/// @return Ce[^Ìw·IuWFNgÌ|C^
	template < class ValueType, class Allocator >
	inline typename tree< ValueType, Allocator >::pointer tree< ValueType, Allocator >::reverse_iterator::operator->( )
	{
		if ( node_ )
		{
			return const_cast< ValueType * >( &node_->val );
		}
		else
		{
			throw invalid_iterator( );
		}
	}

	/// @brief øÌm[hðªÆ·éØ\¢Ìó¢¡»ðì¬·é
	/// @param[in] root ¡»·éØ\¢Ìª
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::Subtree::Subtree( const Node *root ) : tree( root )
	{
	}

	/// @brief QÆðjü·é
	template < class ValueType, class Allocator >
	inline tree< ValueType, Allocator >::Subtree::~Subtree( )
	{
		root_ = NULL;
	}
}

#endif //_TMATSU_TREE_H_