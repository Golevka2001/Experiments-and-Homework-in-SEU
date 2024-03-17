// Don't modify this file as it will be overwritten.
//
#include "CDR/CDR.h"
#include "ReturnCode.h"
#include "BasicTypes.h"

#ifndef IDL_UserDataType_hh
#define IDL_UserDataType_hh

#ifndef Grade_defined
#define Grade_defined

struct Grade {
  Grade()
	{
		name = NULL;
		id = NULL;
	}

  Grade(const Grade  &IDL_s);

  ~Grade(){}

  Grade& operator= (const Grade &IDL_s);

  void Marshal(CDR *cdr) const;
  void UnMarshal(CDR *cdr);

  char* name;
char* id;
float score;
  
};

typedef sequence<Grade> GradeSeq;

#endif

#ifndef AverageGrade_defined
#define AverageGrade_defined

struct AverageGrade {
  AverageGrade()
	{
		id1 = NULL;
		id2 = NULL;
		id3 = NULL;
	}

  AverageGrade(const AverageGrade  &IDL_s);

  ~AverageGrade(){}

  AverageGrade& operator= (const AverageGrade &IDL_s);

  void Marshal(CDR *cdr) const;
  void UnMarshal(CDR *cdr);

  float avg_score;
char* id1;
char* id2;
char* id3;
  
};

typedef sequence<AverageGrade> AverageGradeSeq;

#endif




#endif /*IDL_UserDataType_hh */
