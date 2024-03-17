#pragma once
#ifndef SEQUENCE_hh
#define SEQUENCE_hh
#include "uLinxDataType.h"
#include "CDR/CDR.h"
#include <string>
using std::string;
#define  NULL 0

#define DDS_FALSE (0)
#define DDS_TRUE  (1)

template <typename T>
class sequence
{
public:
	sequence();
	sequence(const sequence &IDL_s);
	sequence(unsigned long IDL_max);

	~sequence();
	
	sequence& operator= (const sequence &IDL_s);

	T& operator [](unsigned long IDL_i){
		if(IDL_i >= _length) throw 0;
		return _buffer[IDL_i];
	}

	T& operator [](unsigned long IDL_i) const{
		if(IDL_i >= _length) throw 0;
		return _buffer[IDL_i];
	}
    
    //申请缓冲区
	static T* allocbuf(unsigned long nelems){
		return (new T[nelems]);
	}

    //释放缓冲区，不可释放借用的缓冲区
	static void freebuf(T* data){
		if (data)
		{
			delete [] data;
		}
	}
	
	unsigned long get_maximum() const {return _maximum; }
    bool set_maximum(unsigned long new_max);

    unsigned long length() const;
	bool length(unsigned long len);
	bool ensure_length(unsigned long length,unsigned long max);

    bool copy(const sequence &src_seq);

    const T get_at(unsigned long i);
    T& set_at(unsigned long i, const  T& val);

    T* get_buffer();

    bool from_array(const T array[], unsigned long copy_length);
    bool to_array(T array[], unsigned long copy_length);

	bool unloan();

	void Marshal(CDR *cdr) const;
	void UnMarshal(CDR *cdr);

private:
    T* get_reference(unsigned long i);
    int check_invariantsI();
    bool copy_no_allocI(const sequence  &src);
    bool loan_buffer(T* buffer, unsigned long new_length, unsigned long new_max);

private:
	unsigned long _maximum;
	unsigned long _length;
	unsigned long _release;
	T* _buffer;
};

#include "SEQ/Sequence.template"
#endif