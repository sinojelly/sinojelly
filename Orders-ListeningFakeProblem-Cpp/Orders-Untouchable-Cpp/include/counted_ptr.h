/// ***************************************************************************
/// Copyright (c) 2009, Industrial Logic, Inc., All Rights Reserved.
///
/// This code is the exclusive property of Industrial Logic, Inc. It may ONLY be
/// used by students during Industrial Logic's workshops or by individuals
/// who are being coached by Industrial Logic on a project.
///
/// This code may NOT be copied or used for any other purpose without the prior
/// written consent of Industrial Logic, Inc.
/// ****************************************************************************

#ifndef COUNTED_PTR_H_
#define COUNTED_PTR_H_
/*
 * counted_ptr - simple reference counted pointer.
 *
 * The is a non-intrusive implementation that allocates an additional
 * int and pointer for every counted object.
 */

/* For ANSI-challenged compilers, you may want to #define
 * NO_MEMBER_TEMPLATES or explicit */

//#define NO_MEMBER_TEMPLATES
#include <assert.h>

template <class X> class counted_ptr
{
public:
    typedef X element_type;

    explicit counted_ptr(X* p = 0) // Allocate a new counter
        : itsCounter(0) {if (p) itsCounter = new counter(p);}
    ~counted_ptr()
        {release();}
    counted_ptr(const counted_ptr& r) throw()
        {acquire(r.itsCounter);}
    counted_ptr& operator=(const counted_ptr& r)
    {
        if (this != &r) {
            release();
            acquire(r.itsCounter);
        }
        return *this;
    }
    bool operator!() const {
    	return get()==0;
    }
    
    
    void* getCounter() const {
    	return itsCounter;
    }

#ifndef NO_MEMBER_TEMPLATES
    template <class Y>bool operator==(const counted_ptr<Y>& r) const {
    	return r.get()==get();
    }
    template <class Y> counted_ptr(const counted_ptr<Y>& r) throw()
        {acquire(reinterpret_cast<counter*>(r.getCounter()));}
    template <class Y> counted_ptr& operator=(const counted_ptr<Y>& r) {
        if (this != &r) {
            release();
            acquire(r.itsCounter);
        }
        return *this;
    }
#endif // NO_MEMBER_TEMPLATES

    X& operator*()  const throw() {
    	// Crash determinstically on NULL ptr...        
    	assert(itsCounter != 0 && itsCounter->ptr != 0);  
        return *itsCounter->ptr;
    }    
    X* operator->() const throw() {
    	// Crash determinstically on NULL ptr...        
    	assert(itsCounter != 0 && itsCounter->ptr != 0);
        return itsCounter->ptr;
    }    
    X* get()        const throw()   {return itsCounter ? itsCounter->ptr : 0;}
    bool unique()   const throw()
        {return (itsCounter ? itsCounter->count == 1 : true);}

private:

    struct counter {
        counter(X* p = 0, unsigned c = 1) : ptr(p), count(c) {}
        X*          ptr;
        unsigned    count;
    }* itsCounter;
    

    void acquire(counter* c) throw() { 
    	// Increment the count
        itsCounter = c;
        if (c) ++c->count;
    }

    void release() { 
    	// Decrement the count, delete if it is 0
        if (itsCounter) {
            if (--itsCounter->count == 0) {
                delete itsCounter->ptr;
                delete itsCounter;
            }
            itsCounter = 0;
        }
    }
};

#endif // COUNTED_PTR_H
