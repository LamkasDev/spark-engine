#ifndef MACROS_LANGUAGE_H_INCLUDED
#define MACROS_LANGUAGE_H_INCLUDED

#define foreach(item, array) \
  for(int keep = 1, \
          count = 0,\
          size = sizeof (array) / sizeof *(array); \
      keep && count != size; \
      keep = !keep, count++) \
    for(item = (array) + count; keep; keep = !keep)

#endif