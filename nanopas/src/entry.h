#ifndef         MAX_NAME
#define         MAX_NAME            128
#endif

/*****   Entry data structure   *****/
struct _entry {
    unsigned char   name[MAX_NAME];     /* name */
    unsigned int    type;               /* data type */
    unsigned int    class;              /* class ID */
    unsigned int    asize;              /* size for ARRAY classID */
    unsigned int    quad;               /* temp. variable for backpatching */
              };
typedef     struct _entry        ENTRY;
