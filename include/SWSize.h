#pragma once 

namespace Util { 
	template <class type> struct _SWSize { 
		type height;
		type width;
	};

	typedef _SWSize<int> SWSizeI;
	typedef _SWSize<float> SWSizeF;
}