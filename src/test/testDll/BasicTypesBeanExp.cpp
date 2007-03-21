
#include "BeanWrapperMacro.h"
#include "BasicTypesBean.h"

AUTUMNBEAN(BasicTypesBean)

AUTUMNBEAN_CREATOR()
AUTUMNBEAN_CONSTRUCTOR(BasicTypesBean)
AUTUMNBEAN_CONSTRUCTOR_13P(BasicTypesBean, char,unsigned char,short,
						   unsigned short,int,unsigned int,long,
						   unsigned long,float,double,string,char*,
						   unsigned char*)
AUTUMNBEAN_CREATOR_END()

AUTUMNBEAN_SETTER()
AUTUMNBEAN_PROPERTY(Char,char)	
AUTUMNBEAN_PROPERTY(UChar,unsigned char)
AUTUMNBEAN_PROPERTY(Short,short	)	
AUTUMNBEAN_PROPERTY(UShort,unsigned short)
AUTUMNBEAN_PROPERTY(Int,int		)	
AUTUMNBEAN_PROPERTY(UInt,unsigned int)
AUTUMNBEAN_PROPERTY(Long,long	)	
AUTUMNBEAN_PROPERTY(ULong,unsigned long)
AUTUMNBEAN_PROPERTY(Float,float	)	
AUTUMNBEAN_PROPERTY(Double,double	)	
AUTUMNBEAN_PROPERTY(String,string)		
AUTUMNBEAN_PROPERTY(CStr,char*	)	
AUTUMNBEAN_PROPERTY(UCStr,unsigned char*)

AUTUMNBEAN_PROPERTY(IntP,int*		)	
AUTUMNBEAN_PROPERTY(CStrP,char**	)	
AUTUMNBEAN_SETTER_END()

AUTUMNBEAN_END(BasicTypesBean)
