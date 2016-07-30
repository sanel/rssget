#ifndef __RD_UTILS_H__
#define __RD_UTILS_H__

#define RD_DEBUG   printf
#define RD_WARNING printf
#define RD_ASSERT  assert

#define _RD_STRLOC_STRINGIFY(arg)          _RD_STRLOC_STRINGIFY_ARG(arg)
#define _RD_STRLOC_STRINGIFY_ARG(content)  #content
#define RD_STRLOC                          __FILE__ ":" _RD_STRLOC_STRINGIFY(__LINE__)

#if defined(__GNUC__) && (__GNUC__ > 2) && defined(__OPTIMIZE__)
	#define _RD_BOOLEAN_EXPR(expr)				\
	__extension__ ({							\
			int _rd_boolean_var_;				\
			if(expr)							\
				_rd_boolean_var_ = 1;			\
			else								\
				_rd_boolean_var_ = 0;			\
			_rd_boolean_var_;                   \
	})

	#define RD_LIKELY(expr)   (__builtin_expect(_RD_BOOLEAN_EXPR(expr), 1))
	#define RD_UNLIKELY(expr) (__builtin_expect(_RD_BOOLEAN_EXPR(expr), 0))
#else
	#define RD_LIKELY(expr)   (expr)
	#define RD_UNLIKELY(expr) (expr)
#endif

#define RD_RETURN_IF_FAIL(expr)											\
	do {																\
		if RD_LIKELY(expr) { }											\
		else {															\
			RD_WARNING(RD_STRLOC ": Condition '%s' failed\n", #expr);	\
			return;														\
		}                                                               \
	} while(0)

#define RD_RETURN_VAL_IF_FAIL(expr, val)								\
	do {																\
		if RD_LIKELY(expr) { }											\
		else {															\
			RD_WARNING(RD_STRLOC ": Condition '%s' failed\n", #expr);	\
			return (val);												\
		}																\
	} while(0)

#endif
