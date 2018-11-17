#ifndef _SUBOBJECT_H
#define _SUBOBJECT_H

#include "observer.h"
#include "public.h"

typedef struct tagSubobject_S {
    Observer_S* astObserver[OBS_MAX_SIZE];
    int         (*_RegisterObserver)(Observer_S*, struct tagSubject_S*);       /** register **/
    int         (*_UnRegisterObserver)(Observer_S*, struct tagSubobject_S*);     /** unregister **/
    int         (*_NotifyObserver)(struct tagSubject_S*);                      /** notify observer **/
    
} Subobject_S;

Subobject_S*     SubCons();
void            SubDestruct(struct tagSubobject_S*);




#endif
