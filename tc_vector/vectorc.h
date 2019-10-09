#ifndef VECTORC_H
#define VECTORC_H

#include <string.h>
#include "alias.h"

#define         VECTOR_CAPACITY_DEFAULT             (64)
#define         VECTOR_CAPACITY_MAX                 (128<<8)
#define         VECTOR_CAPACITY_RESIZE_MIN          (128)

#define         ERR_CODE_INVALIDPARA                            (-1)
#define         ERR_CODE_INVALID_VECTOR_POSITION                (-2)
typedef void (*PFUNC_OBJ_DESTRUCT)(void* ptr);




typedef struct tagVector_S
{
    void**                    ppData;         /* vector�д�ŵĶ���ָ�� */                
    unsigned int              uiCount;        /* ��ǰvector���Ѿ���ŵĶ������ */
    unsigned int              uiCapacity;     /* vector������ */
    PFUNC_OBJ_DESTRUCT        pfnDestruct;    /* vector�ж������������ */

}Vector_S;


/*
 * vector�Ĺ��췽��
 */
UINT32    Vct_Construct(Vector_S** ppstVector, PFUNC_OBJ_DESTRUCT pfnElementDestruct);

/*
 * vector������
 */
void Vct_Destruct(Vector_S** ppstVector);

/*
 * vector���
 */
void Vct_Clear(Vector_S** ppstVector);

/*
 * vector��������
 */
UINT32 Vct_SetCapacity(Vector_S* pstVector, unsigned int uiCapacity);

/*
 * vector ���Ԫ��
 */
UINT32 Vct_Pushback(Vector_S* pstVector,  void* pObj);

/*
 * vector ���Ԫ�ص�vector ���׸���λ��
 */
UINT32 Vct_Push(Vector_S* pstVector,  void* pObj);

/*
 * vector ��������
 */
void* Vct_Popback(Vector_S* pstVector);

/*
 * ��vector��indexλ���滻���µĶ���ֵ
 */
UINT32 Vct_SetIndex(Vector_S* pstVector, unsigned int uiIndex, void* pObj);

#endif
