#define			OK		(0)
#define			ERR		(-1)


#define 		BIE(r) \
    do \
    { \
        if (OK != r) break; \
    } while (0);

#define 		BIN(r) \
    do \
    { \
        if (NULL == r) {\
		Tc_Dummy();\
		break; \
	} \
    } while (0);

void Tc_Dummy(){ return;}
