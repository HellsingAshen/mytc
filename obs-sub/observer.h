#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "public.h"

typedef struct tagObserver_S {
    void (*_Notify) ();    /** callback func **/
    void (*_NotifyImp) ();                 /** callback func **/

} Observer_S;

Observer_S* ObsConstruct();
void        ObsDestruct(Observer_S*);





#endif
