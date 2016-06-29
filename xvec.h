
#ifndef XVEC_H
#define XVEC_H

#include "purity.h"

enum {
  XVEC_DEF_CAP = 16 // Default capacity
};

typedef struct _xvec{
  uint c_ref;
  uint count;
  uint capacity;
  uint data_size;
  void *data;
} xvec;

p_error _impl_xvec_init(xvec *vec,
                        void *data,
                        uint data_count);

p_error _impl_xvec_wedge(xvec *vec,
                         uint idx,
                         void *data);

xvec _impl_xvec_new(void *data,
                    uint data_count,
                    uint data_size);

#define xvec_of(t) \
  { .count=0, \
      .capacity = XVEC_DEF_CAP,       \
      .data_size = sizeof(t),         \
      .data = NULL}

#define xvec_new(t, inits) \
  _impl_xvec_new( (((t)[])inits), array_count(((t)[])inits), sizeof((t)))
  
#define xvec_push(t, vec, val)                                          \
  _impl_xvec_wedge( _Generic( (vec), xvec *: (vec), xvec: &(vec) ),     \
                    _Generic( (vec), xvec *: (vec)->count, xvec: (vec).count), \
                    sizeof( (t) ) )

#define xvec_wedge(t, vec, idx, val)                                    \
  _impl_xvec_wedge( _Generic( (vec), xvec *: (vec), xvec: &(vec) ),     \
                    (idx),                                              \
                    sizeof( (t) ) )
    

#endif
