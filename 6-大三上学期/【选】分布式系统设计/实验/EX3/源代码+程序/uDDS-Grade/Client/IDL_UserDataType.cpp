// Don't modify this file as it will be overwritten.
//
#include "IDL_UserDataType.h"

Grade::Grade(const Grade &IDL_s){
  name = IDL_s.name;
  id = IDL_s.id;
  score = IDL_s.score;
}

Grade& Grade::operator= (const Grade &IDL_s){
  if (this == &IDL_s) return *this;
  name = IDL_s.name;
  id = IDL_s.id;
  score = IDL_s.score;
  return *this;
}

void Grade::Marshal(CDR *cdr) const {
  cdr->PutString(name);
  cdr->PutString(id);
  cdr->PutFloat(score);
}

void Grade::UnMarshal(CDR *cdr){
  {
    char *IDL_str;
    cdr->GetString(IDL_str);
    if(name != NULL )
    {
        delete name;
        name = NULL;
    }
    name = IDL_str;
  }
  {
    char *IDL_str;
    cdr->GetString(IDL_str);
    if(id != NULL )
    {
        delete id;
        id = NULL;
    }
    id = IDL_str;
  }
  cdr->GetFloat(score);
}

AverageGrade::AverageGrade(const AverageGrade &IDL_s){
  avg_score = IDL_s.avg_score;
  id1 = IDL_s.id1;
  id2 = IDL_s.id2;
  id3 = IDL_s.id3;
}

AverageGrade& AverageGrade::operator= (const AverageGrade &IDL_s){
  if (this == &IDL_s) return *this;
  avg_score = IDL_s.avg_score;
  id1 = IDL_s.id1;
  id2 = IDL_s.id2;
  id3 = IDL_s.id3;
  return *this;
}

void AverageGrade::Marshal(CDR *cdr) const {
  cdr->PutFloat(avg_score);
  cdr->PutString(id1);
  cdr->PutString(id2);
  cdr->PutString(id3);
}

void AverageGrade::UnMarshal(CDR *cdr){
  cdr->GetFloat(avg_score);
  {
    char *IDL_str;
    cdr->GetString(IDL_str);
    if(id1 != NULL )
    {
        delete id1;
        id1 = NULL;
    }
    id1 = IDL_str;
  }
  {
    char *IDL_str;
    cdr->GetString(IDL_str);
    if(id2 != NULL )
    {
        delete id2;
        id2 = NULL;
    }
    id2 = IDL_str;
  }
  {
    char *IDL_str;
    cdr->GetString(IDL_str);
    if(id3 != NULL )
    {
        delete id3;
        id3 = NULL;
    }
    id3 = IDL_str;
  }
}

