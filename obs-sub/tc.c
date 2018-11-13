#include "observer.h"
#include "subject.h"

int main()
{
    Subobject_S             *pstSub = NULL;
    Observer_S              *pstObs  = NULL;

    pstSub  = SubCons();
    RETURN_IF_NULL(pstSub, ERR_MALLOC_FAILED);

    pstObs  = ObsConstruct(); 
    RETURN_IF_NULL(pstObs, ERR_MALLOC_FAILED);
    
    pstSub->_RegisterObserver(pstObs, pstSub);
    pstSub->_NotifyObserver(pstSub);
    
    SubDestruct(pstSub);
    ObsDestruct(pstObs);
    return 0;
}
